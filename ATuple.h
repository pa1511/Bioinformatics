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
 * A utility structure that represents a minimizer hit that contains data about
 * mapping between a query minimizer and a target minimizer that acts as a
 * tuple. It is used to wrap data, obtained from the mapping, as input for the
 * LIS algorithm.
 */
struct ATuple {
  std::uint16_t t;
  std::uint8_t r;
  int c;
  int i;

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

