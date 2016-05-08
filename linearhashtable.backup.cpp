#define DEBUG 1
#include "linearhashtable.h"
#include <iostream>
using namespace std;
template <class T>
LinearHashTable<T>::LinearHashTable (int size):  HashTable<T>(size) {}

template <class T>
LinearHashTable<T>::~LinearHashTable(){}
template <class T>
bool LinearHashTable<T>::insert(T el){

	if(this->loadFactorExceeded())
		this->rehashWithUpsizing(); // Rehash

	int k = this->basic_hash(el);
	if(this->is_free(k)) {
		return this->basic_insert(el, k);
	}
	int probe = k+1;
	while(probe%this->capacity != k) {
		if(this->is_free(probe%this->capacity)) {
			return this->basic_insert(el, probe%this->capacity);
		}
		probe++;
	}

	return false;
}
template <class T>
bool LinearHashTable<T>::remove(T el){
	int k = this->find_key(el);
	if(k > -1) {
		if(this->basic_remove(el, k))
			return true;
		return false;
	}
	return false;
}

template <class T>
T  LinearHashTable<T>::find(T el){
	int k = this->find_key(el);
	if(k > -1)
		return *(this->list_ptr[k]);
	return nullptr;
}

template <class T>
int  LinearHashTable<T>::find_key(T el){
	int k = this->basic_hash(el);

	int probe = k;
	if(!this->is_free(probe%this->capacity) && (strcmp(el, *(this->list_ptr[probe%this->capacity])) == 0 ))
		return  probe%this->capacity;

	probe++;

	while(probe%this->capacity != k){
		if(!this->is_free(probe%this->capacity) && (strcmp(el, *(this->list_ptr[probe%this->capacity])) == 0 )) {
			return  probe%this->capacity;
		}
		probe++;
	}
	return -1;

}
template <class T>
int LinearHashTable<T>::probe(int from) {
	int start = from % this->capacity;
	++from; while(!is_free(from++));
	return (from == start) ? -1 : from % this->capacity;
}

template <class T>
int LinearHashTable<T>::nextProbe(int current) {
	return ++current % this->capacity;
}


