#define DEBUG 1
#include "doublehashtable.h"
#include <iostream>
using namespace std;
template <class T>
DoubleHashtable<T>::DoubleHashtable(int size,int logging ):  HashTable<T>(size, logging) {}

template <class T>
DoubleHashtable<T>::~DoubleHashtable(){}

template <class T>
int DoubleHashtable<T>::nextProbe(int current, int iteration) {
	if(iteration == 0) return current;
	int i = 0 ;

	while(i < iteration) {
		current = ((current)+this->hash_2(current));
		i++;
	}
	return (current)%this->capacity;
}

template <class T>
int DoubleHashtable<T>::hash_2(int index){ return (1 + ( 121 *index))%this->capacity; }
