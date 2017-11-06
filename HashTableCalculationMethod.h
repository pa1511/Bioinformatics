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

using namespace bioinformatics;

struct minimizer{
    double m;
    int i;
    int r;
    
    bool operator <(const minimizer& other) const{
        //TODO: this needs to be implemented properly 
        //It is needed to place the structure in a set
        return this->m < other.m;
    }

};

class HashTableCalculationMethod {
public:
    HashTableCalculationMethod();
    ~HashTableCalculationMethod();

    HashTable* calculate(FastADocument* document);
    
private:
    std::string PI_function(bioinformatics::BioSequence* biosequence,int r);
    //
    int PHI_function(std::string seqence,int startIndex, int k);
    int PHI_function(char b);
    //
    int invertibleHash(int x, int p);
    //
    std::set<minimizer> minimizerSketch(bioinformatics::BioSequence sequence, int w, int k);

};

#endif /* HASHTABLECALCULATIONMETHOD_H */

