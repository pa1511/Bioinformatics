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

HashTable* HashTableCalculationMethod::calculate(FastADocument* document, int w, int k, int threadCount) {
    
    std::unordered_map<int,std::vector<bioinformatics::Entry>*> *hashTable0 =
                new std::unordered_map<int,std::vector<bioinformatics::Entry>*>();
    std::unordered_map<int,std::vector<bioinformatics::Entry>*> *hashTable1 =
                new std::unordered_map<int,std::vector<bioinformatics::Entry>*>();
        
    if(threadCount==1){
        BioSequence *sequence;
        while ((sequence = document->getNextSequence()) != NULL) {
            std::vector<Minimizer> minimizerSet0;
            std::vector<Minimizer> minimizerSet1;
            minimizerSketch(sequence, w, k, minimizerSet0, minimizerSet1);

            int sequencePosition = sequence->getSequencePosition();
            
            fillMap(hashTable0, minimizerSet0, sequencePosition);
            fillMap(hashTable1, minimizerSet1, sequencePosition);

            delete sequence;
        }
    }    
    else{
        SyncQueue<BioSequence*> tasks;
        SyncQueue<CalculateTaskResult> results;

        std::vector<std::thread*> workers;

        //Create workers
        for(int i=0; i<threadCount; i++){
            std::thread* worker = new std::thread(&HashTableCalculationMethod::calculateTask, HashTableCalculationMethod(),std::ref(tasks),std::ref(results),w ,k);
            workers.push_back(worker);
        }
        
        //Submit tasks
        BioSequence *sequence;
        while ((sequence = document->getNextSequence()) != NULL) {
            tasks.push(sequence);
        }        
        for(int i=0; i<threadCount; i++){
            tasks.push(poison_pill);
        }

        //Destroy workers
        for(int i=0; i<threadCount; i++){
            std::thread* worker = workers.back();
            workers.pop_back();
            worker->join();
            delete worker;
        }
    
        //Process created results
        while(!results.empty()){
            CalculateTaskResult result = results.pop();
            
            fillMap(hashTable0, *result.minimizerSet0, result.sequencePosition);
            fillMap(hashTable1, *result.minimizerSet1, result.sequencePosition);
            
            delete result.minimizerSet0;
            delete result.minimizerSet1;
        }
    }
        
    //Fit vectors to the minimum memory size they need
    shrinkVectors(hashTable0);
    shrinkVectors(hashTable1);
    
    return new HashTable(hashTable0,hashTable1);
}

void HashTableCalculationMethod::calculateTask(SyncQueue<BioSequence*>& tasks, SyncQueue<CalculateTaskResult>& results, int w, int k){
    
    while(true){
        BioSequence* sequence = tasks.pop();
        
        if(sequence==poison_pill)
            break;
        
        CalculateTaskResult taskResult;
        taskResult.sequencePosition = sequence->getSequencePosition();
        taskResult.minimizerSet0 = new std::vector<Minimizer>();
        taskResult.minimizerSet1 = new std::vector<Minimizer>();
        
        minimizerSketch(sequence, w, k, *taskResult.minimizerSet0, *taskResult.minimizerSet1);
        delete sequence;
        
        results.push(taskResult);
    }
    
}



void HashTableCalculationMethod::fillMap(std::unordered_map<int,std::vector<bioinformatics::Entry>*>* hashTable, std::vector<Minimizer>& minimizerSet, int sequencePosition){
    for (auto it = minimizerSet.begin(); it != minimizerSet.end(); it++) {
        bioinformatics::Entry entry;
        entry.sequencePosition = sequencePosition;
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
    int u[w];
    int v[w];
    int minuv[w];
    int pos[w];
    
    const int max = std::numeric_limits<int>::max();
    
    {
        int m = max;
        for (int j = 0; j < w; j++) {
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
        
        for (int j = 0; j < w; j++) {

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
    int m = max;
    for (int i = 1, limit = sequence->size()- w-k+1; i <= limit; i++) {
        
        pos[current_id] = i + w-1;
        u[current_id] = PHI_function(raw_sequence, pos[current_id], k);
        v[current_id] = PHI_function(raw_inv_sequence, pos[current_id], k);

        if (u[current_id] != v[current_id]) {
            minuv[current_id] = std::min(u[current_id], v[current_id]);
        } else {
            minuv[current_id] = max;
        }

        
        //int m = max;
        if(m>=minuv[current_id]){
            m = minuv[current_id];
        }
        else{
            m = max;
            for (int j = 0; j < w; j++) {
                m = std::min(m,minuv[j]); 
            }
        }
        
        for (int j = 0; j < w; j++) {
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
        
        current_id = (current_id + 1) % w;
    }
    
    removeDuplicates(M0);
    removeDuplicates(M1);
}

inline void HashTableCalculationMethod::removeDuplicates(std::vector<Minimizer>& M){
    std::sort(M.begin(), M.end());
    M.erase(std::unique(M.begin(), M.end()), M.end());
    M.shrink_to_fit();
}

