#ifndef _EDGE_H_
#define _EDGE_H_

#include <iostream>

template<class T>
class Edge {
public:
	T* end;				// pointer to end node for faster access
	int weight;
	std::string type;	// type of edge (not really needed since we are using templates)

	int id;				// id of end node

	Edge(T*);
	//Edge(const Edge&); // needs <t>?
	Edge(T*, int, std::string);
	~Edge();

	T* get();
};

#endif
