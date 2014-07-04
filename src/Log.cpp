// Copyright (c) 2014 Junjie_Huang@SYSU(SNO:13331087). All Rights Reserved.
#include <iosteam>
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
  if (instance_ == NULL) instance_ = newLogList;
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
  ifstream in_file(fpath);
  if (!in_file.is_open()) return false;  // read fail
  
  string line;
  string numb_string, time_string, user, command, state;
  std::getline(in_file, line);
  while (in_file >> num_string >> time_string >> user >> command >> state,
         !in_file.eof()) {
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
  ofstream out_file(fpath);
  if (!out_file.is_open()) return false;  // write fail

  out_file << left << setw(14) << "excute_number" << setw(20) << "time"
                   << setw(14) << "user"          << setw(14) << "command"
                   << setw(8)  << "state" << endl;
  list<LogElement>::iterator it;
  for (it = log_list_.begin(); it != log_list_.end(); it++) {
    out_file << left << setw(14) << std::to_string(it->getNumber)
                     << setw(20) << Date::dateToString(it->getTime())
                     << setw(14) << it->getUserName()
                     << setw(14) << it->getCommand()
                     << setw(8)  << it->getState() << endl;
  }
  return true;  // write succeed
}

// function sync:
// synchronize information to log.data
bool LogList::sync(void) {
  writeToLog("log.data");
}

// function creatsElement:
// add a new log element to log_list_
void LogList::createElement(const LogElement& new_element) {
  log_list_.push_back(new_element);
}

