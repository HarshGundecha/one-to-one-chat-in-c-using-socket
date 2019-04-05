#include<stdio.h>
#include<unistd.h>
#include "socketchat.h"
#include "socketconn.h"

#define OpenSocketFD(hostname, port) OpenSocketFDGeneric('c',hostname,port)
//#main
#define ABS(N) ((N<0)?(-N):(N))



// int SocketChat(int connfd)
// {
// 	if(connfd < 0)
// 		return connfd;
// 	int ReadCount;
// 	char TmpStr[MAXLINE];
// 	while( printf("Write : ") && fgets(TmpStr, MAXLINE, stdin) != NULL)
// 	{
// 		RemoveTrailingNewLineChar(TmpStr);
// 		write(connfd, TmpStr, strlen(TmpStr));
// 		ExitCheckMacro(TmpStr); //checks for exit message and does so if it is
// 		TmpStr[read(connfd, TmpStr, MAXLINE)]='\0';
// 		printf2ndGreen("Read : ", TmpStr);
// 		ExitCheckMacro(TmpStr);
// 	}
// 	return connfd;
// }

int main(int argc, char **argv)
{
	short tmp = close( SocketChat( OpenSocketFD( argv[1], argv[2]) ) );
	return ABS(tmp);
}