gcc -c ./lib/socketconn.c -o ./obj/socketconn.o
gcc -c ./lib/socketchat.c -o ./obj/socketchat.o
ar rs ./obj/libmysocketchat.a ./obj/socketconn.o ./obj/socketchat.o
gcc -c ./src/server.c -o ./obj/server.o
gcc ./obj/server.o ./obj/libmysocketchat.a -pthread -o ./bin/server.out
./bin/server.out $1
