#include "../graph.h"
#include "../../Entities/entities.h"

#include <iostream>

using namespace std;

void floyd_warshall(int*** dist, int n) {
	int i, j, k;
	for (k = 0; k < n; ++k) {
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				if (((*dist)[i][k] * (*dist)[k][j] != 0) && (i != j))
					if (((*dist)[i][k] + (*dist)[k][j] < (*dist)[i][j])
							|| ((*dist)[i][j] == 0))
						(*dist)[i][j] = (*dist)[i][k] + (*dist)[k][j];
	}
}


void Graph::printDist() {
	cout << "  ";
	for (int k = 0; k < EntIn; k++) {
		cout << k << " ";
	}
	cout << endl;
	for (int k = 0; k < EntIn; k++) {
		cout << k << "|";
		for (int j = 0; j < EntIn; j++) {
			cout << dist[k][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::getShortestPaths() {

	dist = new int*[EntIn];
	for (int j = 0; j < EntIn; j++) {
		dist[j] = new int[EntIn];
	}

	for (int j = 0; j < EntIn; j++) {
		for (int k = 0; k < EntIn; k++) {
			dist[j][k] = 0;
		}
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
	List<Edge<Person> >* kp;
	for (int j = 0; j < EntIn; j++) {
		if ((temp = graph->lookupNode(Nodes[j])) == NULL)
			cout << "Node " << j << " cannot be found" << endl;
		if ((kp = temp->get_knows_person()) == NULL)
			cout << "List of Node " << j << " cannot be found" << endl;
		kp->ptrStart();
		for (int k = 0; k < kp->getSize(); k++) {

			int id = kp->ptrGet()->get()->id;
			int pos;

			for (int i = 0; i < EntIn; i++) {
				if (Nodes[i] == id) {
					pos = i;
					break;
				}
			}

			dist[j][pos] = 1; // DIST IS 1
			kp->ptrNext();
		}
	}
	floyd_warshall(&dist, EntIn);
}

void Graph::removeShortestPaths() {
	for (int i = 0; i < EntIn; i++) {
		delete dist[i];
	}
	delete[] dist;
	dist = NULL;
}

double Graph::averagePathLength() {
	if (!dist) {
		getShortestPaths();
	}

	double average = 0;
	for (int i = 0; i < EntIn; i++) {
		for (int j = 0; j < EntIn; j++) {
			average = average + dist[i][j];
		}
	}
	average = average / ((EntIn - 1) * EntIn); // -1 to exclude distance from self (diagonal)
	return average;

}
