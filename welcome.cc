
#include <fstream>
#include <iostream>
#include <string>
#include "Stopwatch.h"
#include "FastADocument.h"
#include "HashTable.h"
#include "HashTableCalculationMethod.h"
#include "QueryMapper.h"
#include "PAF.h"

#define PROGRAM 1

using namespace bioinformatics;

// List of methods defined in this file
int main(int argc, char**argv);

// Method implementations
int main(int argc, char**argv) {
    
    #if PROGRAM == 1

    std::string document = argv[1];
    std::string queryDocument = argv[2];
    int w = std::stoi(argv[3]);
    int k = std::stoi(argv[4]);
    int threadCount = std::stoi(argv[5]);
    if(threadCount<0)
        threadCount = std::thread::hardware_concurrency();
  
    // Start stopwatch after user inputs the parameters
    Stopwatch stopwatch;
    stopwatch.start();
    
    // Calculate and save hash table
    FastADocument *targetFastADoc = new FastADocument(document, true);    
    HashTableCalculationMethod method;
    HashTable *hashTable = method.calculate(targetFastADoc, w, k, threadCount);
        
    // Map query sequences to the hash table    
    int const epsilon = 500;
    FastADocument *queryFastADoc = new FastADocument(queryDocument);
    QueryMapper queryMapper;
    PAF *output = new PAF(k);
    
    // std::cout << "Started quering..." << std::endl;
    BioSequence* querySequence;
    while ((querySequence = queryFastADoc->getNextSequence()) != NULL) {
        queryMapper.mapQuerySequence(hashTable, targetFastADoc, querySequence, output, w, k, epsilon);
        delete querySequence;
    }
    
    delete queryFastADoc;
    delete hashTable;
    delete targetFastADoc;
    
    stopwatch.end();
    std::cout << "Time: " << stopwatch.getTime() << " ms" << std::endl;
        
    #elif PROGRAM == 2    
    std::string document = argv[1];
    FastADocument *fastADoc = new FastADocument(document);    
    BioSequence* sequence;
    
    std::ofstream hashFile;
    
    hashFile.open("copy.txt", std::ios::out);
    
    if (hashFile.is_open()) {

        while ((sequence = fastADoc->getNextSequence()) != NULL) {
            hashFile << ">" << (sequence->getSequencePosition()+1) << std::endl;
            hashFile << (*sequence->getSequence()) << std::endl;
            delete sequence;
        }
    
        hashFile.close();
    }
    delete fastADoc;
    #else

    std::string document("fasta-example");//"Lambda_reads.fasta"
    
    FastADocument *fastADoc = new FastADocument(document);
    BioSequence *sequence;
    while((sequence = fastADoc->getNextSequence())!=NULL){

        std::cout << "Sequence: " << sequence->getName() << std::endl;
        std::cout << "Comment: " << sequence->getComment() << std::endl;
        std::cout << "Sequence:  " << *sequence->getSequence() << std::endl;
        std::cout << "!Sequence: " << *sequence->getInvertedSequence() << std::endl;
        std::cout << std::endl;
        delete sequence;
    }    
    
    #endif
                
    return 0;
}
