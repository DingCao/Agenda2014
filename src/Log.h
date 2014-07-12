// Copyright (c) 2014 Junjie_Huang@SYSU(SNO:13331087). All Rights Reserved.
#ifndef LOG_H_
#define LOG_H_

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

#include <list>
#include <string>
#include "LogElement.h"

using std::list;

class LogList {
 public:
  static LogList* getInstance();
  ~LogList();

  // we just need to record the command read from Service
  // hence we may only create new log and append them to the loglist.
  void createElement(const LogElement&);
  int getSize();
  bool sync(void);

 private:
  LogList();
  bool readFromLog(const char *fpath);
  bool writeToLog(const char *fpath);
  static LogList* instance_;
  list<LogElement> log_list_;
  DISALLOW_COPY_AND_ASSIGN(LogList);
};

#endif  // LOG_H_

