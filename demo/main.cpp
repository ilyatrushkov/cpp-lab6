// Copyright 2022 Trushkov ILya ilya.tr20002@gmail.com

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include <thread>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <csignal>
#include <atomic>

#include "for_json.hpp"
#include "processing.hpp"

int main(int argc, char *argv[]) {
  unsigned int number_of_threads;
  std::string jsonfile_path;
  unsigned int max_number_of_threads = std::thread::hardware_concurrency();
  std::srand(time(nullptr));
  switch (argc) {
    case 1:
      number_of_threads = max_number_of_threads;
      break;
    case 2:
      number_of_threads = std::atoi(argv[1]);
      if ((number_of_threads == 0) ||
          (number_of_threads > max_number_of_threads)) {
        throw std::out_of_range("Error! Invalid number of threads!");
      }
      break;
    case 3:
      number_of_threads = std::atoi(argv[1]);
      if ((number_of_threads == 0) ||
          (number_of_threads > max_number_of_threads)) {
        throw std::out_of_range("Error! Invalid number of threads!");
      }
      jsonfile_path = argv[2];
      // preparing for making json file
      break;
    default:
      throw std::out_of_range("Error! Invalid number of parameters!");
  }

  //Настройка логирования
  // Файловый логгер, в который записываются результаты с уровнями логгирования
  // trace и info
  auto fileLoggerTrace = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/Users/evgenij/lab-06-multithreads/logs/"
          "loggerFileTrace_%N.log",
      boost::log::keywords::rotation_size = 10 * 1024 * 1024,
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  // Файловый логгер, в который записываются результаты с уровнем логгирования
  // info
  auto fileLoggerInfo = boost::log::add_file_log(
      boost::log::keywords::file_name =
          "/Users/evgenij/lab-06-multithreads/logs/"
          "loggerFileInfo.log",
      boost::log::keywords::format =
          "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
  // Консольный логгер, в который записываются результаты с уровнем логгирования
  // info
  auto consoleLogger = boost::log::add_console_log(
      std::cout, boost::log::keywords::format =
                     "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");

  //Установка фильтрации
  fileLoggerTrace->set_filter(boost::log::trivial::severity >=
                              boost::log::trivial::trace);
  fileLoggerInfo->set_filter(boost::log::trivial::severity ==
                             boost::log::trivial::info);
  consoleLogger->set_filter(boost::log::trivial::severity ==
                            boost::log::trivial::info);

  // Добавление распространенных атрибутов в лог
  boost::log::add_common_attributes();
  std::vector<std::thread> threads;
  JSON json_obj;
  //Задает емкость контейнера по крайней мере, size. Новая память выделяется при
  //необходимости.
  threads.reserve(number_of_threads);
  // Обработка сигналов терминала
  std::signal(SIGINT, stopProcess);
  // Запуск потоков

  for (size_t i = 0; i < number_of_threads; i++) {
    threads.emplace_back(hashConfig, std::ref(json_obj));
  }
  for (auto& thread : threads) {
    thread.join();
  }
  if (jsonfile_exist_flag) {
    std::ofstream fout{jsonfile_path};
    fout << json_obj;
  }
  return 0;
}