/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File: HashTableCalculationMethod.h
 * Author: paf
 *
 * Created on November 5, 2017, 1:56 PM
 */

#ifndef HASHTABLECALCULATIONMETHOD_H
#define HASHTABLECALCULATIONMETHOD_H

#include "BioSequence.h"
#include "FastADocument.h"
#include "HashTable.h"
#include "Minimizer.h"
#include "SyncQueue.h"

#include <string>
#include <set>
#include <map>
#include <limits>
#include <algorithm>

#include <thread>
#include <functional>


using namespace bioinformatics;

/**
 * Data structure used for storing the result of a Minimizer set calculation. <br/>
 * This structure is used when using multy-threaded Minimizer set calculation.
 */
struct CalculateTaskResult {
    /**
     * "Set" containing all minimizer on the original sequence
     */
    std::vector<Minimizer>* minimizerSet0;
    /**
     * "Set" containing all minimizers on the inverse of the original sequence
     */
    std::vector<Minimizer>* minimizerSet1;
    /**
     * Index of the sequence from which the minimizer sets were calculated
     */
    int sequencePosition;
};


class HashTableCalculationMethod {
 public:
        HashTableCalculationMethod();
        ~HashTableCalculationMethod();

        /**
         * Calculates the HashTable which can be used for query mapping. <br/>
         * The HashTable is calculated using BioSequences in the provided
         * document and based on the given w and k parameters. <br/>
         * Calculation can be parallelized if a threadCount number larger then 1
         * is given to the method.  <br/>
         *
         * @param document - document from which the BioSequences are read
         * @param w - window size
         * @param k - k-mer size
         * @param threadCount - how many threads should work on calculating the HashTable
         * @return
         */
        HashTable* calculate(Document* document, int w, int k, int threadCount);

        /**
         * Calculates the minimizer sketch for the given BioSequence.
         * @param sequence - for which the sketch is calculated
         * @param w - window size
         * @param k - k-mer size
         * @param minimizerSet0 - minimizers for the original sequence
         * @param minimizerSet1 - minimizers for the invert of the original sequence
         */
        void minimizerSketch(bioinformatics::BioSequence *sequence, int w,
                int k, std::vector<Minimizer>& minimizerSet0,
                std::vector<Minimizer>& minimizerSet1
        );


 private:
        /**
         * Worker thread calculation task. <br/>
         * The worker will work until it receives a poison pill. <br/>
         * @param tasks - queue from which tasks are pulled
         * @param results - queue to which results are submitted
         * @param w - window size
         * @param k - k-mer size
         */
        void calculateTask(SyncQueue<BioSequence*>& tasks,
                SyncQueue<CalculateTaskResult>& results, int w, int k
        );

        /**
         * Fills hashTable with the given minimizers.
         * @param hashTable
         * @param minimizerSet
         * @param sequencePosition - sequence id for whichthe minimizers were calulated
         */
        void fillMap(std::unordered_map<int, std::vector<bioinformatics::Entry>*>* hashTable,
                std::vector<Minimizer>& minimizerSet, int sequencePosition);

        /**
         * Tries to reduce the size of vectors in the hashTable
         * @param hashTable0
         */
        inline void shrinkVectors(std::unordered_map<int, std::vector<bioinformatics::Entry>*>* hashTable0);
        /**
         * Removes duplicates from the given vector of minimizers to make it
         * "set" like.
         * @param M
         */
        inline void removeDuplicates(std::vector<Minimizer>& M);

          // == =
          // The next functions are used in Minimizer hash calculation

        /**
         * Calculates the hash of a sequence k-mer starting from
         * position startIndex
         * @param seqence - sequence containing the k-mer
         * @param startIndex - start position of the k-mer
         * @param k - k-mer size
         * @return k-mer hash value
         */
        int PHI_function(std::string *seqence, int startIndex, int k);
        inline int PHI_function(char b);
        /**
         * Applied when calculating the k-mer hash value to reduce the amount
         * of hash collisions when using them as map keys.
         * @param x - hash value
         * @param m - mask used in invertibleHash calculation
         * @return - new hash value
         */
        int invertibleHash(int x, int m);
          // == ==

          // Static structures used for calculation optimization
        static int PHI_VALUE[8];
        static int POW_4_VALUE[16];
        static int INV_HASH_MASK[16];
        static BioSequence* poison_pill;
};

#endif /* HASHTABLECALCULATIONMETHOD_H */

