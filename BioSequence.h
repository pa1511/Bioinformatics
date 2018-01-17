/*
 * File: BioSequence.h
 * Author: paf
 *
 * Created on October 15, 2017, 10:35 PM
 */

#ifndef BIOSEQUENCE_H
#define BIOSEQUENCE_H

#include <string>
#include <sstream>
#include <algorithm>

namespace bioinformatics {

/**
   * This class models a single bio-sequence. <br/>
   * It stores the sequence relevant data such as: <br/>
   * <ul>
   * <li> Sequence name</li>
   * <li> Comment associated with the sequence </li>
   * <li> Sequence size (number of characters in the sequence) </li>
   * <li> Sequence position in the document it was read from </li>
   * <li> The actual sequence string </li>
   * </ul>
   * The class provides the user with the ability get the stored data and also
   * the inverted sequence string. <br/>
   *
   * The class provides the ability to load the sequence part by part.
   * To achieve this the class offers:
   * <ul>
   * <li> setSequence - sets sequence to the given string </li>
   * <li> appeandSequence - appends the given sequence to the current sequence </li>
   * </ul>
   * After fully reading the sequence initialize should be called in order to properly initialize the BioSequence data.
   */
  class BioSequence {
  public:
    /**
     * Constructor
     * @param name - sequence name
     * @param comment - sequence comment
     * @param sequencePosition - sequence position in the document it was read from
     */
    BioSequence(std::string name, std::string comment, int sequencePosition);

    /**
     * Destructor
     */
    ~BioSequence();

    /**
     * Initializes the BioSequence data structures. <br/>
     * Should be called after full setting the sequence string.
     */
    void initialize();

    /**
     * Sets the sequence to the given string. <br/>
     * <b>Don't forget</b> to call initialize once you are done loading the sequence!
     * @param sequence - bio sequence string
     */
    void setSequence(std::string sequence);
    /**
     * Appends the given sequence to the current sequence string. <br/>
     * <b>Don't forget</b> to call initialize once you are done loading the sequence!
     * @param sequence - bio sequence string
     */
    void appeandSequence(std::string sequence);

    /**
     * Returns the BioSequence name
     */
    std::string getName();

    /**
     * Returns the BioSequence comment
     */
    std::string getComment();

    /**
     * Returns the BioSequence size which is the number of characters in the sequence string.
     */
    int size();

    /**
     * Returns the BioSequence sequence string
     */
    std::string *getSequence();

    /**
     * Returns the BioSequence inverted sequence string
     */
    std::string *getInvertedSequence();

    /**
     * Returns the BioSequence position in the document it was read from
     */
    int getSequencePosition();

  private:
    static char inversion[4];
    std::string calculateInvertedSequence();
    inline char invert(char c);

    std::string name;
    std::string comment;
    std::stringstream sequenceBuilder;
    std::string sequence;
    std::string inv_sequence;
    int sequencePosition;
  };
} // namespace bioinformatics

#endif /* BIOSEQUENCE_H */

