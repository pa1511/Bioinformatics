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

namespace bioinformatics {

struct Entry{

    std::string *rawSequence;
    int i;
    int r;
    
};    
    
    
class HashTable {
    public:
        HashTable(std::map<int,bioinformatics::Entry> *hashTableRaw);
        ~HashTable(); //destruktor
        void save(std::string path);
        
        static HashTable* load(std::string path);
    private:
        std::map<double,bioinformatics::Entry> *hashTableRaw;
    };
}
#endif /* HASHTABLE_H */

