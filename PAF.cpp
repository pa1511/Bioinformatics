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

PAF::PAF(int k):k(k) {
}

PAF::PAF(const PAF& orig) {
}

PAF::~PAF() {
}

void PAF::print(BioSequence *query, FastADocument *target, ATuple *startATuple, ATuple *endATuple, int minimizerCount) {
    int targetSeqPos = startATuple->t;
    auto targetSeq = target->getSequenceDetails()->at(targetSeqPos);
    
    char sameOrOppositeStrand; // ‘+’ if query and target on the same strand; ‘–’ if opposite
    int queryStartCoord;
    int queryEndCoord;
    
    if (startATuple->r == 0) {
        sameOrOppositeStrand = '+';
        queryStartCoord = startATuple->c + startATuple->i;
        queryEndCoord = endATuple->c + endATuple->i;
    } else {
        sameOrOppositeStrand = '-';
        queryStartCoord = startATuple->c - startATuple->i;
        queryEndCoord = endATuple->c - endATuple->i;
    }
    
    int targetStartCoord = startATuple->i;
    int targetEndCoord = endATuple->i;
    int matchingBases = minimizerCount * k;
    int totalNumberOfBases = std::max(queryEndCoord - queryStartCoord, targetEndCoord - targetStartCoord);
    int mappingQuality = 255; // TODO
    
    std::printf("%s\t%d\t%d\t%d\t%c\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
            query->getName().c_str(), query->size(), queryStartCoord, queryEndCoord,
            sameOrOppositeStrand,
            targetSeq.name.c_str(), targetSeq.length, targetStartCoord, targetEndCoord,
            matchingBases, totalNumberOfBases, mappingQuality
    );
}


