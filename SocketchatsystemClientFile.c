
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/socket.h>
#include <winsock2.h>
//#include <netdb.h>
#include <ws2tcpip.h>
void send_file(
	int serv, char *s, int sz, char *serverFileName, char *clientFileName)
{
		
			
			//send filename
			write(serv, serverFileName, strlen(serverFileName));
			
			//clumsy delay
			
			for(int i = 0; i < 100000; i++) ;
			
			printf("start to transfer file...");
			
			// open file
			int file = open(clientFileName);
			int len = 0;
			
			while (( len = read(file, s, sz)) > 0) {
				//after connected, it's client turn to chat
				write(serv, s, len);
				
			}
			close(file);
			
		
		
}

int main(int argc, char* argv[]) {
    int so;
    char s[100];
    struct sockaddr_in ad;

    socklen_t ad_length = sizeof(ad);
    struct hostent *hep;

    // create socket
    int serv = socket(AF_INET, SOCK_STREAM, 0);

    // init address
    hep = gethostbyname(argv[1]);
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(12345);

    // connect to server
    connect(serv, (struct sockaddr *)&ad, ad_length);
	//here is start of modify
	//argv[3] == server filename
	//argv[2] == client filename
    send_file(serv, s, sizeof(s), argv[3], argv[2]);
}
