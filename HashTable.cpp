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

#include "HashTable.h"

using namespace bioinformatics;

HashTable::HashTable(std::map<double,bioinformatics::Entry> *hashTableRaw):hashTableRaw(hashTableRaw){
    
}

HashTable::~HashTable() {
    delete hashTableRaw;
}

void HashTable::save(std::string path) {
    // TODO
}


HashTable* HashTable::load(std::string path) {

}

