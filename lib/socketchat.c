#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

//#SocketChat()
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE   "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAXLINE 8000
#define ExitCheckMacro(TmpStr) if(strcmp("EXIT",TmpStr)==0){printf("Chat Ended\n");break;}
#define printf2ndGreen(str1,str2)	printf(ANSI_COLOR_BLUE"%s" ANSI_COLOR_GREEN"%s\n" ANSI_COLOR_RESET, str1, str2)
#define RemoveTrailingNewLineChar(TmpStr) TmpStr[strlen(TmpStr)-1]='\0'

void* PT_SocketReadMessage(void *connfd)
{
	if( *(int*)connfd < 0 )
		return ((int*)connfd);
	char TmpStr[MAXLINE];
	while(1)
	{
		TmpStr[read(*(int*)connfd, TmpStr, MAXLINE)]='\0';
		if(TmpStr[0] == '\0')
		{
			*(int*)connfd = 0;
			return 0;
		}
		printf2ndGreen("Read : ", TmpStr);
		ExitCheckMacro(TmpStr);
	}
	*(int*)connfd = 0;
	return 0;
}

int SocketWriteMessage(int *connfd)
{
	if(*connfd < 0 )
		return *connfd;
	int tmp = *connfd;
	char TmpStr[MAXLINE];
	while( printf("Write : ") && fgets(TmpStr, MAXLINE, stdin) != NULL && *connfd )
	{
		RemoveTrailingNewLineChar(TmpStr);
		write(*connfd, TmpStr, strlen(TmpStr));
		ExitCheckMacro(TmpStr); //checks for exit message and does so if it is
	}
	return tmp;
}

int SocketChat(int connfd)
{
	if(connfd < 0 )
		return connfd;
	int err, tmp = connfd;
	pthread_t reader;
	pthread_create(&reader, NULL, PT_SocketReadMessage, (void *)&tmp);
	return SocketWriteMessage(&tmp);
}