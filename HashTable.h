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
#include <map>
#include <set>
#include <vector>

namespace bioinformatics {

struct Entry {

    int sequencePosition;
    int i;
    int r;
    
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
    
    
class HashTable {
    public:
        HashTable(std::map<int, std::set<bioinformatics::Entry>*> *hashTableRaw);
        ~HashTable();
        void save(std::string path);
        void empty();
        
        static HashTable* load(std::string path);
        //static HashTable* loadWithM(std::string path, int m);
        std::map<int, std::set<bioinformatics::Entry>*> getHashTableRaw();
    private:
        std::map<int, std::set<bioinformatics::Entry>*> *hashTableRaw;
    };
}

#endif /* HASHTABLE_H */

