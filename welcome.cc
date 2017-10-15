
#include <iostream>
#include "SimpleClass.h"

int main(int argc, char**argv) {
    
    SimpleClass objectOnStack;
    SimpleClass *objectOnHeap = new SimpleClass();
    
    
    //notice you don't need to delete objects on stack
    delete objectOnHeap;
    
    return 0;
}
