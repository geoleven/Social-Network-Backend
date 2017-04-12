#include "bucket.h"

#include <iostream>
#include "../Entities/entities.h"
#include "../Graph/graph.h"
using namespace std;

template<class T>
Bucket<T>::Bucket(int s) {
	size = s;
	initSize = s;
	entitiesIn = 0;
	table = new T*[size];
	for (int i = 0; i < size; i++) {
		table[i] = NULL;
	}
}

template<class T>
Bucket<T>::~Bucket() {
	for (int i = 0; i < size; i++) {
		if (table[i] != NULL) {
			delete table[i];
		}
	}
	delete[] table;
}

template<class T>
void Bucket<T>::swaptd(int a, int b) {
	T* temp;
	temp = table[a];
	table[a] = table[b];
	table[b] = temp;
}

template<class T>
int Bucket<T>::binSearch(int localid, int imin, int imax) {
	if (imax < imin)
		return -1;
	else {
		long int imid = (imin + imax) / 2;
		if (table[imid]->id > localid)
			return binSearch(localid, imin, imid - 1);
		else if (table[imid]->id < localid)
			return binSearch(localid, imid + 1, imax);
		else
			return imid;
	}
}

template<class T>
T* Bucket<T>::search(int myid) {
	if(entitiesIn>0){
		int position = binSearch(myid, 0, entitiesIn-1);

		return get(position);
	}
	else return NULL;
}

template<class T>
int Bucket<T>::getSize() {
	return size;
}

template<class T>
T* Bucket<T>::get(int i) {
	if (i >= 0 && i < size)
		return table[i];
	else
		return NULL;
}

template<class T>
bool Bucket<T>::insert(T* data) {
	if (entitiesIn < size) {
		table[entitiesIn] = data;
		entitiesIn++;
		return true;
	} else
		return false;

}

template<class T>
int Bucket<T>::sortb() {
	if(entitiesIn>0)
		return qsort(0, entitiesIn - 1);
	else return 1;
}

template<class T>
int Bucket<T>::qsort(int left, int right) {
	int i = left;
	int j = right;
	int pivot = table[(left + right) / 2]->id;

	while (i <= j) {
		while (table[i]->id < pivot)
			i++;
		while (table[j]->id > pivot)
			j--;
		if (i <= j) {
			swaptd(i, j);
			i++;
			j--;
		}
	};

	if (left < j)
		qsort(left, j);
	if (i < right)
		qsort(i, right);
	return 1;
}

template<class T>
bool Bucket<T>::remove(int pos) {
	if (table[pos] != NULL) {
		delete table[pos];
		table[pos] = NULL;
		entitiesIn--;
		return true;
	}
	return false;
}

template<class T>
bool Bucket<T>::isFull() {
	return (size == entitiesIn);
}

template<class T>
void Bucket<T>::extend() {
	/* creates a temporary table of increased size
	 * and copies the bucket table to this one*/

	T** temp = new T*[size + initSize];
	for (int i = 0; i < size; i++) {
		temp[i] = table[i];
	}
	for (int i = size; i < size + initSize; i++) {
		temp[i] = NULL;
	}
	delete[] table;
	table = temp;
	size = size + initSize;
}

template<class T>
T* Bucket<T>::getAndRemove(int position) {
	T* temp;
	temp = table[position];
	table[position] = NULL;
	entitiesIn--;
	return temp;
}

template<class T>
int Bucket<T>::getEntIn() {
	return entitiesIn;
}

template<class T>
void Bucket<T>::print() {
	cout << "[ ";
	for (int i = 0; i < size; i++) {
		if (table[i] != NULL)
			cout << table[i]->id;
		else
			cout << "_";
		if (i < size - 1)
			cout << " | ";
	}
	cout << " ] " << endl;
}

// template<class T>
// void Bucket<T>::printwithfriends() {
// 	for (int i = 0; i < size; i++) {
// 		if (table[i] != NULL) {
// 			cout << table[i]->id << ": ";
// 			table[i]->print_known_person();
// 			cout << endl;
// 		}
// 	}
// }

//-----------------Template Types used--------------------//
template class Bucket<Person> ;
template class Bucket<Forum> ;
template class Bucket<Organisation> ;
template class Bucket<Place> ;
template class Bucket<Post> ;
template class Bucket<Tag> ;
template class Bucket<Community> ;
