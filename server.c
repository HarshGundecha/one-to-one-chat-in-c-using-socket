#include<netdb.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAXLINE 8000
#define LISTENQ 1000
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ABS(N) ((N<0)?(-N):(N))
#define ExitCheckMacro(TmpStr) if(strcmp("EXIT",TmpStr)==0){printf("Chat Ended\n");break;}
#define printf2ndGreen(str1,str2)	printf("%s" ANSI_COLOR_GREEN"%s\n" ANSI_COLOR_RESET, str1, str2)
#define RemoveTrailingNewLineChar(TmpStr) TmpStr[strlen(TmpStr)-1]='\0'

typedef struct addrinfo addrinfo;
typedef struct sockaddr sockaddr;
typedef struct sockaddr_storage sockaddr_storage;
//typedef char[MAXLINE] maxchar;

int open_client_fd(char *port)
{
	// validate parameters here
	addrinfo hints, *listp, *p;
	int listenfd, optval=1, flags = NI_NUMERICHOST | NI_NUMERICSERV, errorno=0; 
	char host[MAXLINE],service[MAXLINE];
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
	getaddrinfo(NULL, port, &hints, &listp);
	for(p = listp; p; p = p->ai_next)
		if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))<0)
		{
			continue;
			errorno = -1;
		}
		else
		{
			setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
			getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
			printf("Host : %s | Service : %s\n",host, service);
			if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
			{
				printf("Connected to Client : %s at Port : %s\n", host, service);
				break;
			}
			else
			{
				close(listenfd);
				errorno = -2;
			}
		}
	freeaddrinfo(listp);
	return ((((listen(listenfd, LISTENQ) < 0) && (close(listenfd) == 0 && (errorno=-3))) || !p) ? errorno : listenfd );
}

int GetClientFD(int listenfd)
{
	if(listenfd < 0)
		return listenfd;
	socklen_t clientlen;
	sockaddr_storage clientaddr;
	char client_hostname[MAXLINE], client_port[MAXLINE];
	printf("Waiting for a client to connect\n");
	clientlen = sizeof(clientaddr);
	int connfd = accept(listenfd, (sockaddr *)&clientaddr, &clientlen);
	getnameinfo((sockaddr *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
	return connfd;
}

//will be splited to 2 seperate () for readinf and writing on parallel execution by threads
int ReadWriteToFD(int connfd)
{
	if(connfd < 0 )
		return connfd;
	size_t ReadCount;
	char TmpStr[MAXLINE];
	while((ReadCount=read(connfd, TmpStr, MAXLINE)) != 0)
	{
		TmpStr[ReadCount]='\0';
		printf2ndGreen("Read : ", TmpStr);
		ExitCheckMacro(TmpStr);
		fflush(stdin);
		printf("Write : ");
		fgets(TmpStr, MAXLINE, stdin);
		RemoveTrailingNewLineChar(TmpStr);
		write(connfd, TmpStr, strlen(TmpStr));
		ExitCheckMacro(TmpStr);
	}
	return connfd;
}


int main(int argc, char* argv[])
{
	short tmp = close( ReadWriteToFD( GetClientFD( open_client_fd( argv[1] ) ) ) );
	return ABS( tmp );
}