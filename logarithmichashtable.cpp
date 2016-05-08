#define DEBUG 1
#include "logarithmichashtable.h"
#include <iostream>
using namespace std;
template <class T>
LogarithmicHashtable<T>::LogarithmicHashtable(int size,int logging ):  HashTable<T>(size, logging) {}

template <class T>
LogarithmicHashtable<T>::~LogarithmicHashtable(){}

template <class T>
int LogarithmicHashtable<T>::nextProbe(int current, int iteration) {
	if(iteration == 0) return current;
	int i = 0 ;

	while(i < iteration) {
		current = ((current)+(int)log2(current%2==0?current:current+1));
		i++;
	}
	return (current)%this->capacity;
}

