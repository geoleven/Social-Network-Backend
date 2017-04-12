#include "../graph.h"

using namespace std;

bool check_clique(int clq[], int size, HashTable<Person> *ht) {
	Person *cur_person1 = NULL;
	Person *cur_person2 = NULL;
	for (int i = 0, j = 1; j < size; i++, j++) {
		if (clq[i] != -1 && clq[j] != -1) {
			cur_person1 = ht->lookupNode(clq[i]);
			cur_person2 = ht->lookupNode(clq[j]);
			if (cur_person1->knows_person->search(cur_person2->id) != NULL
					&& cur_person2->knows_person->search(cur_person1->id)
							!= NULL)
				continue;
			else
				return false;
		}
	}
	return true;
}

bool creatEdge(Community *com1, Community *com2, int size) {
	int* members1 = com1->members;
	int* members2 = com2->members;

	int same = 0;
	for (int j = 0; j < size; j++) {
		for (int w = 0; w < size; w++) {
			if (members1[j] == members2[w]) {
				same++;
				break;
			}
		}
	}
	if (same == size - 1)
		return true;
	return false;
}

bool table_exists(int *A, int *B, int size) {
	int p[size];
	for (int i = 0; i < size; i++) {
		p[i] = B[i];
	}
	for (int i = 0; i < size; i++) {
		bool found = false;
		for (int j = 0; j < size; j++) {
			if (A[i] == p[j]) {
				p[j] = -1;
				found = true;
				break;
			}
		}
		if (found == false)
			return found;
	}
	return true;
}

bool clique_exists(int clq[], List<Community>* cliques, int size) {
	for (int i = 0; i < cliques->getSize(); i++) {
		int *cl = cliques->get(i)->members;
		int same = 0;
		for (int j = 0; j < size; j++) {
			for (int w = 0; w < size; w++) {
				if (clq[j] == cl[w]) {
					same++;
					break;
				}
			}
		}
		if (same == size) {
			return true;
		}
	}
	return false;
}

void printhtwf(HashTable<Person> *ht) {
	Person *cur_person = NULL;
	int count = 0;
	int l = 0;
	int s = 0;
	while (count < ht->EntIn) {
		cur_person = ht->hashTable[l]->get(s);
		if (cur_person == NULL) {
			l++;
			s = 0;
		} else {
			s++;
			count++;
			cout << "Person: " << cur_person->id << " has friends: ";
			for (int j = 0; j < cur_person->knows_person->getSize(); j++) {
				cout << cur_person->knows_person->get(j)->id << ", ";
			}
			cout << endl;
		}
	}
	cout << endl;
}

Communities* cliquePercolationMethod(int k, ForumPersons* g) {
	int cur_clique[k];
	List<Community> *cliques = new List<Community>(false);
	HashTable<Person> *ht = g->ht;
	int *nodes = ht->getAllNodeID();
	for (int i = 0; i < ht->EntIn; i++) {
		int pos = 0;
		for (int l = 0; l < k; l++) {
			cur_clique[l] = -1;
		}
		int id = nodes[i];
		cur_clique[pos] = id;
		pos++;
		Person *cur_person = ht->lookupNode(id);
		Person *per_friend = NULL;
		int left_size = cur_person->knows_person->getSize();
		if (left_size > k) {
			left_size = k - 1;
		}
		for (int j = 0; j < cur_person->knows_person->getSize(); j++) {
			per_friend = cur_person->knows_person->get(j)->end;
			cur_clique[pos] = per_friend->id;
			if (check_clique(cur_clique, k, ht) == false) {
				cur_clique[pos] = -1;
			} else {
				pos++;
			}
			if (pos == k) {
				if (!clique_exists(cur_clique, cliques, k)) {
					Community* cl = new Community(0);
					cl->length = k;
					for (int p = 0; p < k; p++) {
						cl->members[p] = cur_clique[p];
					}
					cliques->pushBack(cl);
				}
				for (int i = k; i >= left_size; i--) {
					cur_clique[i] = -1;
					pos--;
				}
				left_size--;
			}

		}
	}
	HashTable<Community> *da_cliques = new HashTable<Community>(4, 4);
	for (int i = 0; i < cliques->getSize(); i++) {
		cliques->get(i)->id = i;
		da_cliques->insertNode(cliques->get(i));
	}
	da_cliques->sort();

	int *da_ids = da_cliques->getAllNodeID();

	for (int i = 0; i < da_cliques->EntIn; i++) {
		Community *com = da_cliques->lookupNode(da_ids[i]);
		for (int j = i; j < da_cliques->EntIn; j++) {
			Community *com2 = da_cliques->lookupNode(da_ids[j]);
			if (com->id != com2->id) {
				if (creatEdge(com, com2, k)) {
					if (com->edges->search(com2->id) == NULL)
						com->edges->pushBack(com2);
					if (com2->edges->search(com->id) == NULL)
						com2->edges->pushBack(com);
				}
			}
		}
	}
	Communities *result = new Communities();
	for (int i = 0; i < da_cliques->EntIn; i++) {
		Community *com = da_cliques->lookupNode(da_ids[i]);
		int edges_l = com->length;
		for (int j = 0; j < com->edges->getSize(); j++) {
			edges_l += com->edges->get(j)->length;
		}
		int com_table[edges_l];
		for (int j = 0; j < edges_l; j++) {
			com_table[j] = -1;
		}
		int j;
		for (j = 0; j < com->length; j++) {
			com_table[j] = com->members[j];
		};
		for (int l = 0; l < com->edges->getSize(); l++) {
			for (k = 0; k < com->edges->get(l)->length; k++) {
				bool put = true;
				for (int i = 0; i < edges_l; i++) {
					if (com_table[i] == com->edges->get(l)->members[k]) {
						put = false;
						break;
					}
				}
				if (put) {
					com_table[j] = com->edges->get(l)->members[k];
					j++;
				}
			}
		}
		int real_size = 0;
		for (int i = 0; i < edges_l; i++) {
			if (com_table[i] != -1) {
				real_size++;
			}
		}
		int *com_table_r = new int[real_size];
		for (int i = 0; i < real_size; i++) {
			com_table_r[i] = com_table[i];
		}
		bool exists = false;
		for (int i = 0; i < result->results->getSize(); i++) {
			int csize = result->results->get(i)->size;
			int *ctable = result->results->get(i)->cc;
			if (csize == real_size) {
				if (table_exists(ctable, com_table_r, real_size)) {
					exists = true;
					break;
				}
			}
		}
		if (!exists)
			result->results->pushBack(new CC(com_table_r, real_size));
	}
	return result;
}

