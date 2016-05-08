#define DEBUG 1
#include "quadratichashtable.h"
#include <iostream>
using namespace std;
template <class T>
QuadraticHashtable<T>::QuadraticHashtable (int size, int logging):  HashTable<T>(size, logging) {
	if(logging){
		this->log << "Quadratic Hashing Report :: " << endl ;
		this->log << "*************************************" << endl ;
	}
}

template <class T>
QuadraticHashtable<T>::~QuadraticHashtable(){}

template <class T>
int QuadraticHashtable<T>::nextProbe(int current, int iteration) {
	return (current+(int)pow(iteration, 2))%this->capacity;
}



