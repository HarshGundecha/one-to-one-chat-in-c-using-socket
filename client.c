#include<stdio.h>
#include<unistd.h>
#include "socketchat.h"
#include "socketconn.h"

//#main()
#define ABS(N) ((N<0)?(-N):(N))
#define OpenSocketFD(hostname, port) OpenSocketFDGeneric('c',hostname,port)

int main(int argc, char **argv)
{
	short tmp = close( SocketChat( OpenSocketFD( argv[1], argv[2]) ) );
	return ABS(tmp);
}