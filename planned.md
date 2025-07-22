# Drift Database Enhancement Learning Path

## Overview
This document provides a structured learning path to implement the planned enhancements for the Drift Key-Value Store and grow as a database systems developer.

---

## Phase 1: Core Database Concepts & Current Enhancements

### 1. TTL (Time-To-Live) Implementation
**What to Study:**
- **Time-based data structures**: Learn about priority queues, min-heaps for efficient expiration tracking
- **System time handling**: `std::chrono` in C++, timestamp management
- **Background threading**: `std::thread`, `std::async`, thread-safe operations

**Implementation Approach:**
- Add expiration timestamps to your key-value pairs
- Create a background thread that periodically checks and removes expired keys
- Implement efficient data structures to track expiration times

### 2. Write-Ahead Logging (WAL)
**What to Study:**
- **Database durability concepts**: ACID properties, crash recovery
- **File I/O and binary formats**: Efficient logging formats, append-only files
- **Recovery algorithms**: How to replay logs after crashes

**Implementation Steps:**
- Design a log entry format (operation type, key, value, timestamp)
- Implement log writing before any data modification
- Create recovery mechanism to replay logs on startup

### 3. LRU Cache Integration
**What to Study:**
- **Cache algorithms**: LRU, LFU, cache replacement policies
- **Hash tables + doubly linked lists**: The classic LRU implementation
- **Memory management**: Cache size limits, eviction strategies

**Implementation:**
- Build an LRU cache class with O(1) get/put operations
- Integrate it as a layer above your file-based storage
- Handle cache invalidation on updates/deletes

---

## Phase 2: Advanced Database Features

### 4. Multi-threading & Concurrency
**What to Study:**
- **Thread synchronization**: Mutexes, read-write locks, atomic operations
- **Concurrent data structures**: Thread-safe hash maps, lock-free programming
- **Database concurrency control**: Reader-writer locks, optimistic concurrency

**Key Concepts:**
- MVCC (Multi-Version Concurrency Control)
- Deadlock prevention
- Connection pooling

### 5. Query Engine Enhancement
**What to Study:**
- **Indexing**: B-trees, B+ trees, hash indexes
- **Query optimization**: Query planners, cost-based optimization
- **Range queries**: Sorted data structures, binary search trees

---

## Phase 3: Production-Ready Features

### 6. Persistence & Storage Engine
**What to Study:**
- **Storage formats**: Move beyond CSV to binary formats (Protocol Buffers, MessagePack)
- **Page-based storage**: Database pages, buffer management
- **Compression**: Data compression algorithms

### 7. Networking & Distributed Systems
**What to Study:**
- **Network programming**: TCP/UDP sockets, protocol design
- **Serialization**: Binary protocols, message framing
- **Distributed consensus**: Raft algorithm, leader election

---

## Immediate Next Steps (Priority Order)

### Week 1-2: TTL Implementation
Start with this structure:
```cpp
struct KeyValueEntry {
    std::string key;
    std::string value;
    std::chrono::steady_clock::time_point expiry;
    bool has_ttl;
};
```

### Week 3-4: Basic WAL
- Create a simple log file format
- Implement log writing for all operations
- Add basic recovery on startup

### Week 5-6: LRU Cache
- Implement in-memory LRU cache
- Add cache hit/miss metrics
- Integrate with existing get/set operations

---

## Learning Resources

### Books
- **"Database System Concepts"** by Silberschatz (fundamental database theory)
- **"Designing Data-Intensive Applications"** by Martin Kleppmann (modern systems)
- **"C++ Concurrency in Action"** by Anthony Williams (threading in C++)

### Practical Projects
- Study Redis source code (excellent C implementation)
- Look at RocksDB for storage engine concepts
- Examine SQLite for simple, effective design patterns

### Online Resources
- CMU Database Systems course (free online)
- "Build Your Own Database" tutorials
- LeetCode system design problems

---

## Long-term Roadmap

### Months 1-2
Implement the three planned features (TTL, WAL, LRU Cache)

### Months 3-4
Add networking layer, make it a client-server system

### Months 5-6
Implement indexing and query optimization

### Months 7+
Explore distributed systems concepts

---

## Pro Tips

- **Test-driven development**: Write tests for each feature first
- **Benchmarking**: Measure performance before and after each enhancement
- **Documentation**: Document your design decisions and trade-offs
- **Version control**: Use git branches for each major feature
- **Code review**: Share your code on GitHub for community feedback

---

## Getting Started

Start with TTL implementation as it's the most straightforward and will teach you valuable threading concepts that apply to other features. Each enhancement builds upon previous knowledge, creating a solid foundation for advanced database system development.

### Sample TTL Implementation Structure
```cpp
class TTLManager {
private:
    std::priority_queue<ExpiryEntry> expiry_queue;
    std::thread cleanup_thread;
    std::mutex expiry_mutex;
    
public:
    void addWithTTL(const std::string& key, const std::string& value, int ttl_seconds);
    void cleanup_expired();
    void start_background_cleanup();
};
```

### Sample WAL Entry Format
```cpp
struct WALEntry {
    enum OperationType { SET, DELETE, UPDATE, RENAME };
    OperationType op_type;
    std::string key;
    std::string value;
    std::string old_key; // for rename operations
    uint64_t timestamp;
    uint32_t checksum;
};
```

### Sample LRU Cache Interface
```cpp
template<typename K, typename V>
class LRUCache {
private:
    size_t capacity;
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> cache_map;
    std::list<std::pair<K, V>> cache_list;
    
public:
    LRUCache(size_t cap) : capacity(cap) {}
    
    V get(const K& key);
    void put(const K& key, const V& value);
    void remove(const K& key);
    size_t size() const;
};
```

Remember: Each feature you implement makes you a better systems programmer. Focus on understanding the underlying concepts, not just copying code. Good luck with your database journey!