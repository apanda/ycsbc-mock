//
//  mock_db.h
//  YCSB-C
//

#ifndef YCSB_C_MOCK_DB_H_
#define YCSB_C_MOCK_DB_H_

#include "core/db.h"

#include <iostream>
#include <string>
#include "core/properties.h"
#include <forward_list>
#include <unordered_map>
//#include "redis/redis_client.h"
//#include "redis/hiredis/hiredis.h"

using std::cout;
using std::endl;

namespace ycsbc {

class MockDB : public DB {
 public:
  MockDB() : fields_(){
  }

  int Read(const std::string &table, const std::string &key,
           const std::vector<std::string> *fields,
           std::vector<KVPair> &result);

  int Scan(const std::string &table, const std::string &key,
           int len, const std::vector<std::string> *fields,
           std::vector<std::vector<KVPair>> &result) {
    throw "Scan: function not implemented!";
  }

  int Update(const std::string &table, const std::string &key,
             std::vector<KVPair> &values);

  int Insert(const std::string &table, const std::string &key,
             std::vector<KVPair> &values) {
    return Update(table, key, values);
  }

  int Delete(const std::string &table, const std::string &key) {
    //std::string cmd("DEL " + key);
    //redis_.Command(cmd);
    return DB::kOK;
  }

 private:
  typedef std::unordered_map<std::string, std::forward_list<std::string>> field_map;
  field_map fields_;
  //RedisClient redis_;
};

} // ycsbc

#endif // YCSB_C_MOCK_DB_H_

