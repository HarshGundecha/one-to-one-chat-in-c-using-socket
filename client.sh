gcc -c ./src/client.c -o ./obj/client.o
gcc ./obj/client.o ./obj/libmysocketchat.a -pthread -o ./bin/client.out
./bin/client.out $1 $2
