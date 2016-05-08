#include "collidablehashtable.h"
template <class T>
CollidableHashTable<T>::CollidableHashTable(int size) : HashTable<T>(size) { }

template <class T>
CollidableHashTable<T>::~CollidableHashTable() { }

template <class T>
bool CollidableHashTable<T>::remove(T el){ return this->basic_remove(this->basic_hash(el)); }

template <class T>
T CollidableHashTable<T>::find(T el){ return this->basic_find(el); }

template <class T>
bool CollidableHashTable<T>::insert(T el) { return this->basic_insert(el, this->basic_hash(el)); }





