/* HASHTABLE IMPLEMENTATION
* COLIN MACRAE
* 11/22/2020*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <stdio.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iostream>

namespace cop4530
{
// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

	template<typename K, typename V>
		class HashTable
		{
			private:
				std::vector<std::list<std::pair<K,V>>> table; // hashtable vector with lists of type V 
				int currentSize;
				void makeEmpty(); // delete all elements in hashtable
				void rehash(); // rehash function (called when num elements > size of vector)
				size_t myhash(const K &k); // returns index of the vector entry where k should be stored 
				unsigned long prime_below(unsigned long); // returns prime number below 
				void setPrimes(std::vector<unsigned long> &); //	creates vector of primes	
			public:
				explicit HashTable( size_t size = 101); // constructor
				~HashTable(); // destructor 			
				bool contains(const K &k); // Check if key is in the hashtable. 			
				bool match(const std::pair<K,V> &kv); // check if key-value pair is in the hash table 
				bool insert(const std::pair<K,V> &kv); // add key-value pair into the hash table 
				bool insert(std::pair<K,V> &&kv); // move version of insert function 
				bool remove(const K &k); //delete key k and corresponding value 
				void clear(); // delete all elements in hashtable 
				bool load(const char * filename); // load contents of file into hashtable 
				void dump(); // display all entries in hashtable 
				bool write_to_file(const char* filename); // write all elements in the hashtable into file 
				size_t size(); // returns size of hashtable 
		};


#include "hashtable.hpp"
}


#endif

