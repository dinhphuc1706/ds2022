#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#define PORT 8080

int main() {
    int ss, cli, pid;
    struct sockaddr_in ad;
    char s[80];
    socklen_t ad_length = sizeof(ad);

    // create the socket and verification
    ss = socket(AF_INET, SOCK_STREAM, 0);
    if (ss == -1) {
      printf("socket creation failed...\n");
      exit(0);
    }
    else
        printf("Socket successfully created..\n");

    // bind the socket to port
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;
    ad.sin_addr.s_addr = INADDR_ANY;
    ad.sin_port = htons(PORT);

    if(bind(ss, (struct sockaddr *)&ad, ad_length) != 0) {
      printf("socket bind failed...\n");
        exit(0);
    }
    else
      printf("Socket successfully binded..\n");
    // then listen
    if(listen(ss, 0)) {
      printf("Listen Successfully.");
    }

    while (1) {
        // an incoming connection
        cli = accept(ss, (struct sockaddr *)&ad, &ad_length);

        pid = fork();
        if (pid == 0) {
            printf("client connected\n");
            while (1) {
                // get a request from client
                read(cli, s, sizeof(s));
                printf("client> %s\n",s);

                //server response back
                printf("server: ", s);
                scanf("%s", s);
                write(cli, s, strlen(s) + 1);
            }
            return 0;
        }
        else {
            //continue the loop to accept more clients
            continue;
        }
    }
    // disconnect
    close(cli);

}