#include "edge.h"
#include "entities.h"

using namespace std;

template<class T>
Edge<T>::Edge(T* endpoint) {
	end = endpoint;
	id=end->id;
	/*To evala gia na min vgazei weight*/
	weight = 0;
}

//template<class T>
//Edge<T>::Edge(const Edge& old) {
//	end = new T(*(old.end));
//	weight = old.weight;
//	type = old.type;
//	id = old.id;
//}

template<class T>
Edge<T>::Edge(T* endpoint, int w, string t) {
	end = endpoint;
	id = end->id;
	weight = w;
	type = t;
}

template<class T>
Edge<T>::~Edge() {
}

template<class T>
T* Edge<T>::get() {
	return end;
}

//-----------------Template Types used--------------------//
template class Edge<Person> ;
template class Edge<Forum> ;
template class Edge<Organisation> ;
template class Edge<Place> ;
template class Edge<Post> ;
template class Edge<Tag> ;

