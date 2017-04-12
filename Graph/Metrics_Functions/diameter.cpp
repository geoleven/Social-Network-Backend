#include "../graph.h"
#include "../../Entities/entities.h"

#include <iostream>

using namespace std;

int Graph::diameter() {
	if (!dist) {
		getShortestPaths();
	}
	int max = 0;
	for (int i = 0; i < EntIn; i++) {
		for (int j = 0; j < EntIn; j++) {
			if (dist[i][j] > max)
				max = dist[i][j];
		}
	}
	return max;
}