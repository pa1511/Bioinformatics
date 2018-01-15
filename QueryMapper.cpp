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
    
    int MATCHING_BASES_MIN_COUNT = 100;
    int MIN_MAPPING_SUBSET_SIZE = 4;
    
    HashTableCalculationMethod method;
    std::vector<Minimizer> queryMinimizerSet0;
    std::vector<Minimizer> queryMinimizerSet1;
    method.minimizerSketch(q, w, k,queryMinimizerSet0,queryMinimizerSet1);
    
    auto hashTable = H->getHashTableRaw();

    std::vector<ATuple> A;
    ATuple tuple;
    
    fillA(0,queryMinimizerSet0, hashTable, A, tuple);
    fillA(1,queryMinimizerSet1, hashTable, A, tuple);
    
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
            
            int N = lisC.size();
            int matchingBases = N * k;
            
            if (N >= MIN_MAPPING_SUBSET_SIZE && matchingBases >= MATCHING_BASES_MIN_COUNT) {
                output->print(q, targetFastADoc, &lisC[0], &lisC[N-1], N);
            }
            
            
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

void QueryMapper::fillA(int r, std::vector<Minimizer>& queryMinimizerSet, std::unordered_map<int, std::vector<bioinformatics::Entry>*> * hashTable, std::vector<ATuple>& A, ATuple& tuple){
    for (auto qMsIt = queryMinimizerSet.begin(); qMsIt != queryMinimizerSet.end(); qMsIt++) { 
        auto hashEntry = hashTable->find(qMsIt->m);
        if (hashEntry == hashTable->end())
            continue;
        
        auto entrySet = hashEntry->second;
        
        for (auto entryIt = entrySet->begin(); entryIt != entrySet->end(); entryIt++) {
            if (r == entryIt->r) {
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
}

void QueryMapper::LongestIncreasingSubsequence(std::vector<ATuple>& A, int b, int e, std::vector<ATuple>& ret) {
    
    int n=e-b;
    
    std::vector<int> tail(n+1, 0);
    std::vector<int> prev(n+1, -1);
    
    int len = 1;
    
    for (int i = 1; i < n; i++) {
        if (A[i+b].i < A[tail[0]+b].i) {
            tail[0] = i;
        } else if (A[tail[len - 1]+b].i < A[i+b].i) {
            prev[i] = tail[len - 1];
            tail[len++] = i;
        } else {
            int pos = 0;
            for (int j = 1; j < n; j++) {
                if (A[pos+b].i < A[j+b].i) {
                    pos = j;
                }
            }
            prev[i] = tail[pos - 1];
            tail[pos] = i;
        }
    }
    
    for (int i = tail[len - 1]; i >= 0; i = prev[i]) {
        ret.insert(ret.begin(), A[i+b]);
    }
}
