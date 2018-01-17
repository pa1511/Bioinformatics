/*
 * File: HashTable.h
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
#include <set>

namespace bioinformatics {

#pragma pack(push, 1)

 /**
  * Data structure used for storing the result of a Minimizer id and the id of a sequence
  * @param sequencePosition - id of a sequence
  * @param i - position in the sequence
  */
struct Entry {
    std::uint16_t sequencePosition;
    int i;

    /**
     * Comparison operator implemented for comparing entries
     * @param other
     * @return 
     */
    bool operator<(const Entry& other) const {
      if (this->sequencePosition == other.sequencePosition) {
        return this->i < other.i;
      }
      return this->sequencePosition < other.sequencePosition;
    }
  };
#pragma pack(pop)

  class HashTable {
  public:
      /**
       * Constructor
       * @param hashTableRaw0
       * @param hashTableRaw1
       */
    HashTable(std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw0,
            std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw1);
    /**
     * Destructor
     */
    ~HashTable();
    /**
     * Empties a hash table
     */
    void empty();
    /**
     * 
     * @return HashTableRaw0
     */
    std::unordered_map<int, std::vector<bioinformatics::Entry>*>* getHashTableRaw0();
    /**
     * 
     * @return HashTableRaw1
     */
    std::unordered_map<int, std::vector<bioinformatics::Entry>*>* getHashTableRaw1();

    /**
     * Saves the hash table in a output file
     * @param path
     */
    void save(std::string path);
    
    /**
     * Creates a hash table with the values written in a file
     * @param path
     * @return 
     */
    static HashTable* load(std::string path);
    
    /**
     * Creates a hash table for a specific key
     * @param path
     * @param m
     * @return 
     */
    static HashTable* loadWithM(std::string path, int m);
  private:
    std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw0;
    std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTableRaw1;
  };
} // namespace bioinformatics

#endif /* HASHTABLE_H */

