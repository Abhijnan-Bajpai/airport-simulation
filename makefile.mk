a.out : server.o client.o
	gcc client.c server.c
client.o : client.c server.h
	gcc -c client.c
server.o : server.c server.h
	gcc -c server.c