/*
 * File: QueryMapper.cpp
 * Author: papric
 *
 * Created on December 17,  2017,  11:46 AM
 */

#include "QueryMapper.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

using namespace bioinformatics;

QueryMapper::QueryMapper() {
}

QueryMapper::~QueryMapper() {
}

void QueryMapper::mapQuerySequence(HashTable *H, Document *targetFastADoc,
        BioSequence *q, PAF *output, int w, int k, int epsilon) {
  
  int const MATCHING_BASES_MIN_COUNT = 100;
  int const MIN_MAPPING_SUBSET_SIZE = 4;

  std::vector<ATuple> A;


  { // added block so Minimizers sets get removed from memory as soon as they
    // are no longer needed
    HashTableCalculationMethod method;
    std::vector<Minimizer> queryMinimizerSet0;
    std::vector<Minimizer> queryMinimizerSet1;
    
    method.minimizerSketch(q, w, k, queryMinimizerSet0, queryMinimizerSet1);

    auto hashTable0 = H->getHashTableRaw0();
    auto hashTable1 = H->getHashTableRaw1();

    fillASame(queryMinimizerSet0, hashTable0, A);
    fillADiff(queryMinimizerSet0, hashTable1, A);
    fillASame(queryMinimizerSet1, hashTable1, A);
    fillADiff(queryMinimizerSet1, hashTable0, A);
  }

  std::sort(A.begin(), A.end());
  std::vector<ATuple>lisC;

  int b = 0;
  for (int e = 0, size = A.size(); e < size; e++) {
    if ((e == size - 1) ||
            (A[e + 1].t != A[e].t) || (A[e + 1].r != A[e].r) ||
            (A[e + 1].c - A[e].c >= epsilon)) {
      if (e - b + 1 >= MIN_MAPPING_SUBSET_SIZE) {
        lis_test(A, b, e, lisC);

        int N = lisC.size();
        int matchingBases = N * k;

        if (N >= MIN_MAPPING_SUBSET_SIZE &&
                matchingBases >= MATCHING_BASES_MIN_COUNT) {
          output->print(q, targetFastADoc, &((lisC)[0]), &((lisC)[N - 1]), N);
        }

        lisC.clear();
      }

      b = e + 1;
    }
  }
}

void QueryMapper::fillASame(std::vector<Minimizer>& queryMinimizerSet,
        std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTable,
        std::vector<ATuple>& A) {
  
  ATuple tuple;
  for (auto qMsIt = queryMinimizerSet.begin(); qMsIt != queryMinimizerSet.end(); qMsIt++) {
    auto hashEntry = hashTable->find(qMsIt->m);

    if (hashEntry == hashTable->end()) {
      continue;
    }

    auto entrySet = hashEntry->second;

    for (auto entryIt = entrySet->begin(); entryIt != entrySet->end(); entryIt++) {
      tuple.t = entryIt->sequencePosition;
      tuple.r = 0;
      tuple.c = qMsIt->i - entryIt->i;
      tuple.i = entryIt->i;
      A.push_back(tuple);
    }
  }
}

void QueryMapper::fillADiff(std::vector<Minimizer>& queryMinimizerSet,
        std::unordered_map<int, std::vector<bioinformatics::Entry>*> *hashTable,
        std::vector<ATuple>& A) {

  ATuple tuple;
  for (auto qMsIt = queryMinimizerSet.begin(); qMsIt != queryMinimizerSet.end(); qMsIt++) {
    auto hashEntry = hashTable->find(qMsIt->m);

    if (hashEntry == hashTable->end()) {
      continue;
    }

    auto entrySet = hashEntry->second;

    for (auto entryIt = entrySet->begin(); entryIt != entrySet->end(); entryIt++) {
      tuple.t = entryIt->sequencePosition;
      tuple.r = 1;
      tuple.c = qMsIt->i + entryIt->i;
      tuple.i = entryIt->i;
      A.push_back(tuple);
    }
  }
}

void QueryMapper::lis_test(std::vector<ATuple>& A, int b, int e, std::vector<ATuple>& ret) {
  int N = e - b + 1;
  int P[N];
  int M[N + 1];

  int L = 0;
  ret.clear();
  for (int i = 0; i < N; i++) {
    //  Binary search for the largest positive j ≤ L
    //  such that X[M[j]] < X[i]
    int lo = 1;
    int hi = L;
    while (lo <= hi) {
      int mid = ceil((lo + hi) / 2);
      if (A[M[mid] + b].i < A[i + b].i) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    // After searching,  lo is 1 greater than the
    // length of the longest prefix of X[i]
    int newL = lo;

    // The predecessor of X[i] is the last index of
    // the subsequence of length newL-1
    P[i] = M[newL - 1];
    M[newL] = i;

    if (newL > L)
      // If we found a subsequence longer than any we've
      // found yet,  update L
      L = newL;
  }

  // Reconstruct the longest increasing subsequence
  int k = M[L];
  for (int i = L - 1; i >= 0; i--) {
    ret.insert(ret.begin(), A[k + b]);
    k = P[k];
  }
}

std::vector<ATuple>* QueryMapper::lis(std::vector<ATuple>& array, int b, int e) {
  std::vector<ATuple>* s0 = new std::vector<ATuple>();
  s0->push_back(array[b]);

  std::vector<std::vector<ATuple>*> solutions;
  solutions.push_back(s0);

  for (int i = b + 1; i <= e; i++) {
    ATuple elem = array[i];

    std::vector<ATuple>* longest_solution = solutions.back();
    ATuple last_max = longest_solution->back();

    if (last_max.i < elem.i) {
      std::vector<ATuple>* new_longest_solution =
              new std::vector<ATuple>(*longest_solution);

      new_longest_solution->push_back(elem);
      solutions.push_back(new_longest_solution);
    }

    for (auto solution = solutions.begin(); solution < solutions.end(); solution++) {
      int sol_size = (*solution)->size();

      ATuple last = (*solution)->at(sol_size - 1);

      if (sol_size == 1) {
        if (elem.i < last.i) {
          (*solution)->clear();
          (*solution)->push_back(elem);
        }
      } else {
        ATuple second_last = (*solution)->at(sol_size - 2);

        if (elem.i > second_last.i && elem.i < last.i) {
          (*solution)->clear();
          (*solution)->insert(
                  (*solution)->end(),
                  (*(solution - 1))->begin(),
                  (*(solution - 1))->end()
                  );
          (*solution)->push_back(elem);
        }
      }
    }
  }
  std::vector<ATuple>* solution = solutions.back();
  solutions.pop_back();

  // free memory
  while (!solutions.empty()) {
    std::vector<ATuple>* s = solutions.back();
    solutions.pop_back();
    delete s;
  }

  return solution;
}
