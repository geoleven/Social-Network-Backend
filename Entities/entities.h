#ifndef _ENTITIES_
#define _ENTITIES_

#include <string>

#include "../List_Template/list.h"
#include "edge.h"

using namespace std;

enum Gender {
	male, female
};

struct Date {
	int year;
	int day;
	int month;
	Date(const Date& other);
	Date();
	Date(int, int, int);
	~Date();
};

struct CreationDate {
	Date date;
	int hour;
	int minute;
	int second;
	CreationDate(const CreationDate& other);
	CreationDate();
	CreationDate(int, int, int, int, int, int);
	~CreationDate();
};

class Forum;
class Organisation;
class Place;
class Post;
class Tag;
class Comment;

class Person { //id|firstName|lastName|gender|birthday|creationDate|locationIP|browserUsed
public:
	string firstName;
	string lastName;
	Gender gender;
	Date birthday;
	CreationDate creationDate;
	string locationIP;
	string browserUsed;

	List<Edge<Person> > *knows_person;
	List<Post> *likes_post;
	List<Tag> *has_interest;
	List<Post> *created_post;
	List<Comment> *replied;

	Place* lives_in;

	List<Organisation> *studiedAt;
	int classYear;

	List<Organisation> *worksAt;
	int workFrom;

	int id;

	Person(const Person& other);
	Person(int);
	Person(int, string, string, Gender, int, int, int, int, int, int, int, int,
			int, string, string);
	~Person();

	int getId();
	void print();

	bool insertEdge(Edge<Person>*);

	void insert_knows_person(Person*);

	void print_known_person();

	List<Edge<Person> >* get_knows_person();
};

class Forum { //id|title|creationDate
public:
	string title;
	CreationDate creationDate;
	int id;

	List<Person>* members;
	List<Post>* has_posts;

	//Forum(int);
	Forum(const Forum& other);
	Forum(int, string, int, int, int, int, int, int);
	~Forum();

	bool insertEdge(Edge<Forum>*);

	void print();
};

class Organisation { //id|type|name|url
public:
	string type;
	string name;
	string url;
	int id;

	//Organisation(int);
	Organisation(int, string, string, string);
	Organisation(const Organisation& other);
	~Organisation();

	bool insertEdge(Edge<Organisation>*);

	void print();
};

class Place { //cast(id as long)|name|url|type
public:
	string name;
	string url;
	string type;
	int id;

	//Place(int);
	Place(int, string, string, string);
	~Place();

	bool insertEdge(Edge<Place>*);

	void print();
};

class Post { //id|imageFile|creationDate|locationIP|browserUsed|language|content
public:
	string imageFile;
	CreationDate creationDate;
	string locationIP;
	string browserUsed;
	string language;
	string content;
	int id;

	int creatorId;

	List<Comment>* comments;

	//Post(int);
	Post(const Post& other);
	Post(int, string, int, int, int, int, int, int, string, string, string,
			string);
	~Post();

	bool insertEdge(Edge<Post>*);

	void print();

};

class Tag { //id|name|url
public:
	string name;
	string url;
	int id;

	//Tag(int);
	Tag(const Tag& other);
	Tag(int, string, string);
	~Tag();

	bool insertEdge(Edge<Tag>*);

	void print();
};

class Comment {
public:
	int id;
	int posterID;

	Comment(int);
	Comment(const Comment& other);
	~Comment();
};

#endif
