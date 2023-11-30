/*
 * Dictionary.cpp
 *
 * Class Description: Dictionary data collection ADT class.
 *                    The implementation of this class is based on
 *                    the hashing strategy and the open addressing
 *                    collision resolution strategy called linear probing hashing.
 * Class Invariant: Each element stored in this Dictionary is unique (no duplications allowed).
 *
 * Author: AL
 * Date: Last modified: Nov. 2023
 */

// You can add more #include statements if you wish.

#include <iostream>
#include <cstring>
#include "Dictionary.h"
#include "Profile.h"
#include "UnableToInsertException.h"
#include "ElementAlreadyExistsException.h"
#include "EmptyDataCollectionException.h"
#include "ElementDoesNotExistException.h"

using std::cout;
using std::endl;
using std::__cxx11::stoul;

// Constructor
Dictionary::Dictionary()
{
  hashTable = new Profile *[CAPACITY];
  elementCount = 0;
  for (unsigned i = 0; i < CAPACITY; ++i)
  {
    hashTable[i] = nullptr;
  }
}

// Destructor
// Description: Destruct a Dictionary object, releasing heap-allocated memory.
Dictionary::~Dictionary()
{
  // Release all heap memory
  if (hashTable != nullptr)
  {
    for (unsigned int i = 0; i < CAPACITY; i++)
      if (hashTable[i] != nullptr)
      {
        delete hashTable[i]; // Delete object of Profile class on heap
        hashTable[i] = nullptr;
      }
    delete[] hashTable;
    hashTable = nullptr;
  }
}

// Description: Returns the total element count currently stored in Dictionary.
// Postcondition: Dictionary remains unchanged.
unsigned int Dictionary::getElementCount() const
{
  return elementCount;
}

// Description: Returns the CAPACITY (size) of the Dictionary.
// Postcondition: Dictionary remains unchanged.
unsigned int Dictionary::getCapacity() const
{
  return CAPACITY;
}

// Hash Function
// Description: Hashes the given indexingKey producing a "hash table index".
// Time Efficiency: For you to complete!
// Example of Time Efficiency: max(O(1),O(1)) = O(1)
// Space Efficiency: For you to complete!
// Example of Space Efficiency: O(1)
unsigned int Dictionary::hashFunction(string indexingKey)
{

  // Implement your own hash function here!

  // Time Efficiency Analysis: Two statements done in sequence: max(O(1),O(1)) = O(1)
  // Space Efficiency Analysis: Hash Function does not require another
  //                            data structure (of size n) to operate: O(1)
  // Convert the 16-digit string to an integral number
  uint64_t indexingKeyInt = stoul(indexingKey); // O(1)

  // "hashCode" is an intermediate result
  unsigned int hashCode = indexingKeyInt % CAPACITY; // O(1)

  return hashCode;
}

// Description: Inserts an element into the Dictionary and increments "elementCount".
//              For this Assignment 5, you do not have to expand the hashTable when it is full.
// Precondition: newElement must not already be in in the Dictionary.
// Exception: Throws UnableToInsertException if we cannot insert newElement in the Dictionary.
//            For example, if the operator "new" fails, or Dictionary is full (temporary solution).
// Exception: Throws ElementAlreadyExistsException if newElement is already in the Dictionary.
void Dictionary::insert(Profile *newElement)
{

  // Put your code here!

  if (getElementCount() >= CAPACITY)
  {
    throw UnableToInsertException("Unable to insert.");
  }
  if (get(*newElement) != nullptr)
  {
    throw ElementAlreadyExistsException("Element already exists.");
  }

  Profile *nextElement = new Profile(*newElement);
  int newIndex = hashFunction(newElement->getUserName());
  while (hashTable[newIndex] != nullptr)
  {
    // Linear probing: Move to the next slot
    newIndex = (newIndex + 1) % CAPACITY;
  }

  hashTable[newIndex] = nextElement;

  elementCount++;

  return;
}

// Description: Returns a pointer to the target element if found.
// Postcondition: Dictionary remains unchanged.
// Exception: Throws EmptyDataCollectionException if the Dictionary is empty.
// Exception: Throws ElementDoesNotExistException if target is not found in the Dictionary.
Profile *Dictionary::get(Profile &target)
{

  // Put your code here!
  if (elementCount == 0)
  {
    throw EmptyDataCollectionException("Dictionary is empty.");
  }

  for (unsigned int i = 0; i < CAPACITY; i++)
  {
    for (unsigned int j = 0; j < CAPACITY; j++)
    {
      if (hashTable[i][j] == target)
      {
        return hashTable[i];
      }
    }
  }

  return nullptr;
  throw ElementDoesNotExistException("Target not found.");
}

// Description: Prints all elements stored in the Dictionary (unsorted).
// Postcondition: Dictionary remains unchanged.
// Exception: Throws EmptyDataCollectionException if the Dictionary is empty.
void Dictionary::printDictionary() const
{
  if (elementCount == 0)
    throw EmptyDataCollectionException("In printDictionary(): hashTable is empty.");

  cout << endl
       << "Printing the Dictionary with " << this->elementCount << " elements: " << endl;
  for (unsigned int index = 0; index < CAPACITY; index++)
  {
    if (hashTable[index] != nullptr)
      cout << "HashTable[" << index << "] = " << *(hashTable[index]) << endl;
  }
  return;
}
