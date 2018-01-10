/* 
 * File:   BioSequence.h
 * Author: paf
 *
 * Created on October 15, 2017, 10:35 PM
 */

#ifndef BIOSEQUENCE_H
#define BIOSEQUENCE_H

#include <string>
#include <sstream>
namespace bioinformatics {

class BioSequence {
    public:
        static char inversion[4];

        BioSequence(std::string name, std::string comment, int sequencePosition);
        ~BioSequence();

        void initialize();
        
        void setSequence(std::string sequence);
        void appeandSequence(std::string sequence);

        std::string getName();
        std::string getComment();
        int size();
        std::string *getSequence();
        std::string *getInvertedSequence();
        int getSequencePosition();

    private:
        std::string calculateInvertedSequence();
        inline char invert(char c);

        std::string name;
        std::string comment;
        std::stringstream sequenceBuilder;
        std::string sequence;
        std::string inv_sequence;   
        int sequencePosition;
}; 
}

#endif /* BIOSEQUENCE_H */

