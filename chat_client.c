#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[]) {  
    char s[100];
    int port = 12345;
    struct sockaddr_in ad;
    socklen_t ad_length = sizeof(ad);
    struct hostent *hep;
   
    // create socket
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    if (serv == -1) {
	printf("socket creation failed...\n");
	exit(0);
    }else
	printf("Socket successfully created..\n");
		
    // init address
    hep = gethostbyname(argv[1]);
    memset(&ad,0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(port);
    
    // connect to server
    if(connect(serv, (struct sockaddr *)&ad, ad_length)!=0){
	printf("connection with the server failed...\n");
	exit(0);
    }else
	printf("connected to the server..\n");
	
    // write the message from server   
    printf("Enter the string : ");
    int n = 0;
    while ((s[n++] = getchar()) != '\n');
    write(serv, s, sizeof(s));
  
    // read the message from server        
    read(serv, s, sizeof(s));
    printf("From Server : %s", s);		

}

   	

