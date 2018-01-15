/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTable.h
 * Author: lucy
 *
 * Created on November 5, 2017, 12:13 PM
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <iterator>
#include <algorithm>

namespace bioinformatics {

#pragma pack(push, 1)
struct Entry {

    std::uint16_t sequencePosition;
    int i;
    
    bool operator <(const Entry& other) const {
        if (this->sequencePosition == other.sequencePosition) {
            return this->i < other.i;
        }
        return this->sequencePosition < other.sequencePosition;
    }
};    
#pragma pack(pop)
    
    
class HashTable {
    public:
        HashTable(std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw0,
                std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw1);
        ~HashTable();
        void empty();
        std::unordered_map<int, std::vector<bioinformatics::Entry>*>* getHashTableRaw0();
        std::unordered_map<int, std::vector<bioinformatics::Entry>*>* getHashTableRaw1();
        
        void save(std::string path);
        static HashTable* load(std::string path);
//        static HashTable* loadWithM(std::string path, int m);
    private:
        std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw0;
        std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw1;
    };
}

#endif /* HASHTABLE_H */

