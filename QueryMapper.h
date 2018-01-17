/*
 * To change this license header,  choose License Headers in Project Properties.
 * To change this template file,  choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   QueryMapper.h
 * Author: papric
 *
 * Created on December 17,  2017,  11:46 AM
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
        QueryMapper();
        ~QueryMapper();

        void mapQuerySequence(HashTable *H,  Document *targetFastADoc,  BioSequence *q,  PAF *output,  int w,  int k,  int epsilon);
        std::vector<ATuple>* lis(std::vector<ATuple>& array,  int b,  int e);
        void lis_test(std::vector<ATuple>& A,  int b,  int e,  std::vector<ATuple>& ret);
 private:
        void fillASame(std::vector<Minimizer>& queryMinimizerSet,  std::unordered_map<int,  std::vector<bioinformatics::Entry>*> * hashTable,  std::vector<ATuple>& A);
        void fillADiff(std::vector<Minimizer>& queryMinimizerSet,  std::unordered_map<int,  std::vector<bioinformatics::Entry>*> * hashTable,  std::vector<ATuple>& A);
};

#endif /* QUERYMAPPER_H */

