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
    std::string inverted(this->sequence);
    
    //reverse the sequence 
    std::reverse(inverted.begin(),inverted.end());
    
    //change sequence bases
    for(int i=0,limit=inverted.size();i<limit;i++){
        if(inverted[i]=='A'){
            inverted[i] = 'T';
        }
        else if(inverted[i]=='C'){
            inverted[i] = 'G';
        }
        else if(inverted[i]=='G'){
            inverted[i] = 'C';
        }
        else if(inverted[i]=='T'){
            inverted[i] = 'A';
        }
    }
        
    return inverted;
}
