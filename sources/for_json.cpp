// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#include "for_json.hpp"

void JSON::addHash(const std::string& data, const std::string& hash,
                   std::time_t timestamp) {
  std::scoped_lock<std::mutex> lock(_mut);
  std::stringstream rightData;
  rightData << std::hex << std::uppercase << std::stoi(data);
  json j_map;
  j_map["data"] = rightData.str();
  j_map["hash"] = hash;
  j_map["timestamp"] = timestamp;
  _j_array.push_back(j_map);
}
std::ostream& operator<<(std::ostream& out, const JSON& j) {
  std::scoped_lock<std::mutex> lock(j._mut);
  out << j._j_array.dump(4);
  return out;
}

