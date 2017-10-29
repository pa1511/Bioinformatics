/* 
 * File:   BioSequence.h
 * Author: paf
 *
 * Created on October 15, 2017, 10:35 PM
 */

#ifndef BIOSEQUENCE_H
#define BIOSEQUENCE_H

#include <string>

namespace bioinformatics{

    class BioSequence {
    public:
        BioSequence(std::string name,std::string comment);
        BioSequence(const BioSequence& orig);
        ~BioSequence();
        
        void setSequence(std::string sequence);

        std::string getName();
        std::string getComment();
        int size();
        std::string getSequence();
        std::string getInvertedSequence();
        
        
    private:
        
        std::string calculateInvertedSequence();
        
        std::string name;
        std::string comment;
        std::string sequence;
        std::string inv_sequence;
        
    };
}
#endif /* BIOSEQUENCE_H */

