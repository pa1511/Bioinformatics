
#include <fstream>
#include <iostream>
#include <string>
#include "Stopwatch.h"
#include "FastADocument.h"

#define PROGRAM 1

using namespace bioinformatics;

//List of methods defined in this file
int main(int argc, char**argv);

//Method implementations

int main(int argc, char**argv) {

    Stopwatch stopwatch;
    stopwatch.start();
    
    #if PROGRAM == 1
    
    std::cout << "Please enter document name: " ;
    std::string document;//("Lambda_reads.fasta");
    std::cin >> document;
    
    std::cout << "FastA example" << std::endl;
    FastADocument fastADoc(document);
    std::cout << "Document: " << fastADoc.getDocumentName() << std::endl;
    std::cout << std::endl;
    
    BioSequence *sequence;
    while((sequence = fastADoc.getNextSequence())!=NULL){
        
        std::cout << "Sequence: " << sequence->getName() << std::endl;
        std::cout << "Comment: " << sequence->getComment() << std::endl;
        std::cout << "Sequence:  " << sequence->getSequence() << std::endl;
        std::cout << "!Sequence: " << sequence->getInvertedSequence() << std::endl;
        std::cout << std::endl;
        delete sequence;
    }
    
    #elif PROGRAM == 2
    
        std::cout << " TODO " << std::endl;
        
    #endif
            
    stopwatch.end();
    std::cout << "Time: " << stopwatch.getTime() << " ms" << std::endl;
    
    return 0;
}