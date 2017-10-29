/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CodeDump.h
 * Author: paf
 *
 * Created on October 29, 2017, 4:32 PM
 */

#ifndef CODEDUMP_H
#define CODEDUMP_H

#include "BioSequence.h"
#include <string>
#include <set>

struct minimizer{
    double m;
    int i;
    int r;
    
    bool operator <(const minimizer& other) const{
        //TODO: this needs to be implemented properly 
        //It is needed to place the structure in a set
        return this->m < other.m;
    }

};


class CodeDump {
public:
    CodeDump();
    CodeDump(const CodeDump& orig);
    ~CodeDump();
    
    std::string PI_function(bioinformatics::BioSequence* biosequence,int r);
    //
    int PHI_function(std::string seqence,int startIndex, int k);
    int PHI_function(char b);
    //
    int invertibleHash(int x, int p);
    //
    std::set<minimizer> minimizerSketch(bioinformatics::BioSequence sequence, int w, int k);
    
private:

};

#endif /* CODEDUMP_H */

