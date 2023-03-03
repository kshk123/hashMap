#ifndef HASH_BUCKET_H_
#define HASH_BUCKET_H_

#include "HashNode.h"
#include <shared_mutex>
#include <mutex>

namespace CTSL // Concurrent Thread Safe Library
{
// Class representing a hash bucket. The bucket is implemented as a singly linked list.
// A bucket is always constructed with a dummy head node
template <typename K, typename V> class HashBucket
{
public:
  HashBucket()
  {
  }

  ~HashBucket() // delete the bucket
  {
    clear();
  }

  // Function to find an entry in the bucket matching the key
  // If key is found, the corresponding value is copied into the parameter "value" and function returns true.
  // If key is not found, function returns false
  bool find(const K &key, V &value) const
  {
    // A shared mutex is used to enable mutiple concurrent reads
    std::shared_lock lock(mutex_);
    HashNode<K, V> *node = head;

    while (node != nullptr)
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

  // Function to insert into the bucket
  // If key already exists, update the value, else insert a new node in the bucket with the <key, value> pair
  void insert(const K &key, const V &value)
  {
    // Exclusive lock to enable single write in the bucket
    std::unique_lock lock(mutex_);
    HashNode<K, V> *prev = nullptr;
    HashNode<K, V> *node = head;

    while (node != nullptr && node->getKey() != key)
    {
      prev = node;
      node = node->next;
    }

    if (nullptr == node) // New entry, create a node and add to bucket
    {
      if (nullptr == head)
      {
        head = new HashNode<K, V>(key, value);
      }
      else
      {
        prev->next = new HashNode<K, V>(key, value);
      }
    }
    else
    {
      node->setValue(value); // Key found in bucket, update the value
    }
  }

  // Function to remove an entry from the bucket, if found
  void erase(const K &key)
  {
    // Exclusive lock to enable single write in the bucket
    std::unique_lock lock(mutex_);
    HashNode<K, V> *prev = nullptr;
    HashNode<K, V> *node = head;

    while (node != nullptr && node->getKey() != key)
    {
      prev = node;
      node = node->next;
    }

    if (nullptr == node) // Key not found, nothing to be done
    {
      return;
    }
    else // Remove the node from the bucket
    {
      if (head == node)
      {
        head = node->next;
      }
      else
      {
        prev->next = node->next;
      }
      delete node; // Free up the memory
    }
  }

  // Function to clear the bucket
  void clear()
  {
    // Exclusive lock to enable single write in the bucket
    std::unique_lock lock(mutex_);
    HashNode<K, V> *prev = nullptr;
    HashNode<K, V> *node = head;
    while (node != nullptr)
    {
      prev = node;
      node = node->next;
      delete prev;
    }
    head = nullptr;
  }

private:
  HashNode<K, V> *head = nullptr;         // The head node of the bucket
  mutable std::shared_timed_mutex mutex_; // The mutex for this bucket
};
} // namespace CTSL

#endif