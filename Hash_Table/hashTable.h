#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "bucket.h"
#include "../Entities/entities.h"

template<class T>
class HashTable {
public:
	int m;	// hashtable size
	int c;	// bucket size
	int p;	// pointer
	int i;
	int htcurSize;	// hashtable current size
	Bucket<T>** hashTable;

	int id;

	int EntIn;

	bool insert(T*);

	HashTable(int, int);
	HashTable(int, int, int);
	~HashTable();

	int hf(int, int);// hash function, first argument is the id to be hashed, second argument is 0 or 1 (depending on the hash function needed)
	bool insertNode(T*);
	void extend();		// extends the hashtable
	void splitBucket();	// splits the bucket that p points to
	void print();
	//void printwithfriends();
	T* lookupNode(int);
	int sort();	// when node insertion is done, uses quicksort to sort the buckets
	int getEntIn();

	int* getAllNodeID();
};

#endif
