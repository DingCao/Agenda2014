#include "Date.h"
#include "Storage.h"
#include <iostream>
#include <fstream>
#include "AgendaService.h"
using namespace std;

void cmp(bool a, bool b) {
	if (a != b)
		cout << "Fail" << endl;
	else
		cout << "Pass" << endl;
	cout << endl;
}

void dateTest() {
	cout << "****************************Class Date*************************" << endl;
	cout << "--------------------------Date::isValid------------------------" << endl;
	Date date1(1300, 2, 29, 1, 1);
	cout << "case:" << Date::dateToString(date1) << endl;
	cmp(Date::isValid(date1),false);
	Date date2(2012, 2, 30, 1, 1);
	cout << "case:" << Date::dateToString(date2) << endl;
	cmp(Date::isValid(date2),false);
	Date date3(-1000, 2, 11, 1, 1);
	cout << "case:" << "-1000-2-11/1:1" << endl;
	cmp(Date::isValid(date3),false);
	Date date4(10000, 2, 11, 1, 1);
	cout << "case:" << "10000-2-11/1:1" << endl;
	cmp(Date::isValid(date4),false);
	Date date5(2012, 2, 29, 24, 1);
	cout << "case:" << Date::dateToString(date5) << endl;
	cmp(Date::isValid(date5),false);
	Date date6(2012, 2, 29, 1, 60);
	cout << "case:" << Date::dateToString(date6) << endl;
	cmp(Date::isValid(date6),false);
	Date date7(2012, 0, 1, 1, 1);
	cout << "case:" << Date::dateToString(date7) << endl;
	cmp(Date::isValid(date7),false);
	Date date8(2012, 1, 0, 1, 1);
	cout << "case:" << Date::dateToString(date8) << endl;
	cmp(Date::isValid(date8),false);
	cout << "-----------------------Date::stringToDate----------------------" << endl;
	Date date9(2012, 12, 12, 12, 12);
	cout << "case:" << Date::dateToString(date9) << endl;
	cmp(date9 == Date::stringToDate("2012-12-12/12:12"),true);
	cout << "-----------------------Date::dateToString----------------------" << endl;
	Date date10(2013, 12, 12, 12, 12);
	cout << "case:" << Date::dateToString(date10) << endl;
	cmp("2013-12-12/12:12" == Date::dateToString(date10),true);
	cout << "***************************************************************" << endl << endl << endl;
}

void storageTest() {
	Storage *ins = Storage::getInstance();
	User u1("Luffy", "123", "Luffy@163.com", "110");
	User u2("Zoro", "123", "Zoro@163.com", "119");
	User u3("Chopper", "123", "Chopper@163.com", "120");
	User u4("Nami", "123", "Nami@163.com", "114");
	cout << "***********************Class Storage***************************" << endl;
	cout << "--------------------------UserCRUD-----------------------------" << endl;
	ins -> createUser(u1);
	ins -> createUser(u2);
	ins -> createUser(u3);
	cout << "Create case:Query Nami is faild before create the user." << endl;
	cmp(ins->queryUser([](const User& u){return u.getName() == "Nami";}).size() == 0, true);
	ins->createUser(u4);
	cout << "Retrieve case:Query Nami is successd after create the user." << endl;
	cmp(ins->queryUser([](const User& u){return u.getName() == "Nami";}).size() != 0, true);
	ins -> updateUser([](const User& u){return true;}, [](User& u){u.setPhone("112");});
	cout << "Update case:Query who's phone number is 112 is successd after update all users' phone to 112." << endl;
	cmp(ins->queryUser([](const User& u){return u.getPhone() == "112";}).size() != 0, true);
	ins -> deleteUser([](const User& u){return u.getName() == "Nami";});
	cout << "Delete case:Query Nami is faild after delete the user." << endl;
	cmp(ins->queryUser([](const User& u){return u.getName() == "Nami";}).size() == 0, true);
	cout << "--------------------------FileCheck----------------------------" << endl;
	ins->sync();
	delete ins;
	ins = Storage::getInstance();
	cout << "case:User list should't be empty." << endl;
	cmp(ins->queryUser([](const User& u){return true;}).size() != 0, true);
	cout << "case:Meeting list should be empty." << endl;
	cmp(ins->queryMeeting([](const Meeting& m){return true;}).size() == 0, true);
	cout << "***************************************************************" << endl;
    delete ins;
}

void agendeServiceTest() {
    cout << "\n\n--------------------------AgendaService-----------------------------\n" << endl;
    AgendaService agendaService_;
    agendaService_.startAgenda();
    
    {
        cout << "\n1.-----------------login with a user not exist!--------------------\n" << endl;
        cmp(agendaService_.userLogIn("wc", "123"), false);
    }
    {
        cout << "\n2.-----------------Create user with the same name------------------\n" << endl;
        agendaService_.userRegister("wc", "12345", "wc@qq.com", "123456"); //succeed
        cmp(agendaService_.userRegister("wc", "12345", "wc@qq.com", "123456"), false);
    }
    
    //register
    {
        agendaService_.userRegister("wc3", "12345", "wc@qq.com", "123456"); //succeed
        agendaService_.userRegister("wc4", "12345", "wc@qq.com", "123456"); //succeed
        agendaService_.userRegister("wc5", "12345", "wc@qq.com", "123456"); //succeed
        agendaService_.userRegister("wc6", "12345", "wc@qq.com", "123456"); //succeed
        agendaService_.userRegister("wc10", "12345", "wc@qq.com", "123456"); //succeed
    }
    {
        cout << "\n3.-----------------delete user------------------------------------\n" << endl;
        cmp(agendaService_.deleteUser("wc10", "12345"), true);
        cmp(agendaService_.deleteUser("wc20", "12345"), false);
    }
    {
        cout << "\n4.-----------------listAllUser------------------------------------\n" << endl;
        cmp(agendaService_.listAllUsers().size() == 8, true);
    }
    {
        cout << "\n5.-----------------create meeting, particitor not exist-----------\n" << endl;
        cmp(agendaService_.createMeeting("wc", "today0", "wc1", "2012-12-12/12:12", "2012-12-13/12:12"), false);
    }
    {
        cout << "\n6.-----------------create meeting, time not valid-----------------\n" << endl;
        cmp(agendaService_.createMeeting("wc", "today1", "wc3", "2012-12-12/12:12", "2012-12-12/11:12"), false); //t_s > t_e
        cmp(agendaService_.createMeeting("wc", "today1", "wc3", "2012-12-12/12:12", "2012-12-12/12:12"), false); //t_s == t_b
        cmp(agendaService_.createMeeting("wc", "today1", "wc3", "2012-12-12/24:00", "2012-12-13/11:12"), false); //t_s not valid
    }
    
    cout << "\n7.-----------------create meeting, time conflict------------------\n" << endl;
    cout << "0: "; cmp(agendaService_.createMeeting("wc", "today2", "wc3", "2012-12-12/12:12", "2012-12-13/11:12"), true); //succeed
    { //sponsor time conflict
       cout << "1: "; cmp(agendaService_.createMeeting("wc", "today3", "wc4", "2012-12-12/21:12", "2012-12-14/11:12"), false);  //right intersection
       cout << "2: "; cmp(agendaService_.createMeeting("wc", "today4", "wc4", "2012-12-11/21:12", "2012-12-14/11:12"), false);  //outer include
       cout << "3: "; cmp(agendaService_.createMeeting("wc", "today5", "wc4", "2012-12-11/21:12", "2012-12-13/10:12"), false);  //left intersection
       cout << "4: "; cmp(agendaService_.createMeeting("wc", "today6", "wc4", "2012-12-12/13:12", "2012-12-13/10:12"), false);  //inside include
    }
    {//participator time conflict
        cout << "5: "; cmp(agendaService_.createMeeting("wc4", "today3", "wc3", "2012-12-12/21:12", "2012-12-14/11:12"), false);
        cout << "6: "; cmp(agendaService_.createMeeting("wc4", "today4", "wc3", "2012-12-11/21:12", "2012-12-14/11:12"), false);
        cout << "7: "; cmp(agendaService_.createMeeting("wc4", "today5", "wc3", "2012-12-11/21:12", "2012-12-13/10:12"), false);
        cout << "8: "; cmp(agendaService_.createMeeting("wc4", "today6", "wc3", "2012-12-12/13:12", "2012-12-13/10:12"), false);
    }
    {//create
        cout << "9: "; cmp(agendaService_.createMeeting("wc", "today7", "wc4", "2012-12-13/11:12", "2012-12-14/12:12"), true); //succeed
        cout << "10: "; cmp(agendaService_.createMeeting("wc5", "today8", "wc6", "2012-12-13/12:12", "2012-12-14/12:12"), true); //succeed
    }
    {//create meeting, title conflict
        cout << "\n8.-----------------create meeting, title conflict-------------------\n" << endl;
        cmp(agendaService_.createMeeting("wc", "today2", "wc4", "2013-12-12/21:12", "2013-12-14/11:12"), false);
        cmp(agendaService_.createMeeting("wc4", "today2", "wc", "2013-12-12/21:12", "2013-12-14/11:12"), false);
        cmp(agendaService_.createMeeting("wc3", "today2", "wc4", "2013-12-12/21:12", "2013-12-14/11:12"), false);
        cmp(agendaService_.createMeeting("wc4", "today2", "wc3", "2013-12-12/21:12", "2013-12-14/11:12"), false);
    }
    
    {//query meeting by title
        cout << "\n9.-----------------query meeting by title--------------------------\n" << endl;
        cmp(agendaService_.meetingQuery("wc", "today2").size() == 1, true);
        cmp(agendaService_.meetingQuery("wc", "today3").size() == 0, true);
    }
    {//query meeting by time interval
        cout << "\n10.-----------------query meeting by time interval------------------\n" << endl;
        cmp(agendaService_.meetingQuery("wc", "2012-12-13/11:11", "2012-12-13/12:13").size() == 2, true);
        cmp(agendaService_.meetingQuery("wc3", "2012-12-13/11:11", "2012-12-13/12:13").size() == 1, true);
        cmp(agendaService_.meetingQuery("wc3", "2012-12-11/11:11", "2012-12-12/12:12").size() == 0, true);
    }
    {//list meetings
        cout << "\n11.-----------------list meetings-----------------------------------\n" << endl;
        cout << "1: "; cmp(agendaService_.listAllMeetings("wc").size() == 2, true);
        cout << "2: "; cmp(agendaService_.listAllMeetings("wc3").size() == 1, true);
        cout << "3: "; cmp(agendaService_.listAllSponsorMeetings("wc3").size() == 0, true);
        cout << "4: "; cmp(agendaService_.listAllSponsorMeetings("wc4").size() == 0, true);
        cout << "5: "; cmp(agendaService_.listAllParticipateMeetings("wc3").size() == 1, true);
        cout << "6: "; cmp(agendaService_.listAllParticipateMeetings("wc").size() == 0, true);
        cout << "7: "; cmp(agendaService_.listAllParticipateMeetings("wc10").size() == 0, true);
        agendaService_.deleteUser("wc", "12345");
        cout << "8: "; cmp(agendaService_.listAllMeetings("wc3").size() == 0, true);
    }
    {//delete meeting
        cout << "\n12.-----------------delete meeting----------------------------------\n" << endl;
        agendaService_.createMeeting("wc6", "today10", "wc3", "2014-12-12/12:12", "2012-15-13/11:12");
        agendaService_.createMeeting("wc7", "today11", "wc3", "2016-12-12/12:12", "2017-12-13/11:12");
        agendaService_.createMeeting("wc8", "today12", "wc3", "2018-12-12/12:12", "2019-12-13/11:12");
        agendaService_.createMeeting("wc9", "today13", "wc3", "2020-12-12/12:12", "2021-12-13/11:12");
        cmp(agendaService_.deleteMeeting("wc3", "today10"), false); //delete a meeting which is not create by wc3
        cmp(agendaService_.deleteAllMeetings("wc3"), false);  //there are no meetings create by wc3
    }
    agendaService_.quitAgenda();
    
}

int main() {
	dateTest();
	storageTest();
    agendeServiceTest();
	return 0;
}

