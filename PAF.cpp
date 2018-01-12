/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PAF.cpp
 * Author: paf
 * 
 * Created on November 5, 2017, 1:57 PM
 */

#include "PAF.h"

PAF::PAF() {
}

PAF::PAF(const PAF& orig) {
}

PAF::~PAF() {
}

void PAF::print(BioSequence *query, FastADocument *target, int targetSeqPos) {
    auto sequenceInfo = target->getSequenceDetails()->at(targetSeqPos);
    std::printf("%s\t%d\t%s\t%d\n", query->getName().c_str(), query->size(),
            sequenceInfo.name.c_str(), sequenceInfo.length);
}


