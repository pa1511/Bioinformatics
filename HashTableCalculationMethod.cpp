/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTableCalculationMethod.cpp
 * Author: paf
 * 
 * Created on November 5, 2017, 1:56 PM
 */

#include "HashTableCalculationMethod.h"

#include <math.h>
#include <limits.h>
#include <algorithm>

int HashTableCalculationMethod::PHI_VALUE[] = {0, 1, 3, 2};

HashTableCalculationMethod::HashTableCalculationMethod() {
}

HashTableCalculationMethod::~HashTableCalculationMethod() {
}

HashTable* HashTableCalculationMethod::calculate(FastADocument* document, int w, int k) {

    // TODO: change so it follows the logic from the text
    // The key is the minimizer hash value and the value is a set of target sequence index, the position of the minimizer and the strand
    
    std::unordered_map<int,std::vector<bioinformatics::Entry>*> *hashTable = new std::unordered_map<int,std::vector<bioinformatics::Entry>*>();
    
    BioSequence *sequence;
    while ((sequence = document->getNextSequence()) != NULL) {
        
        std::vector<Minimizer>* minimizerSet = minimizerSketch(sequence,w,k);
        
        for (auto it = minimizerSet->begin(); it != minimizerSet->end(); it++) {
            
            bioinformatics::Entry entry;
            entry.sequencePosition = sequence->getSequencePosition();
            entry.i = it->i;
            entry.r = it->r;
            
            std::unordered_map<int,std::vector<bioinformatics::Entry>*>::iterator mapIt = hashTable->find(it->m);
            if (mapIt != hashTable->end()) {
                std::vector<bioinformatics::Entry>* entrySet = mapIt->second;
                entrySet->push_back(entry);
            } else {
                std::vector<Entry>* entrySet = new std::vector<Entry>;
                entrySet->push_back(entry);
                hashTable->insert(std::pair<int, std::vector<bioinformatics::Entry>*>(it->m, entrySet));
            }
        }
        
        delete minimizerSet;
        delete sequence;
    }
    
    //Fit vectors to the minimum memory size they need
    for(auto it=hashTable->begin(); it!=hashTable->end(); it++){
        it->second->shrink_to_fit();
    }
    
    return new HashTable(hashTable);
}

std::string* HashTableCalculationMethod::PI_function(bioinformatics::BioSequence* biosequence, int r) {
    if(r == 0) {
        return biosequence->getSequence();
    } else if(r == 1) {
        return biosequence->getInvertedSequence();
    }
    throw "r was different from 0 and 1";
}

int HashTableCalculationMethod::PHI_function(std::string *seqence, int startIndex, int k) {
    int hashValue = 0;
    
    for (int i = 0; i < k; i++){
        hashValue += powf(4.0, k-i-1) * PHI_function((*seqence)[startIndex + i]);
    }
    
    return hashValue;
}

inline int HashTableCalculationMethod::PHI_function(char b) {

    // A 0x41   0100 0001   0
    // T 0x54   0101 0100   2
    // C 0x43   0100 0011   1
    // G 0x47   0100 0111   3
    // mask     0000 0110
        
    // if (b == 'A') {
    //     return 0;
    // } else if (b == 'C') {
    //     return 1;
    // } else if (b == 'G') {
    //     return 2;
    // } else if (b == 'T') {
    //     return 3;
    // }
    
    return (b & 0x6) >> 1;
    
    // TODO: what if it is some other value
    throw "Unknown b";
}

// ALGORITHM 2
int HashTableCalculationMethod::invertibleHash(int x, int p) {

    int m = 0x1 << p - 1;
    x = (~x + (x << 21)) & m;
    x = x^x >> 24;
    x = (x + (x << 3) + (x << 8)) & m;
    x = x^x >> 14;
    x = (x +(x << 2) + (x << 4)) & m;
    x = x^x >> 28;
    x = (x + (x << 31)) & m;
    
    return x;
}

// ALGORITHM 1
std::vector<Minimizer>* HashTableCalculationMethod::minimizerSketch(bioinformatics::BioSequence *sequence, int w, int k) {

    // TODO: optimize implementation
    
    std::vector<Minimizer>* M = new std::vector<Minimizer>;
    
    std::string* raw_sequence = sequence->getSequence();
    std::string* raw_inv_sequence = sequence->getInvertedSequence();

    Minimizer min;
    int u[w-1];
    int v[w-1];
    
    for (int i = 1, limit = sequence->size()- w-k+1; i < limit; i++) {
        int m = std::numeric_limits<int>::max();
        for (int j = 0; j < w-1; j++) {
            u[j] = PHI_function(raw_sequence, i + j, k);
            v[j] = PHI_function(raw_inv_sequence, i + j, k);
            
            if (u[j] != v[j]) {
                m = std::min(m,std::min(u[j], v[j])); 
            }
        }
        
        for (int j = 0; j < w-1; j++) {

            if (u[j] < v[j] && u[j] == m) {
                min.m = m;
                min.i = i + j;
                min.r = 0;
                
                M->push_back(min);//a copy is created
            } else if (v[j] < u[j] && v[j] == m) {
                min.m = m;
                min.i = i + j;
                min.r = 1;
                
                M->push_back(min);//a copy is created
            }
        }
    }
    
    return M;
}
