#include "../graph.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
using namespace std;

Match::Match() {
	id = 0;
	score = 0;
	size = 0;
}

Match::~Match() {

}

void Match::print() {
	cout << "[id: " << id << " - score: " << score << "]" << endl;
}

Match* Graph::matchSuggestion(Person* n, int k, int h, int x, int limit) {

	Person* p = graph->lookupNode(n->id);

	Match* matches = new Match[limit];
	for (int i = 0; i < limit; i++) {
		matches[i].id = -1;
	}

	List<Match> *match_list = new List<Match>(true);

	if (p->worksAt == NULL && p->studiedAt == NULL) {
		cout << "Person " << p->id << " does not work or studies anywhere"
				<< endl;
	}

	ResultSet* rs = reachNodeN(p->id);

	while (next(rs) == false && rs->pair->distance <= h) { //Look h steps deep
		Person* m = rs->pair->p;
		int intersection_size = 0;
		int union_size = 0;
		double jaccard_index;
		if (p->gender != m->gender) {
			if ((p->birthday.year - m->birthday.year <= x)
					&& (p->birthday.year - m->birthday.year >= -x)) {
				bool hasCommon = false;

				if (m->lives_in != NULL && p->lives_in != NULL) {
					if (m->lives_in->id == p->lives_in->id)
						hasCommon = true;
				}
				if (m->worksAt->getSize() != 0 && p->worksAt->getSize() != 0) {
					for (int w = 0; w < p->worksAt->getSize(); w++) {
						if (m->worksAt->search(p->worksAt->get(w)->id)) {
							hasCommon = true;
							break;
						}
					}
				}
				if (m->studiedAt->getSize() != 0
						&& p->studiedAt->getSize() != 0) {
					for (int w = 0; w < p->studiedAt->getSize(); w++) {
						if (m->studiedAt->search(p->studiedAt->get(w)->id)) {
							hasCommon = true;
							break;
						}
					}
				}

				if (hasCommon) {
					intersection_size = 0;
					union_size = 0;
					if (p->has_interest->getSize() == 0
							&& m->has_interest->getSize() == 0) {
						jaccard_index = 1.0;
					} else {
						for (int i = 0; i < p->has_interest->getSize(); i++) {
							Tag* pint = p->has_interest->get(i);
							for (int j = 0; j < m->has_interest->getSize();
									j++) {
								if (pint->id == m->has_interest->get(j)->id) {
									intersection_size++;
								}
							}
						}
						union_size = p->has_interest->getSize()
								+ m->has_interest->getSize()
								- intersection_size;
						jaccard_index = double(
								(double) intersection_size
										/ (double) union_size);
					}
				}
			}
		}
		if (intersection_size >= k) {
			Match *tmatch = new Match();
			tmatch->score = 1 - jaccard_index;
			tmatch->id = m->id;
			match_list->pushBack(tmatch);
		}
	}

	for (int i = 0; i < limit; i++) {
		Match *max = match_list->get(0);
		for (int j = 0; j < match_list->getSize(); j++) {
			if (max->score < match_list->get(j)->score) {
				max = match_list->get(j);
			}
		}
		if (max != NULL) {
			matches[i].id = max->id;
			matches[i].score = max->score;
			match_list->remove(max);
			matches->size += 1;
		} else {
			break;
		}
	}
	if (rs != NULL)
		delete rs;

	/*Allaksa*/
	delete match_list;

	return matches;
}
