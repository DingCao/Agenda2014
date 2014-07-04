// Copyright (c) 2014 Junjie_Huang@SYSU. All Rights Reserved.
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include "AgendaUI.h"
#include "AgendaService.h"

AgendaUI::AgendaUI() {}

void AgendaUI::OperationLoop(void) {
  std::string op;
  while (executeOperation(op)) {
    op = getOperation();
  }
}

// task functions
void AgendaUI::startAgenda(void) {
  userName_ = "";
  userPassword_ = "";
  agendaService_.startAgenda();
}

std::string AgendaUI::getOperation() {
  if (userName_ == "") {
    std::cout << std::endl;
    std::cout << "----------------------- Agenda -----------------------\n";
    std::cout << "Action :\n";
    std::cout << "l   - log in Agenda by user name and password\n";
    std::cout << "r   - register an Agenda account\n";
    std::cout << "q   - quit Agenda\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << std::endl << "Agenda: ~$ ";
  } else {
    std::cout << std::endl;
    std::cout << "----------------------- Agenda -----------------------\n";
    std::cout << "Action :\n";
    std::cout << "o   - log out Agenda\n";
    std::cout << "dc  - delete Agenda account\n";
    std::cout << "lu  - list all Agenda user\n";
    std::cout << "cm  - create a meeting\n";
    std::cout << "la  - list all meetings\n";
    std::cout << "las - list all sponsor meetings\n";
    std::cout << "lap - list all participate meetings\n";
    std::cout << "qm  - query meeting by title\n";
    std::cout << "qt  - query meeting by time interval\n";
    std::cout << "dm  - delete meeting by title\n";
    std::cout << "da  - delete all meetings\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << std::endl << "Agenda@" << userName_ << " : # ";
  }
  std::string operation;
  std::cin >> operation;
  return operation;
}

bool AgendaUI::executeOperation(std::string op) {
  if (op == "") return true;
  if (userName_ == "") {
    if (op == "l") {
      userLogIn();
      return true;
    }
    if (op == "r") {
      userRegister();
      return true;
    }
    if (op == "q") {
      quitAgenda();
      return false;
    }
    std::cout << "[error] unexcepted command!" << std::endl;
    return true;
  } else {
    if (op == "o") {
      userLogOut();
      return true;
    }
    if (op == "dc") {
      deleteUser();
      return true;
    }
    if (op == "lu") {
      listAllUsers();
      return true;
    }
    if (op == "cm") {
      createMeeting();
      return true;
    }
    if (op == "la") {
      listAllMeetings();
      return true;
    }
    if (op == "las") {
      listAllSponsorMeetings();
      return true;
    }
    if (op == "lap") {
      listAllParticipateMeetings();
      return true;
    }
    if (op == "qm") {
      queryMeetingByTitle();
      return true;
    }
    if (op == "qt") {
      queryMeetingByTimeInterval();
      return true;
    }
    if (op == "dm") {
      deleteMeetingByTitle();
      return true;
    }
    if (op == "da") {
      deleteAllMeetings();
      return true;
    }
    std::cout << "[error] unexcepted command!" << std::endl;
    return true;
  }
}

void AgendaUI::userLogIn(void) {
  std::cout << "[log in] [user name] [password]" << std::endl;
  std::cout << "[log in] ";
  std::string userName, password;
  std::cin >> userName >> password;

  if (agendaService_.userLogIn(userName, password)) {
    userName_ = userName;
    userPassword_ = password;
    std::cout << "[log in] succeed!" << std::endl;
    std::cout << std::endl;
  } else {
    std::cout << "[error] log in fail!" << std::endl;
  }
}

void AgendaUI::userRegister(void) {
  std::cout << "[register] [user name] [password] [email] [phone]" << std::endl;
  std::cout << "[register] ";
  std::string userName, password, email, phone;
  std::cin >> userName >> password >> email >> phone;

  if (agendaService_.userRegister(userName, password, email, phone))
    std::cout << "[register] succeed!" << std::endl;
  else
    std::cout << "[error] register fail!" << std::endl;
}

void AgendaUI::quitAgenda(void) {
  agendaService_.quitAgenda();
}

void AgendaUI::userLogOut(void) {
  userName_ = "";
  userPassword_ = "";
}

void AgendaUI::deleteUser(void) {
  if (agendaService_.deleteUser(userName_, userPassword_)) {
    std::cout << "[delete agenda account] succeed!" << std::endl;
    userLogOut();
  } else {
    std::cout << "[error] delete agenda account fail!" << std::endl;
  }
}

void AgendaUI::listAllUsers(void) {
  std::list<User> allUserList = agendaService_.listAllUsers();
  std::list<User>::iterator it;

  std::cout << std::endl;
  std::cout << "[list all users]" << std::endl;
  std::cout << std::endl;
  std::cout << std::left << std::setw(8) << "name"
      << std::setw(16) << "email" << "phone" << std::endl;
  for (it = allUserList.begin(); it != allUserList.end(); it++)
    std::cout << std::left << std::setw(8) << it->getName()
      << std::setw(16) << it->getEmail() << it->getPhone() << std::endl;
}

void AgendaUI::createMeeting(void) {
  std::cout << std::endl;
  std::cout << "[create meeting] [title] [participator] "
      << "[start time(yyyy-mm-dd/hh:mm)] [endtime time(yyyy-mm-dd/hh:mm)]"
      << std::endl;
  std::cout << "[create meeting] ";
  std::string title, participator, sDate, eDate;
  std::cin >> title >> participator >> sDate >> eDate;

  if (agendaService_.createMeeting(
    userName_, title, participator, sDate, eDate))
    std::cout << "[create meeting] succeed!" << std::endl;
  else
    std::cout << "[error] create meeting fail!" << std::endl;
}

void AgendaUI::listAllMeetings(void) {
  std::list<Meeting> allMeetingList = agendaService_.listAllMeetings(userName_);
  std::list<Meeting>::iterator it;

  std::cout << std::endl;
  std::cout << "[list all meetings]" << std::endl;
  std::cout << std::endl;
  std::cout << std::left << std::setw(8) << "title"
      << std::setw(10) << "sponsor"
      << std::setw(14) << "participator"
      << std::setw(18) << "start time"
      << std::setw(16) << "end time"
      << std::endl;
  for (it = allMeetingList.begin(); it != allMeetingList.end(); it++) {
    std::cout << std::left << std::setw(8) << it->getTitle()
      << std::setw(10) << it->getSponsor()
      << std::setw(14) << it->getParticipator()
      << std::setw(18) << Date::dateToString(it->getStartDate())
      << std::setw(16) << Date::dateToString(it->getEndDate())
      << std::endl;
  }
}

void AgendaUI::listAllSponsorMeetings(void) {
  std::list<Meeting> sponsorMeetingList =
      agendaService_.listAllSponsorMeetings(userName_);
  std::list<Meeting>::iterator it;

  std::cout << std::endl;
  std::cout << "[list all sponsor meetings]" << std::endl;
  std::cout << std::endl;
  std::cout << std::left << std::setw(16) << "title"
    << std::setw(16) << "sponsor"
    << std::setw(16) << "participator"
    << std::setw(16) << "start time"
    << std::setw(16) << "end time"
    << std::endl;
  for (it = sponsorMeetingList.begin(); it != sponsorMeetingList.end(); it++) {
    std::cout << std::left << std::setw(16) << it->getTitle()
      << std::setw(16) << it->getSponsor()
      << std::setw(16) << it->getParticipator()
      << std::setw(16) << Date::dateToString(it->getStartDate())
      << std::setw(16) << Date::dateToString(it->getEndDate())
      << std::endl;
  }
}

void AgendaUI::listAllParticipateMeetings(void)  {
  std::list<Meeting> participateMeetingList =
      agendaService_.listAllParticipateMeetings(userName_);

  std::cout << std::endl;
  std::cout << "[list all paricipate meetings]" << std::endl;
  printMeetings(participateMeetingList);
}

void AgendaUI::queryMeetingByTitle(void)  {
  std::cout << std::endl;
  std::cout << "[query meeting] [title]:" << std::endl;
  std::cout << "[query meeting] ";
  std::string title;
  std::cin >> title;

  std::list<Meeting> titleMeetingList =
      agendaService_.meetingQuery(userName_, title);
  printMeetings(titleMeetingList);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
  std::cout << std::endl;
  std::cout << "[query meetings] "
      << "[start time(yyyy-mm-dd/hh:mm)] "
      << "[end time(yyyy-mm-dd/hh:mm)]"
      << std::endl;
  std::cout << "[query meetings] ";
  std::string sDate, eDate;
  std::cin >> sDate >> eDate;

  std::list<Meeting> timeMeetingList =
    agendaService_.meetingQuery(userName_, sDate, eDate);

  std::cout << std::endl;
  std::cout << "[query meetings]";
  printMeetings(timeMeetingList);
}

void AgendaUI::deleteMeetingByTitle(void) {
  std::cout << std::endl;
  std::cout << "[delete meeting] [title]:" << std::endl;
  std::cout << "[delete meeting] ";
  std::string title;
  std::cin >> title;

  if (agendaService_.deleteMeeting(userName_, title)) {
    std::cout << std::endl;
    std::cout << "[delete meeting by title] succeed!" << std::endl;
  } else {
    std::cout << "[error] delete meeting fail!" << std::endl;
  }
}

void AgendaUI::deleteAllMeetings(void) {
  // Actually, the function is to delete all meeting sponsored by the user.
  if (agendaService_.deleteAllMeetings(userName_)) {
    std::cout << std::endl;
    std::cout << "[delete all meetings] succeed!" << std::endl;
  } else {
    std::cout << "[error] delete meeting fail!" << std::endl;
  }
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
  std::list<Meeting>::iterator it;
  std::cout << std::endl;
  std::cout << std::left << std::setw(8) << "title"
    << std::setw(10) << "sponsor"
    << std::setw(14) << "participator"
    << std::setw(18) << "start time"
    << std::setw(16) << "end time"
    << std::endl;
  for (it = meetings.begin();
       it != meetings.end();
       it++) {
    std::cout << std::left << std::setw(8) << it->getTitle()
      << std::setw(10) << it->getSponsor()
      << std::setw(14) << it->getParticipator()
      << std::setw(18) << Date::dateToString(it->getStartDate())
      << std::setw(16) << Date::dateToString(it->getEndDate())
      << std::endl;
  }
}

