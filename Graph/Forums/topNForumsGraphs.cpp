#include "../graph.h"
#include "../mQuickSort.h"

#include <cstring>

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define HSM 4
#define HSC 4

typedef struct {
	HashTable<Person>* g;
	List<Forum>* tnf;
	pthread_mutex_t* mtx;
	int place;
	ForumPersons* res;
} t_args;

List<Forum>* Graph::topNForums(int N) {
	List<Forum>* topForums = new List<Forum>(true);
	Forum *cur_forum = NULL;
	int i = 0;
	int j = 0;
	int allF[forums->getEntIn()]; //= forums->getAllNodeID();
	int FS[forums->getEntIn()];
	for (int c = 0; c < forums->getEntIn(); c++) {
		cur_forum = forums->hashTable[i]->get(j);
		if (cur_forum == NULL) {
			i++;
			j = 0;
			c--;
		} else {
			j++;
			allF[c] = cur_forum->id;
			FS[c] = cur_forum->members->getSize();
		}
	}

	qs(allF, FS, 0, ((forums->EntIn) - 1));

	int ma = forums->getEntIn() - 1;
	for (int c = 0; c < N; c++, ma--) {
//		cout << forums->lookupNode(allF[ma])->title << " id: "
//				<< forums->lookupNode(allF[ma])->id << " size: "
//				<< forums->lookupNode(allF[ma])->members->getSize() << endl;
		topForums->pushBack(forums->lookupNode(allF[ma]));
	}
	//cout << "\n\n" << endl;

	return topForums;
}

static void* cNFG_thread(void* arg) {
	HashTable<Person>* g = ((t_args*) arg)->g;
	List<Forum>* tnf = ((t_args*) arg)->tnf;
	pthread_mutex_t* mutex = ((t_args*) arg)->mtx;
	int i = ((t_args*) arg)->place;
	HashTable<Person>* ht = new HashTable<Person>(HSM, HSC);
	for (int j = 0; j < tnf->get(i)->members->getSize(); j++) {
		Person *p = new Person(tnf->get(i)->members->get(j)->id);
		ht->insertNode(p);
	}
	ht->sort();
	for (int j = 0; j < tnf->get(i)->members->getSize(); j++) {
		Person *original_p = g->lookupNode(tnf->get(i)->members->get(j)->id);
		Person *p = ht->lookupNode(tnf->get(i)->members->get(j)->id);
		for (int l = 0; l < original_p->knows_person->getSize(); l++) {
			if (ht->lookupNode(original_p->knows_person->get(l)->id) != NULL) {
				p->knows_person->pushBack(
						new Edge<Person>(
								ht->lookupNode(
										original_p->knows_person->get(l)->id)));
			}
		}
	}
	pthread_mutex_lock(mutex);
	((t_args*) arg)->res = new ForumPersons(tnf->get(i)->id, ht);
	pthread_mutex_unlock(mutex);
	return (void*) NULL;
}

List<ForumPersons>* Graph::createNForumsGraphs(List<Forum>* topNForums) {
	List<ForumPersons>* result = new List<ForumPersons>(true);
	int N = topNForums->getSize();
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	pthread_attr_t attr;
	if (pthread_attr_init(&attr) != 0)
		cout << "Thread attribute initialization not completed" << endl;
	pthread_t tid[N];
	t_args myargs[N];
	for (int i = 0; i < N; i++) {
		tid[i] = 0;
		myargs[i].g = graph;
		myargs[i].tnf = topNForums;
		myargs[i].mtx = &mutex;
		myargs[i].place = i;
		myargs[i].res = NULL;
	}
	for (int i = 0; i < N; i++) {
		if (pthread_create(&(tid[i]), &attr, &cNFG_thread,
				(void*) (&myargs[i]))) {
			cout << "Error creating thread!" << endl;
		}
	}
	double trash = 0;
	for (int i = 0; i < N; i++) {
		pthread_join(tid[i], (void**) (&trash));
		result->pushBack(myargs[i].res);
	}
	return result;
}
