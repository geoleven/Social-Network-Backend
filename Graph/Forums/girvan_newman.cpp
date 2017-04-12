#include "../graph.h"

using namespace std;

int get_posit(int *, int, int);
int** calculate_distances(HashTable<Person> *, int*);
void da_floyd_warshall(int***, int);
int calculate_shortest_paths(int**, int, int, int);
int calculate_shortest_paths_from_edge(int **, int, int, int, int, int);
void edgeBetweenness(int *, int **, int, double**);

Communities* GirvanNewman(double modularity, HashTable<Person>* ht) {
	int *nodes = ht->getAllNodeID();
	int **distances = calculate_distances(ht, nodes);
	HashTable<Person> gtest(4, 4);
	Person *p1 = new Person(1);
	Person *p2 = new Person(2);
	Person *p3 = new Person(3);
	Person *p4 = new Person(4);
	Person *p5 = new Person(5);
	Person *p6 = new Person(6);
	Person *p7 = new Person(7);
	Person *p8 = new Person(8);
	Person *p9 = new Person(9);
	p1->knows_person->pushBack(new Edge<Person>(p2));
	p1->knows_person->pushBack(new Edge<Person>(p3));
	p1->knows_person->pushBack(new Edge<Person>(p4));
	p2->knows_person->pushBack(new Edge<Person>(p1));
	p2->knows_person->pushBack(new Edge<Person>(p3));
	p3->knows_person->pushBack(new Edge<Person>(p1));
	p3->knows_person->pushBack(new Edge<Person>(p2));
	p3->knows_person->pushBack(new Edge<Person>(p4));
	p4->knows_person->pushBack(new Edge<Person>(p1));
//	double temp = (double) all_sp[w][k];
	//					double temp2 = 0;
	//					double temp3 = 0;
	//					double temp4 = 0;
	//					double temp5 = 0;
	//					double min = 0;
	//					if (dist[i][j] == 1) {
	//						temp2 = (double) all_sp[i][k];
	//						temp3 = (double) all_sp[w][j];
	//						temp4 = (double) all_sp[i][w];
	//						temp5 = (double) all_sp[j][k];
	//						if (temp2 * temp3 < temp4 * temp5) {
	//							min = temp2 * temp3;
	//						} else {
	//							min = temp4 * temp5;
	//						}
	//						if ((i == w && j == k) || (i == k && j == w)) {
	//							min = 1;
	//						}
	//						if (dist[w][i] > dist[w][k] || dist[w][j] > dist[w][k]
	//								|| dist[k][i] > dist[w][k]
	//								|| dist[k][j] > dist[w][k]) {
	//							min = 0;
	//						}
	//						cout << nodes[i] << ", " << nodes[j] << " " << nodes[w]
	//								<< " " << nodes[k] << " " << min << endl;
	//					}
	p4->knows_person->pushBack(new Edge<Person>(p3));
	p4->knows_person->pushBack(new Edge<Person>(p5));
	p4->knows_person->pushBack(new Edge<Person>(p6));
	p5->knows_person->pushBack(new Edge<Person>(p4));
	p5->knows_person->pushBack(new Edge<Person>(p6));
	p5->knows_person->pushBack(new Edge<Person>(p7));
	p5->knows_person->pushBack(new Edge<Person>(p8));
	p6->knows_person->pushBack(new Edge<Person>(p4));
	p6->knows_person->pushBack(new Edge<Person>(p5));
	p6->knows_person->pushBack(new Edge<Person>(p7));
	p6->knows_person->pushBack(new Edge<Person>(p8));
	p7->knows_person->pushBack(new Edge<Person>(p5));
	p7->knows_person->pushBack(new Edge<Person>(p6));
	p7->knows_person->pushBack(new Edge<Person>(p8));
	p7->knows_person->pushBack(new Edge<Person>(p9));
	p8->knows_person->pushBack(new Edge<Person>(p5));
	p8->knows_person->pushBack(new Edge<Person>(p6));
	p8->knows_person->pushBack(new Edge<Person>(p7));
	p9->knows_person->pushBack(new Edge<Person>(p7));
	gtest.insertNode(p1);
	gtest.insertNode(p2);
	gtest.insertNode(p3);
	gtest.insertNode(p4);
	gtest.insertNode(p5);
	gtest.insertNode(p6);
	gtest.insertNode(p7);
	gtest.insertNode(p8);
	gtest.insertNode(p9);
	gtest.sort();
	int *nodestest = gtest.getAllNodeID();
	int **distancestest = calculate_distances(&gtest, nodestest);
	double **cb = new double*[gtest.EntIn];
	for (int i = 0; i < gtest.EntIn; i++) {
		cb[i] = new double[gtest.EntIn];
	}
	edgeBetweenness(nodestest, distancestest, gtest.EntIn, cb);
	for (int i = 0; i < gtest.EntIn; i++) {
		for (int j = 0; j < gtest.EntIn; j++) {
			cout
					<< cb[get_posit(nodestest, gtest.EntIn, i + 1)][get_posit(
							nodestest, gtest.EntIn, j + 1)] << "\t";
		}
		cout << endl;
	}
}

void edgeBetweenness(int *nodes, int **dist, int size, double **cb) {
	int all_sp[size][size];
	for (int i = 0; i < size - 1; i++) {
		for (int j = i; j < size; j++) {
			int temp = calculate_shortest_paths(dist, i, j, size);
			all_sp[i][j] = temp;
			all_sp[j][i] = temp;
		}
	}
	for (int i = 0; i < size; i++) {
		all_sp[i][i] = 0;
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cb[i][j] = 0.0;
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				for (int w = 0; w < size; w++) {
					double temp = (double) all_sp[w][k];
					double temp2 = 0;
					if (dist[i][j] == 1)
						temp2 = calculate_shortest_paths_from_edge(dist, w, k,
								size, i, j);
//					double temp2 = 0;
//					double temp3 = 0;
//					double temp4 = 0;
//					double temp5 = 0;
//					double min = 0;
//					if (dist[i][j] == 1) {
//						temp2 = (double) all_sp[i][k];
//						temp3 = (double) all_sp[w][j];
//						temp4 = (double) all_sp[i][w];
//						temp5 = (double) all_sp[j][k];
//						if (temp2 * temp3 < temp4 * temp5) {
//							min = temp2 * temp3;
//						} else {
//							min = temp4 * temp5;
//						}
//						if ((i == w && j == k) || (i == k && j == w)) {
//							min = 1;
//						}
//						if (dist[w][i] > dist[w][k] || dist[w][j] > dist[w][k]
//								|| dist[k][i] > dist[w][k]
//								|| dist[k][j] > dist[w][k]) {
//							min = 0;
//						}
//						cout << nodes[i] << ", " << nodes[j] << " " << nodes[w]
//								<< " " << nodes[k] << " " << min << endl;
//					}
					if (temp != 0) {
						cb[i][j] += temp2 / temp;
					}
				}
			}
		}
	}
}

int get_posit(int *nodes, int size, int id) {
	for (int i = 0; i < size; i++) {
		if (nodes[i] == id)
			return i;
	}
	return -1;
}

int calculate_shortest_paths(int **dist2, int x, int y, int n) {
	int dist[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = dist2[i][j];
		}
	}
	if (dist[x][y] != 0) {
		int s_paths = 1;
		int max_dist = dist[x][y];
		for (int i = 0; i < n; i++) {
			if (dist[x][i] + dist[i][y] > max_dist) {
				for (int j = 0; j < n; j++) {
					dist[i][j] = 0;
					dist[j][i] = 0;
				}
			}
		}
		for (int d = 0; d < max_dist; d++) {
			for (int i = 0; i < n; i++) {
				if (dist[x][i] == d) {
					int no_edges = 0;
					for (int j = 0; j < n; j++) {
						if (dist[x][j] == d + 1 && dist[i][j] == 1)
							no_edges++;
					}
					if (no_edges >= 2)
						s_paths = no_edges * s_paths;
				}
			}
		}
		return s_paths;
	} else {
		return 0;
	}
}

int calculate_shortest_paths_from_edge(int **dist2, int x, int y, int n, int k,
		int z) {
	int dist[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = dist2[i][j];
		}
	}
	if (dist[x][y] != 0) {
		int s_paths = 1;
		int max_dist = dist[x][y];
		for (int i = 0; i < n; i++) {
			if (dist[x][i] + dist[i][y] > max_dist) {
				for (int j = 0; j < n; j++) {
					dist[i][j] = 0;
					dist[j][i] = 0;
				}
			}
		}
		int min_dist, min_pos;
		if (dist[x][k] < dist[z][k]) {
			min_dist = dist[x][k];
			min_pos = k;
		} else {
			min_dist = dist[z][k];
			min_pos = z;
		}
		for (int i = 0; i < n; i++) {
			if (dist[i][x] == min_dist && i != min_pos) {
				for (int j = 0; j < n; j++) {
					dist[i][j] = 0;
					dist[j][i] = 0;
				}
			}
		}
		for (int d = 0; d < max_dist; d++) {
			for (int i = 0; i < n; i++) {
				if (dist[x][i] == d) {
					int no_edges = 0;
					for (int j = 0; j < n; j++) {
						if (dist[x][j] == d + 1 && dist[i][j] == 1)
							no_edges++;
					}
					if (no_edges >= 2)
						s_paths = no_edges * s_paths;
				}
			}
		}
		return s_paths;
	} else {
		return 0;
	}
}

int** calculate_distances(HashTable<Person> *ht, int *nodes) {
	int **distances = new int*[ht->EntIn];
	for (int i = 0; i < ht->EntIn; i++) {
		distances[i] = new int[ht->EntIn];
	}
	for (int i = 0; i < ht->EntIn; i++) {
		for (int j = 0; j < ht->EntIn; j++) {
			if (ht->lookupNode(nodes[i])->knows_person->search(
					ht->lookupNode(nodes[j])->id) != NULL) {
				distances[i][j] = 1;
			} else {
				distances[i][j] = 0;
			}
		}
	}
	da_floyd_warshall(&distances, ht->EntIn);
	return distances;
}

void da_floyd_warshall(int*** dist, int n) {
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
