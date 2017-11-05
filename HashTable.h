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

namespace bioinformatics {
    class HashTable {
    public:
        HashTable();
        ~HashTable(); //destruktor
        void save(std::string path);
        
        static HashTable* load(std::string path);
    private:

    };
}
#endif /* HASHTABLE_H */

