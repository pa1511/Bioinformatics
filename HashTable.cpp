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
#include <sstream>
#include <iterator>
#include <algorithm>

#include "HashTable.h"

using namespace bioinformatics;

HashTable::HashTable(std::map<int, std::set<bioinformatics::Entry>*> *hashTableRaw):hashTableRaw(hashTableRaw) {
}

HashTable::~HashTable() {
    
    //TODO: need to delete all the sets in the table
    
    delete hashTableRaw;
}

void HashTable::save(std::string path) {
    std::ofstream hashFile;
    
    hashFile.open(path, std::ios::out);
    
    if (hashFile.is_open()) {
        std::cout << "Saving hash table..." << std::endl;
        
        std::string key;
        std::string value1;
        
        for (auto it = hashTableRaw->begin(); it!=hashTableRaw->end(); it++) {
            int key = it->first;
            hashFile << "# " << key << std::endl;
            
            for (auto setit = it->second->begin(); setit != it->second->end(); setit++) {
                hashFile << setit->sequencePosition << " " << setit->i << " " << setit->r << std::endl;
            }
        }
        std::cout << "Saved as \"" << path << "\"" << std::endl;
    }
    hashFile.close();
}


HashTable* HashTable::load(std::string path) {
    std::map<int, std::set<bioinformatics::Entry>*> *hashTable = new std::map<int,std::set<bioinformatics::Entry>*>();
    std::ifstream hashFile;
    
    hashFile.open(path, std::ios::in);
    std::string line;
    std::string key;
    if (hashFile.is_open()) {
        while (getline(hashFile, line)) {
            // if the first char of the string is a # -> it's a key
            if (line.at(0) == '#') {
                key = line.substr(2);
            } else {
                std::istringstream iss(line);
                std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                  std::istream_iterator<std::string>());
                
                bioinformatics::Entry entry;
                entry.sequencePosition = std::stoi(results[0]);
                entry.i = std::stoi(results[1]);
                entry.r = std::stoi(results[2]);

                std::map<int, std::set<bioinformatics::Entry>*>::iterator mapIt = hashTable->find(std::stoi(key));
                if (mapIt != hashTable->end()) {
                    std::set<bioinformatics::Entry>* entrySet = mapIt->second;
                    entrySet->insert(entry);
                } else {
                    std::set<Entry>* entrySet = new std::set<Entry>;
                    entrySet->insert(entry);
                    hashTable->insert(std::pair<int, std::set<bioinformatics::Entry>*>(std::stoi(key), entrySet));
                }
            }
        }
    }
    return new HashTable(hashTable);
}

HashTable* HashTable::loadWithM(std::string path, int m) {
    std::map<int, std::set<bioinformatics::Entry>*> *hashTable = new std::map<int,std::set<bioinformatics::Entry>*>();
    std::ifstream hashFile;
    
   hashFile.open(path, std::ios::in);
    std::string line;
    int key;
    if (hashFile.is_open()) {
        while (getline(hashFile, line)) {
            // if the first char of the string is a # -> it's a key
            if (line.at(0) == '#') {
                key = std::stoi(line.substr(2));
            } else {
                if (key > m) break;
                if (key != m) continue;
                
                std::istringstream iss(line);
                std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                  std::istream_iterator<std::string>());
                
                bioinformatics::Entry entry;
                
                entry.sequencePosition = std::stoi(results[0]);
                entry.i = std::stoi(results[1]);
                entry.r = std::stoi(results[2]);

                std::map<int, std::set<bioinformatics::Entry>*>::iterator mapIt = hashTable->find(key);
                if (mapIt != hashTable->end()) {
                    std::set<bioinformatics::Entry>* entrySet = mapIt->second;
                    entrySet->insert(entry);
                } else {
                    std::set<Entry>* entrySet = new std::set<Entry>;
                    entrySet->insert(entry);
                    hashTable->insert(std::pair<int, std::set<bioinformatics::Entry>*>(key, entrySet));
                }
            }
        }
    }
    return new HashTable(hashTable);
}

void HashTable::empty() {
    std::cout << "Deleting hash table from memory..." << std::endl;
    
    for (auto it = this->hashTableRaw->begin(); it != this->hashTableRaw->end(); it++) {
        delete it->second;
    }
    this->hashTableRaw->clear();
    
    std::cout << "Hash table deleted from memory" << std::endl;
}

std::map<int, std::set<bioinformatics::Entry>*>* HashTable::getHashTableRaw() {
    return this->hashTableRaw;
}

