#include <cstdio>
#include <cstdlib>
#include <string.h>

#include "./Graph/graph.h"
#include "defines.h"

#include <iostream>
#include <iomanip>

using namespace std;

int main(void) {

	int m = 4;
	int c = 4;

	Graph g(m, c);

	g.LoadData();

	cout << "Diameter: " << g.diameter() << endl;
	cout << endl;
	cout << "Average Path Length: " << g.averagePathLength() << endl;
	cout << endl;
	cout << "Number of connected components: " << g.numberOfCCs() << endl;
	cout << endl;
	cout << "Size of the maximum connected component: " << g.maxCC() << endl;
	cout << endl;
	cout << "Density: " << g.density() << endl;
	cout << endl;
	cout << "Closeness Centrality" << endl;
	cout << "1734: " << g.closenessCentrality(g.graph->lookupNode(1734))
			<< endl;
	cout << "38: " << g.closenessCentrality(g.graph->lookupNode(38)) << endl;
	cout << "8899: " << g.closenessCentrality(g.graph->lookupNode(8899))
			<< endl;
	cout << "3501: " << g.closenessCentrality(g.graph->lookupNode(3501))
			<< endl;
	cout << "75: " << g.closenessCentrality(g.graph->lookupNode(75)) << endl;
	cout << endl;
	cout << "Betweenness Centrality" << endl;
	cout << "1734: " << g.betweennessCentrality(g.graph->lookupNode(1734))
			<< endl;
	cout << "38: " << g.betweennessCentrality(g.graph->lookupNode(38)) << endl;
	cout << "8899: " << g.betweennessCentrality(g.graph->lookupNode(8899))
			<< endl;
	cout << "9900: " << g.betweennessCentrality(g.graph->lookupNode(9900))
			<< endl;
	cout << "75: " << g.betweennessCentrality(g.graph->lookupNode(75)) << endl;
	cout << endl;

//Query 1
	cout << "Query 1" << endl;
	Match* match = g.matchSuggestion(g.graph->lookupNode(3755), 1, 3, 30, 1);
	for (int i = 0; i < match->size; i++) {
		cout << "Person " << g.graph->lookupNode(3755)->firstName
				<< " has match suggestion(s): " << endl;
		match[i].print();
	}
	cout << endl;

//Query 2
	cout << "Query 2" << endl;
	List<Stalker> *st = new List<Stalker>(true);
	HashTable<Person> *hts = g.getTopStalkers(7, 1, 2, st);
	for (int i = 0; i < st->getSize(); i++) {
		cout << "Stalker id: " << st->get(i)->id << endl;
	}
	cout << endl;
	delete st;

//Query 3
	cout << "Query 3" << endl;
	char* wom[4] = { NULL, NULL, NULL, NULL };
	char* men[4] = { NULL, NULL, NULL, NULL };
	g.findTrends(4, wom, men);
	cout << "Women trends:" << endl;
	for (int i = 0; i < 4; i++) {
		if (wom[i] != NULL) {
			cout << wom[i] << endl;
			delete[] (wom[i]);
		}
	}
	cout << endl;
	cout << "Men trends:" << endl;
	for (int i = 0; i < 4; i++) {
		if (men[i] != NULL) {
			cout << men[i] << endl;
			delete[] (men[i]);
		}
	}
	cout << endl;

//Query 4
	cout << "Query 4" << endl;
	g.buildTrustGraph(34680);
	HashTable<Person>* trustGraph = g.trustGraph;
	int trustANodeId = 30;
	int trustBNodeId = 9805;
	int trustCNodeId = 9700;
	Person *ta = g.graph->lookupNode(trustANodeId);
	Person *tb = g.graph->lookupNode(trustBNodeId);
	Person *tc = g.graph->lookupNode(trustCNodeId);
	float trustAB, trustAC;
	trustAB = g.estimateTrust(34680, ta->id, tb->id);
	trustAC = g.estimateTrust(34680, ta->id, tc->id);
	cout << "Trust A - B: " << trustAB << endl;
	cout << "Trust A - C: " << trustAC << endl;
	return EXIT_SUCCESS;
}
