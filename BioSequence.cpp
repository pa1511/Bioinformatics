/* 
 * File:   BioSequence.cpp
 * Author: paf
 * 
 * Created on October 15, 2017, 10:35 PM
 */

#include "BioSequence.h"

using namespace bioinformatics;

BioSequence::BioSequence(std::string name,std::string comment):name(name),comment(comment) {
}

BioSequence::BioSequence(const BioSequence& orig) {
}

BioSequence::~BioSequence() {
}

void BioSequence::setSequence(std::string sequence){
    this->sequence = sequence;
}

std::string BioSequence::getName(){
    return this->name;
}

std::string BioSequence::getComment(){
    return this->comment;
}

std::string BioSequence::getSequence(){
    return this->sequence;
}