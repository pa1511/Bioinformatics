/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueryMapper.h
 * Author: papric
 *
 * Created on December 17, 2017, 11:46 AM
 */

#ifndef QUERYMAPPER_H
#define QUERYMAPPER_H

#include "BioSequence.h"
#include "HashTable.h"
#include "FastADocument.h"
#include "PAF.h"
#include "HashTableCalculationMethod.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace bioinformatics;

#pragma pack(push, 1)
struct ATuple {
    std::uint16_t t;
    std::uint8_t r;
    int c;
    int i;
    
    bool operator <(const ATuple& other) const {
        if (this->t == other.t) {
            if(this->r == other.r) {
                if (this->c == other.c) {
                    return this->i < other.i;
                }
                return this->c < other.c;
            }
            return this->r < other.r;
        }
        return this->t < other.t;
    }
}; 
#pragma pack(pop)

class QueryMapper {
    public:
        QueryMapper();
        ~QueryMapper();

        void mapQuerySequence(HashTable *H, FastADocument *targetFastADoc, BioSequence *q, PAF *output, int w, int k, int epsilon);
        void mapQuerySequence(FastADocument *targetFastADoc, BioSequence *q, PAF *output, int w, int k, int epsilon);
        std::vector<ATuple> LongestIncreasingSubsequence(std::vector<ATuple>& A, int b, int e);
    private:
};

#endif /* QUERYMAPPER_H */

