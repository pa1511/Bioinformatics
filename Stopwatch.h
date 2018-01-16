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

/**
 * The class offers the functionality of a simple stopwatch for precise time measurements <br/>
 * The stopwatch has to be started using start, stopped using end and can be reset using reset. <br/>
 * The get the measured time (difference between stop end end time) the user can call getTime.  <br/>
 */
class Stopwatch {
public:

    /**
     * Constructor
     */
    Stopwatch();
    
    /**
     * Destructor
     */
    ~Stopwatch();
    
    /**
     * Starts the stopwatch or more precisely records the start time.  <br/>
     */
    void start();
    
    /**
     * Stops the stopwatch or more precisely records the end time. <br/>
     */
    void end();
    
    /**
     * Returns the measured time in milliseconds. <br/>
     * @return time in ms
     */
    int getTime();    
    
    /**
     * Resets the measured start and end time. <br/>
     */
    void reset();
    
    
private:    
    inline Moment now();
    Moment startMoment;
    Moment endMoment;
};

#endif /* STOPWATCH_H */

