#define DEBUG 1
#include "linearhashtable.h"
#include <iostream>
using namespace std;
template <class T>
LinearHashTable<T>::LinearHashTable (int size, int logging):  HashTable<T>(size, true) {
}

template <class T>
LinearHashTable<T>::~LinearHashTable(){}

template <class T>
int LinearHashTable<T>::nextProbe(int current, int from) {
	return (current+from) % this->capacity;
}


