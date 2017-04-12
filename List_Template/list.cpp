#include "list.h"

#include <iostream>

#include "../Entities/entities.h"
#include "../Graph/graph.h"

using namespace std;

//---------------------------------ListNode------------------------//
template<class T>
ListNode<T>::ListNode(bool is_cons) {
	data = NULL;
	next = NULL;
	prev = NULL;
	conservative = is_cons;
}

template<class T>
ListNode<T>::ListNode(const ListNode& old, ListNode* thead, ListNode* ttail,
		ListNode* nhead, ListNode* tprev) {
	if (old.data == NULL)
		data = NULL;
	else
		data = new T(*(old.data));
	if (nhead == NULL)
		next = new ListNode<T>(*(old.next), thead, ttail, this, this);
	else if (old.next == NULL)
		next = NULL;
	else if (old.next == nhead) {
		next = nhead;
		nhead->prev = this;
	} else
		next = new ListNode<T>(*(old.next), thead, ttail, nhead, this);
	prev = tprev;
	conservative = old.conservative;
}

template<class T>
ListNode<T>::~ListNode() {
	if (conservative == false) {
		delete data;
	}
}

template<class T>
void ListNode<T>::setData(T* d) {
	data = d;
}

template<class T>
T* ListNode<T>::getData() {
	return data;
}

template<class T>
void ListNode<T>::setNext(ListNode* n) {
	next = n;
}

template<class T>
ListNode<T>* ListNode<T>::getNext() {
	return next;
}

template<class T>
void ListNode<T>::setPrev(ListNode* n) {
	prev = n;
}

template<class T>
ListNode<T>* ListNode<T>::getPrev() {
	return prev;
}

template<class T>
void ListNode<T>::setNode(T* d, ListNode* n, ListNode* p) {
	data = d;
	next = n;
	prev = p;
}

//-------------------------------List---------------------------//

template<class T>
List<T>::List(bool is_cons) {
	head = NULL;
	size = 0;
	ptr = NULL;
	conservative = is_cons;
}

template<class T>
List<T>::List(const List<T>& old) {
//	ListNode* temp1 = old.head->getPrev()->getNext();
//	old.head->getPrev->getNext = NULL;
//	ListNode* temp2 = old.head->getPrev();
//	old.head->getPrev() = NULL;
	head = new ListNode<T>(*(old.head), old.head, old.head->getPrev(), NULL,
	NULL);
//	old.head.prev = temp2;
//	old.head.prev.next = temp1;
//	ListNode* temp3 = head;
//	while(temp3 != NULL){
//		if(temp3->next != NULL)
//			temp3 = temp3->next;
//		else
//			temp3->next = head;
//	}
	size = old.size;
	ptr = head; //????
	conservative = false;
}

template<class T>
List<T>::~List() {
	ListNode<T> *temp1, *temp2;

	temp1 = head;

	for (int i = 0; i < size; i++) {
		temp2 = temp1->getNext();
		delete temp1;
		temp1 = temp2;
	}
}

template<class T>
int List<T>::getSize() {
	return size;
}

template<class T>
void List<T>::pushFront(T* data) {

	if (size == 0) {
		head = new ListNode<T>(conservative);
		head->setNode(data, head, head);
	} else {
		ListNode<T>* temp = new ListNode<T>(conservative);
		ListNode<T>* last = head->getPrev();

		temp->setData(data);

		temp->setNext(head);
		temp->setPrev(last);

		head->setPrev(temp);
		last->setNext(temp);

		head = temp;
	}

	size++;
}

template<class T>
void List<T>::pushBack(T* data) {

	if (size == 0) {
		head = new ListNode<T>(conservative);
		head->setNode(data, head, head);
	} else {
		ListNode<T>* temp = new ListNode<T>(conservative);
		ListNode<T>* last = head->getPrev();

		temp->setData(data);

		temp->setNext(head);
		temp->setPrev(last);

		last->setNext(temp);
		head->setPrev(temp);
	}

	size++;
}

template<class T>
void List<T>::insert(T* data, int pos) {

	if (pos == 0) {
		pushFront(data);
	} else if (pos == size) {
		pushBack(data);
	} else if (pos < size && pos > 0) {

		ListNode<T>* temp = new ListNode<T>(conservative);
		temp->setData(data);

		ListNode<T>* temp2 = head;
		ListNode<T>* temp3;

		int i = 0;
		do {
			temp2 = temp2->getNext();
			i++;
		} while (i < pos);

		temp3 = temp2->getPrev();

		temp->setNext(temp2);
		temp->setPrev(temp3);

		temp3->setNext(temp);
		temp2->setPrev(temp);

		size++;

	}
}

template<class T>
T* List<T>::front() {
	if (size > 0)
		return head->getData();
	else
		return NULL;

}

template<class T>
T* List<T>::end() {
	if (size > 0)
		return (head->getPrev())->getData();
	else
		return NULL;
}

template<class T>
T* List<T>::get(int pos) {
	if (size > 0) {
		if (pos == 0) {
			return front();
		}
		if (pos == (size - 1)) {
			return end();
		} else if (pos < size && pos > 0) {

			ListNode<T>* temp = head;

			if (pos < (size / 2)) {

				int i = 0;
				do {
					temp = temp->getNext();
					i++;
				} while (i < pos);

			} else {

				int i = size;
				do {
					temp = temp->getPrev();
					i--;
				} while (i > pos);

			}

			return temp->getData();
		} else
			return NULL;
	} else
		return NULL;
}

template<class T>
void List<T>::popFront() {
	if (size == 1) {
		delete head;
		head = NULL;
		size = 0;
	} else if (size > 0) {
		ListNode<T>* temp = head;
		ListNode<T>* last = head->getPrev();

		head = head->getNext();
		head->setPrev(last);
		last->setNext(head);

		delete temp;
		size--;
	}
}

template<class T>
void List<T>::popBack() {
	if (size == 1) {
		delete head;
		head = NULL;
		size = 0;
	} else if (size > 0) {
		ListNode<T>* last = head->getPrev();
		ListNode<T>* temp = last;

		last = last->getPrev();
		last->setNext(head);
		head->setPrev(last);

		delete temp;
		size--;
	}
}

template<class T>
void List<T>::remove(int pos) {
	if (size > 0) {
		if (pos == 0) {
			popFront();
		} else if (pos == (size - 1)) {
			popBack();
		} else if (pos < size && pos > 0) {

			ListNode<T>* temp = head;
			ListNode<T>* prev;
			ListNode<T>* next;

			int i = 0;
			do {
				temp = temp->getNext();
				i++;
			} while (i < pos);

			prev = temp->getPrev();
			next = temp->getNext();

			prev->setNext(next);
			next->setPrev(prev);

			delete temp;
			size--;
		}
	}
}

template<class T>
bool List<T>::remove(T* data) {
	if (size > 0) {
		ListNode<T> *temp = head;
		for (int i = 0; i < size; i++) {
			if (data == temp->getData()) {
				remove(i);
				return true;
			}
			temp = temp->getNext();
		}
	}
	return false;
}

template<class T>
void List<T>::ptrStart() {
	if (head != NULL)
		ptr = head;
	else
		ptr = NULL;
}

template<class T>
void List<T>::ptrEnd() {
	if (head != NULL)
		ptr = head->getPrev();
	else
		ptr = NULL;
}

template<class T>
void List<T>::ptrNext() {
	if (ptr != NULL)
		ptr = ptr->getNext();
}

template<class T>
void List<T>::ptrPrev() {
	if (ptr != NULL)
		ptr = ptr->getPrev();
}

template<class T>
T* List<T>::ptrGet() {
	if (ptr != NULL)
		return ptr->getData();
	else
		return NULL;
}

template<class T>
void List<T>::ptrAdd(T* data) {
	if (ptr != NULL) {
		ListNode<T>* prev = ptr->getPrev();
		ListNode<T>* next = ptr->getNext();

		if (ptr == head) {
			ptr = new ListNode<T>(conservative);
			head = ptr;
		} else
			ptr = new ListNode<T>(conservative);

		ptr->setData(data);

		ptr->setNext(next);
		ptr->setPrev(prev);

		next->setPrev(ptr);
		prev->setNext(ptr);

		size++;
	}
}

template<class T>
void List<T>::ptrRemove() {
	if (ptr != NULL) {
		if (size == 1) {
			delete head;
			head = NULL;
			ptr = NULL;
			size = 0;
		} else {
			ListNode<T>* temp = ptr;
			ListNode<T>* next = ptr->getNext();

			if (head == ptr)
				head = ptr->getNext();
			ptr = ptr->getPrev();

			ptr->setNext(next);
			next->setPrev(ptr);

			delete temp;
			size--;
		}
	}
}

template<class T>
T* List<T>::search(int id) {
	ListNode<T>* temp = head;
	T* data;
	for (int i = 0; i < size; i++) {
		data = temp->getData();
		if (data->id == id) {
			return data;
		}
		temp = temp->getNext();
	}
	return NULL;
}

template<class T>
bool List<T>::isCons() {
	return conservative;
}

//-----------------Template Types used--------------------//
template class ListNode<Person> ;
template class List<Person> ;
template class ListNode<Edge<Person> > ;
template class List<Edge<Person> > ;
template class List<Forum> ;
template class ListNode<Forum> ;
template class List<Organisation> ;
template class ListNode<Organisation> ;
template class List<Place> ;
template class ListNode<Place> ;
template class List<Post> ;
template class ListNode<Post> ;
template class List<Tag> ;
template class ListNode<Tag> ;
template class List<Comment> ;
template class ListNode<Comment> ;
template class List<Pair> ;
template class ListNode<Pair> ;
template class List<Info> ;
template class ListNode<Info> ;
template class List<Likes> ;
template class ListNode<Likes> ;
template class List<Stalker> ;
template class ListNode<Stalker> ;
template class List<ForumMembers> ;
template class ListNode<ForumMembers> ;
template class List<HashTable<Person> > ;
template class ListNode<HashTable<Person> > ;
template class List<ForumPersons> ;
template class ListNode<ForumPersons> ;
template class List<Community> ;
template class ListNode<Community> ;
template class List<CC> ;
template class ListNode<CC> ;
template class List<Match> ;
template class ListNode<Match> ;
