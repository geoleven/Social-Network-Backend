#include "../graph.h"
#include <iostream>
#include "../../Entities/entities.h"

using namespace std;

double Graph::closenessCentrality(Person* node) {
	if (!dist) {
		getShortestPaths();
	}
	int Nodes[EntIn];
	int x = 0;
	int y = 0;
	Person* temp;
	int count = 0;
	while (count < EntIn) {
		temp = graph->hashTable[x]->get(y);
		if (temp == NULL) {
			x++;
			y = 0;
			temp = graph->hashTable[x]->get(y);
		} else {
			y++;
			Nodes[count] = temp->id;
			count++;
		}
	}
	int i = 0;
	for (; i < EntIn; i++) {
		if (Nodes[i] == node->id) {
			break;
		}
	}
	double centr = 0;
	for (int j = 0; j < EntIn; j++) {
		if (dist[i][j] != 0) {
			centr += 1 / (double) dist[i][j];
		}
	}
	centr = centr / (EntIn - 1);
	return centr;
}

int get_position(int *nodes, int size, int id) {
	for (int i = 0; i < size; i++) {
		if (nodes[i] == id)
			return i;
	}
	return -1;
}
double Graph::betweennessCentrality(Person* node) {
	double CB[graph->EntIn];
	for (int i = 0; i < graph->EntIn; i++) {
		CB[i] = 0.0;
	}
	int *nodes = graph->getAllNodeID();

	for (int i = 0; i < graph->EntIn; i++) {
		Person* s = graph->lookupNode(nodes[i]);
		List<Person> S(true);   //Stack
		List<Person> **P = new List<Person>*[graph->EntIn];     //List
		int sigma[graph->EntIn];
		int d[graph->EntIn];
		for (int j = 0; j < graph->EntIn; j++) {
			P[j] = new List<Person>(true);
			sigma[j] = 0;
			d[j] = -1;
		}
		sigma[i] = 1;
		d[i] = 0;
		List<Person> Q(true);   //Queue
		Q.pushBack(s);
		while (Q.getSize() != 0) {
			Person *v = Q.front();
			Q.popFront();
			int v_pos = get_position(nodes, graph->EntIn, v->id);
			S.pushFront(v);
			List<Edge<Person> > *neighbors = v->knows_person;
			for (int j = 0; j < neighbors->getSize(); j++) {
				Person* w = neighbors->get(j)->end;
				int w_pos = get_position(nodes, graph->EntIn, w->id);
				//w found for the first time?
				if (d[w_pos] < 0) {
					//cout<<"in 1"<<endl;
					Q.pushBack(w);
					d[w_pos] = d[v_pos] + 1;
				}
				//shortest path to w via v?
				if (d[w_pos] > d[v_pos]) {
					//cout<<"in 2"<<endl;
					sigma[w_pos] += sigma[v_pos];
					P[w_pos]->pushBack(v);
				}
			}
		}

		double delta[graph->EntIn];
		for (int j = 0; j < graph->EntIn; j++) {
			delta[j] = 0.0;
		}
		//S returns vertices in order of non-increasing distance from s
		while (S.getSize() != 0) {
			Person *w = S.front();
			S.popFront();
			int w_pos = get_position(nodes, graph->EntIn, w->id);
			while (P[w_pos]->getSize() != 0) {
				Person *v = P[w_pos]->front();
				P[w_pos]->popFront();
				int v_pos = get_position(nodes, graph->EntIn, v->id);
				delta[v_pos] += sigma[v_pos] * (1.0 + delta[w_pos])
						/ (double) sigma[w_pos];
			}
			if (w->id != s->id) {
				CB[w_pos] = CB[w_pos] + delta[w_pos];
			}
		}
	}

	for (int i = 0; i < graph->EntIn; i++) {
		CB[i] = CB[i]
				/ (((double) (graph->EntIn - 2) * (double) (graph->EntIn - 1)));
	}

	int mypos = get_position(nodes, graph->EntIn, node->id);

	delete[] nodes;

	return CB[mypos];
}
