
#include <iostream>
#include "SimpleClass.h"

//List of methods defined in this file
int main(int argc, char**argv);

void example1();
SimpleClass createSimpleClassObject1();
SimpleClass* createSimpleClassObject2();
SimpleClass& createSimpleClassObject3();



//Method implementations

int main(int argc, char**argv) {
    
    example1();
            
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

