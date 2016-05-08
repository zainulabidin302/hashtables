#ifndef COLLIDABLEHASHTABLE_H
#define COLLIDABLEHASHTABLE_H

#include "hashtable.h"

template <class T>
class CollidableHashTable : public HashTable<T>
{
	public:
		CollidableHashTable(int size);
		virtual ~CollidableHashTable();
		bool insert(T el);
		bool remove(T el);
		T  find(T el);
	protected:
	private:
};

#endif // COLLIDABLEHASHTABLE_H
