#include "entities.h"

#include <string>
#include <iostream>

using namespace std;

Date::Date(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

Date::Date(const Date& old) {
	year = old.year;
	month = old.month;
	day = old.day;
}

Date::Date() {
	year = 0;
	month = 0;
	day = 0;
}

Date::~Date() {
}

CreationDate::CreationDate(int y, int mo, int d, int h, int m, int s) :
		date(y, mo, d) {
	hour = h;
	minute = m;
	second = s;
}

CreationDate::CreationDate(const CreationDate& old) {
	date = old.date;
	hour = old.hour;
	minute = old.minute;
	second = old.second;
}

CreationDate::CreationDate() {
	hour = 0;
	minute = 0;
	second = 0;
}

CreationDate::~CreationDate() {
}

Person::Person(int pid) :
		birthday(0, 0, 0), creationDate(0, 0, 0, 0, 0, 0) {
	id = pid;
	knows_person = new List<Edge<Person> >(false);
	likes_post = new List<Post>(true);
	has_interest = new List<Tag>(true);
	studiedAt = new List<Organisation>(true);
	worksAt = new List<Organisation>(true);
	lives_in = NULL;
	studiedAt = NULL;
	classYear = -1;
	worksAt = NULL;
	workFrom = -1;
	created_post = NULL;
	gender = male;
	replied = NULL;
}

Person::Person(const Person& old) {
	firstName = old.firstName;
	lastName = old.lastName;
	gender = old.gender;
	birthday = old.birthday;
	locationIP = old.locationIP;
	browserUsed = old.browserUsed;
	workFrom = old.workFrom;
	id = old.id;
	classYear = old.classYear;

	creationDate.date.day = old.creationDate.date.day;
	creationDate.date.month = old.creationDate.date.month;
	creationDate.date.year = old.creationDate.date.year;
	creationDate.hour = old.creationDate.hour;
	creationDate.minute = old.creationDate.minute;
	creationDate.second = old.creationDate.second;

	/*Dynamic copies*/

	knows_person = new List<Edge<Person> >(*(old.knows_person));
	likes_post = new List<Post>(*(old.likes_post));
	has_interest = new List<Tag>(*(old.has_interest));
	created_post = new List<Post>(*(old.created_post));
	replied = new List<Comment>(*(old.replied));

	lives_in = new Place(*(old.lives_in));
	studiedAt = new List<Organisation>(*(old.studiedAt));
	worksAt = new List<Organisation>(*(old.worksAt));

}

Person::Person(int pid, string pfirstn, string plastn, Gender pgen, int pbirthy,
		int pbirthm, int pbirthd, int pcreaty, int pcreatmo, int pcreatd,
		int pcreath, int pcreatm, int pcreats, string pip, string pbrowser) :
		birthday(pbirthy, pbirthm, pbirthd), creationDate(pcreaty, pcreatmo,
				pcreatd, pcreath, pcreatm, pcreats) {
	id = pid;
	firstName = pfirstn;
	lastName = plastn;
	gender = pgen;
	locationIP = pip;
	browserUsed = pbrowser;

	knows_person = new List<Edge<Person> >(false);
	likes_post = new List<Post>(true);
	created_post = new List<Post>(true);
	has_interest = new List<Tag>(true);
	//replied = new List<Comment>(true);
	//allakse
	replied = new List<Comment>(false);
	studiedAt = new List<Organisation>(true);
	worksAt = new List<Organisation>(true);
	lives_in = NULL;
	classYear = -1;
	workFrom = -1;

}

Person::~Person() {
	if (knows_person != NULL)
		delete knows_person;
	if (likes_post != NULL)
		delete likes_post;
	if (created_post != NULL)
		delete created_post;
	if (has_interest != NULL)
		delete has_interest;
	if (replied != NULL)
		delete replied;
	if (studiedAt != NULL)
		delete studiedAt;
	if (worksAt != NULL)
		delete worksAt;
}

void Person::print() {
	cout << id << " " << firstName << " " << lastName << " " << gender << " "
			<< birthday.year << "-" << birthday.month << "-" << birthday.day
			<< " " << creationDate.date.year << "-" << creationDate.date.month
			<< "-" << creationDate.date.day << "T" << creationDate.hour << ":"
			<< creationDate.minute << ":" << creationDate.second << "Z "
			<< locationIP << " " << browserUsed << endl;
}

bool Person::insertEdge(Edge<Person> *e) {
	knows_person->pushBack(e);
	return true;
}

void Person::insert_knows_person(Person *p) {
	knows_person->pushBack(new Edge<Person>(p));
}

void Person::print_known_person() {
	for (int i = 0; i < knows_person->getSize(); i++) {
		cout << knows_person->get(i)->id;
		if (i < knows_person->getSize() - 1) {
			cout << "|";
		}
	}
}

List<Edge<Person> >* Person::get_knows_person() {
	return knows_person;
}

Forum::Forum(int pid, string ptitle, int pcreaty, int pcreatmo, int pcreatd,
		int pcreath, int pcreatm, int pcreats) :
		creationDate(pcreaty, pcreatmo, pcreatd, pcreath, pcreatm, pcreats) {
	id = pid;
	title = ptitle;

	members = new List<Person>(true);
	has_posts = new List<Post>(true);
}

Forum::Forum(const Forum& old) {
	title = old.title;
	creationDate = old.creationDate;
	id = old.id;

	members = new List<Person>(*(old.members));
	has_posts = new List<Post>(*(old.has_posts));
}

Forum::~Forum() {
	delete members;
	delete has_posts;
}

bool Forum::insertEdge(Edge<Forum> *e) {

	return true;
}

void Forum::print() {
	cout << id << " " << title << " " << creationDate.date.year << "-"
			<< creationDate.date.month << "-" << creationDate.date.day << "T"
			<< creationDate.hour << ":" << creationDate.minute << ":"
			<< creationDate.second << "Z " << endl;
}

Organisation::Organisation(int pid, string ptype, string pname, string purl) {
	id = pid;
	type = ptype;
	name = pname;
	url = purl;
}

Organisation::Organisation(const Organisation& old) {
	id = old.id;
	type = old.type;
	name = old.name;
	url = old.url;
}

Organisation::~Organisation() {

}

bool Organisation::insertEdge(Edge<Organisation> *e) {

	return true;
}

void Organisation::print() {
	cout << id << " " << type << " " << name << " " << url << endl;
}

Place::Place(int pid, string pname, string purl, string ptype) {
	id = pid;
	name = pname;
	url = purl;
	type = ptype;
}

Place::~Place() {

}

bool Place::insertEdge(Edge<Place> *e) {
	return true;
}

void Place::print() {
	cout << id << " " << name << " " << type << " " << url << " " << type
			<< endl;
}

Post::Post(const Post& old) {
	imageFile = old.imageFile;
	creationDate = old.creationDate;
	locationIP = old.locationIP;
	browserUsed = old.browserUsed;
	language = old.language;
	content = old.content;
	id = old.id;
	creatorId = old.creatorId;

	comments = new List<Comment>(*(old.comments));
}

Post::Post(int pid, string pimageFile, int pcreaty, int pcreatmo, int pcreatd,
		int pcreath, int pcreatm, int pcreats, string plocationIP,
		string pbrowser, string planguage, string pcontent) :
		creationDate(pcreaty, pcreatmo, pcreatd, pcreath, pcreatm, pcreats) {
	id = pid;
	imageFile = pimageFile;
	locationIP = plocationIP;
	browserUsed = pbrowser;
	language = planguage;
	content = pcontent;
	creatorId = 0;
	comments = new List<Comment>(false);
}

Post::~Post() {
	delete comments;
}

bool Post::insertEdge(Edge<Post> *e) {

	return true;
}

void Post::print() {
	cout << id << " " << imageFile << " " << creationDate.date.year << "-"
			<< creationDate.date.month << "-" << creationDate.date.day << "T"
			<< creationDate.hour << ":" << creationDate.minute << ":"
			<< creationDate.second << "Z " << " " << locationIP << " "
			<< browserUsed << " " << language << " " << content << endl;
}

Tag::Tag(int pid, string pname, string purl) {
	id = pid;
	name = pname;
	url = purl;
}

Tag::Tag(const Tag& old) {
	id = old.id;
	name = old.name;
	url = old.url;
}

Tag::~Tag() {

}

void Tag::print() {
	cout << id << " " << name << " " << url << endl;
}

Comment::Comment(int pid) {
	id = pid;
	posterID = -1;
}

Comment::Comment(const Comment& old) {
	id = old.id;
	posterID = old.posterID;
}

Comment::~Comment() {

}

//-----------------Template Types used--------------------//

