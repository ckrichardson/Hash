/**
@file HashTable.cpp
@author Cliff Richardson AKA The Supreme Gentleman
*/


#include <iostream>
#include <string>
#include "HashTable.h"



/**
@brief  This is the paramterized constructor for the hash table which will
take the table size and create a table of that size
*/
template<typename DataType, class KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
{
  tableSize = initTableSize;
  dataTable = new BSTree<DataType, KeyType>[initTableSize];
}

/**
@brief  This is the copy constructor for the hash tableSize
@details This accepts another HashTable object by const reference, and will copy_helper
its information to the calling object.
*/
template<typename DataType, class KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
{
  for(int i = 0; i < tableSize; i++)
  {
    dataTable[i] = other.dataTable[i];
  }
}

/**
@brief This is the overloaded assignment operator for the hash tableSize
@details This performs the same function as the copy constructor except that it Checks
whether the referenced object is the calling object, and clears its own table at
the beginning
*/

template<typename DataType, class KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
{
  if(this == &other)
    return *this;


  clear();
  tableSize = other.tableSize();
  dataTable = new BSTree<DataType, KeyType>[tableSize];
  for(int i = 0; i < tableSize; i++)
  {
    dataTable[i] = other.dataTable[i];
  }

  return *this;
}

/**
@brief This is the destructor of the hash table
@details  This deallocates all dynamically allocated memory in the hash table
*/
template<typename DataType, class KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
  clear();
}

/**
@brief This function inserts data into the hash
@details  A DataType item is passed in, which is used as the criteria for the insertion
*/
template<typename DataType, class KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{

  string key = newDataItem.getKey();

  dataTable[newDataItem.hash(key) % tableSize].insert(newDataItem);
}

/**
@brief This function removes a data from the hash
*/
template<typename DataType, class KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
  for(int i = 0; i < tableSize; i++)
  {
    if(dataTable[i].remove(deleteKey))
    {
      return true;
    }
  }

  return false;
}

/**
@brief This function retrieves an item from the hash
@details Using the given arguments, it searches along the hash until it encounters a data item
in a Binary Search Tree that matches its description, and then copies it returnItem
*/
template<typename DataType, class KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
  for(int i = 0; i < tableSize; i++)
  {
    if(dataTable[i].retrieve(searchKey, returnItem))
    {
      return true;
    }
  }

  return false;
}

/**
@brief This function clears the hash table
*/
template<typename DataType, class KeyType>
void HashTable<DataType, KeyType>::clear()
{
  for(int i = 0; i < tableSize; i++)
  {
    dataTable[i].clear();
  }
}

/**
@brief This function checks whether or not the hash table is empty
@details  The condition of whether or not the hash table is empty is predicated through
iterating through each Binary Search Tree in the hash and clearing each of those
*/

template<typename DataType, class KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
  for(int i = 0; i < tableSize; i++)
  {
    if(dataTable[i].isEmpty() == false)
      return false;
  }

  return true;
}


/**
@brief This shows the structure of the hash
*/
// show10.cpp: contains implementation of the HashTable showStructure function
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
    for (int i = 0; i < tableSize; ++i) {
	cout << i << ": ";
	dataTable[i].writeKeys();
    }
}


template<typename DataType, class KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const
{

}

template<typename DataType, class KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable& source)
{

}
