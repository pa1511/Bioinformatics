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
        std::string value;
        for(auto it=hashTableRaw->begin(); it!=hashTableRaw->end(); it++) {
            key = std::to_string(it->first);
            hashFile << "# " << key << std::endl;
            for(auto setit=it->second.begin(); setit!=it->second.end(); setit++) {
                value.append(std::to_string(setit->sequencePosition));
                value.append(" ");
                value.append(std::to_string(setit->i));
                value.append(" ");
                value.append(std::to_string(setit->r));
                hashFile << value;
            }
        }
        std::cout << "Done." << std::endl ;
    }
  /*  hashFile.open(path, std::ios::out | std::ios::binary);
    
    char buff[1024];
    if(hashFile.is_open()) {
        std::string key;
        for(auto it=hashTableRaw->begin(); it!=hashTableRaw->end(); it++) {
            key = std::to_string(it->first);
            std::strncpy(buff, key.c_str(), sizeof(buff));
            buff[sizeof(buff) - 1] = 0;
            hashFile.write(buff, sizeof(buff));
            
            std::cout << "Key: " << it->first << std::endl;
            for(auto setit=it->second.begin(); setit!=it->second.end(); setit++) {
//                std::cout << setit->i << std::endl;
            }
        }
        std::cout << "Done." << std::endl ;
    }*/
    
    hashFile.close();
}


HashTable* HashTable::load(std::string path) {
    // TODO
}

std::map<int,std::set<bioinformatics::Entry>> HashTable::getHashTableRaw() {
    return *(this->hashTableRaw);
}

