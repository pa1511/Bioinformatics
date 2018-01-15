/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTableCalculationMethod.h
 * Author: paf
 *
 * Created on November 5, 2017, 1:56 PM
 */

#ifndef HASHTABLECALCULATIONMETHOD_H
#define HASHTABLECALCULATIONMETHOD_H

#include "BioSequence.h"
#include "FastADocument.h"
#include "HashTable.h"

#include <string>
#include <set>
#include <map>
#include <limits.h>
#include <limits>
#include <algorithm>

using namespace bioinformatics;

#pragma pack(push, 1)
struct Minimizer {
    int m;
    int i;
    
    bool operator <(const Minimizer& other) const {
        if (this->m == other.m) {
            return this->i < other.i;
        }
        return this->m < other.m;
    }
    
    bool operator ==(const Minimizer& other) const {
        return this->m==other.m && this->i==other.i;
    }

};
#pragma pack(pop)

class HashTableCalculationMethod {
    public:
        static int PHI_VALUE[8];
        static int POW_4_VALUE[16];
        static int INV_HASH_MASK[16];

        HashTableCalculationMethod();
        ~HashTableCalculationMethod();

        HashTable* calculate(FastADocument* document, int w, int k);

        void minimizerSketch(bioinformatics::BioSequence *sequence, int w, int k,std::vector<Minimizer>& minimizerSet0, std::vector<Minimizer>& minimizerSet1);


    private:
        void fillMap(std::unordered_map<int,std::vector<bioinformatics::Entry>*>* hashTable, int r, std::vector<Minimizer>& minimizerSet, BioSequence* sequence);
        void removeDuplicates(std::vector<Minimizer>& M);
        int PHI_function(std::string *seqence, int startIndex, int k);
        inline int PHI_function(char b);
        int invertibleHash(int x, int m);
};

#endif /* HASHTABLECALCULATIONMETHOD_H */

