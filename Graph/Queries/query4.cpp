#include "../graph.h"

#include <iostream>


using namespace std;

void Graph::buildTrustGraph(int forumID){

	Forum* f = forums->lookupNode(forumID);

	trustGraph = new HashTable<Person>(4,4);

	Person* p ;

	for(int i=0;i<f->members->getSize(); i++){
		p = new Person(f->members->get(i)->id);
		trustGraph->insertNode(p);

		//cout<<"Inserted "<<p->id<<" to trustGraph"<<endl;
	}

	trustGraph->sort();
	//trustGraph->print();

	// cout<<"Posts in forum "<<endl;
	// for(int i = 0 ; i < forums->lookupNode(forumID)->has_posts->getSize() ; i++){
	// 	cout<<forums->lookupNode(forumID)->has_posts->get(i)->id<<endl;
	// }

	List<Edge<Person> >* friends;
	Person* cur;
	Person* fr;
	Edge<Person>* e;
	for(int i=0;i<f->members->getSize(); i++){
		cur = f->members->get(i);
		friends = cur->knows_person;

		for(int j =0 ; j<friends->getSize(); j++){
			if((fr=trustGraph->lookupNode(friends->get(j)->id))!=NULL){
				//cout<<cur->id<<" knows "<<fr->id<<endl;

				e = new Edge<Person>(fr);

				if(float tr = estimateTrust(forumID , cur->id , fr->id)>0){
					cout<<cur->id<<"-"<<fr->id<<" "<<(float)tr<<endl;
				}

				trustGraph->lookupNode(cur->id)->knows_person->pushBack(e);
			}
		}
	}

	//To commentara gt evgaze warn gia unused		int* Nodes  = trustGraph->getAllNodeID();

	// for(int i =0 ; i<trustGraph->EntIn ; i++){
	// 	cout<<Nodes[i]<<" :";
	// 	trustGraph->lookupNode(Nodes[i])->print_known_person();
	// 	cout<<endl;
	// }

}

void Graph::deleteTrustGraph(){
	if(trustGraph!=NULL){
		delete trustGraph;
	}
	trustGraph = NULL;
}

float Graph::estimateTrust(int forumID , int startID , int endID){

	float noLikes = 0;
	float noComments = 0;

	List<Post>* createdPosts = graph->lookupNode(startID)->created_post;

	//cout<<startID<<":"<<endl;

	Post* post = NULL;
	for(int i = 0 ; i < createdPosts->getSize() ; i++){
		post = createdPosts->get(i);

		if(post !=NULL){
			if(forums->lookupNode(forumID)->has_posts->search(post->id)!=NULL){
				//cout<<"in forum"<<endl;
				if(graph->lookupNode(endID)->likes_post->search(post->id)!=NULL){
					//cout<<"liked by "<<endID<<endl;
					noLikes++;
				}
				List<Comment>* postComments = post->comments;

				if(postComments!=NULL){
					for(int i = 0 ; i < postComments->getSize() ; i++){
						Comment* c = postComments->get(i);

						if(graph->lookupNode(endID)->replied->search(c->id)!=NULL){
							noComments++;
						}
					}
				}
			}
		}
	}
	if(noLikes>0 || noComments>0){
		cout<<endID<<" nL "<<noLikes<<" nC "<<noComments<<endl;
	}
	return (float)(0.3*(float)noLikes + 0.7*(float)noComments);
}
