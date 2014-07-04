// Copyright (c) 2014 Junjie_Huang@SYSU(SNO:13331087). All Rights Reserved.
#include <fstream>
#include <sstream>
#include <string>

#include "User.h"
#include "Meeting.h"
#include "Storage.h"

Storage* Storage::instance_ = NULL;

Storage::Storage() {
  readFromFile("agenda.data");
}

std::string getMessage(const std::string& src,
                       const std::string& info,
                       const char sep) {
  int begin_pos = src.find(info);
  if (begin_pos == std::string::npos) return "";
  begin_pos += info.size();
  int end_pos = src.find(sep, begin_pos);
  int len = end_pos - begin_pos;
  std::string result(src, begin_pos, len);
  return result;
}

bool Storage::readFromFile(const char *fpath) {
  std::ifstream inFile;
  inFile.open(fpath);
  if (!inFile.is_open()) return false;

  std::string line;
  std::string collection;
  int total;
  std::getline(inFile, line);
  std::string totalString = getMessage(line, "total:", '}');
  std::stringstream ss;
  ss << totalString;
  ss >> total;
  ss.clear();
  for (int i = 0; i < total; i++) {
    std::getline(inFile, line);
    std::string name = getMessage(line, "name:\"", '\"');
    std::string password = getMessage(line, "password:\"", '\"');
    std::string email = getMessage(line, "email:\"", '\"');
    std::string phone = getMessage(line, "phone:\"", '\"');
    if (name == "" || password == "" || email == "" || phone == "") continue;
    User newUser(name, password, email, phone);
    createUser(newUser);
  }

  std::getline(inFile, line);
  totalString = getMessage(line, "total:", '}');
  ss << totalString;
  ss >> total;
  ss.clear();
  for (int i = 0; i < total; i++) {
    std::getline(inFile, line);
    std::string sponsor = getMessage(line, "sponsor:\"", '\"');
    std::string participator = getMessage(line, "participator:\"", '\"');
    std::string sdateString = getMessage(line, "sdate:\"", '\"');
    std::string edateString = getMessage(line, "edate:\"", '\"');
    std::string title = getMessage(line, "title:\"", '\"');

    Date sdate = Date::stringToDate(sdateString);
    Date edate = Date::stringToDate(edateString);
    if (sponsor == "" || participator == "" ||
        !Date::isValid(sdate) || !Date::isValid(edate)) continue;
    Meeting newMeeting(sponsor, participator, sdate, edate, title);
    createMeeting(newMeeting);
  }
  inFile.close();
  return true;
}

bool Storage::writeToFile(const char *fpath) {
  std::ofstream outFile;
  outFile.open(fpath);
  outFile << "{collecion:\"User\",total:" << userList_.size() << "}"
    << std::endl;
  std::list<User>::iterator userIt;
  for (userIt = userList_.begin(); userIt != userList_.end(); userIt++) {
    outFile << "{name:\"" << userIt->getName() << "\","
      << "password:\"" << userIt->getPassword() << "\","
      << "email:\"" << userIt->getEmail() << "\","
      << "phone:\"" << userIt->getPhone() << "\"}"
      << std::endl;
  }
  outFile << "{collecion:\"Meeting\",total:" << meetingList_.size() << "}"
    << std::endl;
  std::list<Meeting>::iterator meetingIt;
  for (meetingIt = meetingList_.begin();
       meetingIt != meetingList_.end();
       meetingIt++) {
    outFile << "{sponsor:\"" << meetingIt->getSponsor() << "\","
      << "participator:\"" << meetingIt->getParticipator() << "\","
      << "sdate:\"" << Date::dateToString(meetingIt->getStartDate()) << "\","
      << "edate:\"" << Date::dateToString(meetingIt->getEndDate()) << "\","
      << "title:\"" << meetingIt->getTitle() << "\"}"
      << std::endl;
  }
  outFile.close();
  return true;
}

Storage* Storage::getInstance(void) {
  if (instance_ == NULL) {
    instance_ = new Storage;
  }
  return instance_;
}

Storage::~Storage() {
  this->sync();
  instance_ = NULL;
}

void Storage::createUser(const User& toAdd) { userList_.push_back(toAdd); }

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
  std::list<User> listFiltered;
  std::list<User>::iterator it;
  for (it = userList_.begin(); it != userList_.end(); it++) {
    if (filter(*it)) listFiltered.push_back(*it);
  }
  return listFiltered;
}

int Storage::updateUser(std::function<bool(const User&)> filter,
                        std::function<void(User&)> switcher) {
  int count = 0;
  std::list<User>::iterator it;
  for (it = userList_.begin(); it != userList_.end(); it++) {
    if (filter(*it)) {
      switcher(*it);
      count++;
    }
  }
  return count;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
  int count = 0;
  std::list<User>::iterator it;
  for (it = userList_.begin(); it != userList_.end(); it++) {
    if (filter(*it)) {
      it = userList_.erase(it);
      count++;
      if (it == userList_.end()) break;
      // the return  value of erase() is the iterator following the one erased.
    }
  }
  return count;
}

void Storage::createMeeting(const Meeting& toAdd) {
  meetingList_.push_back(toAdd);
}

std::list<Meeting> Storage::queryMeeting(
  std::function<bool(const Meeting&)> filter) {
  std::list<Meeting> listFiltered;
  std::list<Meeting>::iterator it;
  for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
    if (filter(*it)) listFiltered.push_back(*it);
  }
  return listFiltered;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
                           std::function<void(Meeting&)> switcher) {
  int count = 0;
  std::list<Meeting>::iterator it;
  for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
    if (filter(*it)) {
      switcher(*it);
      count++;
    }
  }
  return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
  int count = 0;
  std::list<Meeting>::iterator it;
  for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
    if (filter(*it)) {
      it = meetingList_.erase(it);
      // information seen in Storage::deleteUser()
      count++;
    }
  }
  return count;
}

// Call the private menber function writeToFile().
bool Storage::sync(void) {
  return writeToFile("agenda.data");
}

