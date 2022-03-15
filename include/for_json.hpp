// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#ifndef TEMPLATE_FOR_JSON_HPP
#define TEMPLATE_FOR_JSON_HPP

#include <ctime>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

using json = nlohmann::json;

class JSON {
 public:
  void addHash(const std::string& data, const std::string& hash,
               std::time_t timestamp);
  friend std::ostream& operator<<(std::ostream& out, const JSON& j);

 private:
  mutable std::mutex mut;
  json j_array;
};

#endif  // TEMPLATE_FOR_JSON_HPP
