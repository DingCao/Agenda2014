// Copyright (c) 2014 Junjie_Huang@SYSU. All Rights Reserved.
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include "AgendaUI.h"

AgendaUI::AgendaUI() {
  startAgenda();
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current, "system",
      "start_Agenda", "succeed");
  log_->createElement(new_log);
}

AgendaUI::~AgendaUI() {
  delete log_;
}

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
  log_ = LogList::getInstance();
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

    Date current;
    Date::setToCurrentTime(current);
    LogElement new_log(log_->getSize()+1, current, "system",
        "unexcepted_command", "error");
    log_->createElement(new_log);

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
    
    Date current;
    Date::setToCurrentTime(current);
    LogElement new_log(log_->getSize()+1, current, "system",
        "unexcepted_command", "error");
    log_->createElement(new_log);
    
    std::cout << "[error] unexcepted command!" << std::endl;
    return true;
  }
}

void AgendaUI::userLogIn(void) {
  std::cout << "[log in] [user name] [password]" << std::endl;
  std::cout << "[log in] ";
  std::string userName, password;
  std::cin >> userName >> password;

  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current, userName, "log_in");

  if (agendaService_.userLogIn(userName, password)) {
    userName_ = userName;
    userPassword_ = password;

    new_log.setState("succeed");
    log_->createElement(new_log);

    std::cout << "[log in] succeed!" << std::endl;
    std::cout << std::endl;
  } else {
    new_log.setState("fail");
    log_->createElement(new_log);
    
    std::cout << "[error] log in fail!" << std::endl;
  }
}

void AgendaUI::userRegister(void) {
  std::cout << "[register] [user name] [password] [email] [phone]" << std::endl;
  std::cout << "[register] ";
  std::string userName, password, email, phone;
  std::cin >> userName >> password >> email >> phone;
  
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current, userName, "register");

  if (agendaService_.userRegister(userName, password, email, phone)) {
    new_log.setState("succeed");
    log_->createElement(new_log);
    std::cout << "[register] succeed!" << std::endl;
  } else {
    new_log.setState("fail");
    log_->createElement(new_log);
    std::cout << "[error] register fail!" << std::endl;
  }
}

void AgendaUI::quitAgenda(void) {
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current, "system",
      "quit_Agenda", "succeed");
  log_->createElement(new_log);
  log_->sync();
  agendaService_.quitAgenda();
}

void AgendaUI::userLogOut(void) {
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "log_out", "succeed");
  log_->createElement(new_log);
  userName_ = "";
  userPassword_ = "";
}

void AgendaUI::deleteUser(void) {
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "delete_account");
  if (agendaService_.deleteUser(userName_, userPassword_)) {
    new_log.setState("succeed");
    log_->createElement(new_log);
    std::cout << "[delete agenda account] succeed!" << std::endl;
    userLogOut();
  } else {
    new_log.setState("fail");
    log_->createElement(new_log);
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
      << std::setw(20) << "email" << "phone" << std::endl;
  for (it = allUserList.begin(); it != allUserList.end(); it++)
    std::cout << std::left << std::setw(8) << it->getName()
      << std::setw(20) << it->getEmail() << it->getPhone() << std::endl;

  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "list_all_users", "succeed");
  log_->createElement(new_log);
}

void AgendaUI::createMeeting(void) {
  std::cout << std::endl;
  std::cout << "[create meeting] [title] [participator] "
      << "[start time(yyyy-mm-dd/hh:mm)] [endtime time(yyyy-mm-dd/hh:mm)]"
      << std::endl;
  std::cout << "[create meeting] ";
  std::string title, participator, sDate, eDate;
  std::cin >> title >> participator >> sDate >> eDate;
  
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "create_meeting");

  if (agendaService_.createMeeting(
    userName_, title, participator, sDate, eDate)) {
    new_log.setState("succeed");
    log_->createElement(new_log);
    std::cout << "[create meeting] succeed!" << std::endl;
  } else {
    new_log.setState("fail");
    log_->createElement(new_log);
    std::cout << "[error] create meeting fail!" << std::endl;
  }
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
  
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "list_all_meetings", "succeed");
  log_->createElement(new_log);
}

void AgendaUI::listAllSponsorMeetings(void) {
  std::list<Meeting> sponsorMeetingList =
      agendaService_.listAllSponsorMeetings(userName_);
  std::list<Meeting>::iterator it;

  std::cout << std::endl;
  std::cout << "[list all sponsor meetings]" << std::endl;
  std::cout << std::endl;
  printMeetings(sponsorMeetingList);

  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "list_all_sponsor_meetings", "succeed");
  log_->createElement(new_log);
}

void AgendaUI::listAllParticipateMeetings(void)  {
  std::list<Meeting> participateMeetingList =
      agendaService_.listAllParticipateMeetings(userName_);

  std::cout << std::endl;
  std::cout << "[list all paricipate meetings]" << std::endl;
  printMeetings(participateMeetingList);

  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "list_all_participate_meetings", "succeed");
  log_->createElement(new_log);
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

  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "query_meetings_by_title", "succeed");
  log_->createElement(new_log);
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
  
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "query_meetings_by_time", "succeed");
  log_->createElement(new_log);
}

void AgendaUI::deleteMeetingByTitle(void) {
  std::cout << std::endl;
  std::cout << "[delete meeting] [title]:" << std::endl;
  std::cout << "[delete meeting] ";
  std::string title;
  std::cin >> title;
  
  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "delete_meeting_by_title");

  if (agendaService_.deleteMeeting(userName_, title)) {
    new_log.setState("succeed");
    std::cout << std::endl;
    std::cout << "[delete meeting by title] succeed!" << std::endl;
  } else {
    new_log.setState("fail");
    std::cout << "[error] delete meeting fail!" << std::endl;
  }
  log_->createElement(new_log);
}

void AgendaUI::deleteAllMeetings(void) {

  Date current;
  Date::setToCurrentTime(current);
  LogElement new_log(log_->getSize()+1, current,
      userName_, "delete_sponsored_meetings");

  // Actually, the function is to delete all meeting sponsored by the user.
  if (agendaService_.deleteAllMeetings(userName_)) {
    new_log.setState("succeed");
    std::cout << std::endl;
    std::cout << "[delete all meetings] succeed!" << std::endl;
  } else {
    new_log.setState("fail");
    std::cout << "[error] delete meeting fail!" << std::endl;
  }
  log_->createElement(new_log);
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

