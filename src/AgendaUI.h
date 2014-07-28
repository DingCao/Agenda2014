#ifndef AGENDA_UI_H_
#define AGENDA_UI_H_

#include <string>
#include "AgendaService.h"
#include "Log.h"

class AgendaUI {
 public:
  AgendaUI();
  ~AgendaUI();
  void OperationLoop(void);

 private:
  // task functions
  void startAgenda(void);
  std::string getOperation();
  bool executeOperation(std::string op);
  void userLogIn(void);
  void userRegister(void);
  void quitAgenda(void);
  void userLogOut(void);
  void deleteUser(void);
  void listAllUsers(void);
  void createMeeting(void);
  void listAllMeetings(void);
  void listAllSponsorMeetings(void);
  void listAllParticipateMeetings(void);
  void queryMeetingByTitle(void);
  void queryMeetingByTimeInterval(void);
  void deleteMeetingByTitle(void);
  void deleteAllMeetings(void);
  void printMeetings(std::list<Meeting> meetings);
  // datas
  std::string userName_;
  std::string userPassword_;
  LogList* log_;
  AgendaService agendaService_;
};

#endif

