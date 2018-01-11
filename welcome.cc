
#include <fstream>
#include <iostream>
#include <string>
#include "Stopwatch.h"
#include "FastADocument.h"
#include "HashTable.h"
#include "HashTableCalculationMethod.h"
#include "QueryMapper.h"

#define PROGRAM 1

using namespace bioinformatics;

//List of methods defined in this file
int main(int argc, char**argv);

//Method implementations

int main(int argc, char**argv) {
    
    #if PROGRAM == 1

    std::string document = argv[1];
    std::string hashDocumentName = argv[2];
    std::string queryDocument = argv[3];
    int w = std::stoi(argv[4]);
    int k = std::stoi(argv[5]);
   
    if (k > w) {
        return 1;
    }

    // Start stopwatch after user inputs the parameters
    Stopwatch stopwatch;
    stopwatch.start();
    
    // Calculate and save hash table
    FastADocument *fastADoc = new FastADocument(document);    
    HashTableCalculationMethod method;
    HashTable *hashTable = method.calculate(fastADoc, w, k);
    
    hashTable->save(hashDocumentName);
//    hashTable->empty();
//    delete hashTable;
    delete fastADoc;
    
    // Map query sequences to the hash table
    int const epsilon = 500;
    FastADocument *queryFastADoc = new FastADocument(queryDocument);
    QueryMapper queryMapper;
    
    BioSequence* querySequence;
    while ((querySequence = queryFastADoc->getNextSequence()) != NULL) {
        //queryMapper.mapQuerySequence(querySequence, w, k, epsilon);
        queryMapper.mapQuerySequence(hashTable,querySequence, w, k, epsilon);
        delete querySequence;
    }
    
    delete hashTable; //TODO: remove this line
    delete queryFastADoc;
    
    // test usporedbe
    // HashTable *load_test;
    // load_test = HashTable::load("hash_example");
    // load_test->save("usporedba");
        
    #elif PROGRAM == 2
    
        std::cout << " TODO " << std::endl;
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
            
    stopwatch.end();
    std::cout << "Time: " << stopwatch.getTime() << " ms" << std::endl;
    
    return 0;
}
