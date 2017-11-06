/* 
 * File:   BioSequence.cpp
 * Author: paf
 * 
 * Created on October 15, 2017, 10:35 PM
 */

#include <algorithm>

#include "BioSequence.h"

using namespace bioinformatics;


char BioSequence::inversion[4] = {'T','G','A','C'};

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

std::string* BioSequence::getSequence(){
    return &this->sequence;
}

std::string* BioSequence::getInvertedSequence() {
    return &this->inv_sequence;
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

    // Faster inversion will not work if any other character appears
    
    // A 0x41   0100 0001   0
    // T 0x54   0101 0100   2
    // C 0x43   0100 0011   1
    // G 0x47   0100 0111   3
    // mask     0000 0110

//    faster inversion 1
//    char mask = (0x2 ^ c) & 0x2;
//    mask = 0x4 | (mask<<3) | (mask>>1);
//    c = c ^ mask;
//    return c;

    
//    faster inversion 2
    int id = (c & 0x6) >> 1;
    return BioSequence::inversion[id];
}
