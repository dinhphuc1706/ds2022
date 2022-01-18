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

int Send_Recv(int cli)
{
  char s[80];
  //Create a infinite loop function
  while (true)
  {
    pid = fork();
    if (pid == 0)
    {
      printf("client connected\n");
      while (true)
      {
        // get a request from client
        read(cli, s, sizeof(s));
        printf("From client: %s\n", s);

        //server response back
        printf("server: ", s);
        scanf("%s", s);
        write(cli, s, strlen(s) + 1);
      }
      return 0;
    }
    else
    {
      //continue the loop to accept more clients
      continue;
    }
  }
}

int main()
{
  int sockdesc, pid, cli;
  struct sockaddr_in serveraddress;

  socklen_t len = sizeof(serveraddress);

  // create the socket: socket descriptor = socket(domain, type, protocol)
  sockdesc = socket(AF_INET, SOCK_STREAM, 0);
  if (sockdesc == -1)
  {
    printf("Create socket failed...\n");
    exit(0);
  }
  else
    printf("Create socket successfully...\n");

  // bind the socket to port int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  memset(&serveraddress, 0, sizeof(serveraddress));
  serveraddress.sin_family = AF_INET;
  serveraddress.sin_addr.s_addr = INADDR_ANY;
  serveraddress.sin_port = htons(PORT);

  if (bind(sockdesc, (struct sockaddr *)&serveraddress, len) != 0)
  {
    printf("bind socket failed...\n");
    exit(0);
  }
  else
    printf("Bind socket successfully...\n");

  // then listen listen(int sockfd, int backlog);
  if (listen(sockdesc, 0))
  {
    printf("Listen Successfully.");
  }

  // accept connection new_socket = accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  cli = accept(sockdesc, (struct sockaddr *)&serveraddress, &len);

  //Run Function
  Send_Recv(cli);

  // disconnect
  close(cli);
}