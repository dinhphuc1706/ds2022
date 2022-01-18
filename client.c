#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <sys/socket.h>
//#include <winsock2.h>
#include <netdb.h>
//#include <ws2tcpip.h>
#include <unistd.h>
#define PORT 8080

void send_file(int sockdesc)
{
  char s[100];
    while (1) {
        // after connected, it's client turn to chat
        // send some request to server
        printf("client: ");
        scanf("%s", s);
        write(serv, s, strlen(s) + 1);

        // then server response
        read(serv, s, sizeof(s));

        printf("server: %s\n", s);
    }
}

int main(int argc, char *argv[])
{
  int sockdesc, cli;
  struct sockaddr_in serveraddress;
  socklen_t len = sizeof(serveraddress);
  struct hostent *hep;
  hep = gethostbyname(argv[1]);

  // create the socket: socket descriptor = socket(domain, type, protocol)
  sockdesc = socket(AF_INET, SOCK_STREAM, 0);
  if (sockdesc == -1)
  {
    printf("Create socket failed...\n");
    exit(0);
  }
  else
    printf("Create socket successfully...\n");

  memset(&serveraddress, 0, sizeof(serveraddress));
  //IP, PORT
  ad.sin_family = AF_INET;
  ad.sin_addr = *(struct in_addr *)hep->h_addr_list[0];
  ad.sin_port = htons(PORT);

  // connect to server: connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  if (connect(sockdesc, (struct sockaddr *)&serveraddress, len) != 0)
  {
    printf("Failed when connect to server...\n");
    exit(0);
  }
  else
    printf("connected to the server..\n");

  //Run Function
  send_file(sockdesc)

  //close socket
  close(sockfd);
}