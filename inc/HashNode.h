#ifndef HASH_NODE_H_
#define HASH_NODE_H_

#include <shared_mutex>
namespace CTSL  //Concurrent Thread Safe Library
{
    // Class representing a templatized hash node
    template <typename K, typename V>
    class HashNode
    {
        public:
            HashNode() : next(nullptr) {
            }

            HashNode(K key_, V value_) : next(nullptr), key(key_), value(value_) {
            }

            ~HashNode()
            {
                next = nullptr;
            }

            const K& getKey() const {return key;}
            void setValue(V value_) {value = value_;}
            const V& getValue() const {return value;}

            HashNode *next; //Pointer to the next node in the same bucket
        private:
            K key;   //the hash key
            V value; //the value corresponding to the key
    };


    //Class representing a hash bucket. The bucket is implemented as a singly linked list.
    //A bucket is always constructed with a dummy head node
    template <typename K, typename V>
    class HashBucket
    {
        public:
            HashBucket() : head(nullptr)
            {
            }

            ~HashBucket() //delete the bucket
            {
                std::unique_lock<std::shared_timed_mutex> lock(mutex_); //take a lock before removing the nodes

                while(head)
                {
                    HashNode<K, V>* next = head->next;
                    delete head;

                    head = next;
                }
            }

            //Function to find an entry in the bucket matching the key
            //If key is found, the corresponding value is copied into the parameter "value" and function returns true.
            //If key is not found, function returns false
            bool find(const K &key, V &value) const
            {
                // A shared mutex is used to enable mutiple concurrent reads
                std::shared_lock<std::shared_timed_mutex> lock(mutex_);
                HashNode<K, V> * node = head;

                while (node)
                {
                    if (node->getKey() == key)
                    {
                        value = node->getValue();
                        return true;
                    }
                    node = node->next;
                }
                return false;
            }

            //Function to insert into the bucket
            //If key already exists, update the value, else insert a new node in the bucket with the <key, value> pair
            void insert(const K &key, const V &value)
            {
                //Exclusive lock to enable single write in the bucket
                std::unique_lock<std::shared_timed_mutex> lock(mutex_);
                HashNode<K, V>** node = &head;

                while (*node)
                {
                    if ((*node)->getKey() == key)
                    {
                        (*node)->setValue(value); //Key found in bucket, update the value
                        return;
                    }
                    node = &((*node)->next);
                }

                // now node points to lasts element ->next or head so we can construct the new object unconditionaly here :)
                *node = new HashNode<K, V>(key, value);
            }

            //Function to remove an entry from the bucket, if found
            void erase(const K &key)
            {
                //Exclusive lock to enable single write in the bucket
                std::unique_lock<std::shared_timed_mutex> lock(mutex_);

                HashNode<K, V>*  node = head;
                HashNode<K, V>** prev = &head;

                while (node)
                {
                    if (node->getKey() ==  key)
                    {
                        *prev = node->next;
                        delete node;
                        return;
                    }
                    else
                    {
                        prev = &node;
                        node = node->next;
                    }
                }

            }

            //Function to clear the bucket, all nodes except the dummy head node will be removed
            //The head node will be destroyed only when the bucket itself is destroyed
            void clear()
            {
                //Exclusive lock to enable single write in the bucket
                std::unique_lock<std::shared_timed_mutex> lock(mutex_);

                while(head)
                {
                    HashNode<K, V>* toDel = head;
                    delete toDel;

                    head = head->next;
                }
            }

        private:
            HashNode<K, V> * head; //The head node of the bucket
            mutable std::shared_timed_mutex mutex_; //The mutex for this bucket
    };
}

#endif

