/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleClass.h
 * Author: paf
 *
 * Created on October 15, 2017, 12:48 PM
 */

#ifndef SIMPLECLASS_H
#define SIMPLECLASS_H

#include <iostream>

class SimpleClass {
public:
    /*
     *This is the default object constructor 
     */
    SimpleClass(int id);
       
    /*
     * This is a object copy constructor. 
     * It is used when cpp decides it needs to create a copy or clone of a object. 
     */
    SimpleClass(const SimpleClass& orig);
    virtual ~SimpleClass();
private:
    int id;
};

#endif /* SIMPLECLASS_H */

