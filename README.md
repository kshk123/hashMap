# hashMap
A concurrent thread-safe hash map implemented in C++.

Anyone can use the hash-map by simply including the header files in the "inc" folder.
Currently, copy and move of the hash is not supported.

A main is provided to test the basic scenarios of the hash-map.

The hash map is implemented as an array of hash buckets.
Each hash bucket is a single linked list of hash nodes and has a mutex associated with it.
Multiple threads can read from the same bucket simulatenously, but only one thread can write
into the same bucket. Since the mutex is per bucket, if multiple threads try to write into different
buckets simulatenously, they will be allowed to do so. This allows some level of concurrency for the hash map.

The mutex is implemented as "std::shared_timed_mutex" from C++14 and uses "std::unique_lock" from C++11 for writes
and "std::shared_lock" from C++14 for reading from a bucket.
