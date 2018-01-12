/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FastADocument.h
 * Author: paf
 *
 * Created on October 15, 2017, 10:20 PM
 */

#ifndef FASTADOCUMENT_H
#define FASTADOCUMENT_H

#include <fstream>
#include <vector>
#include "BioSequence.h"

namespace bioinformatics {
    
struct SequenceInfo {
    std::string name;
    int length;
};   

class FastADocument {
    public:
        FastADocument(std::string documentLocation);
        FastADocument(std::string documentLocation, bool saveSequenceDetails);
        ~FastADocument();

        std::string getDocumentName();
        BioSequence* getNextSequence();
        std::vector<bioinformatics::SequenceInfo>* getSequenceDetails();

    private:
        std::string document;
        std::ifstream *inputStream;
        int sequencePosition = 0;
        bool saveSequenceDetails;
        std::vector<bioinformatics::SequenceInfo> sequenceDetails;
};
}

#endif /* FASTADOCUMENT_H */

