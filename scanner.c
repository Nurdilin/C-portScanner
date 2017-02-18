#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

int scan(int port, char *hostname) {
    int socketFD;
    int ret;


    struct hostent *host;
    struct sockaddr_in serv_addr;

    memset(&serv_addr, '0', sizeof(serv_addr));
    if (isdigit(hostname[0])) {//if it's an ip address
        serv_addr.sin_addr.s_addr = inet_addr(hostname);
   } 
   else {
        //resolve hostname to ip address
        host=gethostbyname(hostname);
        strncpy((char*)&serv_addr.sin_addr, (char*)host->h_addr, sizeof serv_addr.sin_addr);
        //serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    }
    //create a socket
    if((socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("Error: socket() failed\n");
        exit(-1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    ret = connect(socketFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    close(socketFD);

    if (ret==-1)
        return 0;
    else
        return 1;
}

int main(int argc, char *argv[])
{
	int maxPort=0;
    int i=0;
	struct servent *service;

	if (argc < 2 || argc > 3) {
        printf("usage: %s <host> [highest port]\n", argv[0]);
        exit(0);
	}
    else if (argc == 2)
        maxPort = 1024;
	else if (argc == 3)
        maxPort = atoi(argv[2]);
    
    printf("Scanning %s .. port 1 - %d\n", argv[1],maxPort);
    printf("\tPort\tService\tState\n");
    for(i=1; i<=maxPort; i++) {
	    if(scan(i, argv[1])) {
            service = getservbyport(htons(i), "tcp");
	        printf("\t%d\t%s\tOpen\n", i , (service == NULL) ? "UNKNOWN" : service->s_name);
        }
    }
    exit(0);
}
