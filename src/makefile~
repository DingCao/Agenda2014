objects = Agenda.o AgendaUI.o AgendaService.o Storage.o Meeting.o User.o Date.o
files   = Agenda.cpp AgendaUI.cpp AgendaService.cpp Storage.cpp User.cpp Date.cpp Meeting.cpp
FLAG    = -std=c++0x
EXC     = Agenda
CC      = g++

$(EXC): $(objects)
	$(CC) $(FLAG) -o $(EXC) $(objects)
Agenda.o: Agenda.cpp AgendaUI.h
	$(CC) $(FLAG) -c Agenda.cpp
AgendaUI.o: AgendaUI.cpp AgendaUI.h AgendaService.h
	$(CC) $(FLAG) -c AgendaUI.cpp
AgendaService.o: AgendaService.cpp AgendaService.h Storage.h
	$(CC) $(FLAG) -c AgendaService.cpp
Storage.o: Storage.cpp Storage.h User.h Meeting.h
	$(CC) $(FLAG) -c Storage.cpp
Meeting.o: Meeting.cpp Meeting.h Date.h
	$(CC) $(FLAG) -c Meeting.cpp
User.o: User.cpp User.h
	$(CC) $(FLAG) -c User.cpp
Date.o: Date.cpp Date.h
	$(CC) $(FLAG) -c Date.cpp

cleanAll:
	rm $(objects) $(EXC) agenda.data
cleanObj:
	rm $(objects)
gdb:
	$(CC) $(FLAG) -o $(EXC) -g $(files)

