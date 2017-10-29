/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CodeDump.cpp
 * Author: paf
 * 
 * Created on October 29, 2017, 4:32 PM
 */

#include <math.h>
#include <limits.h>
#include <algorithm>

#include "CodeDump.h"

CodeDump::CodeDump() {
}

CodeDump::CodeDump(const CodeDump& orig) {
}

CodeDump::~CodeDump() {
}

std::string CodeDump::PI_function(bioinformatics::BioSequence* biosequence, int r) {
    if(r==0)
        return biosequence->getSequence();
    
    if(r==1)
        return biosequence->getInvertedSequence();
    
    throw "r was different from 0 and 1";
}

int CodeDump::PHI_function(std::string seqence, int startIndex, int k) {

    int hashValue = 0;
    
    for(int i=0; i<k; i++){
        hashValue += powf(4.0,k-i-1)*PHI_function(seqence[startIndex+i]);
    }
    
    return hashValue;
}

int CodeDump::PHI_function(char b) {

    if(b=='A')
        return 0;
    if(b=='C')
        return 1;
    if(b=='G')
        return 2;
    if(b=='T')
        return 3;
    
    //TODO: what if it is some other value
    throw "Unknown b";
}

//ALGORITHM 2
int CodeDump::invertibleHash(int x, int p) {

    int m = 0x1 << p -1;
    x = (~x +(x<<21)) & m;
    x = x^x>>24;
    x = (x+(x<<3)+(x<<8)) & m;
    x = x^x>>28;
    x = (x+(x<<31)) & m;
    
    return x;
}

//ALGORITHM 1
std::set<minimizer> CodeDump::minimizerSketch(bioinformatics::BioSequence sequence, int w, int k) {

    std::set<minimizer> M;
    
    std::string raw_sequence = sequence.getSequence();
    std::string raw_inv_sequence = sequence.getInvertedSequence();
    
    for(int i=1,limit = sequence.size()-w-k+1; i<limit; i++){
        double m  = std::numeric_limits<double>::max();
        for(int j=0; j<w-1;j++){
            double u = PHI_function(raw_sequence,i+j,k);
            double v = PHI_function(raw_inv_sequence,i+j,k);
            
            if(u!=v){
                m = std::min(m,std::min(u,v)); 
            }
        }
        
        for(int j=0; j<w-1; j++){
            double u = PHI_function(raw_sequence,i+j,k);
            double v = PHI_function(raw_inv_sequence,i+j,k);

            if(u<v && u == m){
                minimizer min;
                min.m = m;
                min.i = i+j;
                min.r = 0;
                
                M.insert(min);
            }
            else if(v<u && v == m){
                minimizer min;
                min.m = m;
                min.i = i+j;
                min.r = 1;
                
                M.insert(min);
            }
        }
    }
    
    return M;
}


