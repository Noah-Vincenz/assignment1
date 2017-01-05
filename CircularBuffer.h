#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H


#include "vector.h"
using pep::vector;


/** TODO: complete the definition of the class CircularBuffer here
 *
 * Its constructor should take the size of the buffer as an argument
 *
 * It needs to have the functions:
 * - count() which returns how many things are in the buffer
 * - full() which returns true iff the buffer is full
 * - add() which takes an element and adds it to the buffer (you can assume the buffer is not full)
 * - remove() which removes the next element from the buffer (you can assume the buffer is not empty)
 */
class CircularBuffer {

protected:
    vector<char> bufferVector;
    int bufferCapacity = 0;
    int indexOfLastChar = 0;
    int indexOfFrontChar = 0;
    int numElts = 0;

public:
    CircularBuffer(int capacityIn)
            : bufferVector(capacityIn), bufferCapacity(capacityIn) {
    }
    int count() const {
        return numElts;
    }
    bool full() const {
        if (numElts == bufferCapacity) {
            return true;
        } else {
            return false;
        }
    }
    void add(char & c) {
        bufferVector.at(indexOfLastChar) = c;
        indexOfLastChar = (indexOfLastChar + 1) % bufferCapacity;
        numElts++;
    }
    char remove() {
        char removedChar = bufferVector.at(indexOfFrontChar);
        bufferVector.at(indexOfFrontChar) = '\n';
        indexOfFrontChar = (indexOfFrontChar + 1) % bufferCapacity;
        numElts--;
        return removedChar;
    }
};
// don't write any code below this line

#endif
