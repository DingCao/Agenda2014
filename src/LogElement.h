// Copyright (c) 2014 Junjie_Huang@SYSU(SNO:13331087). All Rights Reserved.
#ifndef LOG_ELEMENT_H_
#define LOG_ELEMENT_H_

using std::string;

class LogElement {
 public:
  LogElement();
  LogElement(int number, string time, string name,
             string command, string state);
  int getNumber();
  void setNumber(int excute_number);
  Date getTime();
  void setTime(Date excute_time);
  string getUserName();
  void setUserName(string user_name);
  string getCommand();
  void setCommand(string command);
  string getState();
  void setState(string excute_state);

 private:
  int excute_number_;
  Date excute_time_;
  string user_name_;
  string command_;
  string excute_state;
};

#endif // LOG_ELEMENT_H_

