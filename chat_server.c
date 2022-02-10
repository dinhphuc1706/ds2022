#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main() {
    int ss, cli, pid;
    struct sockaddr_in ad;
    char s[100];
    socklen_t ad_length = sizeof(ad);
    
    // create the socket
    ss = socket(AF_INET, SOCK_STREAM, 0);
    
    // bind the socket to port 12345
    memset(&ad,0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = INADDR_ANY;
    ad.sin_port = htons(12345);
    
    //check bind
    if((bind(ss, (struct sockaddr *)&ad, ad_length)) !=0){
    	printf("socket bind failed...\n");
    	exit(0);
    }else
	printf("Socket successfully bind.\n");
	
    // then listen
    if((listen(ss, 0)) !=0){
    	printf("listen failed...\n");
    	exit(0);
    }else
    	printf("Listening...\n");
    
    while (1) {
        // an incoming connection
        cli = accept(ss, (struct sockaddr *)&ad, &ad_length);
        if (cli < 0) {
		printf("server accept failed...\n");
		exit(0);	
	}else
		printf("server accept the client...\n");
		
	// read the message from client and copy it in buffer 
	read(cli, s, sizeof(s));
	
	// print buffer which contains the client contents
	printf("From client: %s\t To client : ", s);

	// copy server message in the buffer
	int n = 0;
	while ((s[n++] = getchar()) != '\n');
	
	// and send that buffer to client
	write(cli, s, sizeof(s));	   
	
    // disconnect
    close(cli);

}
}


