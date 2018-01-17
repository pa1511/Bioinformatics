/*
 * To change this license header,  choose License Headers in Project Properties.
 * To change this template file,  choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   HashTable.cpp
 * Author: lucy
 *
 * Created on November 5,  2017,  12:13 PM
 */

#include "HashTable.h"
#include <set>

using namespace bioinformatics;

HashTable::HashTable(std::unordered_map<int,  std::vector<bioinformatics::Entry>*> *hashTableRaw0,
        std::unordered_map<int,  std::vector<bioinformatics::Entry>*> *hashTableRaw1):hashTableRaw0(hashTableRaw0), hashTableRaw1(hashTableRaw1) {
}

HashTable::~HashTable() {
    for (auto it = this->hashTableRaw0->begin(); it  !=  this->hashTableRaw0->end(); it++) {
        delete it->second;
    }
    delete hashTableRaw0;

    for (auto it = this->hashTableRaw1->begin(); it  !=  this->hashTableRaw1->end(); it++) {
        delete it->second;
    }
    delete hashTableRaw1;
}

void HashTable::empty() {
    for (auto it = this->hashTableRaw0->begin(); it  !=  this->hashTableRaw0->end(); it++) {
        delete it->second;
    }
    this->hashTableRaw0->clear();

    for (auto it = this->hashTableRaw1->begin(); it  !=  this->hashTableRaw1->end(); it++) {
        delete it->second;
    }
    this->hashTableRaw1->clear();
}

std::unordered_map<int,  std::vector<bioinformatics::Entry>*>* HashTable::getHashTableRaw0() {
    return this->hashTableRaw0;
}

std::unordered_map<int,  std::vector<bioinformatics::Entry>*>* HashTable::getHashTableRaw1() {
    return this->hashTableRaw1;
}

void HashTable::save(std::string path) {
    std::ofstream hashFile;

    hashFile.open(path,  std::ios::out);

    if (hashFile.is_open()) {
        std::cout << "Saving hash table..." << std::endl;

        std::set<int> keys;
        for (auto it = hashTableRaw0->begin(); it != hashTableRaw0->end(); it++) {
            keys.insert(it->first);
        }
        for (auto it = hashTableRaw1->begin(); it != hashTableRaw1->end(); it++) {
            keys.insert(it->first);
        }


        for (auto it = keys.begin(); it != keys.end(); it++) {
            int key = *it;
            hashFile << "# " << key << std::endl;

            auto h0It = this->hashTableRaw0->find(key);
            if (h0It != this->hashTableRaw0->end()) {
                for (auto setit = h0It->second->begin(); setit  !=  h0It->second->end(); setit++) {
                    hashFile << ((int)setit->sequencePosition) << " " << setit->i << " " << 0 << std::endl;
                }
            }

            auto h1It = this->hashTableRaw1->find(key);
            if (h1It != this->hashTableRaw1->end()) {
                for (auto setit = h1It->second->begin(); setit  !=  h1It->second->end(); setit++) {
                    hashFile << ((int)setit->sequencePosition) << " " << setit->i << " " << 1 << std::endl;
                }
            }
        }
        std::cout << "Saved as \"" << path << "\"" << std::endl;
    }
    hashFile.close();
}


HashTable* HashTable::load(std::string path) {
    std::unordered_map<int,  std::vector<bioinformatics::Entry>*> *hashTable0 = new std::unordered_map<int, std::vector<bioinformatics::Entry>*>();
    std::unordered_map<int,  std::vector<bioinformatics::Entry>*> *hashTable1 = new std::unordered_map<int, std::vector<bioinformatics::Entry>*>();

    std::ifstream hashFile;

    hashFile.open(path,  std::ios::in);
    std::string line;
    std::string key;
    if (hashFile.is_open()) {
        while (getline(hashFile,  line)) {
              //  if the first char of the string is a # -> it's a key
            if (line.at(0)  ==  '#') {
                key = line.substr(2);
            } else {
                std::istringstream iss(line);
                std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                  std::istream_iterator<std::string>());

                bioinformatics::Entry entry;
                entry.sequencePosition = std::stoi(results[0]);
                entry.i = std::stoi(results[1]);
                int r = std::stoi(results[2]);

                if (r == 0) {
                    std::unordered_map<int,  std::vector<bioinformatics::Entry>*>::iterator mapIt = hashTable0->find(std::stoi(key));
                    std::vector<bioinformatics::Entry>* entrySet;
                    if (mapIt  !=  hashTable0->end()) {
                        entrySet = mapIt->second;
                    } else {
                        entrySet = new std::vector<Entry>;
                        hashTable0->insert(std::pair<int,  std::vector<bioinformatics::Entry>*>(std::stoi(key),  entrySet));
                    }
                    entrySet->push_back(entry);
                } else {
                    std::unordered_map<int,  std::vector<bioinformatics::Entry>*>::iterator mapIt = hashTable1->find(std::stoi(key));
                    std::vector<bioinformatics::Entry>* entrySet;
                    if (mapIt  !=  hashTable1->end()) {
                        entrySet = mapIt->second;
                    } else {
                        entrySet = new std::vector<Entry>;
                        hashTable1->insert(std::pair<int,  std::vector<bioinformatics::Entry>*>(std::stoi(key),  entrySet));
                    }
                    entrySet->push_back(entry);
                }
            }
        }
    }
    return new HashTable(hashTable0,  hashTable1);
}

HashTable* HashTable::loadWithM(std::string path,  int m) {
    std::unordered_map<int,  std::vector<bioinformatics::Entry>*> *hashTable0 = new std::unordered_map<int, std::vector<bioinformatics::Entry>*>();
    std::unordered_map<int,  std::vector<bioinformatics::Entry>*> *hashTable1 = new std::unordered_map<int, std::vector<bioinformatics::Entry>*>();

    std::ifstream hashFile;

    hashFile.open(path,  std::ios::in);
    std::string line;
    int key;
    if (hashFile.is_open()) {
        while (getline(hashFile,  line)) {
            //  if the first char of the string is a # -> it's a key
                    if (line.at(0)  ==  '#') {
                        key = std::stoi(line.substr(2));
            } else {
                if (key > m) break;
                if (key  !=  m) continue;

                std::istringstream iss(line);
                std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                      std::istream_iterator<std::string>());

                bioinformatics::Entry entry;

                entry.sequencePosition = std::stoi(results[0]);
                entry.i = std::stoi(results[1]);
                int r = std::stoi(results[2]);

                if (r == 0) {
                    std::unordered_map<int,  std::vector<bioinformatics::Entry>*>::iterator mapIt = hashTable0->find(key);
                    std::vector<bioinformatics::Entry>* entrySet;
                    if (mapIt  !=  hashTable0->end()) {
                        entrySet = mapIt->second;
                    } else {
                        entrySet = new std::vector<Entry>;
                        hashTable0->insert(std::pair<int,  std::vector<bioinformatics::Entry>*>(key,  entrySet));
                    }
                    entrySet->push_back(entry);
                } else {
                    std::unordered_map<int,  std::vector<bioinformatics::Entry>*>::iterator mapIt = hashTable1->find(key);
                    std::vector<bioinformatics::Entry>* entrySet;
                    if (mapIt  !=  hashTable1->end()) {
                        entrySet = mapIt->second;
                    } else {
                        entrySet = new std::vector<Entry>;
                        hashTable1->insert(std::pair<int,  std::vector<bioinformatics::Entry>*>(key,  entrySet));
                    }
                    entrySet->push_back(entry);
                }
            }
        }
    }
    return new HashTable(hashTable0,  hashTable1);
}
