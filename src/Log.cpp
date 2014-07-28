// Copyright (c) 2014 Junjie_Huang@SYSU(SNO:13331087). All Rights Reserved.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Log.h"

using std::cin;
using std::endl;
using std::string;
using std::list;

using std::left;
using std::setw;

// default list pointer set to NULL
// point to a new LogList when a loglist is read from log.data
LogList* LogList::instance_ = NULL;

// get the only LogList* instance_ in the progress of the program
LogList* LogList::getInstance() {
  if (instance_ == NULL) instance_ = new LogList;
  return instance_;
}

// default constructor
// only run when LogList::getInstance() is called
// get log from log.data
LogList::LogList() {
  readFromLog("log.data");
}

// destructor
// before the instance is delete, synchronize all information to log.data
LogList::~LogList() {
  instance_->sync();
  instance_ = NULL;
}

// FILE IO

// function readFromLog:
// get a line of information once,
// then put then into the log storage, that is, the instance_
bool LogList::readFromLog(const char *fpath) {
  std::ifstream in_file(fpath);
  if (!in_file.is_open()) return false;  // read fail

  string line;
  string num_string, time_string, user, command, state;
  std::getline(in_file, line);
  while (!in_file.eof(),
      in_file >> num_string >> time_string >> user >> command >> state) {
    int number = std::stoi(num_string);
    Date time = Date::stringToDate(time_string);
    LogElement new_element(number, time, user, command, state);
    createElement(new_element);
  }
  return true;  // read succeed
}

// function writetoLog:
// get information from log_list_ and write it to log.data
bool LogList::writeToLog(const char *fpath) {
  std::ofstream out_file(fpath);
  if (!out_file.is_open()) return false;  // write fail

  out_file << left << setw(14) << "excute_number" << setw(20) << "time"
                   << setw(14) << "user"          << setw(30) << "command"
                   << "state" << endl;
  list<LogElement>::iterator it;
  for (it = log_list_.begin(); it != log_list_.end(); it++) {
    out_file << left << setw(14) << it->getNumber()
                     << setw(20) << Date::dateToString(it->getTime())
                     << setw(14) << it->getUserName()
                     << setw(30) << it->getCommand()
                     << it->getState() << endl;
  }
  out_file << endl;
  return true;  // write succeed
}

// function sync:
// synchronize information to log.data
bool LogList::sync(void) {
  writeToLog("log.data");
  return true;
}

// function creatsElement:
// add a new log element to log_list_
void LogList::createElement(const LogElement& new_element) {
  log_list_.push_back(new_element);
}

// function getSize:
// return the size of the log. used to add new element.
int LogList::getSize() { return log_list_.size(); }

