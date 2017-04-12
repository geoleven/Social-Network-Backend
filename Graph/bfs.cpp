#include "graph.h"
#include "../defines.h"

#include <iostream>

using namespace std;

Pair::Pair(int i, int d) {
	distance = d;
	id = i;
	p = NULL;
}

Pair::Pair() {
	distance = -1;
	id = -1;
	p = NULL;
}

Pair::~Pair() {
}

void Pair::print() {
	cout << "[ID: " << id << " Distance: " << distance << "] "<<endl;
}

ResultSet::ResultSet(){
	pair=NULL;
	Q=NULL;
	V=NULL;
}

ResultSet::~ResultSet(){
	//delete pair;
	delete Q;
	delete V;
}

int Graph::reachNode1(int startID, int endID) {
	List<Pair> *Q = new List<Pair>(true);
	List<Person> *V = new List<Person>(true);
	List<Edge<Person> > *adjacentEdges;
	List<Pair> *deletion_list = new List<Pair>(false);
	Person *v = graph->lookupNode(startID);
	Pair *t;
	Person *u;
	V->pushBack(v);
	Pair *rs = new Pair();
	rs->p = v;
	rs->id = v->id;
	rs->distance = 0;
	Q->pushBack(rs);
	while (Q->getSize()) {
		t = Q->front();
		deletion_list->pushBack(t);
		Q->popFront();
		if (t->id == endID) {
			int distance = t->distance;
			while (Q->getSize()) {
				deletion_list->pushBack(Q->front());
				Q->popFront();
			}
			delete deletion_list;
			delete Q;
			delete V;
			return distance;
		}
		adjacentEdges = t->p->get_knows_person();
		for (int i = 0; i < adjacentEdges->getSize(); i++) {
			u = adjacentEdges->get(i)->get();
			if (V->search(u->id) == NULL) {
				V->pushBack(u);
				rs = new Pair();
				rs->p = u;
				rs->id = u->id;
				rs->distance = t->distance + 1;
				Q->pushBack(rs);
			}
		}
	}
	delete deletion_list;
	delete Q;
	delete V;
	return INFINITY_REACH_NODE;
}

ResultSet* Graph::reachNodeN(int startID){
	ResultSet* rs = new ResultSet();
	rs->Q = new List<Pair>(true);
	rs->V = new List<Person>(true);

	Person *v = graph->lookupNode(startID);
	rs->V->pushBack(v);

	rs->pair = new Pair();
	Pair* temp = rs->pair;
	rs->pair->p = v;
	rs->pair->id = v->id;
	rs->pair->distance = 0;
	rs->Q->pushBack(rs->pair);

	next(rs); //get rid of the first element

	delete temp;
	return rs;
}

bool Graph::next(ResultSet* rs){
	Pair *t;
	Pair *p;
	Person *u;
	List<Edge<Person> > *adjacentEdges;

	if(rs->Q->getSize()) {
		t = rs->Q->front();
		rs->Q->popFront();

		rs->pair = t;

		adjacentEdges = t->p->get_knows_person();

		for (int i = 0; i < adjacentEdges->getSize(); i++) {
			u = adjacentEdges->get(i)->get();
			if (rs->V->search(u->id) == NULL) {
				rs->V->pushBack(u);
				p = new Pair();
				p->p = u;
				p->id = u->id;
				p->distance = t->distance + 1;
				rs->Q->pushBack(p);
			}
		}
		return false;
	}
	else{
		return true;
	}
}

// ResultSet* Graph::reachNodeNTag(int startID , int tagID,  int gender){
// 	ResultSet* rs = new ResultSet();
// 	rs->Q = new List<Pair>(true);
// 	rs->V = new List<Person>(true);

// 	Person *v = graph->lookupNode(startID);
// 	rs->V->pushBack(v);

// 	rs->pair = new Pair();
// 	Pair* temp = rs->pair;
// 	rs->pair->p = v;
// 	rs->pair->id = v->id;
// 	rs->pair->distance = 0;
// 	rs->Q->pushBack(rs->pair);

// 	nextTag(rs , tagID , gender); //get rid of the first element

// 	delete temp;
// 	return rs;
// }

// bool Graph::nextTag(ResultSet* rs , int tagID , int gender){
// 	Pair *t;
// 	Pair *p;
// 	Person *u;
// 	List<Edge<Person> > *adjacentEdges;

// 	if(rs->Q->getSize()) {
// 		t = rs->Q->front();
// 		rs->Q->popFront();

// 		rs->pair = t;

// 		adjacentEdges = new List<Edge<Person> >(true);
		
// 		Edge<Person>* e;
// 		for(int i = 0 ; i < t->p->knows_person->getSize() ; i++){
// 			e = t->p->knows_person->get(i);
// 			if(e->end->has_interest->search(tagID)!=NULL && e->end->gender==gender){
// 				adjacentEdges->pushBack(e);
// 			}

// 		}

// 		for (int i = 0; i < adjacentEdges->getSize(); i++) {
// 			u = adjacentEdges->get(i)->get();
// 			if (rs->V->search(u->id) == NULL) {
// 				rs->V->pushBack(u);
// 				p = new Pair();
// 				p->p = u;
// 				p->id = u->id;
// 				p->distance = t->distance + 1;
// 				rs->Q->pushBack(p);
// 			}
// 		}
// 		return false;
// 	}
// 	else{
// 		return true;
// 	}
// }
