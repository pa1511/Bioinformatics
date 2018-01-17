/*
 * To change this license header,  choose License Headers in Project Properties.
 * To change this template file,  choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Minimizer.h
 * Author: paf
 *
 * Created on January 15,  2018,  12:59 PM
 */

#ifndef MINIMIZER_H
#define MINIMIZER_H

#pragma pack(push,  1)

/**
 * Single minimizer data package. <br/>
 * A minimizer contains two values: <br/>
 * <ul>
 * <li> m - minimizer hash value </li>
 * <lI> i - position in the sequence </li>
 * </ul>
 */
struct Minimizer {
    int m;
    int i;

    /*
     * Comparison operators implemented so minimizers can be easily compared
     */

    bool operator<(const Minimizer& other) const {
        if (this->m  ==  other.m) {
            return this->i < other.i;
        }
        return this->m < other.m;
    }

    bool operator>(const Minimizer& other) const {
        if (this->m  ==  other.m) {
            return this->i > other.i;
        }
        return this->m > other.m;
    }

    bool operator == (const Minimizer& other) const {
        return this->m  ==  other.m && this->i  ==  other.i;
    }

    bool operator <= (const Minimizer& other) const {
        return *this < other || *this  ==  other;
    }

    bool operator >= (const Minimizer& other) const {
        return *this > other || *this  ==  other;
    }
};
#pragma pack(pop)

#endif /* MINIMIZER_H */

