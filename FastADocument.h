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
#include "SequenceInfo.h"

namespace bioinformatics {

/**
 * This class models a stream like FastADocument. <br/>
 * Stream like because sequences are read one by one sequentially and it 
 * is not possible to reread the same sequence multiple times. 
 * The class stores the document relevant data:
 * <ul>
 * <li> Document name </li>
 * <li> Details about BioSequences read from the document </li>
 * </ul>
 */
class FastADocument {
    public:
        /**
         * Constructor 
         * BioSequence details will not be stored
         * @param documentLocation - location of the document to be read
         */
        FastADocument(std::string documentLocation);
        
        /**
         * Constructor
         * @param documentLocation - location of the document to be read
         * @param saveSequenceDetails - should sequence details be stored
         */
        FastADocument(std::string documentLocation, bool saveSequenceDetails);
        
        /**
         * Destructor
         */
        ~FastADocument();

        /**
         * Returns the document name
         */
        std::string getDocumentName();
        
        /**
         * Returns the next BioSequnce in the document if it exists. 
         * If there is no more sequences the NULL is returned.
         * @return Next BioSequnce if it exists or <b>NULL</b> if it does not. 
         */
        BioSequence* getNextSequence();
        
        /**
         * If the object was initialized to store sequence details then this will return a vector
         * containing them. If not it will return an empty vector. <br/>
         * @return 
         */
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

