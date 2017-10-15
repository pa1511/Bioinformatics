/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stopwatch.h
 * Author: paf
 *
 * Created on October 15, 2017, 4:11 PM
 */

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <utility>

typedef std::chrono::high_resolution_clock::time_point Moment;

class Stopwatch {
public:
    Stopwatch();
    Stopwatch(const Stopwatch& orig);
    virtual ~Stopwatch();
    
    void start();
    void end();
    int getTime();    
    void reset();
    
    
private:    
    Moment now();
    Moment startMoment;
    Moment endMoment;
};

#endif /* STOPWATCH_H */

