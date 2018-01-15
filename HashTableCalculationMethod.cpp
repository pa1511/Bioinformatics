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

int HashTableCalculationMethod::PHI_VALUE[] = {0, -1, 1, -1, 3, -1, 2, -1};

int HashTableCalculationMethod::POW_4_VALUE[] = { 1, 4, 16, 64, 256,
                        1024, 4096, 16384, 65536, 262144, 1048576,
                        4194304, 16777216, 67108864, 268435456, 1073741824 };

int HashTableCalculationMethod::INV_HASH_MASK[] = { 0x0, 0x3, 0xf, 0x3f, 0xff, 
                        0x3ff, 0xfff, 0x3fff, 0xffff, 0x3ffff, 0xfffff, 0x3fffff, 
                        0xffffff, 0x3ffffff, 0xfffffff, 0x3fffffff };


HashTableCalculationMethod::HashTableCalculationMethod() {
}

HashTableCalculationMethod::~HashTableCalculationMethod() {
}

HashTable* HashTableCalculationMethod::calculate(FastADocument* document, int w, int k) {
    
    std::unordered_map<int,std::vector<bioinformatics::Entry>*> *hashTable0 =
                new std::unordered_map<int,std::vector<bioinformatics::Entry>*>();
    std::unordered_map<int,std::vector<bioinformatics::Entry>*> *hashTable1 =
                new std::unordered_map<int,std::vector<bioinformatics::Entry>*>();
    
    std::vector<Minimizer> minimizerSet0;
    std::vector<Minimizer> minimizerSet1;
    
    BioSequence *sequence;
    while ((sequence = document->getNextSequence()) != NULL) {
        minimizerSet0.clear();
        minimizerSet1.clear();
        minimizerSketch(sequence, w, k, minimizerSet0, minimizerSet1);
        
        fillMap(hashTable0, minimizerSet0, sequence);
        fillMap(hashTable1, minimizerSet1, sequence);
        
        delete sequence;
    }
    
    //Fit vectors to the minimum memory size they need
    shrinkVectors(hashTable0);
    shrinkVectors(hashTable1);
    
    return new HashTable(hashTable0,hashTable1);
}

void HashTableCalculationMethod::fillMap(std::unordered_map<int,std::vector<bioinformatics::Entry>*>* hashTable, std::vector<Minimizer>& minimizerSet, BioSequence* sequence){
    for (auto it = minimizerSet.begin(); it != minimizerSet.end(); it++) {
        bioinformatics::Entry entry;
        entry.sequencePosition = sequence->getSequencePosition();
        entry.i = it->i;
        
        std::unordered_map<int,std::vector<bioinformatics::Entry>*>::iterator mapIt = hashTable->find(it->m);
        std::vector<bioinformatics::Entry>* entrySet;
        
        if (mapIt != hashTable->end()) {
            entrySet = mapIt->second;
        } else {
            entrySet = new std::vector<Entry>;
            hashTable->insert(std::pair<int, std::vector<bioinformatics::Entry>*>(it->m, entrySet));
        }
        entrySet->push_back(entry);
    }
}

inline void HashTableCalculationMethod::shrinkVectors(std::unordered_map<int,std::vector<bioinformatics::Entry>*>* hashTable){
    for(auto it=hashTable->begin(); it!=hashTable->end(); it++){
        it->second->shrink_to_fit();
    }
}

int HashTableCalculationMethod::PHI_function(std::string *seqence, int startIndex, int k) {
    int hashValue = 0;
    
    for (int i = 0; i < k; i++) {
        //powf(4.0, k-i-1)
        //(0x1 << (2*(k-i-1)))
        //POW_4_VALUE[k-i-1]
        hashValue +=  POW_4_VALUE[k-i-1]*PHI_function((*seqence)[startIndex + i]);
    }
    
    hashValue = invertibleHash(hashValue,INV_HASH_MASK[k]);
    
    return hashValue;
}

inline int HashTableCalculationMethod::PHI_function(char b) {

    // A 0x41   0100 0001   0
    // T 0x54   0101 0100   2
    // C 0x43   0100 0011   1
    // G 0x47   0100 0111   3
    // mask     0000 0110
 /*   
    int res;    
    if (b == 'A') {
        res = 0;
    } else if (b == 'C') {
        res = 1;
    } else if (b == 'G') {
        res = 2;
    } else if (b == 'T') {
        res = 3;
    }
*/        
    
    return PHI_VALUE[b & 0x6];
}

// ALGORITHM 2
int HashTableCalculationMethod::invertibleHash(int x, int m) {

    //int m = (0x1 << p) - 1; //says p=2k
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
void HashTableCalculationMethod::minimizerSketch(bioinformatics::BioSequence *sequence, int w, int k, std::vector<Minimizer>& M0, std::vector<Minimizer>& M1) {
    
    std::string* raw_sequence = sequence->getSequence();
    std::string* raw_inv_sequence = sequence->getInvertedSequence();

    Minimizer min;
    int u[w - 1];
    int v[w - 1];
    int minuv[w - 1];
    int pos[w - 1];
    
    const int max = std::numeric_limits<int>::max();
    
    {
        int m = max;
        for (int j = 0; j < w-1; j++) {
            u[j] = PHI_function(raw_sequence, j, k);
            v[j] = PHI_function(raw_inv_sequence, j, k);
            
            if (u[j] != v[j]) {
                minuv[j] = std::min(u[j], v[j]);
                m = std::min(m,minuv[j]); 
            } else {
                minuv[j] = max;
            }
            
            pos[j] = j;
        }
        
        for (int j = 0; j < w-1; j++) {

            if (u[j] == m && u[j] < v[j]) {
                min.m = m;
                min.i = pos[j];
                
                M0.push_back(min); // a copy is created
            } else if (v[j] == m && v[j] < u[j]) {
                min.m = m;
                min.i = pos[j];
                
                M1.push_back(min); // a copy is created
            }
        }    
    }
    
    int current_id = 0;
    
    for (int i = 1, limit = sequence->size()- w-k+1; i < limit; i++) {
        
        pos[current_id] = i + w-1-1;
        u[current_id] = PHI_function(raw_sequence, pos[current_id], k);
        v[current_id] = PHI_function(raw_inv_sequence, pos[current_id], k);

        if (u[current_id] != v[current_id]) {
            minuv[current_id] = std::min(u[current_id], v[current_id]);
        } else {
            minuv[current_id] = max;
        }

        
        int m = max;
        for (int j = 0; j < w-1; j++) {
            m = std::min(m,minuv[j]); 
        }
        
        for (int j = 0; j < w-1; j++) {
            if (u[j] == m && u[j] < v[j]) {
                min.m = m;
                min.i = pos[j];
                
                M0.push_back(min); // a copy is created
            } else if (v[j] == m && v[j] < u[j]) {
                min.m = m;
                min.i = pos[j];
                
                M1.push_back(min); // a copy is created
            }
        }
        
        current_id = (current_id + 1) % (w - 1);
    }
    
    removeDuplicates(M0);
    removeDuplicates(M1);
}

inline void HashTableCalculationMethod::removeDuplicates(std::vector<Minimizer>& M){
    std::sort(M.begin(), M.end());
    M.erase(std::unique(M.begin(), M.end()), M.end());
    M.shrink_to_fit();    
}

