/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueryMapper.cpp
 * Author: papric
 * 
 * Created on December 17, 2017, 11:46 AM
 */

#include "QueryMapper.h"
#include <iostream>

using namespace bioinformatics;

QueryMapper::QueryMapper() {
}

QueryMapper::~QueryMapper() {
}

void QueryMapper::mapQuerySequence(HashTable *H, BioSequence *q, int w, int k, int epsilon){
    
    std::vector<ATuple> A;
    
    HashTableCalculationMethod method;
    std::vector<Minimizer>* queryMinimizerSet = method.minimizerSketch(q, w, k);
    
    auto hashTable = H->getHashTableRaw();

    for(auto qMsIt=queryMinimizerSet->begin(); qMsIt!=queryMinimizerSet->end(); qMsIt++){
        std::cout << "Iteration finished" << std::endl;
        auto hashEntry = hashTable->find(qMsIt->m);
        if(hashEntry==hashTable->end())
            continue;
        
        auto entrySet = hashEntry->second;
        
        
        for(auto entryIt=entrySet->begin(); entryIt!=entrySet->end(); entryIt++){
            if(qMsIt->r==entryIt->r){
                ATuple tuple;
                tuple.t = entryIt->sequencePosition;
                tuple.r = 0;
                tuple.c = qMsIt->i-entryIt->i;
                tuple.i = entryIt->i;
                A.push_back(tuple);
            }
            else{
                ATuple tuple;
                tuple.t = entryIt->sequencePosition;
                tuple.r = 1;
                tuple.c = qMsIt->i+entryIt->i;
                tuple.i = entryIt->i;
                A.push_back(tuple);
            }
        }
    }
    
    delete queryMinimizerSet;
    
    std::cout << "Finished building A" << std::endl;
    
    std::sort(A.begin(), A.end()); 

    int b = 1;
    for(int e=0, size=A.size(); e<size;e++){
        if(e==size-1 || A[e+1].t!=A[e].t ||  
           A[e+1].r!=A[e].r || A[e+1].c-A[e].c>=epsilon){
        
            auto lisC = LongestIncreasingSubsequence(A, b, e);
            
            std::cout << "Left: " << lisC[0].t << "Right: " << lisC[lisC.size()-1].t << std::endl;
            
            b = e+1;
        }
    }
    
}


void QueryMapper::mapQuerySequence(BioSequence *q, int w, int k, int epsilon) {
    std::vector<ATuple> A;
    
    HashTableCalculationMethod method;
    std::vector<Minimizer>* queryMinimizerSet = method.minimizerSketch(q, w, k);
    
    HashTable* hashTableLoaded = NULL;
    std::vector<bioinformatics::Entry> *hashMinimizerSet;
    int m = -1;
    
    for (auto queryMinIt = queryMinimizerSet->begin(); queryMinIt != queryMinimizerSet->end(); queryMinIt++) {
        if (m >= 0 and queryMinIt->m != m) {
            hashTableLoaded->empty();
            delete hashMinimizerSet;
        }
        
        // Just for testing (until the performance problem is solved)
      if (queryMinIt->i >= 25) {
            std::printf("Breaking...\n");
            break;
        }
        
        if (queryMinIt->m != m) {
            
            if(hashTableLoaded!=NULL){
                delete hashTableLoaded;
            }
            
            hashTableLoaded = HashTable::loadWithM("hash_example", queryMinIt->m);
            std::unordered_map<int, std::vector<bioinformatics::Entry>*> *H = hashTableLoaded->getHashTableRaw();
            
            std::unordered_map<int,std::vector<bioinformatics::Entry>*>::iterator found = H->find(queryMinIt->m);
            
            //TODO: is the old value deleted
            if (found != H->end()) {
                hashMinimizerSet = found->second;
            } else {
                hashMinimizerSet = NULL;
            }
                        
            m = queryMinIt->m;
        }
        
        
        if (hashMinimizerSet != NULL) { // TODO: think what should be done here
            for (auto hashMinIt = hashMinimizerSet->begin(); hashMinIt != hashMinimizerSet->end(); hashMinIt++) {
                ATuple tuple;
                tuple.t = hashMinIt->sequencePosition;
                tuple.i = hashMinIt->i;

                if (queryMinIt->r == hashMinIt->r) {
                    tuple.r = 0;
                    tuple.c = queryMinIt->i - hashMinIt->i;
                } else {
                    tuple.r = 1;
                    tuple.c = queryMinIt->i + hashMinIt->i;
                }

                
                std::printf("Query h, i, r: %d, %d, %d\tt, r, c, i': %d, %d, %d, %d\n",
                       queryMinIt->m, queryMinIt->i, unsigned(queryMinIt->r),
                        tuple.t, tuple.r, tuple.c, tuple.i
                );

                A.push_back(tuple);
            }
        }
    }   
    
    if (hashTableLoaded != NULL) {
        delete hashTableLoaded;
    }
    delete queryMinimizerSet;
    
    std::sort(A.begin(), A.end()); 

    int b = 0;
    int ALength = A.size();

    for (int e = 0; e < ALength; e++) {
       if (e == ALength - 1 or
           A.at(e + 1).t != A.at(e).t or
           A.at(e + 1).r != A.at(e).r or
           A.at(e + 1).c - A.at(e).c >= epsilon) {

           //std::vector<ATuple> sub(A.begin()+b, A.begin()+e);
           std::vector<ATuple> C = QueryMapper::LongestIncreasingSubsequence(A, b, e);
           
           // TODO: print the left-most and right-most query/target positions in C
           /*
           int last = C.size()-1;
           std::printf("t: %d, r: %d, c: %d, i\': %d | ", C[0].t, C[0].r, C[0].c, C[0].i);
           std::printf("t: %d, r: %d, c: %d, i\': %d\n", C[last].t, C[last].r, C[last].c, C[last].i);
           */
           
           for (auto c = C.begin(); c != C.end(); c++) {
               std::printf("t: %d, r: %d, c: %d, i\': %d \n", c->t, unsigned(c->r), c->c, c->i);
           }
           printf("\n");
           
           b = e + 1;
       }
    }   
}

std::vector<ATuple> QueryMapper::LongestIncreasingSubsequence(std::vector<ATuple>& A, int b, int e) {
    int n=e-b;
    
    std::vector<int> tail(n, 0);
    std::vector<int> prev(n, -1);
    
    int len = 1;
    
    for (int i = 1; i < n; i++) {
        if (A.at(i+b).c < A.at(tail[0]+b).c) {
            tail[0] = i;
            // TODO napisati A>B
        } else if (A.at(tail[len - 1]+b).c < A.at(i+b).c) {
            prev[i] = tail[len - 1];
            tail[len++] = i;
        } else {
            int pos = 0;
            for (int j = 1; j < n; j++) {
                if (A.at(pos+b).c < A.at(j+b).c) {
                    pos = j;
                }
            }
            prev[i] = tail[pos - 1];
            tail[pos] = i;
        }
    }
    
    std::vector<ATuple> ret;
    for (int i = tail[len - 1]; i >= 0; i = prev[i]) {
        ret.insert(ret.begin(), A.at(i));
    }
    return ret;
}
