//
//  tbb_hashtable.h
//
//  Created by Jinglei Ren on 12/23/14.
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#ifndef VM_PERSISTENCE_SLIB_HASHTABLE_H_
#define VM_PERSISTENCE_SLIB_HASHTABLE_H_

#include "hashtable.h"

#include "lib/string_hashtable.h"
#include "slib/core_hashtable.h"
#include "lib/string.h"

namespace vmp {

template<class V>
class SLibHashtable : public StringHashtable<V> {
 public:
  typedef typename StringHashtable<V>::KVPair KVPair;

  V Get(const char *key) const; ///< Returns NULL if the key is not found
  bool Insert(const char *key, V value);
  V Update(const char *key, V value);
  V Remove(const char *key);
  std::vector<KVPair> Entries(const char *key, size_t n) const;
  size_t Size() const { return table_.size(); }

 private:
  struct HashEqual {
    inline uint64_t hash(const String &hstr) const {
      return hstr.hash();
    }

    inline bool equal(const String &a, const String &b) const {
      if (a.hash() != b.hash()) return false;
      return strcmp(a.value(), b.value()) == 0;
    }
  };

  typedef typename
      slib::hashtable<String, V, HashEqual> Hashtable;
  Hashtable table_;
};

template<class V>
V SLibHashtable<V>::Get(const char *key) const {
  String skey;
  skey.set_value(key);
  V value;
  if (!table_.find(skey, value)) return NULL;
  else return value;
}

template<class V>
bool SLibHashtable<V>::Insert(const char *key, V value) {
  if (!key) return false;
  String skey(key);
  return table_.insert(skey, value);
}

template<class V>
V SLibHashtable<V>::Update(const char *key, V value) {
  String skey;
  skey.set_value(key);
  if (!table_.update(skey, value)) return NULL;
  return value;
}

template<class V>
V SLibHashtable<V>::Remove(const char *key) {
  String skey;
  skey.set_value(key);
  std::pair<String, V> removed;
  if (!table_.erase(skey, removed)) return NULL;
  FREE(removed.first.value());
  return removed.second;
}

template<class V>
std::vector<typename SLibHashtable<V>::KVPair> SLibHashtable<V>::Entries(
    const char *key, size_t n) const {
  String skey;
  skey.set_value(key);
  std::vector<std::pair<String, V>> entries = table_.entries(skey, n);
  std::vector<KVPair> results;
  for (auto entry : entries) {
    results.push_back(std::make_pair(entry.first.value(), entry.second));
  }
  return results;
}

} // vmp

#endif // VM_PERSISTENCE_SLIB_HASHTABLE_H_
