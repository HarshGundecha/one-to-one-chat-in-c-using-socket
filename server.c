#include<stdio.h>
#include<unistd.h>
#include "socketchat.h"
#include "socketconn.h"
#define OpenSocketFD(port) OpenSocketFDGeneric('s',NULL,port)
//#main()
#define ABS(N) ((N<0)?(-N):(N))

//will be splited to 2 seperate () for readinf and writing on parallel execution by threads
// int SocketChat(int connfd)
// {
// 	if(connfd < 0 )
// 		return connfd;
// 	size_t ReadCount;
// 	char TmpStr[MAXLINE];
// 	while((ReadCount=read(connfd, TmpStr, MAXLINE)) != 0)
// 	{
// 		TmpStr[ReadCount]='\0';
// 		printf("Read : %s\n", TmpStr);
// 		//printf2ndGreen("Read : ", TmpStr);
// 		ExitCheckMacro(TmpStr);
// 		fflush(stdin);
// 		printf("Write : ");
// 		fgets(TmpStr, MAXLINE, stdin);
// 		RemoveTrailingNewLineChar(TmpStr);
// 		write(connfd, TmpStr, strlen(TmpStr));
// 		ExitCheckMacro(TmpStr);
// 	}
// 	return connfd;
// }

int main(int argc, char* argv[])
{
	short tmp = close( SocketChat( GetClientFD( OpenSocketFD( argv[1] ) ) ) );
	return ABS(tmp);
}