#include<netdb.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAXLINE 8000
#define LISTENQ 1000
typedef struct addrinfo addrinfo2;
typedef struct sockaddr sockaddr2;
typedef struct sockaddr_storage sockaddr_storage2;
//typedef char[MAXLINE] maxchar;
int open_client_fd(char *port)
{
	addrinfo2 hints, *listp, *p;
	int listenfd, optval=1, flags = NI_NUMERICHOST | NI_NUMERICSERV; 
	char host[MAXLINE],service[MAXLINE];
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
	hints.ai_flags |= AI_NUMERICSERV;
	getaddrinfo(NULL, port, &hints, &listp);
	for(p = listp; p; p = p->ai_next)
		if((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))<0)
		{	
			printf("Listen Failed\n");
			continue;			
		}
		else
		{
			setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
			getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
			printf("host : %s, service : %s\n",host, service);

			if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
			{
				printf("Hello, stuck here");
				break;
			}
			else
			{
				printf("binding failed");
				close(listenfd);
			}
		}
	freeaddrinfo(listp);
	return ((((listen(listenfd, LISTENQ) < 0) && (close(listenfd) == 0)) || !p) ? -1 : listenfd );
	// return (!p?-1:listenfd);
}
void echo(int connfd)
{
	size_t n;
	char buf[MAXLINE];
	while((n=read(connfd, buf, MAXLINE)) != 0)
	{
		buf[n]='\0';
		printf("Server received %d bytes\nServer received message : %s\n", (int)n, buf);
		write(connfd, buf, n);
	}
}
int main(int argc, char* argv[])
{
	int listenfd, connfd;
	socklen_t clientlen;
	sockaddr_storage2 clientaddr;
	char client_hostname[MAXLINE], client_port[MAXLINE];
	listenfd = open_client_fd(argv[1]);
	printf("out");
	if(listenfd!=-1)
		while(1)
		{
			printf("wfc2c");
			//printf("Waiting for a new client to connect\n");
			clientlen = sizeof(sockaddr_storage2);
			connfd = accept(listenfd, (sockaddr2 *)&clientaddr, &clientlen);
			getnameinfo((sockaddr2 *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
			printf(".");
			printf("Starting Communication\n");
			echo(connfd);
			printf("Ending Communication\n");
			close(connfd);
		}
	else
	{
		printf("Listenfd error");
	}
	
	return 0;
}