#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#define ABS(N) ((N<0)?(-N):(N))
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//include <netinet/in.h>
//include <arpa/inet.h>

#define	MAXLINE	 8192 
int open_clientfd(char *hostname, char *port)
{
	//validate parameters here
	int clientfd, flags=NI_NUMERICHOST | NI_NUMERICSERV;
	struct addrinfo hints, *listp, *p;
	char host[MAXLINE],service[MAXLINE];
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
	getaddrinfo(hostname, port, &hints, &listp);
	for (p = listp; p; p = p->ai_next)
		if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) 
				continue;
		else
		{			
			getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
			printf("Host : %s | Service : %s\n",host, service);
			if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) 
			{
				printf("Connected to Server : %s at Port : %s\n", host, service);
				break;
			}
			close(clientfd);
		}
	freeaddrinfo(listp);
	return (!p?-1:clientfd);
}

int ReadWriteMessageToFD(int connfd)
{
	if(connfd < 0)
		return connfd;
	int ReadCount;
	char TmpStr[MAXLINE];
	printf("\nWrite : ");
	fflush(stdin);
	while (fgets(TmpStr, MAXLINE, stdin) != NULL)
	{
		TmpStr[strlen(TmpStr)-1]='\0';
		write(connfd, TmpStr, strlen(TmpStr));
		if(strcmp("EXIT", TmpStr)==0)
		{
			printf("Chat Ended\n");			
			break;
		}
		ReadCount=read(connfd, TmpStr, MAXLINE);
		TmpStr[ReadCount]='\0';
		printf("Read : " ANSI_COLOR_GREEN"%s\n" ANSI_COLOR_RESET, TmpStr);
		if (TmpStr[0] == '\0' || strcmp("EXIT", TmpStr)==0)
		{
			printf("Chat Ended\n");
			break;
		}
		printf("Write : ");
	}
	return connfd;
}

int main(int argc, char **argv)
{
	return ABS( close( ReadWriteMessageToFD( open_clientfd( argv[1], argv[2]) ) ) );
}