/* 
 * File:   SimpleClass.cpp
 * Author: paf
 * 
 * Created on October 15, 2017, 12:48 PM
 */

#include "SimpleClass.h"

SimpleClass::SimpleClass(int id) : id(id) {
    std::cout << "SimpleClass constructor execution " << this->id << std::endl; 
}

SimpleClass::SimpleClass(const SimpleClass& orig) {
    std::cout << "Creating a copy of " << orig.id << std::endl;
    this->id = orig.id +100;
}

SimpleClass::~SimpleClass() {
    std::cout << "Object destruction execution " << this->id << std::endl;
}

