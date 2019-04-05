gcc -c socketconn.c -o socketconn.o
gcc -c socketchat.c -o socketchat.o
ar rs libmysocketchat.a socketconn.o socketchat.o
gcc -c server.c -o server.o
gcc server.o libmysocketchat.a -pthread -o server.out
./server.out $1