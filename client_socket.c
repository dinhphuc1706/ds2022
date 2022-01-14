
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char* argv[]) {
    int so;
    char s[100];
    struct sockaddr_in ad;

    socklen_t ad_length = sizeof(ad);
    struct hostent *hep;

    //  create the socket and verification
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    if (serv == -1) {
      printf("socket creation failed...\n");
      exit(0);
    }
    else
      printf("Socket successfully created..\n");

    // init address
    hep = gethostbyname(argv[1]);
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
    ad.sin_port = htons(PORT);

    // connect to server
    if(connect(serv, (struct sockaddr *)&ad, ad_length) != 0) {
      printf("connection with the server failed...\n");
      exit(0);
    }
    else
      printf("connected to the server..\n");

    while (1) {
        // after connected, it's client turn to chat

        // send some request to server
        printf("client> ");
        scanf("%s", s);
        write(serv, s, strlen(s) + 1);

        // then server response
        read(serv, s, sizeof(s));

        printf("server> %s\n", s);
    }
}