#include "../graph.h"
#include "../mQuickSort.h"

#include <iostream>
#include <cstring>

//int partition(int* tl /*taglist reference*/, int* hl /*hitlist reference*/, int l, int r) {
//	int pivot, i, j, t1, t2;
//	pivot = hl[l];
//	i = l;
//	j = r+1;
//	while(1) {
//		do ++i; while (hl[i] <= pivot && i <= r);
//		do --j; while (hl[j] > pivot);
//		if (i >= j)
//			break;
//		t1 = hl[i];  t2 = tl[i];
//		hl[i] = hl[j];  tl[i] = tl[j];
//		hl[j] = t1;  tl[j] = t2;
//	}
//	t1 = hl[l];  t2 = tl[l];
//	hl[l] = hl[j];  tl[l] = tl[j];
//	hl[j] = t1;  tl[j] = t2;
//	return j;
//}
//
//void qs(int* tl /*taglist reference*/, int* hl /*hitlist reference*/, int l, int r) {
//	/*http://www.comp.dit.ie/rlawlor/Alg_DS/sorting/quickSort.c*/
//	int j = 0;
//	if (l < r) {
//		j = partition(tl, hl, l, r);
//		qs(tl, hl, l, j-1);
//		qs(tl, hl, j+1, r);
//	}
//}

int visit_tables(int* visited, int* allpers, int per_id, int alln) {
	for (int counter = 0; counter < alln; counter++) {
		if (allpers[counter] == per_id) {
			if (visited[counter] == 0) {
				visited[counter] = 1;
				return 1;
			}
			else {
				return 2;
			}
		}
	}
	return 0;
}

void otherswithtag(int* hits, int* visited, int mytag, int gc, Person* cp, int* allpers, int alln) {
	int visit = visit_tables(visited, allpers, cp->id, alln);
	if (visit) {
		if (visit == 2)
			return;
		if (cp->has_interest->search(mytag) && cp->gender == gc) {
			(*hits)++;
			for (int others = 0; others < cp->knows_person->getSize(); others++) {
				otherswithtag(hits, visited, mytag, gc, (cp->knows_person->get(others)->end), allpers, alln);
			}
		}
	}
	else {
		cout << "Weird things happening.. (@Graph::otherswithtag)" << endl;
	}
	return;
}


void Graph::findTrends(int num, char** womenTrends/*Address of a pointer to char* */, char** menTrends) {
	int taghitsm[tags->EntIn];
	int taghitsw[tags->EntIn];
	for (int ttc = 0; ttc < tags->EntIn; ttc++) {
		taghitsm[ttc] = 0;
		taghitsw[ttc] = 0;
	}
	int* alltags = tags->getAllNodeID();
	int* allpers = graph->getAllNodeID();
	for (int gc = 0; gc < 2; gc++) {
		for (int mc = 0; mc < tags->EntIn; mc++) {
			for (int pc = 0; pc < graph->EntIn; pc++) {
				int myhits = 0;
				int visited[EntIn];
				int mytag = alltags[mc];
				Person* cp = graph->lookupNode(allpers[pc]);
				for (int t1 = 0; t1 < graph->EntIn; t1++)
					visited[t1] = 0;
				otherswithtag(&myhits, visited, mytag, gc, cp, allpers, EntIn);
				if (gc) {
					if (myhits > taghitsw[mc])
						taghitsw[mc] = myhits;
				}
				else {
					if (myhits > taghitsm[mc])
						taghitsm[mc] = myhits;
				}
			}
		}
	}
	int* atm = alltags;
	int* atw = tags->getAllNodeID();
	int ml = tags->EntIn-1;
	qs(atm, taghitsm, 0, ml);
	qs(atw, taghitsw, 0, ml);
	for(int tc = 0; tc < num; tc++, ml--) {
		if(tags->lookupNode(atm[ml]) != NULL && taghitsm[ml] > 1) {
			menTrends[tc] = new char[50];
			strcpy(menTrends[tc], tags->lookupNode(atm[ml])->name.c_str());
			//cout << "Man " << tc+1 << " with id " << atm[ml] << " " << menTrends[tc] << " hits: " << taghitsm[ml] << endl;
		} else menTrends[tc] = NULL;
		if(tags->lookupNode(atw[ml]) != NULL && taghitsw[ml] > 1) {
			womenTrends[tc] = new char[50];
			strcpy(womenTrends[tc], tags->lookupNode(atw[ml])->name.c_str());
			//cout << "Woman " << tc+1 << " with id " << atw[ml] << " " << womenTrends[tc] << " hits: " << taghitsw[ml] << endl;
		} else womenTrends[tc] = NULL;

	}

	delete[] alltags;
	delete[] allpers;
	delete[] atw;

	return;
}
