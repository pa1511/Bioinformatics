
/* 
 * File:   FastADocument.cpp
 * Author: paf
 * 
 * Created on October 15, 2017, 10:20 PM
 */

#include <string>

#include "FastADocument.h"
#include "BioSequence.h"

using namespace bioinformatics;

FastADocument::FastADocument(std::string documentLocation):document(documentLocation) {
}

FastADocument::FastADocument(const FastADocument& orig) {
}

FastADocument::~FastADocument() {
    for (auto elem : sequences) {
        delete elem;
    }
    sequences.clear();
}

void FastADocument::initialize(){
    std::ifstream fileReader;
    fileReader.open(this->document);
    char c;
    if(fileReader.is_open()){
        std::string input;
        BioSequence *sequence = NULL;
        
        while(std::getline(fileReader,input)){
            const char c = input.at(0);
            if(c=='>'){
                if(sequence!=NULL){
                    this->addSequence(sequence);
                }
                
                std::string name;
                std::string comment;
                
                std::size_t firstEmptySpacePosition = input.find(" ");
                if (firstEmptySpacePosition!=std::string::npos){
                    name = input.substr(0,firstEmptySpacePosition);
                    comment = input.substr(firstEmptySpacePosition);
                }
                else{
                    name = input;
                }
                    
                sequence = new BioSequence(name,comment);
            }
            else if(c==','){
                continue;
            }
            else{
                sequence->setSequence(input);
            }
        }
        if(sequence!=NULL){
            this->addSequence(sequence);
        }
    }
    fileReader.close();

}

std::string FastADocument::getDocumentName(){
    return this->document;
}

void FastADocument::addSequence(BioSequence* sequence){
    this->sequences.push_back(sequence);
}

int FastADocument::getSequenceCount(){
    return this->sequences.size();
}

BioSequence* FastADocument::getSequence(int i){
    return this->sequences[i];
}
