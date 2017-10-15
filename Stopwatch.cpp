/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stopwatch.cpp
 * Author: paf
 * 
 * Created on October 15, 2017, 4:11 PM
 */

#include "Stopwatch.h"

Stopwatch::Stopwatch() {
}

Stopwatch::Stopwatch(const Stopwatch& orig) {
}

Stopwatch::~Stopwatch() {
}

void Stopwatch::start(){
    this->startMoment = std::chrono::high_resolution_clock::now();
}

void Stopwatch::end(){
    this->endMoment = std::chrono::high_resolution_clock::now();
}

int Stopwatch::getTime(){
    return  std::chrono::duration_cast<std::chrono::microseconds>( endMoment - startMoment ).count();
}

void Stopwatch::reset(){
    Moment now = std::chrono::high_resolution_clock::now();
    this->startMoment = now;
    this->endMoment = now;
}