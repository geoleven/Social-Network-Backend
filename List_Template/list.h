#ifndef _LIST_
#define _LIST_

template <class T>
class ListNode{
private:
	T* data;
	bool conservative;	// if true, data of Listnode are not deleted in its destructor
	ListNode<T>* next;
	ListNode<T>* prev;
public:
	ListNode(bool);
	ListNode(const ListNode& other, ListNode*, ListNode*, ListNode*, ListNode*);
	~ListNode();

	void setNode(T* ,ListNode* ,ListNode* );
	T* getData();
	void setData(T*);
	ListNode<T>* getNext();
	void setNext(ListNode<T>*);
	ListNode<T>* getPrev();
	void setPrev(ListNode<T>*);

};

template <class T>
class List{
private:
	ListNode<T>* head;
	int size;
	ListNode<T>* ptr;	// internal pointer to elements of the List for quick access
	bool conservative;	// if true, data of Lists Listnodes are not deleted in the destructors
public:
	List(bool);
	List(const List& other);
	~List();	

	int getSize();
	void pushFront(T*);
	void pushBack(T*);
	void insert(T*,int);

	void popFront();	// removes first element of the list
	void popBack();		// removes last element of the list
	bool remove(T*);	// removes T from list, returns true on success, false otherwise
	void remove(int);	// removes element of given position from list

	T* front();			// returns first element of the list
	T* end();			// returns last element of the list
	T* get(int);

	/* handles the ptr pointer */
	void ptrStart();
	void ptrEnd();
	void ptrNext();
	void ptrPrev();
	T* ptrGet();
	void ptrAdd(T*);
	void ptrRemove();

	T* search(int);		// element of class T must have member "id" in order for this to work

	bool isCons();
};

#endif	
