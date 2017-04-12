#ifndef GRAPH_H_
#define GRAPH_H_

#include "../Hash_Table/hashTable.h"

class ForumPersons {
public:
	int id;
	HashTable<Person> * ht;
	ForumPersons(int mid, HashTable<Person>* h);
	ForumPersons(const ForumPersons& old);
	~ForumPersons();
};

class Likes {
public:
	int poster;
	int likes;
	int id;
	Likes(const Likes& old) {
		poster = old.poster;
		likes = old.likes;
		id = old.id;
	}
	Likes(int p) {
		id = p;
		poster = p;
		likes = 1;
	}
	~Likes() {
	}
};

class Stalker {
public:
	int id;
	float score;
	Stalker(const Stalker& old) {
		id = old.id;
		score = old.score;
	}
	Stalker(int ids, float scores) {
		id = ids;
		score = scores;
	}
	~Stalker() {
	}
};

class Info {
public:
	double x_coord;
	double y_coord;
	int id;			// keeps our list happy and functional :)
	Info(const Info& old) {
		x_coord = old.x_coord;
		y_coord = old.y_coord;
		id = old.id;
	}
	Info(double x, double y) {
		x_coord = x;
		y_coord = y;
		id = y;
	}
	~Info() {
	}
};

class Pair {
public:
	int id;
	int distance;
	Person *p;
	Pair();
	Pair(int, int);
	~Pair();
	void print();
};

class ResultSet {
public:
	Pair* pair;
	List<Pair> *Q;
	List<Person> *V;

	ResultSet();
	~ResultSet();
};

class Match {
public:
	int id;
	double score;
	int size;

	Match();
	~Match();

	void print();
};

class ForumMembers {
public:
	int members;
	int id;
	Forum* forum;

	ForumMembers(Forum* f, int m) {
		forum = f;
		members = m;
		id = f->id;
	}

	~ForumMembers() {
	}
};

class Community {
public:
	int id;
	int *members;
	List<Community> *edges;
	int length;

	Community(int size) {
		edges = new List<Community>(true);
		id = -1;
		members = new int[size];
		length = size;
	}
	~Community() {
		delete members;
	}
	void print_members() {
		cout << "(";
		for (int i = 0; i < length; i++) {
			cout << members[i];
			if (i != length - 1)
				cout << ", ";
		}
		cout << ")";
	}
};

class CC {
public:
	int id;
	int *cc;
	int size;

	CC(int *table, int s) {
		id = -1;
		cc = table;
		size = s;
	}
	~CC() {
	}
};

class Communities {
public:
	int id;
	List<CC> *results;

	Communities() {
		id = -1;
		results = new List<CC>(true);
	}
	~Communities() {
	}

	void print_coms() {
		for (int i = 0; i < results->getSize(); i++) {
			CC *temp = results->get(i);
			for (int j = 0; j < temp->size; j++) {
				cout << temp->cc[j] << " ";
			}
			cout << endl;
		}
	}
};

Communities* cliquePercolationMethod(int, ForumPersons*);
Communities* GirvanNewman(double, ForumPersons*);

class Graph {
public:
	HashTable<Person>* graph;
	HashTable<Forum>* forums;
	HashTable<Organisation>* orgs;
	HashTable<Place>* places;
	HashTable<Post>* posts;
	HashTable<Tag>* tags;

	HashTable<Person>* trustGraph;

	int** dist;
	int EntIn;

	Graph(int, int);
	~Graph();

	//Load data from .csv files
	void LoadData();

	//BFS 
	int reachNode1(int, int);
	ResultSet* reachNodeN(int);
	bool next(ResultSet*);

	//Metric Function
	int numberOfCCs();
	int maxCC();
	double averagePathLength();
	void degreeDistribution(bool);
	int diameter();
	double density();
	double closenessCentrality(Person*);
	double betweennessCentrality(Person*);

	void getShortestPaths();
	void removeShortestPaths();
	void printDist();
	void setEntIn();

	//Queries
	Match* matchSuggestion(Person*, int, int, int, int);

	void buildTrustGraph(int);
	void deleteTrustGraph();
	float estimateTrust(int, int, int);
	void findTrends(int num, char** womenTrends, char** menTrends);
	HashTable<Person>* getTopStalkers(int k, int x, int centralityMode,
			List<Stalker>* st);

	//TopNForums
	List<Forum>* topNForums(int);
	List<ForumPersons>* createNForumsGraphs(List<Forum>* topNForums);
//	void findCCs(CC**, int);
};

/* Data Input Funcs */
void insertPerson(HashTable<Person>* graph, string filepath);
void insertPersonKnowsPerson(HashTable<Person>* graph, string filepath);
void insertForum(HashTable<Forum>* graph, string filepath);
void insertOrganisation(HashTable<Organisation>* graph, string filepath);
void insertPlace(HashTable<Place>* graph, string filepath);
void insertPost(HashTable<Post>* graph, string filepath);
void insertTag(HashTable<Tag>* graph, string filepath);
void insertKnowsPerson(HashTable<Person>* graph, string filepath);
void insertStudy(HashTable<Person>* graph, HashTable<Organisation>* org,
		string filepath);
void insertWork(HashTable<Person>* graph, HashTable<Organisation>* org,
		string filepath);
void insertLike(HashTable<Person>* graph, HashTable<Post>* posts,
		string filepath);
void insertInterest(HashTable<Person>* graph, HashTable<Tag>* tag,
		string filepath);
void insertLocation(HashTable<Person>* graph, HashTable<Place>* place,
		string filepath);
void insertForumMembers(HashTable<Forum>* forums, HashTable<Person>* ppl,
		string filepath);
void insertForumPosts(HashTable<Forum>* forums, HashTable<Post>* post,
		string filepath);
void insertCreatedPosts(HashTable<Person>* graph, HashTable<Post>* post,
		string filepath);
void insertComments(HashTable<Post>* post, string filepath);
void insertCommentCreator(HashTable<Person>* graph, HashTable<Post>*,
		string filepath);
void insertPostHasCreator(HashTable<Post>* graph, string filepath);

#endif
