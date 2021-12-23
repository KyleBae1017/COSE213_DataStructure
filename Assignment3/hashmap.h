#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>

/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * 2021. 11. 1   Won-Ki Jeong
  *
  */

// Map element
template <class KeyType, class ValType>
class MapElem
{
public:
	typedef KeyType ktype;
	typedef ValType vtype;
	
	KeyType key;
	ValType val;
	
	MapElem* link = NULL;
};

bool inline operator==(std::string a, std::string b)
{
	if((a).compare(b) == 0) return true;
	return false;
}

//
// Hash Map data structure
//
template <class HashMapElemType> 
class HashMap
{
public:
	typedef typename HashMapElemType::ktype KeyType;
	typedef typename HashMapElemType::vtype ValType;
	
	// constructor
	HashMap(unsigned int c = 1000);
	
	// destructor
	~HashMap();
	
	// Modify below functions
	int size() { return mapsize; };
	
	bool isEmpty() { return (mapsize == 0); };
	
	// ToDo
	HashMapElemType* find(const KeyType k);
	
	void insert(const KeyType k, const ValType v);
		
	bool remove(const KeyType k);
	
	unsigned int hashfunction(const KeyType k);
	
	void print();
	
private:
	// Hash Table
	HashMapElemType** ht;
	
	unsigned int mapsize, capacity, divisor;
};



#ifndef HASHMAP_TXX
#define HASHMAP_TXX
#include "hashmap.txx"
#endif


#endif
