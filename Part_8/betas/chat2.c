/*******************************************************************************
* Solves the chatting problem with select()
*******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>

#include<sys/select.h>                  /* For select()                       */
#include<unistd.h>                      /* For select()                       */
#include<sys/select.h>                  /* For select()                       */
#include<sys/time.h>                    /* For select()                       */
#include<sys/socket.h>                  /* For socket(), listen(),            */
                                        /* setsockopt()                       */
#include<sys/types.h>                   /* For bind(), setsockopt()           */
#include<netinet/in.h>                  /* For IPPROTO_TCP                    */
#include<netdb.h>                       /* For gethostbyname()                */

#define PORT_NR 1025
#define STR_SIZE 100

/* Function decleration */
void printSetup();
int client_setup(char *server);
int server_setup();

/*******************************************************************************
* Function name:    INT main(INT argc, CHAR, **argv)
* Parameters:       argc - number of arguments
*                   **argv - array of arguments
* Returns:          0 on success
*                   < 0 on failure
* Description:      Assumes client if one argument is incuded on startup, else
*                   server. Initiates the server/client setup respectively.
*******************************************************************************/
int main(int argc, char **argv) {
  char *machine;
  struct hostent *hostp;

  if (argc == 1) {                      /* Start as a server                  */
    printf("Server\n");
    return server_setup();

  } else if (argc == 2){                /* Start as client                    */
    printf("Client\n");
    machine = argv[1];                  /* Get machine                        */
    int retVal = client_setup(machine);
    return retVal;
  }

  printf("Invalid argument count");
  return -1;
}

/*******************************************************************************
* Function name:    INT server_setup(VOID)
* Returns:          0 on success
*                   -1 if unable to find create socket
*                   -2 if bind error
*                   -3 if listen error
* Description:      Assumes client if one argument is incuded on startup, else
*                   server. Initiates the server/client setup respectively.
*******************************************************************************/
int server_setup() {

  /* Declearations */
  struct sockaddr_in serv_addr, client_addr;

  printSetup();                         /* Print server data                  */

  /* Create socket */
  int request_sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(request_sd < 0) {                  /* Unable to create socket            */
    perror("Unable to create socket");
    return -1;
  }

  /* Initiate address structure */
  int yes = 1;
  /* avoid "address already in use" error */
  if(setsockopt(request_sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
    perror("Error setting socket option");
    close(request_sd);
    return -2;
  }

  bzero(&serv_addr, sizeof(struct sockaddr_in));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(PORT_NR);

  /* bind address to socket */
  int status = bind(request_sd, (struct sockaddr *) &serv_addr, 
		    sizeof(struct sockaddr_in));
  if(status < 0) {                      /* Unable to bind socket              */
    perror("Unable to bind socket");
    close(request_sd);
    return -2;
  }

  /* Set passive mode - listen */
  status = listen(request_sd, SOMAXCONN);
  if(status) {                          /* Unable to start listen             */
    perror("Unable to start listen");
    close(request_sd);
    return -3;
  }

  printf("waiting for connection\n");
  int clientaddrlen = sizeof(struct sockaddr_in);
  int client_sd = accept(request_sd, (struct sockaddr *) &client_addr, 
			 &clientaddrlen);
  close(request_sd);                    /* No longer needed                   */
  if(client_sd < 0) {
    perror("Error creating new socket");
    return client_sd;
  }

  chat(client_sd);                      /* Start chat program                 */
  close(client_sd);                     /* Cleanup                            */

  printf("Chat ended\n");

  return 0;
}

/*******************************************************************************
* Function name:    INT client_setup(CHAR *server)
* Parameter:        *server - name of server
* Returns:          0 on success
*                   -1 if unable to get host
*                   -2 if unable to create socket
*                   -3 if error during connect
* Description:      Creates a connection to a server and starts a chat procedure
*******************************************************************************/
int client_setup(char *server) {

  /* Get server details */
  struct hostent *hostp;
  hostp = gethostbyname(server);
  if(hostp == 0) {                      /* Unable to get host                 */
    perror("Hostname error");
    return -1;
  }

  /* create socket */
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sock < 0) {
    perror("Error creating new socket");
    return -2;
  }

  /* Initiate server address structure */
  struct sockaddr_in serv_addr;
  bzero(&serv_addr, sizeof(struct sockaddr_in));
  serv_addr.sin_family = AF_INET;
  memcpy(&serv_addr.sin_addr, hostp->h_addr, hostp->h_length);
  serv_addr.sin_port = htons(PORT_NR);


  /* connect to server */
  int status = connect(sock, (struct sockaddr*)&serv_addr, 
		       sizeof(struct sockaddr_in));
  if(status != 0) {
    perror("Error during connect()");
    return -3;
  }

  printf("Connected to server\n");

  /* Start chat program */
  chat(sock);
  close(sock);
  
  printf("Chat ended\n");

  return 0;
}

/*******************************************************************************
* Function name:    INT char(INT socket)
* Parameter:        socket - socket connection is established on
* Returns:          0 on success
*                   -1 on select error
* Description:      Allows chatting over a socket connection
*******************************************************************************/
int chat(int socket) {
  char rcv_buf[STR_SIZE];
  char inp_buf[STR_SIZE];

  fd_set fds, readfds;
  int numsocks, maxsocks, active_sock_cnt, i;
  struct timeval timeout;

  numsocks = socket + 1;
  maxsocks = numsocks;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  FD_ZERO(&fds);
  FD_SET(socket, &fds);                 /* Add chat input                     */
  FD_SET(0, &fds);                      /* Add keyboard input                 */

  fprintf(stderr, "entering chat on sock %i\n>", socket);

  do {
    readfds = fds;
    active_sock_cnt = select(numsocks, &readfds, NULL, NULL, &timeout);
    if(active_sock_cnt == -1) {         /* Select error */
      perror("Select error");
      return -1;
    }

    if(active_sock_cnt == 0) ;          /* Timeout - will never happen        */

    if(active_sock_cnt > 0) {           /* Socket with data available         */

      for(i = 0; i < maxsocks; i++) {   /* Search for active sockets          */

	if(FD_ISSET(i, &readfds)) {     /* Active socket found                */

	  if(i == socket) {             /* Chat input                         */
	    read(socket, rcv_buf, STR_SIZE);
	    fprintf(stderr, "Received: %s>", rcv_buf);

	  } else if(i == 0){            /* keyboard input                     */
	    fgets(inp_buf, STR_SIZE, stdin);
	    write(socket, inp_buf, sizeof(inp_buf));
	    fprintf(stderr, ">");
	  }
	}
      }
      FD_ZERO(&readfds);
    }
  } while(strcmp("exit\n", rcv_buf) && strcmp("exit\n", inp_buf));
  
  return 0;
}

/*******************************************************************************
* Function name:    VOID printSetup(VOID)
* Returns:          VOID
* Description:      Prints server data
*******************************************************************************/
void printSetup() {
  fprintf(stderr, "Selected port number: %d\n", PORT_NR       );
  fprintf(stderr, "Name:                 %s\n", getenv("HOST"));
}
