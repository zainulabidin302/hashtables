#ifndef LINEARHASHTABLE_H
#define LINEARHASHTABLE_H

#include "HashTable.h"

template <class T>
class LinearHashTable : public HashTable<T>
{
	public:
		LinearHashTable(int size, int logging = false);
		virtual ~LinearHashTable();
		virtual int nextProbe(int current, int from);
};

#endif // LINEARHASHTABLE_H
