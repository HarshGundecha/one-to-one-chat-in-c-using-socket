#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include "socketcomm.h"
#define OpenSocketFD(port) OpenSocketFDGeneric('s',NULL,port)
//#main()
#define ABS(N) ((N<0)?(-N):(N))

//#ReadWriteMessageToFD()
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE   "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAXLINE 8000
#define ExitCheckMacro(TmpStr) if(strcmp("EXIT",TmpStr)==0){printf("Chat Ended\n");break;}
#define printf2ndGreen(str1,str2)	printf(ANSI_COLOR_BLUE"%s" ANSI_COLOR_GREEN"%s\n" ANSI_COLOR_RESET, str1, str2)
#define RemoveTrailingNewLineChar(TmpStr) TmpStr[strlen(TmpStr)-1]='\0'

//will be splited to 2 seperate () for readinf and writing on parallel execution by threads
// int ReadWriteToFD(int connfd)
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

void* readerfn(void *fd)
{
	char TmpStr[MAXLINE];
	while(1)
	{
		TmpStr[read(*(int*)fd, TmpStr, MAXLINE)]='\0';
		printf2ndGreen("Read : ", TmpStr);
		//ExitCheckMacro(TmpStr);
	}
}


int ReadWriteToFD(int connfd)
{
	if(connfd < 0 )
		return connfd;
	pthread_t reader;
	pthread_create(&reader, NULL, readerfn, (void *)&connfd);
	char TmpStr[MAXLINE];
	while( printf("Write : ") && fgets(TmpStr, MAXLINE, stdin) != NULL)
	{
		RemoveTrailingNewLineChar(TmpStr);
		write(connfd, TmpStr, strlen(TmpStr));
		//ExitCheckMacro(TmpStr); //checks for exit message and does so if it is
	}
	return connfd;
}

int main(int argc, char* argv[])
{
	short tmp = close( ReadWriteToFD( GetClientFD( OpenSocketFD( argv[1] ) ) ) );
	return ABS( tmp );
}