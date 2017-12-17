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

void QueryMapper::mapQuerySequence(HashTable *hashTable, BioSequence *q, int w, int k, int epsilon) {
    std::vector<ATuple> A;
    std::map<int,std::set<bioinformatics::Entry>> H = hashTable->getHashTableRaw();
    
    HashTableCalculationMethod method;
    std::set<Minimizer> queryMinimizerSet = method.minimizerSketch(q,w,k);
    
    for (auto queryMinIt=queryMinimizerSet.begin(); queryMinIt!=queryMinimizerSet.end(); queryMinIt++) {
        std::set<bioinformatics::Entry> hashMinimizerSet = H.find(queryMinIt->m)->second;
        
        for (auto hashMinIt=hashMinimizerSet.begin(); hashMinIt!=hashMinimizerSet.end(); hashMinIt++) {
            ATuple tuple;
            tuple.t = hashMinIt->sequencePosition;
            tuple.i = hashMinIt->i;
            
            if (queryMinIt->r == hashMinIt->r) {
                tuple.r = 0;
                tuple.c = queryMinIt->i - hashMinIt->i;
            }
            else {
                tuple.r = 1;
                tuple.c = queryMinIt->i + hashMinIt->i;
            }
            
            A.push_back(tuple);
        }
        
        std::sort(A.begin(), A.end()); 
        
        int b = 0;
        int ALength = A.size();
        
        for (auto e=0; e<ALength; e++) {
           if (e == ALength - 1
                   or A.at(e+1).t != A.at(e).t
                   or A.at(e+1).r != A.at(e).r
                   or A.at(e+1).c - A.at(e).c >= epsilon) {
               // TODO: finish this algorithm
               // C = maximal colinear subset
               // print the left-most and right-most query/target positions in C
               b = e + 1;
           }
        }
    }
}