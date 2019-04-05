#include<stdio.h>
#include<unistd.h>
#include "socketchat.h"
#include "socketconn.h"

//#main()
#define ABS(N) ((N<0)?(-N):(N))
#define OpenSocketFD(port) OpenSocketFDGeneric('s',NULL,port)

int main(int argc, char** argv)
{
	short tmp = close( SocketChat( GetClientFD( OpenSocketFD( argv[1] ) ) ) );
	return ABS(tmp);
}