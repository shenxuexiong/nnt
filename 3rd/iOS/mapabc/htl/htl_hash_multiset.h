
/*
 * htl-lite - a basic data structures and algorithms.
 * Copyright (C) 2009 leon hong. All rights reserved.
 * authors:
 *   leon hong <codeblocker@gmail.com>
 */

#ifndef __HTL_HASH_MULTISET_H__
#define __HTL_HASH_MULTISET_H__

#include "htl_hashtable.h"
#include "htl_functional.h"

__HTL_BEGIN_NAMESPACE

template<class Value,
         class HashFcn = hash<Value>,
         class EqualKey = equal_to<Value>,
         class Alloc = allocator>
class hash_multiset {
private:
    typedef hashtable<Value, Value, HashFcn, identity<Value>, EqualKey, Alloc> ht;
    ht rep;
public:
    typedef typename ht::key_type key_type;
    typedef typename ht::value_type value_type;
    typedef typename ht::hasher hasher;
    typedef typename ht::key_equal key_equal;

    typedef typename ht::size_type size_type;
    typedef typename ht::difference_type difference_type;
    typedef typename ht::reference reference;
    typedef typename ht::iterator iterator;

    hasher hash_funct() const { return rep.hash_funct(); }
    key_equal key_eq() const { return rep.key_eq(); }
public:
    hash_multiset() : rep(100, hasher(), key_equal()) {}
    hash_multiset(size_type n) : rep(n, hasher(), key_equal()) {}
public:
    size_type size() const { return rep.size(); }
    bool empty() const { return rep.empty(); }
    iterator begin() { return rep.begin(); }
    iterator end() { return rep.end(); }
    iterator insert(const value_type& obj) {
        return rep.insert_equal(obj);
    }

    iterator find(const key_type& key) { return rep.find(key); }
    size_type count(const key_type& key) { return rep.count(key); }
    pair<iterator, iterator> equal_range( key_type& key) {
        return rep.equal_range(key);
    }
    size_type erase(const key_type& key) { return rep.erase(key); }
    void erase(iterator it) { return rep.erase(it); }
    void clear() { return rep.clear(); }
    void resize(size_type hint) { return rep.resize(hint); }
    size_type bucket_count() { return rep.bucket_count(); }

};

__HTL_END_NAMESPACE

#endif
