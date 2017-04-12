#ifndef _BUCKET_H_
#define _BUCKET_H_

template<class T>
class Bucket {
public:
	int initSize;	// bucket initial size
	int size;		// bucket current size (can be higher than initial)
	int entitiesIn;
	T** table;
	int qsort(int, int);
	int binSearch(int, int, int);	// binary search for an element

	Bucket(int);
	~Bucket();

	int getSize();
	int getEntIn();
	T* get(int);			// returns element at given position
	T* getAndRemove(int);	// returns and removes element at given positions

	bool isFull();
	bool insert(T*);		// inserts elements in the bucket
	bool remove(int);
	void extend(); 			// extends bucket. newSize = size + initSize
	void print();
	//void printwithfriends();
	void swaptd(int, int);	// swaps two elements of a bucket
	T* search(int);
	int sortb();
};

#endif
