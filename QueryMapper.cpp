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

using namespace bioinformatics;

QueryMapper::QueryMapper() {
}

QueryMapper::~QueryMapper() {
}

void QueryMapper::mapQuerySequence(HashTable *H, FastADocument *targetFastADoc,
        BioSequence *q, PAF *output, int w, int k, int epsilon){
    
    HashTableCalculationMethod method;
    std::vector<Minimizer> queryMinimizerSet;
    method.minimizerSketch(q, w, k,queryMinimizerSet);
    
    auto hashTable = H->getHashTableRaw();
    
    int i = 0;
    int size = queryMinimizerSet.size();

    std::vector<ATuple> A;
    ATuple tuple;
    
    for (auto qMsIt = queryMinimizerSet.begin(); qMsIt != queryMinimizerSet.end(); qMsIt++) {
        // std::printf("%d/%d\n", ++i, size);
        
        auto hashEntry = hashTable->find(qMsIt->m);
        if (hashEntry == hashTable->end())
            continue;
        
        auto entrySet = hashEntry->second;
        
        for (auto entryIt = entrySet->begin(); entryIt != entrySet->end(); entryIt++) {
            if (qMsIt->r == entryIt->r) {
                tuple.t = entryIt->sequencePosition;
                tuple.r = 0;
                tuple.c = qMsIt->i - entryIt->i;
                tuple.i = entryIt->i;
                A.push_back(tuple);
            } else {
                tuple.t = entryIt->sequencePosition;
                tuple.r = 1;
                tuple.c = qMsIt->i + entryIt->i;
                tuple.i = entryIt->i;
                A.push_back(tuple);
            }

            // std::printf("Query h, i, r: %d, %d, %d\tt, r, c, i': %d, %d, %d, %d\n",
            // qMsIt->m, qMsIt->i, unsigned(qMsIt->r), tuple.t, tuple.r, tuple.c, tuple.i);
        }
    }
    
    // std::printf("Finished building A\n");
    
    std::sort(A.begin(), A.end()); 
    
    std::vector<ATuple> lisC;

    int b = 0;
    for (int e = 0, size = A.size(); e < size; e++){
        if ((e == size - 1) ||
                (A[e + 1].t != A[e].t) || (A[e + 1].r != A[e].r) ||
                (A[e + 1].c - A[e].c >= epsilon)) {
    
            lisC.clear();
            
            LongestIncreasingSubsequence(A, b, e, lisC);
            output->print(q, targetFastADoc, &lisC[0], &lisC[lisC.size()-1]);
            
            /*
            if (lisC[0].i > lisC[lisC.size()-1].i) {
                for (int g = 0; g < lisC.size(); g++) {
                    printf("(i=%d, c=%d)  ", lisC[g].i, lisC[g].c);
                }
                
                printf("\n\n");
            }
            */
            
            b = e + 1;
        }
    }
}

void QueryMapper::LongestIncreasingSubsequence(std::vector<ATuple>& A, int b, int e, std::vector<ATuple>& ret) {
    
    if (b == e) { 
        ret.push_back(A[b]);
        return;
    }
    
    int n=e-b;
    
    std::vector<int> tail(n+1, 0);
    std::vector<int> prev(n+1, -1);
    
    int len = 1;
    
    for (int i = 1; i < n; i++) {
        if (A.at(i+b).c < A.at(tail[0]+b).c) {
            tail[0] = i;
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
    
    for (int i = tail[len - 1]; i >= 0; i = prev[i]) {
        ret.insert(ret.begin(), A.at(i+b));
    }
}
