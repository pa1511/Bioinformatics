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

using namespace bioinformatics;

#pragma pack(push, 1)
struct Minimizer {
    int m;
    int i;
    std::uint8_t r;
    
    bool operator <(const Minimizer& other) const {
        if (this->m == other.m) {
            if (this->i == other.i) {
                return this->r < other.r;
            }
            return this->i < other.i;
        }
        return this->m < other.m;
    }

};
#pragma pack(pop)

class HashTableCalculationMethod {
    public:
        static int PHI_VALUE[4];

        HashTableCalculationMethod();
        ~HashTableCalculationMethod();

        HashTable* calculate(FastADocument* document, int w, int k);
        std::set<Minimizer>* minimizerSketch(bioinformatics::BioSequence *sequence, int w, int k);

    private:
        std::string* PI_function(bioinformatics::BioSequence *biosequence, int r);
        int PHI_function(std::string *seqence, int startIndex, int k);
        inline int PHI_function(char b);
        int invertibleHash(int x, int p);
};

#endif /* HASHTABLECALCULATIONMETHOD_H */

