#include "graph.h"

#include <iostream>

#define ALLDATA 1

using namespace std;

Graph::Graph(int m, int c) {

	graph = new HashTable<Person>(m, c);

	forums = new HashTable<Forum>(m, c);

	orgs = new HashTable<Organisation>(m, c);

	places = new HashTable<Place>(m, c);

	posts = new HashTable<Post>(m, c);

	tags = new HashTable<Tag>(m, c);

	trustGraph = NULL;

	EntIn = 0;
	dist = NULL;

}

Graph::~Graph() {
	//cout<<endl;
	delete graph;
	//cout<<"Deleted Graph"<<endl;
	delete forums;
	//cout<<"Deleted Forum"<<endl;
	delete orgs;
	//cout<<"Deleted Organisation"<<endl;
	delete places;
	//cout<<"Deleted Place"<<endl;
	delete posts;
	//cout<<"Deleted Post"<<endl;
	delete tags;
	//cout<<"Deleted Tag"<<endl;
	//deleteTrustGraph();
}

void Graph::LoadData() {
	string path;

	cout << "Loading person.csv..." << endl;
	cout.flush();
	path = "./dataset/person.csv";
	insertPerson(graph, path);
	graph->sort();
	setEntIn();
	cout << "Done" << endl;

	cout << "Loading person_knows_person.csv..." << endl;
	cout.flush();
	path = "./dataset/person_knows_person.csv";
	insertPersonKnowsPerson(graph, path);
	graph->sort();
	cout << "Done" << endl;

	cout << "Loading forum.csv..." << endl;
	cout.flush();
	path = "./dataset/forum.csv";
	insertForum(forums, path);
	forums->sort();
	cout << "Done" << endl;

	cout << "Loading organisation.csv..." << endl;
	cout.flush();
	path = "./dataset/organisation.csv";
	insertOrganisation(orgs, path);
	orgs->sort();
	cout << "Done" << endl;

	cout << "Loading place.csv..." << endl;
	cout.flush();
	path = "./dataset/place.csv";
	insertPlace(places, path);
	places->sort();
	cout << "Done" << endl;

	if (ALLDATA) {
		cout << "Loading post.csv..." << endl;
		cout.flush();
		path = "./dataset/post.csv";
		insertPost(posts, path);
		posts->sort();
		cout << "Done" << endl;

		cout << "Loading comment_replyOf_post.csv..." << endl;
		cout.flush();
		path = "./dataset/comment_replyOf_post.csv";
		insertComments(posts, path);
		posts->sort();
		cout << "Done" << endl;
	}

	cout << "Loading tag.csv...";
	cout.flush();
	path = "./dataset/tag.csv";
	insertTag(tags, path);
	tags->sort();
	cout << "Done" << endl;
	cout << endl;

	cout << "Loading person_studyAt_organisation.csv..." << endl;
	cout.flush();
	path = "./dataset/person_studyAt_organisation.csv";
	insertStudy(graph, orgs, path);
	graph->sort();
	orgs->sort();
	cout << "Done" << endl;

	cout << "Loading person_workAt_organisation.csv..." << endl;
	cout.flush();
	path = "./dataset/person_workAt_organisation.csv";
	insertWork(graph, orgs, path);
	graph->sort();
	orgs->sort();
	cout << "Done" << endl;

	cout << "Loading person_hasInterest_tag.csv..." << endl;
	cout.flush();
	path = "./dataset/person_hasInterest_tag.csv";
	insertInterest(graph, tags, path);
	graph->sort();
	tags->sort();
	cout << "Done" << endl;

	cout << "Loading person_isLocated_place.csv..." << endl;
	cout.flush();
	path = "./dataset/person_isLocatedIn_place.csv";
	insertLocation(graph, places, path);
	graph->sort();
	places->sort();
	cout << "Done" << endl;

	cout << "Loading forum_hasMember_person.csv..." << endl;
	cout.flush();
	path = "./dataset/forum_hasMember_person.csv";
	insertForumMembers(forums, graph, path);
	forums->sort();
	graph->sort();
	cout << "Done" << endl;

	if (ALLDATA) {
		cout << "Loading forum_containerOf_post.csv..." << endl;
		cout.flush();
		path = "./dataset/forum_containerOf_post.csv";
		insertForumPosts(forums, posts, path);
		forums->sort();
		posts->sort();
		cout << "Done" << endl;


		cout << "Loading comment_hasCreator_person.csv..." << endl;
		cout.flush();
		path = "./dataset/comment_hasCreator_person.csv";
		insertCommentCreator(graph, posts, path);
		graph->sort();
		cout << "Done" << endl;

		cout << "Loading post_hasCreator_person.csv..." << endl;
		cout.flush();
		path = "./dataset/post_hasCreator_person.csv";
		insertPostHasCreator(posts, path);
		graph->sort();
		posts->sort();
		insertCreatedPosts(graph, posts, path);
		graph->sort();
		posts->sort();
		cout << "Done" << endl;

		cout << "Loading person_likes_post.csv..." << endl;
		cout.flush();
		path = "./dataset/person_likes_post.csv";
		insertLike(graph, posts, path);
		graph->sort();
		posts->sort();
		cout << "Done" << endl;
	}

	cout << endl;
}

void Graph::setEntIn() {
	EntIn = graph->getEntIn();
}

ForumPersons::ForumPersons(int mid, HashTable<Person>* h) {
	id = mid;
	ht = h;
}

ForumPersons::ForumPersons(const ForumPersons& old) {
	id = old.id;
	ht = new HashTable<Person>(*(old.ht));
}

ForumPersons::~ForumPersons() {
	if (ht != NULL) {
		delete ht;
	}
}
