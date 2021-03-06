/*
 * File:   PAF.cpp
 * Author: paf
 *
 * Created on November 5, 2017, 1:57 PM
 */

#include "PAF.h"

PAF::PAF(int k) : k(k) {
}

PAF::~PAF() {
}

void PAF::print(BioSequence *query, Document *target,
        ATuple *startATuple, ATuple *endATuple, int minimizerCount) {

  int targetSeqPos = startATuple->t;
  auto targetSeq = target->getSequenceDetails()->at(targetSeqPos);

  int targetStartCoord = startATuple->i;
  int targetEndCoord = endATuple->i + this->k;

  // ‘+’ if query and target on the same strand; ‘–’ if opposite
  char sameOrOppositeStrand;

  int queryStartCoord;
  int queryEndCoord;

  if (startATuple->r == 0) {
    sameOrOppositeStrand = '+';
    queryStartCoord = startATuple->c + targetStartCoord;
    queryEndCoord = endATuple->c + targetEndCoord;
  } else {
    sameOrOppositeStrand = '-';
    queryStartCoord = startATuple->c - targetStartCoord;
    queryEndCoord = endATuple->c - targetEndCoord;
  }

  int matchingBases = minimizerCount * this->k;
  int totalNumberOfBases = std::max(queryEndCoord - queryStartCoord,
          targetEndCoord - targetStartCoord);
  int mappingQuality = 255;

  std::printf("%s\t%d\t%d\t%d\t%c\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
          query->getName().c_str(), query->size(),
          queryStartCoord, queryEndCoord,
          sameOrOppositeStrand,
          targetSeq.name.c_str(), targetSeq.length,
          targetStartCoord, targetEndCoord,
          matchingBases, totalNumberOfBases, mappingQuality
          );
}


