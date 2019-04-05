#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "socketcomm.h"

#define OpenSocketFD(hostname, port) OpenSocketFDGeneric('c',hostname,port)
//#main
#define ABS(N) ((N<0)?(-N):(N))

//#ReadWriteMessageToFD()
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE   "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define	MAXLINE	 8192
#define ExitCheckMacro(TmpStr) if(strcmp("EXIT",TmpStr)==0){printf("Chat Ended\n");break;}
#define printf2ndGreen(str1,str2)	printf(ANSI_COLOR_BLUE"%s" ANSI_COLOR_GREEN"%s\n" ANSI_COLOR_RESET, str1, str2)
#define RemoveTrailingNewLineChar(TmpStr) TmpStr[strlen(TmpStr)-1]='\0'

// int ReadWriteMessageToFD(int connfd)
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

int ReadWriteMessageToFD(int connfd)
{
	if(connfd < 0)
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

int main(int argc, char **argv)
{
	short tmp = close( ReadWriteMessageToFD( OpenSocketFD( argv[1], argv[2]) ) );
	return ABS(tmp);
}