/*
 * To change this license header,  choose License Headers in Project Properties.
 * To change this template file,  choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Document.cpp
 * Author: paf
 *
 * Created on January 17,  2018,  9:45 AM
 */

#include "Document.h"

using namespace bioinformatics;

Document::Document(std::string documentLocation)
                            :document(documentLocation),  saveSequenceDetails(false) {
    inputStream = new std::ifstream();
    inputStream->open(this->document);
}

Document::Document(std::string documentLocation,  bool saveSequenceDetails)
                            :document(documentLocation),  saveSequenceDetails(saveSequenceDetails) {
    inputStream = new std::ifstream();
    inputStream->open(this->document);
}

Document::~Document() {
    inputStream->close();
    delete inputStream;
}

std::string Document::getDocumentName() {
    return this->document;
}

std::vector<bioinformatics::SequenceInfo>* Document::getSequenceDetails() {
    return &this->sequenceDetails;
}

