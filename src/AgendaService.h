// Copyright (c) 2014 Junjie_Huang@SYSU. All Rights Reserved.
#ifndef AGENDA_SERVICE_H_
#define AGENDA_SERVICE_H_

#include "Storage.h"
#include <list>
#include <string>

class AgendaService {
 public:
  AgendaService();
  ~AgendaService();
  bool userLogIn(std::string userName, std::string password);
  bool userRegister(std::string userName, std::string password,
                    std::string email, std::string phone);
  bool deleteUser(std::string userName, std::string password);
  // a user can only delete itself. Beside, delete all meeting the user
  // sponsor or participate
  std::list<User> listAllUsers(void);

  bool createMeeting(std::string userName, std::string title,
                     std::string participator,
                     std::string startDate, std::string endDate);
  std::list<Meeting> meetingQuery(std::string userName, std::string title);
  std::list<Meeting> meetingQuery(std::string userName, std::string startDate,
                                  std::string endDate);
  std::list<Meeting> listAllMeetings(std::string userName);
  std::list<Meeting> listAllSponsorMeetings(std::string userName);
  std::list<Meeting> listAllParticipateMeetings(std::string userName);
  bool deleteMeeting(std::string userName, std::string title);
  bool deleteUserAllMeetings(std::string userName);
  // add a new function for "dc" command in AgendaUI.h
  bool deleteAllMeetings(std::string userName);
  // used by "da" command

  void startAgenda(void);
  void quitAgenda(void);

 private:
  Storage* storage_;
};

#endif

