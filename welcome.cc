
#include <iostream>
#include <fstream>
#include "Stopwatch.h"
#include "FastADocument.h"

using namespace bioinformatics;

//List of methods defined in this file
int main(int argc, char**argv);

char invert(char c);
void fastAExample();

//Method implementations

int main(int argc, char**argv) {

    //Stopwatch stopwatch;
    //stopwatch.start();
    //
    //fastAExample();
    //
    //stopwatch.end();
    //std::cout << "Time: " << stopwatch.getTime() << " ms" << std::endl;
    
    std::cout << invert('A') << std::endl;
    std::cout << invert('T') << std::endl;
    std::cout << invert('C') << std::endl;
    std::cout << invert('G') << std::endl;
    
    return 0;
}

char invert(char c) {

    char mask = (0x2 ^ c) & 0x2;
    mask = 0x4 | (mask<<3) | (mask>>1);
    c = c ^ mask;

    return c;
}

void fastAExample(){
    std::cout << "FastA example" << std::endl;
    FastADocument fastADoc("fasta-example");
    fastADoc.initialize();
    
    std::cout << "Document: " << fastADoc.getDocumentName() << std::endl;
    int count = fastADoc.getSequenceCount();
    std::cout << "Sequence count: " << count << std::endl;
        std::cout << std::endl;
    
    for(int i=0; i<count; i++){
        BioSequence *sequence = fastADoc.getSequence(i);
        
        std::cout << "Sequence: " << sequence->getName() << std::endl;
        std::cout << "Comment: " << sequence->getComment() << std::endl;
        std::cout << "Sequence:  " << sequence->getSequence() << std::endl;
        std::cout << "!Sequence: " << sequence->getInvertedSequence() << std::endl;
        std::cout << std::endl;
    }
    
}