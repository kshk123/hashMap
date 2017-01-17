#ifndef _HASH_MAP_H__
#define _HASH_MAP_H__

#include <stdint.h> 
#include <iostream> 
#include <functional>
#include <mutex> 
#include "HashNode.h" 

const int HASH_SIZE_DEFAULT = 1031; // A prime number as hash size gives a better distribution of values in buckets

//The class represting the hash map.
//It is expected for user defined types, the hash function will be provided.
//By default, the std::hash function will be used
//If the hash size is not provided, then a defult size of 1031 will be used
//The hash table itself consists of an array of hash buckets.
//Each hash bucket is implemented as singly linked list with the head as a dummy node created 
//during the creation of the bucket. All the hash buckets are created during the construction of the map.
//Locks are taken per bucket, hence multiple threads can write simultaneously in different buckets in the hash map
template <typename K, typename V, typename F = std::hash<K> >
class HashMap
{
	public:
		HashMap(uint32_t hashSize_ = HASH_SIZE_DEFAULT) : hashSize(hashSize_)
		{
			hashTable = new HashBucket<K, V> * [hashSize](); //create the hash table as an array of hash buckets
			for(uint32_t i = 0; i < hashSize; i++)
			{
				hashTable[i] = new HashBucket<K, V>(); //create the hash buckets
			}
		}

		~HashMap()
		{
			for(uint32_t i = 0; i < hashSize; i++)
            {
                delete hashTable[i]; //delete all the hash buckets
            }

            delete []hashTable;
		}
	
		//Function to find an entry in the hash map matching the key.
        //If key is found, the corresponding value is copied into the parameter "value" and function returns true.
        //If key is not found, function returns false.
		bool find(const K &key, V &value) const 
		{
        	uint64_t hashValue = hashFn(key) % hashSize ;
        	HashBucket<K, V> * bucket = hashTable[hashValue];
        	return bucket->find(key, value);
    	}

		//Function to insert into the hash map.
        //If key already exists, update the value, else insert a new node in the bucket with the <key, value> pair.
		void insert(const K &key, const V &value) 
		{
			uint64_t hashValue = hashFn(key) % hashSize ;
        	HashBucket<K, V> * bucket = hashTable[hashValue];
			bucket->insert(key, value);
    	}

		//Function to remove an entry from the bucket, if found
		void erase(const K &key) 
		{
			uint64_t hashValue = hashFn(key) % hashSize ;
        	HashBucket<K, V> * bucket = hashTable[hashValue];
			bucket->erase(key);
    	}	

		//Function to clean up the hasp map, i.e., remove all entries from it
		void clear()
		{
			for(uint32_t i = 0; i < hashSize; i++)
            {
                (hashTable[i])->clear();
            }
		}	

	private:
		HashBucket<K, V> ** hashTable;
		F hashFn;
		uint32_t hashSize;
};

#endif
