/*
 * File: BioSequence.cpp
 * Author: paf
 *
 * Created on October 15, 2017, 10:35 PM
 */

#include "BioSequence.h"

using namespace bioinformatics;

char BioSequence::inversion[4] = {'T', 'G', 'A', 'C'};

BioSequence::BioSequence(std::string name, std::string comment,
        int seqPos) : name(name), comment(comment), sequencePosition(seqPos) {
}

BioSequence::~BioSequence() {
}

void BioSequence::initialize() {
  this->sequence = this->sequenceBuilder.str();
  this->inv_sequence = calculateInvertedSequence();
}

void BioSequence::setSequence(std::string sequence) {
  this->sequenceBuilder.clear();
  this->sequenceBuilder << sequence;
}

void BioSequence::appeandSequence(std::string sequence) {
  this->sequenceBuilder << sequence;
}

std::string BioSequence::getName() {
  return this->name;
}

std::string BioSequence::getComment() {
  return this->comment;
}

int BioSequence::size() {
  return this->sequence.size();
}

std::string* BioSequence::getSequence() {
  return &this->sequence;
}

std::string* BioSequence::getInvertedSequence() {
  return &this->inv_sequence;
}

int BioSequence::getSequencePosition() {
  return this->sequencePosition;
}

std::string BioSequence::calculateInvertedSequence() {
  // create a copy of the sequence
  std::string inverted(this->sequence.size(), '0');

  // change sequence bases
  for (int i = 0, size = inverted.size(); i < size; i++) {
    char c = this->sequence[size - i - 1];
    inverted[i] = this->invert(c);
  }

  return inverted;
}

inline char BioSequence::invert(char c) {
  // if (c == 'A') {
  //     c = 'T';
  // } else if (c == 'C') {
  //     c = 'G';
  // } else if (c == 'G') {
  //     c = 'C';
  // } else if (c == 'T') {
  //     c = 'A';
  // }
  //
  // return c;

  // Faster inversion will not work if any other character appears

  // A 0x41  0100 0001  0
  // C 0x43  0100 0011  1
  // G 0x47  0100 0111  3
  // T 0x54  0101 0100  2
  // mask    0000 0110

  //  Faster inversion 1
  //  char mask = (0x2 ^ c) & 0x2;
  //  mask = 0x4 | (mask << 3) | (mask >> 1);
  //  c = c ^ mask;
  //  return c;


  // Faster inversion 2
  int id = (c & 0x6) >> 1;
  return BioSequence::inversion[id];
}
