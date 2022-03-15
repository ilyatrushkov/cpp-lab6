// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#include <cstdlib>
#include <string>
#include <ctime>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <atomic>
#include <picosha2.h>
#include <csignal>

#include "processing.hpp"

void stopProcess(int param) {
  if (param == SIGINT) {
    continueProcess = false;
  }
}

void hashConfig(JSON& j) {
  while (continueProcess) {
    std::string genstring = std::to_string(std::rand());
    std::string hash = picosha2::hash256_hex_string(genstring);
    std::time_t timestamp(std::time(nullptr));
    std::string lastChar = hash.substr(hash.size() - kEndCharSize);

    if (lastChar == kEndChar) {
      BOOST_LOG_TRIVIAL(info) << "0000 founded in hash '" << hash
                              << "' of string '" << genstring << "'";
      if (jsonfile_exist_flag) {
        j.addHash(genstring, hash, timestamp);
      }
    } else {
      BOOST_LOG_TRIVIAL(trace)
          << "Hash '" << hash << "' get from string'" << genstring << "'";
    }
  }
}
