#include "../graph.h"
#include <iostream>

using namespace std;

HashTable<Person>* Graph::getTopStalkers(int k, int x, int centralityMode,
		List<Stalker>* st) {
	int i = 0;
	int j = 0;
	HashTable<Person> *g = new HashTable<Person>(4, 4);
	Person *cur_person;
	int count = 0;
	List<Stalker>* lst = new List<Stalker>(false);
	while (count < EntIn) {
		cur_person = graph->hashTable[i]->get(j);
		if (cur_person == NULL) {
			i++;
			j = 0;
		} else {
			j++;
			count++;
			int creator_id;
			List<Likes> *person_likes = new List<Likes>(false);
			for (int c = 0; c < cur_person->likes_post->getSize(); c++) {
				creator_id = cur_person->likes_post->get(c)->creatorId;
				if (creator_id == 0 || creator_id == cur_person->id)
					continue;
				if (cur_person->knows_person->search(creator_id) == NULL
						|| graph->lookupNode(creator_id)->knows_person->search(
								cur_person->id) == NULL) {
					if (person_likes->search(creator_id) != NULL) {
						person_likes->search(creator_id)->likes += 1;
					} else {
						person_likes->pushBack(new Likes(creator_id));
					}
				}
			}
			for (int c = 0; c < person_likes->getSize(); c++) {
				if ((person_likes->get(c)->likes) > x) {
					// he's a stalker
					g->insertNode(cur_person);
					g->sort();
					Stalker *s = new Stalker(cur_person->id, -1);
					if (centralityMode == 1) {
						s->score = closenessCentrality(cur_person);
					} else {
						s->score = betweennessCentrality(cur_person);
					}
					lst->pushBack(s);
					break;
				}
			}
			delete person_likes;
		}
	}
	for (int c = 0; c < k; c++) {
		Stalker* max = lst->get(0);
		for (int g = 1; g < lst->getSize(); g++) {
			if (max->score < lst->get(g)->score) {
				max = lst->get(g);
			}
		}
		Stalker* nmax = new Stalker(max->id, max->score);
		st->pushBack(nmax);
		lst->remove(max);
	}
	delete lst;
	return g;
}
