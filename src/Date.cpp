// Copyright (c) 2014 Junjie_Huang@SYSU. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include "Date.h"

Date::Date() {
  year_ = -1;
  month_ = -1;
  day_ = -1;
  hour_ = -1;
  minute_ = -1;
}
Date::Date(int y, int m, int d, int h, int mi): year_(y), month_(m), day_(d),
    hour_(h), minute_(mi) {}

int Date::getYear(void) const { return year_; }
void Date::setYear(int year) { year_ = year; }

int Date::getMonth(void) const { return month_; }
void Date::setMonth(int month) { month_ = month; }

int Date::getDay(void) const { return day_; }
void Date::setDay(int day) { day_ = day; }

int Date::getHour(void) const { return hour_; }
void Date::setHour(int hour) { hour_ = hour; }

int Date::getMinute(void) const { return minute_; }
void Date::setMinute(int minute) { minute_ = minute; }

bool Date::isValid(Date date) {
  // display all invalid conditions. If occoured these condition, return false.
  if (date.year_ < 1000 || date.year_ > 9999) return false;
  if (date.month_ < 1 || date.month_ > 12) return false;
  if (date.day_ < 1) return false;
  switch (date.month_) {
    case 1: case 3: case 5: case 8: case 10: case 12:
      if (date.day_ > 31) return false;
      break;
    case 4: case 6: case 11:
      if (date.day_ > 30) return false;
      break;
    case 2:
      if ((date.year_ % 100 == 0 && date.year_ % 400 == 0) ||
          (date.year_ % 100 != 0 && date.year_ % 4 == 0)) {
        if (date.day_ > 29) return false;
      } else {
        if (date.day_ > 28) return false;
      }
      break;
    }
  if (date.hour_ < 0 || date.hour_ > 23) return false;
  if (date.minute_ < 0 || date.minute_ > 59) return false;

  return true;  // don't occour with any invalid condition, the date is valid.
}

void Date::setToCurrentTime(Date& date) {
  time_t s_current_time;
  struct tm* current_time;
  s_current_time = time(NULL);
  current_time = localtime(&s_current_time);
  date.year_ = 1900 + current_time->tm_year;
  date.month_ = 1 + current_time->tm_mon;
  date.day_ = current_time->tm_mday;
  date.hour_ = current_time->tm_hour;
  date.minute_ = current_time->tm_min;
}

Date Date::stringToDate(std::string dateString) {
  Date result;
  std::stringstream ss;
  char ch;
  ss << dateString;
  ss >> result.year_ >> ch
     >> result.month_ >> ch
     >> result.day_ >> ch
     >> result.hour_ >> ch
     >> result.minute_;
  return result;
}

std::string Date::dateToString(Date date) {
  std::string result;
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(4) << std::right << date.year_ << '-'
     << std::setfill('0') << std::setw(2) << std::right << date.month_ << '-'
     << std::setfill('0') << std::setw(2) << std::right << date.day_ << '/';
  ss << std::setfill('0') << std::setw(2) << std::right << date.hour_ << ':'
     << std::setfill('0') << std::setw(2) << std::right << date.minute_;
  ss >> result;
  return result;
}

Date& Date::operator=(const Date& date) {
  this->year_ = date.year_;
  this->month_ = date.month_;
  this->day_ = date.day_;
  this->hour_ = date.hour_;
  this->minute_ = date.minute_;
  return *this;
}

bool Date::operator==(const Date& date) const {
  return (this->year_ == date.year_ &&
          this->month_ == date.month_ &&
          this->day_ == date.day_ &&
          this->hour_ == date.hour_ &&
          this->minute_ == date.minute_);
}
bool Date::operator>(const Date& date) const {
  if (this->year_ > date.year_) return true;
  if (this->year_ == date.year_ && this->month_ > date.month_) return true;
  if (this->year_ == date.year_ && this->month_ == date.month_ &&
      this->day_ > date.day_) return true;
  if (this->year_ == date.year_ && this->month_ == date.month_ &&
      this->day_ == date.day_ && this->hour_ > date.hour_) return true;
  if (this->year_ == date.year_ && this->month_ == date.month_ &&
      this->day_ == date.day_ && this->hour_ == date.hour_ &&
      this->minute_ > date.minute_) return true;
  return false;
}
bool Date::operator<(const Date& date) const {
  return !(*this == date || *this > date);
}
bool Date::operator>=(const Date& date) const {
  return (*this == date || *this > date);
}
bool Date::operator<=(const Date& date) const {
  return !(*this > date);
}

