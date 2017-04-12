#include "graph.h"

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

void insertPerson(HashTable<Person>* graph, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	int pid, pbirthy, pbirthm, pbirthd, pcreaty, pcreatmo, pcreatd, pcreath,
			pcreatm, pcreats;
	string pfirstn, plastn, pip, pbrowser;
	Gender pgen;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);
			getline(streamline, token, '|');
			pid = atoi(token.c_str());
			getline(streamline, token, '|');
			pfirstn = token;
			getline(streamline, token, '|');
			plastn = token;
			getline(streamline, token, '|');
			if (token == "male")
				pgen = male;
			else
				pgen = female;
			getline(streamline, token, '|');
			stringstream streambirthday(token);
			getline(streambirthday, token, '-');
			pbirthy = atoi(token.c_str());
			getline(streambirthday, token, '-');
			pbirthm = atoi(token.c_str());
			getline(streambirthday, token, '-');
			pbirthd = atoi(token.c_str());
			getline(streamline, token, '|');
			stringstream streamcreat(token);
			getline(streamcreat, token, '-');
			pcreaty = atoi(token.c_str());
			getline(streamcreat, token, '-');
			pcreatmo = atoi(token.c_str());
			getline(streamcreat, token, 'T');
			pcreatd = atoi(token.c_str());
			getline(streamcreat, token, ':');
			pcreath = atoi(token.c_str());
			getline(streamcreat, token, ':');
			pcreatm = atoi(token.c_str());
			getline(streamcreat, token, 'Z');
			pcreats = atoi(token.c_str());
			getline(streamline, token, '|');
			pip = token;
			getline(streamline, token, '|');
			pbrowser = token;
			Person *person = new Person(pid, pfirstn, plastn, pgen, pbirthy,
					pbirthm, pbirthd, pcreaty, pcreatmo, pcreatd, pcreath,
					pcreatm, pcreats, pip, pbrowser);
			//person->print();
			graph->insertNode(person);
		}
	}
	file.close();
}

void insertPersonKnowsPerson(HashTable<Person>* graph, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);
			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());
			if (graph->lookupNode(startID) != NULL
					&& graph->lookupNode(endID) != NULL) {
				graph->lookupNode(startID)->insert_knows_person(
						graph->lookupNode(endID));
			} else {
				cout << "Node does not exist" << endl;
			}
		}
	}
	file.close();
}

void insertForum(HashTable<Forum>* graph, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	int pid, pcreaty, pcreatmo, pcreatd, pcreath, pcreatm, pcreats;
	string ptitle;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			pid = atoi(token.c_str());
			getline(streamline, token, '|');
			ptitle = token;
			getline(streamline, token, '|');
			stringstream streamcreat(token);
			getline(streamcreat, token, '-');
			pcreaty = atoi(token.c_str());
			getline(streamcreat, token, '-');
			pcreatmo = atoi(token.c_str());
			getline(streamcreat, token, 'T');
			pcreatd = atoi(token.c_str());
			getline(streamcreat, token, ':');
			pcreath = atoi(token.c_str());
			getline(streamcreat, token, ':');
			pcreatm = atoi(token.c_str());
			getline(streamcreat, token, 'Z');
			pcreats = atoi(token.c_str());

			Forum *forum = new Forum(pid, ptitle, pcreaty, pcreatmo, pcreatd,
					pcreath, pcreatm, pcreats);
			graph->insertNode(forum);
		}
	}
	file.close();
}

void insertOrganisation(HashTable<Organisation>* graph, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	int pid;
	string ptype, pname, purl;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			pid = atoi(token.c_str());
			getline(streamline, token, '|');
			ptype = token;
			getline(streamline, token, '|');
			pname = token;
			getline(streamline, token, '|');
			purl = token;
			Organisation *org = new Organisation(pid, ptype, pname, purl);
			graph->insertNode(org);
		}
	}
	file.close();
}

void insertPlace(HashTable<Place>* graph, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	int pid;
	string ptype, pname, purl;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			pid = atoi(token.c_str());
			getline(streamline, token, '|');
			pname = token;
			getline(streamline, token, '|');
			purl = token;
			getline(streamline, token, '|');
			ptype = token;

			Place *place = new Place(pid, pname, purl, ptype);
			graph->insertNode(place);
		}
	}
	file.close();
}

void insertPost(HashTable<Post>* graph, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	int pid, pcreaty, pcreatmo, pcreatd, pcreath, pcreatm, pcreats;
	string pimg, pip, pbrowser, plang, pcont;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			pid = atoi(token.c_str());
			getline(streamline, token, '|');
			pimg = token;
			getline(streamline, token, '|');
			stringstream streamcreat(token);
			getline(streamcreat, token, '-');
			pcreaty = atoi(token.c_str());
			getline(streamcreat, token, '-');
			pcreatmo = atoi(token.c_str());
			getline(streamcreat, token, 'T');
			pcreatd = atoi(token.c_str());
			getline(streamcreat, token, ':');
			pcreath = atoi(token.c_str());
			getline(streamcreat, token, ':');
			pcreatm = atoi(token.c_str());
			getline(streamcreat, token, 'Z');
			pcreats = atoi(token.c_str());
			getline(streamline, token, '|');
			pip = token;
			getline(streamline, token, '|');
			pbrowser = token;
			getline(streamline, token, '|');
			plang = token;
			getline(streamline, token, '|');
			pcont = token;

			Post *post = new Post(pid, pimg, pcreaty, pcreatmo, pcreatd,
					pcreath, pcreatm, pcreats, pip, pbrowser, plang, pcont);
			graph->insertNode(post);
		}
	}
	file.close();
}

void insertComments(HashTable<Post>* post, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());
			if (post->lookupNode(endID) != NULL) {
				Comment* c = new Comment(startID);
				post->lookupNode(endID)->comments->pushBack(c);
			} else {
				//cout << "Post " << endID << " does not exist" << endl;
			}
		}
	}
	file.close();
}

void insertTag(HashTable<Tag>* graph, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	int pid;
	string pname, purl;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			pid = atoi(token.c_str());
			getline(streamline, token, '|');
			pname = token;
			getline(streamline, token, '|');
			purl = token;

			Tag *tag = new Tag(pid, pname, purl);
			graph->insertNode(tag);
		}
	}
	file.close();
}

void insertStudy(HashTable<Person>* graph, HashTable<Organisation>* org,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID, classYear;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());
			getline(streamline, token, '|');
			classYear = atoi(token.c_str());

			if (graph->lookupNode(startID) != NULL) {
				if (org->lookupNode(endID) == NULL) {
//					cout << "Organisation " << endID << " does not exist."
//							<< endl;
				} else {
					graph->lookupNode(startID)->studiedAt->pushBack(
							org->lookupNode(endID));
					graph->lookupNode(startID)->classYear = classYear;
				}
			}
		}
	}
	file.close();
}

void insertWork(HashTable<Person>* graph, HashTable<Organisation>* org,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID, workFrom;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());
			getline(streamline, token, '|');
			workFrom = atoi(token.c_str());

			if ((graph->lookupNode(startID) != NULL)) {
				if (org->lookupNode(endID) == NULL) {
//					cout << "Organisation " << endID << " does not exits "
//							<< endl;
				} else {
					graph->lookupNode(startID)->worksAt->pushBack(
							org->lookupNode(endID));
					graph->lookupNode(startID)->workFrom = workFrom;
				}
			}
		}
	}
	file.close();
}

void insertInterest(HashTable<Person>* graph, HashTable<Tag>* tag,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());

			if (graph->lookupNode(startID) != NULL) {
				if (tag->lookupNode(endID) == NULL) {
//					cout << "Tag " << endID << " does not exits " << endl;
				} else {
					//tag->lookupNode(endID)->print();
					graph->lookupNode(startID)->has_interest->pushBack(
							tag->lookupNode(endID));
				}
			} else {
				cout << "Node does not exist" << endl;
			}
		}
	}
	file.close();
}

void insertLocation(HashTable<Person>* graph, HashTable<Place>* place,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());

			if (graph->lookupNode(startID) != NULL) {
				if (place->lookupNode(endID) == NULL) {
//					cout << "Place " << endID << " does not exits " << endl;
				} else {
					//place->lookupNode(endID)->print();
					graph->lookupNode(startID)->lives_in = place->lookupNode(
							endID);
				}
			} else {
				cout << "Node does not exist" << endl;
			}
		}
	}
	file.close();
}

void insertForumMembers(HashTable<Forum>* forums, HashTable<Person>* ppl,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());

			if (forums->lookupNode(startID) != NULL) {
				if (ppl->lookupNode(endID) == NULL) {
//					cout << "Person " << endID << " does not exits " << endl;
				} else {
					forums->lookupNode(startID)->members->pushBack(
							ppl->lookupNode(endID));
				}
			} else {
				//cout << "Forum " << startID << " does not exist" << endl;
			}
		}
	}
	file.close();
}

void insertForumPosts(HashTable<Forum>* forums, HashTable<Post>* post,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());

			if (forums->lookupNode(startID) != NULL) {
				if (post->lookupNode(endID) == NULL) {
//					cout << "Post " << endID << " does not exits " << endl;
				} else {
					forums->lookupNode(startID)->has_posts->pushBack(
							post->lookupNode(endID));
				}
			} else {
				//cout << "Forum " << startID << " does not exist" << endl;
			}
		}
	}
	file.close();
}

void insertCommentCreator(HashTable<Person>* graph, HashTable<Post>* posts,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());

			if (graph->lookupNode(endID) != NULL) {
				Comment* c = new Comment(startID);
				graph->lookupNode(endID)->replied->pushBack(c);
			} else {
				cout << "Person " << endID << " does not exist" << endl;
			}
		}
	}
	file.close();
}

void insertPostHasCreator(HashTable<Post>* graph, string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	int pid, creatorid;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			pid = atoi(token.c_str());
			getline(streamline, token, '|');
			creatorid = atoi(token.c_str());
			if (graph->lookupNode(pid) != NULL)
				graph->lookupNode(pid)->creatorId = creatorid;
			else {
				//cout << "Post " << pid << " does not exist." << endl;
			}

		}
	}
	file.close();
}

void insertCreatedPosts(HashTable<Person>* graph, HashTable<Post>* post,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());

			if (graph->lookupNode(endID) != NULL) {
				if (post->lookupNode(startID) == NULL) {
					//cout << "Post " << startID << " does not exist." << endl;
				} else {
					graph->lookupNode(endID)->created_post->pushBack(
							post->lookupNode(startID));
				}
			} else {
				cout << "Person " << startID << " does not exist" << endl;
			}
		}
	}
	file.close();
}

void insertLike(HashTable<Person>* graph, HashTable<Post>* post,
		string filepath) {
	ifstream file(filepath.c_str());
	string line, token;
	if (file.good()) { // ignore first line
		getline(file, line, '\n');
	}
	int startID, endID;
	while (file.good()) {
		getline(file, line, '\n');
		if (!line.empty()) {
			stringstream streamline(line);

			getline(streamline, token, '|');
			startID = atoi(token.c_str());
			getline(streamline, token, '|');
			endID = atoi(token.c_str());

			if (graph->lookupNode(startID) != NULL) {
				if (post->lookupNode(endID) == NULL) {
					//cout << "Post " << startID << " does not exist." << endl;
				} else {
					graph->lookupNode(startID)->likes_post->pushBack(
							post->lookupNode(endID));
				}
			} else {
				cout << "Person " << startID << " does not exist" << endl;
			}
		}
	}
	file.close();
}
