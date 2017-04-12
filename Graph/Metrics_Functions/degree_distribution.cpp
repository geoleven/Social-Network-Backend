#include "../graph.h"
#include "../../Entities/entities.h"
#include "../../List_Template/list.h"
#include <fstream>
#include <cstdlib>

using namespace std;

void Graph::degreeDistribution(bool directed) {
	List<Info> info_list(false);
	ofstream graph_data;
	if (!directed) {
		for (int k = 0; k < graph->htcurSize; k++) {
			// for all buckets
			int bucket_size = graph->hashTable[k]->getEntIn();
			for (int j = 0; j < bucket_size; j++) {
				// for all entries
				int known_persons_size =
						graph->hashTable[k]->get(j)->get_knows_person()->getSize();
				known_persons_size *= 2;	// undirected graph
				Info *temp;
				// search for other entry that knows same number of persons
				if ((temp = info_list.search(known_persons_size)) == NULL) {
					// if not found create entry
					info_list.pushBack(new Info(1, known_persons_size));
				} else {
					// else add 1 person
					temp->x_coord++;
				}
			}
		}
	} else {
		// almost the same but for directed graph
		for (int k = 0; k < graph->htcurSize; k++) {
			int bucket_size = graph->hashTable[k]->getEntIn();
			for (int j = 0; j < bucket_size; j++) {
				Person* temp_node = graph->hashTable[k]->get(j);
				int known_persons_size =
						temp_node->get_knows_person()->getSize();
				for (int o = 0; o < graph->htcurSize; o++) {
					int bucket_size2 = graph->hashTable[o]->getEntIn();
					for (int u = 0; u < bucket_size2; u++) {
						if (graph->hashTable[o]->get(u)->get_knows_person()->search(
								temp_node->id)) {
							known_persons_size++;
						}
					}
				}
				Info *temp;
				if ((temp = info_list.search(known_persons_size)) == NULL) {
					info_list.pushBack(new Info(1, known_persons_size));
				} else {
					temp->x_coord++;
				}
			}
		}
	}
	graph_data.open("graph_data.txt");
	for (int j = 0; j < info_list.getSize(); j++) {
		graph_data << ((info_list.get(j)->x_coord)/EntIn) << "\t"
				<< info_list.get(j)->y_coord << endl;
	}
	graph_data.close();
	system("gnuplot plot_data.p");
	remove("graph_data.txt");
	//system("eog distribution.png"); pops up distribution image, but doesn't work as expected
}

