#include <netinet/in.h>

#include <sys/socket.h>

#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/select.h>


#define STRING_SIZE 100
#define PORT 1025

int chat(int sock);


int main(int argc, char **argv) 
{  
  char *machine;
  int sock = 0;
  int request_sock = 0;
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;
  struct hostent *hostp;
  
  int clientaddrlen=0;
  int test=0;
  
  // Client
  if (argc > 1)
    {
      machine = argv[1];
      
      // Retrieves info from DNS server.
      if ((hostp = gethostbyname(machine)) != 0)
        { 
          sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);    
	
          /*
            domain:
            AF_INET  (IPv4).
            AF_INET6 (IPv6 or IPv4)
            
            type:
            SOCK_STREAM
            SOCK_DGRAM
            
            protocol:
            IPPROTO_IP	 Equivalent to specifying the value zero (0).
            IPPROTO_TCP	 Indicates that the TCP protocol is to be used.
            IPPROTO_UDP	 Indicates that the UDP protocol is to be used.
            IPPROTO_RAW	 Indicates that communications is to the IP layer.
            IPPROTO_ICMP Indicates that the Internet Control Message Protocol (ICMP) is to be used.
          */
          
          if (sock < 0)                                       
            {
              perror("Could not create socket\n");
              printf("Please try again later\n");
              exit(1);
            }
          else
            printf("Successfully created new socket:%d\n", sock);
	
          bzero(&serveraddr, sizeof(serveraddr));
          serveraddr.sin_family = AF_INET;
          memcpy(&serveraddr.sin_addr, hostp->h_addr, hostp->h_length);
          serveraddr.sin_port = htons(PORT);
          test = connect(sock, (struct sockaddr*)&serveraddr, sizeof serveraddr);
          
          if (test != 0)                                
            {
              printf("Unable to connect to server: %s\n",machine);
              printf("Please try again later\n");
              exit(0);
            }
        
          printf("Connected for chat - server: %s\n", machine); 
	
          chat(sock);
        }
      else
        {
          printf("Unknown machine\n");
        }
    }
  // Server
  else
    {
      printf("Entering server mode\n");
      
      request_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
      
      if (request_sock < 0)
	{
	  perror("Could not create socket\n");
	  printf("Please try again later\n");
	  exit(1);
	}

      int yes = 1;
       /* avoid "address already in use" error */
      if (setsockopt(request_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
          perror("setsockopt:");
          return -1;
        }
    
      bzero(&serveraddr, sizeof(serveraddr));
      serveraddr.sin_family = AF_INET;
      serveraddr.sin_addr.s_addr = INADDR_ANY;
      serveraddr.sin_port = htons(PORT);
    
      test = bind(request_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    
      if (test < 0)
	{
          perror("Could not bind socket to port\n");
          printf("Please try again later\n");
          exit(1);
	}
    
      test = listen(request_sock, SOMAXCONN);
    
      if (test < 0)
	{
	  perror("Could not initialize listen queue\n");
	  printf("Please try again later\n");
	  exit(1);
	}
      
      clientaddrlen = sizeof(struct sockaddr_in);
      
      printf("Waiting for connection...\n");
      
      // Waits for a connection
      sock = accept(request_sock, (struct sockaddr*)&clientaddr, &clientaddrlen);
      close(request_sock);
      
      chat(sock);
    }
}



int chat(int sock)
{
  int strlength;
  char buf[STRING_SIZE];
  int retval;
  struct timeval tv;
  
  fd_set rd, rd_tmp;
   
  /*
    The fd_set data type represents file descriptor sets 
    for the select function. It is actually a bit array.
  */
  
  FD_ZERO(&rd);
  FD_SET(0, &rd);
  FD_SET(sock, &rd);
  
  printf("Time to chat\n");

  while (1)
    {
      rd_tmp = rd;
      tv.tv_sec = 0;
      tv.tv_usec = 50;
      
      retval = select(sock+1, &rd_tmp, NULL, NULL, &tv);
      
      if (retval == -1)
	perror("select(1)\n");
      
      else if (retval > 0) {
        
        // Checks for input on standard input
        if (FD_ISSET(0, &rd_tmp))
          {
            bzero(&buf, STRING_SIZE);
            fgets(buf, STRING_SIZE, stdin);
            strlength = strlen(buf);
	 	  
            if (strcmp(buf, "exit\n") == 0)
              {
                close(sock);
                exit(1);
              }
            else
              {
                write(sock, &buf, strlength);
              }
	
            // Checks for input on network socket
          } else if (FD_ISSET(sock, &rd_tmp)) {
            
            bzero(&buf, STRING_SIZE);
            
            read(sock, &buf, STRING_SIZE);
            printf(buf);
          }
      }
      
      FD_ZERO(&rd_tmp);
    }
  	return 0;
}

