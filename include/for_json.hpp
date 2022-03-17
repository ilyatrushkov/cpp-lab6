// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#ifndef INCLUDE_FOR_JSON_HPP_
#define INCLUDE_FOR_JSON_HPP_

#include <ctime>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

using json = nlohmann::json;

class JSON {
 private:
  mutable std::mutex _mut;
  json _j_array;
 public:
  void addHash(const std::string& data, const std::string& hash,
               std::time_t timestamp);
  friend std::ostream& operator<<(std::ostream& out, const JSON& j);
};

#endif  // INCLUDE_FOR_JSON_HPP_
