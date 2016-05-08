#ifndef DOUBLE_H
#define DOUBLE_H

#include "HashTable.h"

template <class T>
class DoubleHashtable : public HashTable<T>
{
	public:
		DoubleHashtable(int, int=false);
		virtual ~DoubleHashtable();
		virtual int nextProbe(int current, int from);
		int hash_2(int index);

	protected:
	private:
};

#endif // QUADRATICHASHTABLE_H
