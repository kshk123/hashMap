#ifndef HASH_NODE_H_
#define HASH_NODE_H_

namespace CTSL // Concurrent Thread Safe Library
{
// Class representing a templatized hash node
template <typename K, typename V> class HashNode
{
public:
  HashNode()
  {
  }
  HashNode(K key_, V value_) : key(key_), value(value_)
  {
  }
  ~HashNode()
  {
    next = nullptr;
  }

  HashNode(const HashNode&) = delete;
  HashNode(HashNode&&)      = delete;
  HashNode& operator=(const HashNode&) = delete;
  HashNode& operator=(HashNode&&) = delete;


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

  HashNode *next = nullptr; // Pointer to the next node in the same bucket
private:
  K key;   // the hash key
  V value; // the value corresponding to the key
};
} // namespace CTSL

#endif
