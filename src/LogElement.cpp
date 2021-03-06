// Copyright (c) 2014 Junjie_Huang@SYSU(SNO:13331087). All Rights Reserved.
#include "LogElement.h"
#include "Date.h"

// defaultconstructors 
LogElement::LogElement() {
  excute_number_ = 0;
  user_name_ = "";
  command_ = "";
  excute_state_ = "";
}
LogElement::LogElement(int number, Date time, string name,
             string command, string state) {
  excute_number_ = number;
  excute_time_ = time;
  user_name_ = name;
  command_ = command;
  excute_state_ = state;
}

int LogElement::getNumber() { return excute_number_; }
void LogElement::setNumber(const int excute_number) {
  excute_number_ = excute_number;
}

Date LogElement::getTime() { return excute_time_; }
void LogElement::setTime(const Date excute_time) { excute_time_ = excute_time; }

string LogElement::getUserName() { return user_name_; }
void LogElement::setUserName(const string user_name) { user_name_ = user_name; }

string LogElement::getCommand() { return command_; }
void LogElement::setCommand(const string command) { command_ = command; }

string LogElement::getState() { return excute_state_; }
void LogElement::setState(const string excute_state) {
  excute_state_ = excute_state;
}

