gcc -c client.c -o client.o
gcc client.o libmysocketchat.a -pthread -o client.out
./client.out 0.0.0.0 $1