/*
 * To change this license header,  choose License Headers in Project Properties.
 * To change this template file,  choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Document.h
 * Author: paf
 *
 * Created on January 17,  2018,  9:45 AM
 */

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <fstream>
#include <vector>
#include <string>
#include "BioSequence.h"
#include "SequenceInfo.h"

class Document {
 public:
    /**
     * Constructor
     * BioSequence details will not be stored
     * @param documentLocation - location of the document to be read
     */
    Document(std::string documentLocation);

    /**
     * Constructor
     * @param documentLocation - location of the document to be read
     * @param saveSequenceDetails - should sequence details be stored
     */
    Document(std::string documentLocation,  bool saveSequenceDetails);

    /**
     * Destructor
     */
    virtual ~Document();

    /**
     * Returns the document name
     */
    std::string getDocumentName();

    /**
     * Returns the next BioSequnce in the document if it exists.
     * If there is no more sequences the NULL is returned.
     * @return Next BioSequnce if it exists or <b>NULL</b> if it does not.
     */
    virtual bioinformatics::BioSequence* getNextSequence() = 0;

    /**
     * If the object was initialized to store sequence details then this will return a vector
     * containing them. If not it will return an empty vector. <br/>
     * @return
     */
    std::vector<bioinformatics::SequenceInfo>* getSequenceDetails();

 protected:
    std::string document;
    std::ifstream *inputStream;
    int sequencePosition = 0;
    bool saveSequenceDetails;
    std::vector<bioinformatics::SequenceInfo> sequenceDetails;
};

#endif /* DOCUMENT_H */

