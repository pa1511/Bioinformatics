/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FastQDocument.cpp
 * Author: paf
 * 
 * Created on January 17, 2018, 10:00 AM
 */

#include "FastQDocument.h"
#include "BioSequence.h"

#include <string>
#include <cctype>
#include <iostream>


using namespace bioinformatics;

FastQDocument::FastQDocument(std::string documentLocation) : Document(documentLocation){
}

FastQDocument::FastQDocument(std::string documentLocation, bool saveSequenceDetails)
                            : Document(documentLocation,saveSequenceDetails) {
    
}

FastQDocument::~FastQDocument() {
}

/**
 * 
 * @return Pointer to BioSequence if it can be read or NULL
 */
BioSequence* FastQDocument::getNextSequence() {
    BioSequence *sequence = NULL;
    
    if (inputStream->is_open()) {
        
        char c;
        std::string input;
        
        while ((c = inputStream->peek()) != EOF) {
            
            // we see the start of the next sequence
            if (c == '@' && sequence != NULL) {
                break;
            }
            // read line
            std::getline(*inputStream, input);
            
            if (c == '@') {      
                std::string name;
                std::string comment;
                
                input.erase(input.begin());
                std::size_t firstEmptySpacePosition = input.find(" ");
                if (firstEmptySpacePosition != std::string::npos) {
                    name = input.substr(0, firstEmptySpacePosition);
                    comment = input.substr(firstEmptySpacePosition);
                } else {
                    name = input;
                }
                    
                sequence = new BioSequence(name, comment, this->sequencePosition);
                        
                this->sequencePosition++;
                
            } else if (c == '+') {
                continue;
            }else {
                
                if (input.find("!")!=std::string::npos || 
                        input.find("'")!=std::string::npos ||
                        input.find("*")!=std::string::npos ||
                        input.find("(")!=std::string::npos ||
                        input.find("+")!=std::string::npos ||
                        input.find("1")!=std::string::npos){
                    //quality strings are ignored because they are not used in the application
                }
                else{
                    sequence->appeandSequence(input);
                }
                
            }
        }      
    }
    
    if (sequence != NULL) {
        sequence->initialize();
        if (this->saveSequenceDetails) {
            SequenceInfo sequenceInfo;
            sequenceInfo.name = sequence->getName();
            sequenceInfo.length = sequence->size();
            this->sequenceDetails.push_back(sequenceInfo);
        }
    }
    
    return sequence;
}

