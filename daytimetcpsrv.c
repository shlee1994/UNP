#include "unp.h"
#include <time.h>

int main(void)
{
	struct sockaddr_in servaddr, cliaddr;
	int listenfd, connfd, len;

	char buff[MAXLINE];
	time_t ticks;
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));
	
	Listen(listenfd, LISTENQ);

	for(;;){
		len = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA*)&cliaddr, &len);
		printf("connection from %s\r\n", 
				inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff))
				);

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n",ctime(&ticks));
		Write(connfd, buff, strlen(buff));

		Close(connfd);

	}
}

