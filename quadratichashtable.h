#ifndef QUADRATICHASHTABLE_H
#define QUADRATICHASHTABLE_H

#include "HashTable.h"

template <class T>
class QuadraticHashtable : public HashTable<T>
{
	public:
		QuadraticHashtable(int size, int logging=0);
		virtual ~QuadraticHashtable();
		virtual int nextProbe(int current, int from);

	protected:
	private:
};

#endif // QUADRATICHASHTABLE_H
