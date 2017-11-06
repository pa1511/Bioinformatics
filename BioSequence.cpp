/* 
 * File:   BioSequence.cpp
 * Author: paf
 * 
 * Created on October 15, 2017, 10:35 PM
 */

#include <algorithm>

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
    this->inv_sequence = calculateInvertedSequence();
}

void BioSequence::appeandSequence(std::string sequence) {
    //TODO: this implementation might need to be changed!
    this->setSequence(sequence);
}


std::string BioSequence::getName(){
    return this->name;
}

std::string BioSequence::getComment(){
    return this->comment;
}

int BioSequence::size() {
    return this->sequence.size();
}

std::string BioSequence::getSequence(){
    return this->sequence;
}

std::string BioSequence::getInvertedSequence() {
    return this->inv_sequence;
}

std::string BioSequence::calculateInvertedSequence(){
    //create a copy of the sequence
    std::string inverted(this->sequence.size(),'0');
        
    //change sequence bases
    for(int i=0,size=inverted.size();i<size;i++){
        char c = this->sequence[size-i-1];
        inverted[i] = this->invert(c);
    }
        
    return inverted;
}

inline char BioSequence::invert(char c) {
//    if(c=='A'){
//        c = 'T';
//    }
//    else if(c=='C'){
//        c = 'G';
//    }
//    else if(c=='G'){
//        c = 'C';
//    }
//    else if(c=='T'){
//        c = 'A';
//    }
//
//    return c;

    char mask = (0x2 ^ c) & 0x2;
    mask = 0x4 | (mask<<3) | (mask>>1);
    c = c ^ mask;
    return c;
}
