
#include <fstream>
#include <iostream>
#include <string>
#include "Stopwatch.h"
#include "FastADocument.h"
#include "FastQDocument.h"
#include "Document.h"
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
    Document *targetDoc = new FastADocument(document, true);    
    HashTableCalculationMethod method;
    HashTable *hashTable = method.calculate(targetDoc, w, k, threadCount);
        
    // Map query sequences to the hash table    
    int const epsilon = 1000;
    Document *queryDoc = new FastADocument(queryDocument);
    QueryMapper queryMapper;
    PAF *output = new PAF(k);
    
    // std::cout << "Started quering..." << std::endl;
    BioSequence* querySequence;
    while ((querySequence = queryDoc->getNextSequence()) != NULL) {
        queryMapper.mapQuerySequence(hashTable, targetDoc, querySequence, output, w, k, epsilon);
        delete querySequence;
    }
    
    delete queryDoc;
    delete hashTable;
    delete targetDoc;
    
    stopwatch.end();
    std::cout << "Time: " << stopwatch.getTime() << " ms" << std::endl;
        
    #elif PROGRAM == 2    
    std::string document = "lambda_reference.fasta";
    Document *fastADoc = new FastADocument(document);    
    BioSequence* sequence;
    
    std::ofstream hashFile;
    
    hashFile.open("copy.txt", std::ios::out);
    
    if (hashFile.is_open()) {

        while ((sequence = fastADoc->getNextSequence()) != NULL) {
            hashFile << ">" << (sequence->getSequencePosition()+1) << std::endl;
            hashFile << (sequence->getSequence()->substr(466,3592-466)) << std::endl;

            hashFile << (sequence->getSequence()->substr(45787,48191-45787)) << std::endl;
            delete sequence;
        }
    
        hashFile.close();
    }
    delete fastADoc;
    #elif PROGRAM == 3    
    std::string document = "example.fastq";
    Document *fastQDoc = new FastQDocument(document);    
    BioSequence* sequence;
    
    while ((sequence = fastQDoc->getNextSequence()) != NULL) {
        std::cout << "Sequence: " << sequence->getName() << std::endl;
        std::cout << *sequence->getSequence() << std::endl;
        std::cout << *sequence->getInvertedSequence() << std::endl;

        delete sequence;
    }
    
    delete fastQDoc;

    #else

    std::string document("fasta-example");//"Lambda_reads.fasta"
    
    Document *fastADoc = new FastADocument(document);
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
