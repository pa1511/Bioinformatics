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

namespace bioinformatics{

    class FastADocument {
    public:
        FastADocument(std::string documentLocation);
        FastADocument(const FastADocument& orig);
        ~FastADocument();
        void initialize();
        
        std::string getDocumentName();
        int getSequenceCount();
        void addSequence(BioSequence *sequence);

        BioSequence* getSequence(int i);
        
    private:
        std::string document;
        std::vector<BioSequence*> sequences;
    };

}

#endif /* FASTADOCUMENT_H */

