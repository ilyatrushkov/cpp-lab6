// Copyright 2022 Trushkov Ilya ilya.tr20002@gmail.com

#ifndef TEMPLATE_PROCESSING_HPP
#define TEMPLATE_PROCESSING_HPP

#include "for_json.hpp"

std::atomic<bool> continueProcess = true;
std::atomic<bool> jsonfile_exist_flag = false;

const char kEndChar[] = "0000";
const size_t kEndCharSize = 4;

void stopProcess(int param);
void hashConfig(JSON& j);

#endif  // TEMPLATE_PROCESSING_HPP
