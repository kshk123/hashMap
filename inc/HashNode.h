#ifndef HASH_NODE_H_
#define HASH_NODE_H_

namespace CTSL // Concurrent Thread Safe Library
{
// Class representing a templatized hash node
template <typename K, typename V> class HashNode
{
public:
  HashNode() : next(nullptr)
  {
  }
  HashNode(K key_, V value_) : next(nullptr), key(key_), value(value_)
  {
  }
  ~HashNode()
  {
    next = nullptr;
  }

  const K &getKey() const
  {
    return key;
  }
  void setValue(V value_)
  {
    value = value_;
  }
  const V &getValue() const
  {
    return value;
  }

  HashNode *next; // Pointer to the next node in the same bucket
private:
  K key;   // the hash key
  V value; // the value corresponding to the key
};
} // namespace CTSL

#endif
