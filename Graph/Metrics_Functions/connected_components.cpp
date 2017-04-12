#include "../graph.h"
#include "../../Entities/entities.h"

#include <iostream>

using namespace std;

int Graph::numberOfCCs() {

	int Nodes[EntIn][2]; // 0 -> node id, 1 -> explored

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
			Nodes[count][0] = temp->id;
			Nodes[count][1] = 0;
			count++;
		}
	}

	int exploredNodes = 0;
	int numOfCCs = 0;

	while (exploredNodes < EntIn) {
		numOfCCs++;

		int startingNode;
		int count = 0;
		while (Nodes[count][1] == 1) {
			// bypass already explored nodes
			count++;
		}
		Nodes[count][1] = 1;
		exploredNodes++;
		startingNode = Nodes[count][0];

		ResultSet* rs = reachNodeN(startingNode);
		//cout<<"starting Node is "<<startingNode<<endl;
		while (next(rs) == false) {
			//cout << startingNode << " is connected to " << rs->pair->id << endl;
			for (int j = 0; j < EntIn; j++) {
				if (Nodes[j][0] == rs->pair->id) {
					Nodes[j][1] = 1;
					exploredNodes++;
					break;
				}
			}
		}
	}
	return numOfCCs;
}

int Graph::maxCC() {

	int Nodes[EntIn][2];

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
			Nodes[count][0] = temp->id;
			Nodes[count][1] = 0;
			count++;
		}
	}

	int exploredNodes = 0;
	int maxCC = 0;

	while (exploredNodes < EntIn) {
		int curCC = 1;
		int startingNode;
		int count = 0;
		while (Nodes[count][1] == 1) {
			count++;
		}
		Nodes[count][1] = 1;
		exploredNodes++;
		startingNode = Nodes[count][0];

		ResultSet* rs = reachNodeN(startingNode);
		while (next(rs) == false) {
			curCC++;
			for (int j = 0; j < EntIn; j++) {
				if (Nodes[j][0] == rs->pair->id) {
					Nodes[j][1] = 1;
					exploredNodes++;
					break;
				}
			}
		}
		if (maxCC < curCC)
			maxCC = curCC;
	}
	return maxCC;
}
