// Copyright (c) 2014 Junjie_Huang@SYSU. All Rights Reserved.
#include "AgendaService.h"

AgendaService::AgendaService() {
  startAgenda();
}

AgendaService::~AgendaService() {
  quitAgenda();
  delete storage_;
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
  std::function<bool(const User&)> toLogIn = [userName, password](
      const User& user) {
    if (user.getName() == userName && user.getPassword() == password)
      return true;
    else
      return false;
  };

  std::list<User> logInList = storage_->queryUser(toLogIn);
  if (!logInList.empty())
    return true;
  else
    return false;
}

bool AgendaService::userRegister(std::string userName, std::string password,
                                 std::string email, std::string phone) {
  std::list<User> allUsers = listAllUsers();
  std::list<User>::iterator it;
  for (it = allUsers.begin(); it != allUsers.end(); it++) {
    if (it->getName() == userName)  {
      return false;
    }
  }
  User newUser(userName, password, email, phone);
  storage_->createUser(newUser);
  return true;
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
  std::function<bool(const User&)> toDelete = [userName, password](
      const User& user) {
    if (user.getName() == userName && user.getPassword() == password)
      return true;
    else
      return false;
  };
  deleteAllMeetings(userName);
  int result = storage_->deleteUser(toDelete);

  return static_cast<bool>(result);
}
// a user can only delete itself

std::list<User> AgendaService::listAllUsers(void) {
  std::function<bool(const User&)> toList = [](const User& user) {
    return true;
  };
  return storage_->queryUser(toList);
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                                  std::string participator,
                                  std::string startDate, std::string endDate) {
  Meeting newMeeting(userName, participator,
                     Date::stringToDate(startDate),
                     Date::stringToDate(endDate),
                     title);

  std::list<Meeting> queryList = listAllMeetings(userName);
  std::list<Meeting> temp = listAllMeetings(participator);
  while (!temp.empty()) {
    std::list<Meeting>::iterator it = temp.begin();
    queryList.push_back(*it);
    temp.pop_back();
  }

  std::list<Meeting>::iterator itTime;
  bool timeValid = true;
  // timeCase1: startTime or endTime is unvalid
  bool timeCase1 = !(Date::isValid(newMeeting.getStartDate()) &&
                     Date::isValid(newMeeting.getEndDate()));
  // timeCase2: the new meeting end before it start
  bool timeCase2 = newMeeting.getStartDate() >= newMeeting.getEndDate();
  if (timeCase1 || timeCase2) timeValid = false;
  for (itTime = queryList.begin(); itTime != queryList.end(); itTime++) {
    if (itTime->getTitle() == newMeeting.getTitle()) {
      timeValid = false;
      break;
    }
    // timeCase3: startTime or endTime is included in existed meeting
    bool timeCase3 = (itTime->getStartDate() <= newMeeting.getStartDate() &&
                      newMeeting.getStartDate() < itTime->getEndDate()) ||
                     (itTime->getStartDate() < newMeeting.getEndDate() &&
                      newMeeting.getEndDate() <= itTime->getEndDate());
    // timeCase$: the existed meeting is included by the new one
    bool timeCase4 = (newMeeting.getStartDate() <= itTime->getStartDate() &&
                      itTime->getStartDate() < newMeeting.getEndDate()) ||
                     (newMeeting.getStartDate() < itTime->getEndDate() &&
                      itTime->getEndDate() <= newMeeting.getEndDate());
    if (timeCase3 || timeCase4) {
      timeValid = false;
      break;
    }
  }

  bool validParticipator = false;
  std::list<User> allUsers = listAllUsers();
  std::list<User>::iterator it;
  for (it = allUsers.begin(); it != allUsers.end(); it++) {
    if (it->getName() == participator) {
      validParticipator = true;
      break;
    }
  }
  if (participator == userName) validParticipator = false;
  if (validParticipator && timeValid) {
    storage_->createMeeting(newMeeting);
    return true;
  } else {
    return false;
  }
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                               std::string title) {
  std::function<bool(const Meeting&)> findMeetingByTitle = [userName, title](
      const Meeting& meeting) {
    if ((meeting.getSponsor() == userName ||
         meeting.getParticipator() == userName) && meeting.getTitle() == title)
      return true;
    else
      return false;
  };
  return storage_->queryMeeting(findMeetingByTitle);
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                               std::string startDate,
                                               std::string endDate) {
  std::function<bool(const Meeting&)> findMeetingByDate = [
      userName, startDate, endDate](
      const Meeting& meeting) {
    Date meetSDate = meeting.getStartDate();
    Date meetEDate = meeting.getEndDate();
    Date sDate = Date::stringToDate(startDate);
    Date eDate = Date::stringToDate(endDate);
    
    bool isNameValid = (meeting.getSponsor() == userName ||
                        meeting.getParticipator() == userName);
    bool isStartTimeValid = meetSDate >= sDate && meetSDate < eDate;
    bool isEndTimeValid = meetEDate > sDate && meetEDate <= eDate;
    bool isInclude = meetSDate <= sDate && meetEDate >= eDate;
    if (isNameValid && (isStartTimeValid || isEndTimeValid || isInclude))
      return true;
    else
      return false;
  };
    return storage_->queryMeeting(findMeetingByDate);
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  std::function<bool(const Meeting&)> findMeetingByName = [userName](
      const Meeting& meeting) {
    if (meeting.getSponsor() == userName ||
        meeting.getParticipator() == userName)
      return true;
    else
      return false;
  };
  return storage_->queryMeeting(findMeetingByName);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
  std::function<bool(const Meeting&)> findMeetingBySponsor = [userName](
      const Meeting& meeting) {
    if (meeting.getSponsor() == userName)
      return true;
    else
      return false;
  };
  return storage_->queryMeeting(findMeetingBySponsor);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(
    std::string userName) {
  std::function<bool(const Meeting&)> findMeetingByParticipator = [userName](
      const Meeting& meeting) {
    if (meeting.getParticipator() == userName)
      return true;
    else
      return false;
  };
  return storage_->queryMeeting(findMeetingByParticipator);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  std::function<bool(const Meeting&)> toDeleteByTitle = [userName, title](
      const Meeting& meet) {
    if (meet.getSponsor() == userName && meet.getTitle() == title)
      return true;
    else
      return false;
  };
  int result = storage_->deleteMeeting(toDeleteByTitle);
  return static_cast<bool>(result);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
  std::function<bool(const Meeting&)> toDeleteBySponsor = [userName](
      const Meeting& meet) {
    if (meet.getSponsor() == userName)
      return true;
    else
      return false;
  };
  int result = storage_->deleteMeeting(toDeleteBySponsor);
  return static_cast<bool>(result);
}

bool AgendaService::deleteUserAllMeetings(std::string userName) {
  std::function<bool(const Meeting&)> toDeleteByName = [userName](
      const Meeting& meet) {
    if (meet.getSponsor() == userName ||
        meet.getParticipator() == userName)
        return true;
    else
      return false;
  };
  int result = storage_->deleteMeeting(toDeleteByName);
  return static_cast<bool>(result);
}

void AgendaService::startAgenda(void) {
  storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
  storage_->sync();
}

