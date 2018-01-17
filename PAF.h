/*
 * File:  PAF.h
 * Author: paf
 *
 * Created on November 5, 2017, 1:57 PM
 */

#ifndef PAF_H
#define PAF_H

#include "BioSequence.h"
#include "Document.h"
#include "SequenceInfo.h"
#include "ATuple.h"
#include <iostream>

using namespace bioinformatics;

/**
 * The class for printing the mapping results in PAF format.
 * @param k - k-mer size
 */
class PAF {
public:
  /**
   * Constructor
   * @param k k-mer size
   */
  PAF(int k);
  /**
   * Destructor
   */
  virtual ~PAF();
  /**
   * Prints information about mapping in PAF format.
   * @param query - query sequence
   * @param target - document with information about target sequences
   * @param startATuple - ATuple from where the mapping starts
   * @param endATuple - ATuple where mapping ends
   * @param minimizerCount - number of target minimizers in the mapping
   */
  void print(BioSequence *query, Document *target, ATuple *startATuple,
          ATuple *endATuple, int minimizerCount);
private:
  int k;
};

#endif /* PAF_H */

