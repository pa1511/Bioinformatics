
#include <iostream>
#include <fstream>
#include "SimpleClass.h"
#include "Stopwatch.h"

#define EXAMPLE 3

//List of methods defined in this file
int main(int argc, char**argv);

void example1();
SimpleClass createSimpleClassObject1();
SimpleClass* createSimpleClassObject2();
SimpleClass& createSimpleClassObject3();

void example2();
void doSomethingFancy1(SimpleClass object);

void example3();

//Method implementations

int main(int argc, char**argv) {

    Stopwatch stopwatch;
    stopwatch.start();
    
#if EXAMPLE == 1  
    example1();
#elif EXAMPLE == 2  
    example2();
#elif EXAMPLE == 3
    example3();
#else  
    std::cout << "Unknown example" << std::endl;  
#endif      
    
    stopwatch.end();
    std::cout << "Time: " << stopwatch.getTime() << " ms" << std::endl;
    
    return 0;
}

void example1(){
    //==============================================================
    //Basic object creation
    
    SimpleClass objectOnStack(1);
    SimpleClass *objectOnHeap = new SimpleClass(2);
    
    //notice you don't need to delete objects on stack
    delete objectOnHeap;
    
    //==============================================================
    std::cout << std::endl;
    //==============================================================
    //Getting objects from methods
    
    SimpleClass object1 = createSimpleClassObject1();
    SimpleClass *object2 = createSimpleClassObject2();
    SimpleClass& object3 = createSimpleClassObject3();
    std::cout << "Objects created" << std::endl;
    
    //Since this is on heap it still needs to be deleted
    delete object2;
    
    //==============================================================
    std::cout << std::endl;
    //==============================================================
    //Notice that in the end you have objects being destroyed
     
}


/*
 * The created object is either copied and returned or the compiler optimizes and directly creates the object
 * in the receiving memory space. 
 */
SimpleClass createSimpleClassObject1(){
    SimpleClass object(3);
    return object;
}

/*
 * This is basically what happens in Java/C#
 */
SimpleClass* createSimpleClassObject2() {
    return new SimpleClass(4);
}

/*
 * Don't do this. 
 * Notice in program output that this gets destroyed as soon as you exit the method.
 * Even before printing objects created.
 */
SimpleClass& createSimpleClassObject3(){
    SimpleClass object(5);
    return object;
}

//===========================================================================
void example2(){
    SimpleClass object(1);
    
    //Please notice that a call by value like this creates a copy of the object
    doSomethingFancy1(object);
    //The copy is destroyed when the method finishes
}

void doSomethingFancy1(SimpleClass object){
    std::cout << "I did something fancy"  << std::endl;
}

//===========================================================================
void example3(){
    
    std::string input;
    
    std::ifstream fileReader;
    fileReader.open("example-input.txt");
    if(fileReader.is_open()){
        while(std::getline(fileReader,input)){
            std::cout << input << std::endl;
        }
    }
    fileReader.close();
    std::cout << std::endl;

    

    fileReader.open("example-input.txt");
    char c;
    if(fileReader.is_open()){
        char c;
        while(!fileReader.eof()){
            fileReader >> c;
            std::cout << c << std::endl;
        }
    }
    fileReader.close();

    
}
