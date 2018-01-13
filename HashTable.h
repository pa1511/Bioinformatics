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

#include <string>
#include <unordered_map>
#include <vector>

namespace bioinformatics {

#pragma pack(push, 1)
struct Entry {

    std::uint16_t sequencePosition;
    int i;
    std::uint8_t r;
    
    bool operator <(const Entry& other) const {
        if (this->sequencePosition == other.sequencePosition) {
            if (this->i == other.i) {
                return this->r < other.r;
            }
            return this->i < other.i;
        }
        return this->sequencePosition < other.sequencePosition;
    }
};    
#pragma pack(pop)
    
    
class HashTable {
    public:
        HashTable(std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw);
        ~HashTable();
        void save(std::string path);
        void empty();
        
        static HashTable* load(std::string path);
        static HashTable* loadWithM(std::string path, int m);
        std::unordered_map<int, std::vector<bioinformatics::Entry>*>* getHashTableRaw();
    private:
        std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw;
    };
}

#endif /* HASHTABLE_H */

