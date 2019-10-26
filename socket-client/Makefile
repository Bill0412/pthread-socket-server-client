CC = gcc
CFLAGS = -std=c11 -Wall -fmax-errors=10 -Wextra -lpthread -g

objects = main.o ClientList.o DieWithMessage.o HandleConnect.o MsgListener.o UserInterface.o

socket_client: $(objects)
	$(CC) $(CFLAGS) $^ -lpthread -lm -o $@
	
main.o: main.c Globals.h Practical.h ClientList.h
	$(CC) -c $<

ClientList.o: ClientList.c ClientList.h
	$(CC) -c $<

DieWithMessage.o: DieWithMessage.c DieWithMessage.h Practical.h
	$(CC) -c $<

HandleConnect.o: HandleConnect.c HandleConnect.h DieWithMessage.h MsgListener.h Globals.h
	$(CC) -c $<

MsgListener.o: MsgListener.c MsgListener.h Globals.h ClientList.h DieWithMessage.h 
	$(CC) -c $<

UserInterface.o: UserInterface.c UserInterface.h DieWithMessage.h Globals.h 
	$(CC) -c $<

.PHONY: clean
clean:
	rm socket_client $(objects)