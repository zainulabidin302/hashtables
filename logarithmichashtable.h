#ifndef LOGARITHAMIC_H
#define LOGARITHAMIC_H

#include "HashTable.h"

template <class T>
class LogarithmicHashtable : public HashTable<T>
{
	public:
		LogarithmicHashtable(int, int=false);
		virtual ~LogarithmicHashtable();
		virtual int nextProbe(int current, int from);

	protected:
	private:
};

#endif // QUADRATICHASHTABLE_H
