/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FastQDocument.h
 * Author: paf
 *
 * Created on January 17, 2018, 10:00 AM
 */

#ifndef FASTQDOCUMENT_H
#define FASTQDOCUMENT_H


#include "BioSequence.h"
#include "Document.h"

namespace bioinformatics {

/**
 * This class models a stream like FastQDocument. <br/>
 * Stream like because sequences are read one by one sequentially and it 
 * is not possible to reread the same sequence multiple times. 
 * The class stores the document relevant data:
 * <ul>
 * <li> Document name </li>
 * <li> Details about BioSequences read from the document </li>
 * </ul>
 */
class FastQDocument : public Document {
    public:
        /**
         * Constructor 
         * BioSequence details will not be stored
         * @param documentLocation - location of the document to be read
         */
        FastQDocument(std::string documentLocation);
        
        /**
         * Constructor
         * @param documentLocation - location of the document to be read
         * @param saveSequenceDetails - should sequence details be stored
         */
        FastQDocument(std::string documentLocation, bool saveSequenceDetails);
        
        /**
         * Destructor
         */
        virtual ~FastQDocument();

        
        /**
         * Returns the next BioSequnce in the document if it exists. 
         * If there is no more sequences the NULL is returned.
         * @return Next BioSequnce if it exists or <b>NULL</b> if it does not. 
         */
        BioSequence* getNextSequence();
        
};
}

#endif /* FASTQDOCUMENT_H */

