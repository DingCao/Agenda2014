// Copyright (c) 2014 Junjie_Huang@SYSU(SNO:13331087). All Rights Reserved.
#ifndef LOG_ELEMENT_H_
#define LOG_ELEMENT_H_

#include "Date.h"

using std::string;

class LogElement {
 public:
  LogElement();
  LogElement(int number, Date time, string name = "",
             string command = "", string state = "");
  int getNumber();
  void setNumber(const int excute_number);
  Date getTime();
  void setTime(const Date excute_time);
  string getUserName();
  void setUserName(const string user_name);
  string getCommand();
  void setCommand(const string command);
  string getState();
  void setState(const string excute_state);

 private:
  int excute_number_;
  Date excute_time_;
  string user_name_;
  string command_;
  string excute_state_;
};

#endif // LOG_ELEMENT_H_

