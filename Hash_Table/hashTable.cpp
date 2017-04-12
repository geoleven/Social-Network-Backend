#include "hashTable.h"

#include <iostream>
#include <math.h>
#include "../Graph/graph.h"
#include "../Entities/entities.h"

using namespace std;

template<class T>
HashTable<T>::HashTable(int m, int c) {
	this->m = m;
	this->c = c;
	p = 0;
	i = 0;
	htcurSize = this->m;
	hashTable = new Bucket<T>*[this->m];
	for (int i = 0; i < this->m; i++) {
		hashTable[i] = new Bucket<T>(c);
	}
	EntIn = 0;
	id = 0;
}

template<class T>
HashTable<T>::HashTable(int m, int c, int my_id) {
	this->m = m;
	this->c = c;
	p = 0;
	i = 0;
	htcurSize = this->m;
	hashTable = new Bucket<T>*[this->m];
	for (int i = 0; i < this->m; i++) {
		hashTable[i] = new Bucket<T>(c);
	}
	EntIn = 0;
	id = my_id;
}

template<class T>
HashTable<T>::~HashTable() {
	for (int mi = 0; mi < htcurSize; mi++) {
//		for(int mc = 0; mc < hashTable[mi]->getEntIn(); mc++) {
//			hashTable[mi]->remove(mc);
//		}
		delete hashTable[mi];
	}
	delete[] hashTable;
	hashTable = NULL;
}

template<class T>
int HashTable<T>::hf(int id, int x) {
	return (id % ((int) pow(2, (i + x)) * m));
}

template<class T>
bool HashTable<T>::insertNode(T* data) {
	EntIn++;
	return insert(data);
}

template<class T>
bool HashTable<T>::insert(T* data) {
	int h = hf(data->id, 0);
	if (h < p) {
		h = hf(data->id, 1);
	}
	// if bucket is full, insert returns false and extends the hashTable re-inserts data and splits the bucket
	if (hashTable[h]->insert(data) == false) {
		hashTable[h]->extend();
		hashTable[h]->insert(data);
		splitBucket();
	}
	return true;
}

template<class T>
int HashTable<T>::sort() {
	for (int counter = 0; counter < htcurSize; counter++) {
		if (!(hashTable[counter]->sortb()))
			return 0;
	}
	return 1;
}

template<class T>
void HashTable<T>::splitBucket() {
	int oldp = p;

	extend();	// extends hashtable
	p++;

	if ((((int) pow(2, i)) * m) == p) {
		// check if p needs to reset
		p = 0;
		i++;
	}

	T* data[hashTable[oldp]->getSize()]; // *2?

	int sizeOfBucket = hashTable[oldp]->getEntIn();

	// removes elements of bucket pointed by p and re-inserts them with the new hashfunction
	for (int counter = 0; counter < sizeOfBucket; counter++) {
		data[counter] = hashTable[oldp]->getAndRemove(counter);
	}
	for (int counter = 0; counter < sizeOfBucket; counter++) {
		insert(data[counter]);
	}
}

template<class T>
void HashTable<T>::extend() {

	Bucket<T>** temp;

	temp = new Bucket<T>*[htcurSize + 1];

	for (int j = 0; j < htcurSize; j++) {
		temp[j] = hashTable[j];
	}

	temp[htcurSize] = new Bucket<T>(c);

	htcurSize++;

	delete[] hashTable;
	hashTable = temp;
}

template<class T>
void HashTable<T>::print() {
	for (int j = 0; j < htcurSize; j++) {
		if (j == p)
			cout << "P";
		else
			cout << " ";
		cout << j << " ->";
		hashTable[j]->print();
	}
}

template<class T>
T* HashTable<T>::lookupNode(int id) {
	int h = hf(id, 0);
	if (h < p) {
		h = hf(id, 1);
	}
	if (hashTable == NULL || hashTable[h] == NULL)
		return NULL;
	return hashTable[h]->search(id);
}

template<class T>
int HashTable<T>::getEntIn() {
	return EntIn;
}

template<class T>
int* HashTable<T>::getAllNodeID() {
	int* Nodes = new int[EntIn];
	int x = 0;
	int y = 0;
	T* temp;
	int count = 0;
	while (count < EntIn) {
		temp = hashTable[x]->get(y);
		if (temp == NULL) {
			x++;
			y = 0;
			temp = hashTable[x]->get(y);
		} else {
			y++;
			Nodes[count] = temp->id;
			count++;
		}
	}

	return Nodes;
}

//-----------------Template Types used--------------------//
template class HashTable<Person> ;
template class HashTable<Forum> ;
template class HashTable<Organisation> ;
template class HashTable<Place> ;
template class HashTable<Post> ;
template class HashTable<Tag> ;
template class HashTable<Community> ;
