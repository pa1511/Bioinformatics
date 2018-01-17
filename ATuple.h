/*
 * File: ATuple.h
 * Author: papric
 *
 * Created on January 14, 2018, 4:56 PM
 */

#ifndef ATUPLE_H
#define ATUPLE_H

#pragma pack(push, 1)

 /**
  * Data structure used for storing the data of target minimizers
  * @param t - id of a target sequence
  * @param r - strand position
  * @param c - distance on a strans
  * @param i - position on target sequence
  */
struct ATuple {
  std::uint16_t t;
  std::uint8_t r;
  int c;
  int i;

  /**
   * 
   * Comparison operators implemented for comparing tuples
   */
  bool operator<(const ATuple& other) const {
    if (this->t == other.t) {
      if (this->r == other.r) {
        if (this->c == other.c) {
          return this->i < other.i;
        }
        return this->c < other.c;
      }
      return this->r < other.r;
    }
    return this->t < other.t;
  }

  bool operator>(const ATuple& other) const {
    if (this->t == other.t) {
      if (this->r == other.r) {
        if (this->c == other.c) {
          return this->i > other.i;
        }
        return this->c > other.c;
      }
      return this->r > other.r;
    }
    return this->t > other.t;
  }

  bool operator==(const ATuple& other) const {
    return this->t == other.t && this->r == other.r &&
            this->c == other.c && this->i == other.i;
  }

  bool operator<=(const ATuple& other) const {
    return *this < other || *this == other;
  }

  bool operator>=(const ATuple& other) const {
    return *this > other || *this == other;
  }
};
#pragma pack(pop)

#endif /* ATUPLE_H */

