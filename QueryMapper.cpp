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

void QueryMapper::mapQuerySequence(BioSequence *q, int w, int k, int epsilon) {
    std::vector<ATuple> A;
    
    HashTableCalculationMethod method;
    std::set<Minimizer>* queryMinimizerSet = method.minimizerSketch(q, w, k);
    
    HashTable* hashTableLoaded = NULL;
    std::set<bioinformatics::Entry> *hashMinimizerSet;
    int m = -1;
    
    for (auto queryMinIt = queryMinimizerSet->begin(); queryMinIt != queryMinimizerSet->end(); queryMinIt++) {
//        std::cout << std::endl << "Query h, i, r: "
//                << queryMinIt->m << " "
//                << queryMinIt->i << " "
//                << queryMinIt->r << std::endl;
        
        if (m >= 0 and queryMinIt->m != m) {
            hashTableLoaded->empty();
            delete hashMinimizerSet;
        } 
        
        if (queryMinIt->m != m) {
            
            if(hashTableLoaded!=NULL){
                delete hashTableLoaded;
            }
            
            hashTableLoaded = HashTable::loadWithM("hash_example", queryMinIt->m);
            std::map<int, std::set<bioinformatics::Entry>*> *H = hashTableLoaded->getHashTableRaw();
            
            std::map<int,std::set<bioinformatics::Entry>*>::iterator found = H->find(queryMinIt->m);
            //TODO: is the old value deleted
            if(found!=H->end()){
                hashMinimizerSet = found->second;
            }
            else{
                hashMinimizerSet = NULL;
            }
                        
            m = queryMinIt->m;
        }
        
        
        if(hashMinimizerSet!=NULL) //TODO: think what should be done here
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

                std::cout << "Query h, i, r: "
                        << queryMinIt->m << " "
                        << queryMinIt->i << " "
                        << queryMinIt->r << " "
                        << "\tt, r, c, i': "
                        << tuple.t << " "
                        << tuple.r << " "
                        << tuple.c << " "
                        << tuple.i << std::endl;

                A.push_back(tuple);
            }
        
        std::sort(A.begin(), A.end()); 
        
        int b = 0;
        int ALength = A.size();
        
        for (auto e = 0; e < ALength; e++) {
           if (e == ALength - 1 or
               A.at(e + 1).t != A.at(e).t or
               A.at(e + 1).r != A.at(e).r or
               A.at(e + 1).c - A.at(e).c >= epsilon) {
               
               // TODO: finish this algorithm
               // C = maximal colinear subset
               // print the left-most and right-most query/target positions in C
               std::vector<ATuple> sub(&A[b], &A[e]);
               std::vector<ATuple> C = QueryMapper::LongestIncreasingSubsequence(sub);
               for(auto g : C) {
                   std::cout << g.c << " ";
               }
               std::cout << std::endl;
               b = e + 1;
           }
        }    
    }
    
    if(hashTableLoaded!=NULL){
        delete hashTableLoaded;
    }
    delete queryMinimizerSet;
}

std::vector<ATuple> QueryMapper::LongestIncreasingSubsequence(std::vector<ATuple> A) {
    int n = sizeof(A)/sizeof(A.at(0));
    std::vector<int> tail(n, 0);
    std::vector<int> prev(n, -1);
    
    int len = 1;
    
    for(int i=1; i<n; i++) {
        if (A.at(0).c < A.at(tail[0]).c) {
            tail[0] = i;
            // TODO napisati A>B
        } else if (A.at(tail[len-1]) < A.at(i)) {
            prev[i] = tail[len-1];
            tail[len++] = i;
        } else {
            int pos = 0;
            for (int j=1; j<n; j++) {
                if (A.at(pos).c < A.at(j).c) {
                    pos = j;
                }
            }
            prev[i] = tail[pos-1];
            tail[pos] = i;
        }
    }
    
    std::vector<ATuple> ret;
    for (int i=tail[len-1]; i>=0; i=prev[i]) {
        ret.insert(ret.begin(), A.at(i));
    }
    return ret;
}
