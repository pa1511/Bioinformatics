/*
 * To change this license header,  choose License Headers in Project Properties.
 * To change this template file,  choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   PAF.h
 * Author: paf
 *
 * Created on November 5,  2017,  1:57 PM
 */

#ifndef PAF_H
#define PAF_H

#include "BioSequence.h"
#include "Document.h"
#include "SequenceInfo.h"
#include "ATuple.h"
#include <iostream>

using namespace bioinformatics;

class PAF {
 public:
    PAF(int k);
    PAF(const PAF& orig);
    virtual ~PAF();
    void print(BioSequence *query,  Document *target,  ATuple *startATuple,  ATuple *endATuple,  int minimizerCount);
 private:
    int k;
};

#endif /* PAF_H */

