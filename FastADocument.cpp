
/* 
 * File:   FastADocument.cpp
 * Author: paf
 * 
 * Created on October 15, 2017, 10:20 PM
 */

#include <string>
#include <cctype>

#include "FastADocument.h"
#include "BioSequence.h"

using namespace bioinformatics;

FastADocument::FastADocument(std::string documentLocation):document(documentLocation), saveSequenceDetails(false) {
    inputStream = new std::ifstream();
    inputStream->open(this->document);
}

FastADocument::FastADocument(std::string documentLocation, bool saveSequenceDetails)
                            :document(documentLocation), saveSequenceDetails(saveSequenceDetails) {
    inputStream = new std::ifstream();
    inputStream->open(this->document);
}

FastADocument::~FastADocument() {
    inputStream->close();
    delete inputStream;
}

std::string FastADocument::getDocumentName() {
    return this->document;
}

std::vector<bioinformatics::SequenceInfo>* FastADocument::getSequenceDetails() {
    return &this->sequenceDetails;
}

/**
 * 
 * @return Pointer to BioSequence if it can be read or NULL
 */
BioSequence* FastADocument::getNextSequence() {
    BioSequence *sequence = NULL;
    std::string name;
    std::string comment;
    
    if (inputStream->is_open()) {
        
        char c;
        std::string input;
        
        while ((c = inputStream->peek()) != EOF) {
            
            //we see the start of the next sequence
            if (c == '>' && sequence != NULL) {
                break;
            }
            //read line
            std::getline(*inputStream, input);
            
            if (c == '>') {               
                std::size_t firstEmptySpacePosition = input.find(" ");
                if (firstEmptySpacePosition != std::string::npos) {
                    name = input.substr(0, firstEmptySpacePosition);
                    comment = input.substr(firstEmptySpacePosition);
                } else {
                    name = input;
                }
                    
                sequence = new BioSequence(name, comment, this->sequencePosition);
                        
                this->sequencePosition++;
                
            } else if (c == ',') {
                continue;
            } else {
                sequence->appeandSequence(input);
            }
        }      
    }
    
    if (sequence != NULL) {
        sequence->initialize();
        if (this->saveSequenceDetails) {
            SequenceInfo sequenceInfo;
            sequenceInfo.name = name;
            sequenceInfo.length = sequence->size();
            this->sequenceDetails.push_back(sequenceInfo);
        }
    }
    
    return sequence;
}
