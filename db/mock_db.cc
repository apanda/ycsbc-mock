//
//  mock_db.cc
//  YCSB-C
//

#include "mock_db.h"

#include <cstring>

using namespace std;

namespace ycsbc {

int MockDB::Read(const string &table, const string &key,
         const vector<string> *fields,
         vector<KVPair> &result) {
  if (fields) {
      for (const auto &field : *fields) {
        std::cout << "GET " << key << " " << field << std::endl;
      }
  } else {
      for (const auto &field : fields_[key]) {
          std::cout << "GET " << key << " " << field << std::endl;
      }
  }
  return DB::kOK;
}

int MockDB::Update(const string &table, const string &key,
           vector<KVPair> &values) {
  if (fields_.find(key) == fields_.end()) {
      fields_.insert({key, std::forward_list<string>()});
  }
  //cout << "UPDATE " << table << " " << key << endl;
  for (auto &p : values) {
      cout << "UPDATE " << key << " " << p.first << "  " << p.second << endl;
      fields_[key].push_front(p.first);
  }
  return DB::kOK;
}

} // namespace ycsbc
