#include "pipe_networking.h"

void error_handler(int status){
  if(status == -1){
    printf("error %d: %s\n", errno, strerror(errno));
    exit(1);
  }
}


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  // Create known pipe
  printf("[Server] Create known pipe\n");
  error_handler(mkfifo(KNOWN_PIPE, 0644));
  // Connect to known pipe
  printf("[Server] Connect to known pipe\n");
  int from_client;
  error_handler(from_client = open(KNOWN_PIPE, O_RDONLY));
  // Read private fifo from known pipe
  printf("[Server] Read private fifo from known pipe\n");
  char private_fifo[HANDSHAKE_BUFFER_SIZE];
  error_handler(read(from_client, private_fifo, sizeof(private_fifo)));
  printf("[Server] Private fifo: %s\n", private_fifo);
  // Remove well known pipe
  remove(KNOWN_PIPE);
  // Open connection to private fifo
  printf("[Server] Connect to private fifo\n");
  error_handler(*to_client = open(private_fifo, O_WRONLY));
  // Send back the private fifo name to client
  printf("[Server] Send private fifo name to client: %s\n", private_fifo);
  error_handler(write(*to_client, private_fifo, sizeof(private_fifo)));
  // Verify that data was sent correctly
  printf("[Server] Verify private fifo name from client\n");
  char buf[HANDSHAKE_BUFFER_SIZE];
  error_handler(read(from_client, buf, sizeof(buf)));
  printf("Private fifo: %s\tData from client: %s\n", private_fifo, buf);
  if(strcmp(private_fifo, buf)){
    printf("[Server error] Data from client invalid\n");
    exit(1);
  } else {
    printf("[Server] Handshake successful!\n");
  }
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  // Connect to server
  printf("[Client] Connect to known pipe\n");
  error_handler(*to_server = open(KNOWN_PIPE, O_WRONLY));
  // Create "private" fifo
  printf("[Client] Create private fifo: ");
  char private_fifo[HANDSHAKE_BUFFER_SIZE];
  sprintf(private_fifo, "%d", getpid());
  printf("%s\n", private_fifo);
  error_handler(mkfifo(private_fifo, 0600));
  // Send private fifo to server via known pipe
  printf("[Client] Send private fifo to server: %s\n", private_fifo);
  error_handler(write(*to_server, private_fifo, sizeof(private_fifo)));
  // Open connection to private fifo
  printf("[Client] Open connection to private fifo\n");
  int from_server;
  error_handler(from_server = open(private_fifo, O_RDONLY));
  // Read from server and make sure data is valid
  printf("[Client] Read from server and make sure data is valid: ");
  char buf[HANDSHAKE_BUFFER_SIZE];
  error_handler(read(from_server, buf, sizeof(buf)));
  printf("%s\n", buf);
  if(strcmp(buf, private_fifo)){
    printf("[Client error] Server sent wrong data!\n");
    exit(1);
  } else {
    remove(private_fifo);
  }
  // Send fifo name to server
  printf("[Client] Send fifo name to server again: %s\n", private_fifo);
  error_handler(write(*to_server, private_fifo, sizeof(private_fifo)));
  return from_server;
}
