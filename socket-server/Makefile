CC = gcc
CFLAGS = -std=c11 -Wall -fmax-errors=10 -Wextra -lpthread -g

objects = main.o Acceptor.o ClientList.o DieWithMessage.o TCPServerUtility.o 

socket_server: $(objects) -lm -lpthread
	$(CC) -o socket_server $(objects) -lm -lpthread

main.o: Practical.h ClientList.h

Acceptor.o: Practical.h ClientList.h Acceptor.h 

ClientList.o: ClientList.h

DieWithMessage.o: Practical.h DieWithMessage.h

TCPServerUtility.o: DieWithMessage.h ClientList.h TCPServerUtility.h

.PHONY: clean
clean:
	rm socket_server $(objects)