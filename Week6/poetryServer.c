//
// A simmple poetry server
//
// Modified by 
// Jasvir Boparoy (z5165068)
// Kanadech (King) (z5176970)
//
// Modified on 2017-09-01
// Tutor's name Zain F09A
//
// simpleServer.c
//
// Richard Buckland 28/01/11, 30/3/14.
// Licensed under Creative Commons SA-BY-NC 3.0, share freely.
//
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <netinet/in.h>
#include <unistd.h>
 
#define SIMPLE_SERVER_VERSION 3.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 1511
#define NUMBER_OF_PAGES_TO_SERVE 10
// after serving this many pages the server will halt

// macOS compatibility
// macOs does not define this in its socket.h
#ifndef MSG_MORE
#define MSG_MORE      0x8000
#endif
 
int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
void showRequest (int number, char request[REQUEST_BUFFER_SIZE]);
void serveText (int socket);
void sendTextHeader (int socket);
 
int main (int argc, char* argv[]) {
 
    printf ("[SERVER] Starting simple server %.2f\n", SIMPLE_SERVER_VERSION);
    printf ("[SERVER] Serving poetry since 2011\n");
    printf ("[SERVER] Access this server at http://localhost:%d/\n", DEFAULT_PORT);
    printf ("[SERVER] Waiting for requests...\n");
 
    int serverSocket = makeServerSocket(DEFAULT_PORT);
    char request[REQUEST_BUFFER_SIZE];
    int numberServed = 0;
    printf ("[SERVER] Served %d requests\n", numberServed);
    while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
 
        // STEP 1. wait for a request to be sent from a web browser, 
        // then open a new connection for this conversation
        int connectionSocket = waitForConnection(serverSocket);
 
        // STEP 2. read the first line of the request
        int bytesRead = recv (connectionSocket, request, sizeof(request) - 1, 0);
        if (bytesRead < 0) {
            errx(EXIT_FAILURE, "Unable to read request data");
        }
        // check that we were able to read some data from the connection
 
        // echo entire request to the console for debugging
        showRequest(numberServed, request);

        // STEP 3. send the browser a simple html page using http
        printf ("[REQUEST:%3d] Sending response:\n\n", numberServed);
        sendTextHeader(connectionSocket);
        serveText (connectionSocket);
        printf ("\n[REQUEST:%3d] Response sent\n", numberServed);
        printf ("[REQUEST:%3d] Closing connection\n", numberServed);
 
        // STEP 4. close the connection after sending the page- keep aust beautiful
        close (connectionSocket);
        ++numberServed;
        printf ("[SERVER] Served %d requests\n", numberServed);
    }
 
    // close the server connection after we are done- keep aust beautiful
    printf ("[SERVER] Shutting down the server\n");
    close (serverSocket);

    return EXIT_SUCCESS;
}
 
void serveText(int socket) {
    const char* message =
    "I come with no wrapping or pretty pink bows. I am who I am from my head to my toes.\r\n"
    "I tend to get loud when speaking mymind. Even a little crazy some of the time.\r\n ";

    // echo the http response to the console for debugging purposes
    printf ("%s", message);

    // send the http response to the web browser which requested it
    send (socket, message, strlen(message), 0);
}

void sendTextHeader (int socket) {
    const char* message =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Connection: close\r\n"
    "\r\n";
    send (socket, message, strlen(message), MSG_MORE);
}

// Log a request that was recieved
void showRequest (int number, char request[REQUEST_BUFFER_SIZE]) {
    // Show full request for debugging
    // printf ("[REQUEST:%3d] Recevied request:\n\n", number);
    // printf ("%s\n\n", request);
    // Log only initial line
    char *lineEnd = strchr(request, '\n');
    size_t lineLength = lineEnd - request;
    char basicRequestBuffer[REQUEST_BUFFER_SIZE] = {'\0'};
    strncpy(basicRequestBuffer, request, lineLength);
    printf("[REQUEST:%3d] Recieved request: %s\n", number, basicRequestBuffer);
}
 
// start the server listening on the specified port number
int makeServerSocket (int portNumber) {
 
    // create socket
    int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        errx(EXIT_FAILURE, "Could not create a server socket");
    }
    // check there was no error in opening the socket
 
    // bind the socket to the listening port  (7191 in this case)
    struct sockaddr_in serverAddress;
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons (portNumber);
 
    // tell the server to restart immediately after a previous shutdown
    // even if it looks like the socket is still in use
    // otherwise we might have to wait a little while before rerunning the
    // server once it has stopped
    const int optionValue = 1;
    setsockopt (serverSocket, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof (int));
 
    int bindSuccess = bind (serverSocket, (struct sockaddr*)&serverAddress, sizeof (serverAddress));
 
    if (bindSuccess < 0) {
        errx(EXIT_FAILURE, "Could not bind to the server port");
    }
    // if this assert fails wait a short while to let the operating
    // system clear the port before trying again
 
    return serverSocket;
}
 
// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
int waitForConnection (int serverSocket) {
 
    // listen for a connection
    const int serverMaxBacklog = 10;
    listen (serverSocket, serverMaxBacklog);
 
    // accept the connection
    struct sockaddr_in clientAddress;
    socklen_t clientLen = sizeof (clientAddress);
    int connectionSocket = accept (serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
    if (connectionSocket < 0) {
        errx(EXIT_FAILURE, "Unable to accept a connection");
    }
    // check for connection error
 
    return connectionSocket;
}

/*
this code calls these external networking functions
try to work out what they do from seeing how they are used,
then google them for full details. 

recv
close
send
socket
setsockopt
bind
listen
accept
*/
