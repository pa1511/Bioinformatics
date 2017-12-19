/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTable.cpp
 * Author: lucy
 * 
 * Created on November 5, 2017, 12:13 PM
 */

#include <fstream>
#include <cstring>
#include <iostream>

#include "HashTable.h"

using namespace bioinformatics;

HashTable::HashTable(std::map<int,std::set<bioinformatics::Entry>> *hashTableRaw):hashTableRaw(hashTableRaw){
    
}

HashTable::~HashTable() {
    delete hashTableRaw;
}

void HashTable::save(std::string path) {
    std::ofstream hashFile;
    
    hashFile.open(path, std::ios::out);
    
    if(hashFile.is_open()) {
        std::string key;
        std::string value1;
        for(auto it=hashTableRaw->begin(); it!=hashTableRaw->end(); it++) {
            int key = it->first;
            hashFile << "# " << key << std::endl;
            for(auto setit=it->second.begin(); setit!=it->second.end(); setit++) {
                hashFile << setit->sequencePosition << " " << setit->i << " " << setit->r << std::endl;
            }
        }
        std::cout << "Saved as \"" << path << "\"" << std::endl ;
    }
    hashFile.close();
}


HashTable* HashTable::load(std::string path) {
    // TODO
}

std::map<int,std::set<bioinformatics::Entry>> HashTable::getHashTableRaw() {
    return *(this->hashTableRaw);
}

