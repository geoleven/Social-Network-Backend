#include "../graph.h"
#include "../../Entities/entities.h"

#include <iostream>

using namespace std;

double Graph::density() {
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
	int e = 0;
	List<Edge<Person> >* kp;
	for (int j = 0; j < EntIn; j++) {
		if ((temp = graph->lookupNode(Nodes[j])) == NULL)
			cout << "Node " << j << " cannot be found" << endl;
		if ((kp = temp->get_knows_person()) == NULL)
			cout << "List of Node " << j << " cannot be found" << endl;
		e += kp->getSize();
	}
	return (2 * (double) e / ((double) EntIn * ((double) EntIn - 1)));
}