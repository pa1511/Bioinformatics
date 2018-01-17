/*
 * File: QueryMapper.h
 * Author: papric
 *
 * Created on December 17, 2017, 11:46 AM
 */

#ifndef QUERYMAPPER_H
#define QUERYMAPPER_H

#include "HashTableCalculationMethod.h"
#include "HashTable.h"
#include "Document.h"
#include "BioSequence.h"
#include "Minimizer.h"
#include "PAF.h"
#include "PAF.h"
#include "ATuple.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace bioinformatics;

class QueryMapper {
public:
  /**
   * Constructor
   */
  QueryMapper();
  /**
   * Destructor
   */
  ~QueryMapper();

  /**
   * Maps query sequence against hash table containing target minimizers.
   * @param H - hash table containing target minimizers 
   * @param targetFastADoc - FastADoc object with target sequences
   * @param q - query sequence
   * @param output - PAF object that prints mapping results in PAF format
   * @param w - window size
   * @param k - k-mer size
   * @param epsilon
   */
  void mapQuerySequence(HashTable *H, Document *targetFastADoc, BioSequence *q,
      PAF *output, int w, int k, int epsilon);
  std::vector<ATuple>* lis(std::vector<ATuple>& array, int b, int e);
  /**
   * Tests if implemented LIS algorithm works right.
   * @param A - vector containing target minimizers for query sequence
   * @param b - start index
   * @param e - end index
   * @param ret - return vector
   */
  void lis_test(std::vector<ATuple>& A, int b, int e, std::vector<ATuple>& ret);
private:
  /**
   * Fills vector A with target minimizers from hash table that are on the same
   * strand as query minimizers.
   * @param queryMinimizerSet - set with minimizers from query sequence
   * @param hashTable - hash table containing target minimizers
   * @param A - vector containing target minimizers for query sequence
   */
  void fillASame(std::vector<Minimizer>& queryMinimizerSet,
        std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTable,
        std::vector<ATuple>& A);
  /**
   * Fills vector A with target minimizers from hash table that are not on
   * the same strand as query minimizers.
   * @param queryMinimizerSet - set with minimizers from query sequence
   * @param hashTable - hash table containing target minimizers
   * @param A - vector containing target minimizers for query sequence
   */
  void fillADiff(std::vector<Minimizer>& queryMinimizerSet,
        std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTable,
        std::vector<ATuple>& A);
};

#endif /* QUERYMAPPER_H */

