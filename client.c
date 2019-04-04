#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
//include <netinet/in.h>
//include <arpa/inet.h>

#define	MAXLINE	 8192 
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ABS(N) ((N<0)?(-N):(N))
#define ExitCheckMacro(TmpStr) if(strcmp("EXIT",TmpStr)==0){printf("Chat Ended\n");break;}
#define printf2ndGreen(str1,str2)	printf("%s" ANSI_COLOR_GREEN"%s\n" ANSI_COLOR_RESET, str1, str2)
#define RemoveTrailingNewLineChar(TmpStr) TmpStr[strlen(TmpStr)-1]='\0'

int open_clientfd(char *hostname, char *port)
{
	//validate parameters here
	struct addrinfo hints, *listp, *p;
	int clientfd, flags=NI_NUMERICHOST | NI_NUMERICSERV, errorno;
	char host[MAXLINE],service[MAXLINE];
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
	getaddrinfo(hostname, port, &hints, &listp);
	for (p = listp; p; p = p->ai_next)
		if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
		{
			errorno = -1;
			continue;
		}

		else
		{			
			getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
			printf("Host : %s | Service : %s\n",host, service);
			if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) 
			{
				printf("Connected to Server : %s at Port : %s\n", host, service);
				break;
			}
			else
			{
				close(clientfd);
				errorno = -2;				
			}
		}
	freeaddrinfo(listp);
	return (!p?errorno:clientfd);
}

int ReadWriteMessageToFD(int connfd)
{
	if(connfd < 0)
		return connfd;
	int ReadCount;
	char TmpStr[MAXLINE];
	while( printf("Write : ") && fgets(TmpStr, MAXLINE, stdin) != NULL)
	{
		RemoveTrailingNewLineChar(TmpStr);
		write(connfd, TmpStr, strlen(TmpStr));
		ExitCheckMacro(TmpStr); //checks for exit message and does so if it is
		TmpStr[read(connfd, TmpStr, MAXLINE)]='\0';
		printf2ndGreen("Read : ", TmpStr);
		ExitCheckMacro(TmpStr);
	}
	return connfd;
}

int main(int argc, char **argv)
{
	short tmp = close( ReadWriteMessageToFD( open_clientfd( argv[1], argv[2]) ) );
	return ABS(tmp);
}