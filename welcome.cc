
#include <iostream>
#include <fstream>
#include "Stopwatch.h"
#include "FastADocument.h"

using namespace bioinformatics;

//List of methods defined in this file
int main(int argc, char**argv);

char invert1(char c);
char invert2(char c);

void fastAExample();

//Method implementations

int main(int argc, char**argv) {

    Stopwatch stopwatch;
    stopwatch.start();
    
    fastAExample();
            
    stopwatch.end();
    std::cout << "Time: " << stopwatch.getTime() << " ms" << std::endl;
    
    return 0;
}

void Hello() {
    std::cout << "Hello, it's meeeeee";
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