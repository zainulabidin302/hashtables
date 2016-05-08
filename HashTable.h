#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "commons.h"
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;
template <class T>
class HashTable
{

protected:

    int capacity;
    int collisions;
    int size;
    int rehashed;
    T ** list_ptr;

	fstream log;
    int logging;

public:
    HashTable(int s, int logging=0){
		this->rehashed = this->collisions = 0;
        this->list_ptr = nullptr;
		this->allocateMemory(s);
		if(logging) {
			this->startLogging();
			log.open("T:\\cppdev\\hashing\\driver\\report_hashtable.txt",  ios::out);
		}

    }

    HashTable(){
		this->rehashed = this->collisions = 0;
        this->list_ptr = NULL;
        this->allocateMemory(HashTable<T>::INITIAL_HASH_TABLE_CAPACITY);
    }

    ~HashTable(){
    	delete [] list_ptr;
		if(this->logging)
			log.close();
    }

    bool allocateMemory(int new_size){

        if(new_size < 1) throw "Negative size error: Size must be positive";


		new_size = this->nextPrime(new_size);
        this->list_ptr = new T*[new_size];
        if(this->list_ptr == NULL) throw "Memory error: Can not allocate memory";
        this->capacity = new_size;
        for(int i = 0; i < this->capacity; i++)
			this->list_ptr[i] = nullptr;
		this->size = 0;

        if(this->logging) {
			this->log << "Allocating Memory :: new size = " << new_size << endl ;
        }

        return true;

    }


    virtual bool insert(char * s) {
    	if(this->loadFactor() > 0.5) {
			if(this->logging) this->log << "Rehashing #" << this->rehashed << endl;
			this->rehashed++;
			this->rehashWithUpsizing(); // if no more memory can be allocated, throw exception
    	}
    	int k = this->hash(s);

		if(this->logging) {
			this->log << setw(50) << left <<  s << setw(20) << left  << k ;
		}
		int i = 0;
		int iter = 0;


		int index = this->nextProbe(k, i);
    	while(!this->is_free(index) && i < this->capacity){
			i++;
			index = this->nextProbe(k, i);

			if (this->logging)
				this->log << "(" << index  <<")" << " ,"   ;

			this->collisions++;
    	}


        if(i >= this->capacity) throw "Iteration Exceeded Capicity";

		this->list_ptr[index] = new char * ;
		*(this->list_ptr[index]) = new char[strlen(s)+1];
		strcpy(*(this->list_ptr[index]), s);
		this->size++;
		if (this->logging)
			this->log << " C="<< this->collisions << endl;

		return true;
    }


    virtual char * find(char * s) {
		int k = find_key(s);
    	return (k > 0) ? *(this->list_ptr[k%this->capacity]) : nullptr;
    }

    virtual int find_key(char * s) {
    	int k = this->hash(s);

		if(!this->is_free(k%this->capacity) && (strcmp(*(this->list_ptr[k%this->capacity]), s) == 0)) return k%this->capacity;

		cout << "Jumping like a dog: " << endl ;
		int i = 1, iter = 0;
		while(i < this->capacity) {
			iter = this->nextProbe(k, i);
			cout << "iter = " << iter << ", ";
			if(!this->is_free(iter%this->capacity) && strcmp(*(this->list_ptr[iter%this->capacity]), s) == 0) return iter;
			i++;
		}
		cout << endl ;
        return -1;
    }

    virtual bool remove(char * s) {
		int k = this->find_key(s);
		k = k%this->capacity;
		if(k == -1)
			return false;

        delete *(this->list_ptr[k]);
        delete (this->list_ptr[k]);
        this->list_ptr[k] = nullptr;
/*        int k_deleted = k;
        int home_slot_hash = this->hash(s);
        while(
            !this->is_free((k+1)%this->capacity) &&
            this->hash(*(this->list_ptr[(k+1)%this->capacity])) == home_slot_hash
        ) {
            this->list_ptr[k_deleted] = this->list_ptr[(k+1)%this->capacity];
            this->list_ptr[(k+1)%this->capacity] = nullptr;
            k_deleted++;

        }
*/
        this->size--;
        return true;
    }




//  virtual bool insert(T el)	=0;

	virtual int nextProbe(int current, int i) = 0;

	//virtual bool remove(T el)	=0;
    //virtual T  find  (T el)		=0;

	virtual void rehashWithUpsizing() {
		this->collisions = 0;
		float upsize_factor = 1.5;
		T ** list_ptr_old = this->list_ptr;
		int old_capacity  = this->capacity;

		this->allocateMemory(this->capacity*upsize_factor);

		for(int i = 0 ; i < old_capacity; i++) {
			if(list_ptr_old[i] != nullptr){
				this->insert(*list_ptr_old[i]);
				delete *list_ptr_old[i];
				delete list_ptr_old[i];

			}
		}
	}
    bool is_free(int k){
        return this->list_ptr[k%this->capacity] == nullptr;
    }

    virtual void  print(){
        for(int i = 0 ; i < this->capacity; i++){
            if(!is_free(i))
                std::cout << *(this->list_ptr[i]) << ", " ;
        }
    }

    virtual void  print_map(){
    	std::cout << "HashTable => {" << std::endl;
        for(int i = 0 ; i < this->capacity; i++){

            if(!is_free(i))
                std::cout <<"\t " <<i << "=>" << *(this->list_ptr[i]) << ", " << std::endl;
            else
                std::cout <<"\t " << i << "=>" << ", " << std::endl;
        }
        std::cout << "} ";
    }

    virtual int count(){
        int c = 0;
        for(int i = 0 ; i < this->capacity; i++){
            if(!is_free(i))
                c++;
        }
        return c;
    }

    int nextPrime(int i){
        i = (i%2 == 0) ? i+1: i;
        while(!is_prime(i)) i += 2;
        return i;
    }

    int is_prime(int n) {
        for(int i = 2; i < n; i++)
            if((n%i) == 0) return false;
        return true;
    }

    double loadFactor() {
		return (float) this->size / (float) this->capacity;
    }




    virtual int hash(char * s){
        int sum = 0;
        for(int i = 0; i < strlen(s); i++) sum += s[i]*pow(2, i);
        return sum  % this->capacity;
    }
	int getCollisions() {return this->collisions;}
    int getRehashedTimes() {return this->rehashed;}
    //static const int DEFAULT_HASH_FUNCTION(key_t) {return 10;};
    static const int INITIAL_HASH_TABLE_CAPACITY = 7;

	void startLogging() {
		this->logging = 1;
	}
	void stopLogging() {
		this->logging = 0;
	}
};
#endif // HASHTABLE_H
