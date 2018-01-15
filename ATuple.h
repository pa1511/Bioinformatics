/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ATuple.h
 * Author: papric
 *
 * Created on January 14, 2018, 4:56 PM
 */

#ifndef ATUPLE_H
#define ATUPLE_H

#pragma pack(push, 1)
struct ATuple {
    std::uint16_t t;
    std::uint8_t r;
    int c;
    int i;
    
    bool operator <(const ATuple& other) const {
        if (this->t == other.t) {
            if(this->r == other.r) {
                if (this->c == other.c) {
                    return this->i < other.i;
                }
                return this->c < other.c;
            }
            return this->r < other.r;
        }
        return this->t < other.t;
    }
          
    bool operator >(const ATuple& other) const {
        if (this->t == other.t) {
            if(this->r == other.r) {
                if (this->c == other.c) {
                    return this->i > other.i;
                }
                return this->c > other.c;
            }
            return this->r > other.r;
        }
        return this->t > other.t;
    }

    bool operator ==(const ATuple& other) const {
        return this->t == other.t && this->r == other.r && this->c == other.c && this->i==other.i;         
    }
    
    bool operator <=(const ATuple& other) const {
        return *this<other || *this==other;
    }

    bool operator >=(const ATuple& other) const {
        return *this>other || *this==other;
    }
}; 
#pragma pack(pop)

#endif /* ATUPLE_H */

