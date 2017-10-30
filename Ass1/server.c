// Assignment 1 Mandelbrot
//
// Completed by
//  ... (z0000000)
//  ... (z0000000)
//
// Modified on 2017-??-??
// Tutor's name (dayHH-lab)

// Originally by Richard Buckland 28/01/11, 30/3/14.
// Licensed under Creative Commons SA-BY-NC 3.0, share freely.
//
// Extended by Curtis Millar 2017-08-29.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <netinet/in.h>
#include <unistd.h>
#include <math.h>
#include "mandelbrot.h"
#include <signal.h>

#define SIMPLE_SERVER_VERSION 3.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 15112
// after serving this many pages+images the server will halt
#define NUMBER_OF_PAGES_TO_SERVE 1024

// macOS compatibility
// macOS does not define this in its socket.h
#ifndef MSG_MORE
#define MSG_MORE      0x8000
#endif

// For writing BMP
#define PIXEL_START 26
#define PIXEL_BYTES 3
#define PIXEL_ALIGN 4
#define PIXEL_BITS  24
#define HEADER_SIZE 12

// Functions for setting up the server
int waitForConnection(int serverSocket);
int makeServerSocket(int portno);
void showRequest(int number, char request[REQUEST_BUFFER_SIZE]);
void routeRequest(int socket, char requestBuffer[REQUEST_BUFFER_SIZE]);
void serveIndex(int socket);
void sendHtmlHeader(int socket);
void serveImage(int socket, double x, double y, int z);
static void serveHTML (int socket);

// Write an image to output
void sendBitmapHeader (int socket);
void sendImage(int socket, pixel pixels[TILE_SIZE][TILE_SIZE]);

int main (int argc, char* argv[]) {
    signal(SIGPIPE, SIG_IGN);    
    
    printf("[SERVER] Starting simple server %.2f\n", SIMPLE_SERVER_VERSION);
    printf("[SERVER] Serving poetry since 2011\n");
    printf("[SERVER] Access this server at http://localhost:%d/\n", DEFAULT_PORT);
    printf("[SERVER] Waiting for requests...\n");

    int serverSocket = makeServerSocket(DEFAULT_PORT);
    char request[REQUEST_BUFFER_SIZE];
    int numberServed = 0;
    printf("[SERVER] Served %d requests\n", numberServed);
    while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {

        // STEP 1. wait for a request to be sent from a web browser,
        // then open a new connection for this conversation
        int connectionSocket = waitForConnection(serverSocket);

        // STEP 2. read the first line of the request
        long int bytesRead = recv(connectionSocket, request, sizeof(request) - 1, 0);
        // check that we were able to read some data from the connection
        if (bytesRead < 0) {
            errx(EXIT_FAILURE, "Unable to read request data");
        }

        // echo entire request to the console for debugging
        showRequest(numberServed, request);

        // STEP 3. send the browser a simple html page using http
        printf("[REQUEST:%3d] Sending response:\n\n", numberServed);
        routeRequest(connectionSocket, request);
        printf("\n[REQUEST:%3d] Response sent\n", numberServed);
        printf("[REQUEST:%3d] Closing connection\n", numberServed);

        // STEP 4. close the connection after sending the page- keep aust beautiful
        close(connectionSocket);
        ++numberServed;
        printf("[SERVER] Served %d requests\n", numberServed);
    }

    // close the server connection after we are done- keep aust beautiful
    printf("[SERVER] Shutting down the server\n");
    close(serverSocket);

    return EXIT_SUCCESS;
}

// Log a request that was received
void showRequest (int number, char request[REQUEST_BUFFER_SIZE]) {
    // Show full request for debugging
    // printf ("[REQUEST:%3d] Received request:\n\n", number);
    // printf ("%s\n\n", request);
    // Log only initial line
    char *lineEnd = strchr(request, '\n');
    size_t lineLength = lineEnd - request;
    char basicRequestBuffer[REQUEST_BUFFER_SIZE] = {'\0'};
    strncpy(basicRequestBuffer, request, lineLength);
    printf("[REQUEST:%3d] Received request: %s\n", number, basicRequestBuffer);
}

// start the server listening on the specified port number
int makeServerSocket (int portNumber) {

    // create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
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
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof (int));

    int bindSuccess = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof (serverAddress));

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
    socklen_t clientLen = sizeof(clientAddress);
    int connectionSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
    // check for connection error
    if (connectionSocket < 0) {
        errx(EXIT_FAILURE, "Unable to accept a connection");
    }

    return connectionSocket;
}

// Route requests from the browser to the relevant parts of the
// mandelbrot server.
// Takes in a string that contains the requested URL, and parses it to
// determine what response to send back to the browser.
// In format: http://localhost:1511/mandelbrot/2/zoom/x-coord/y-coord/tile.bmp
// Will be given something like this:
// http://localhost:1511/mandelbrot/2/8/-1.0/0.5/tile.bmp
void routeRequest(int socket, char requestBuffer[REQUEST_BUFFER_SIZE]) {
    // TODO: COMPLETE THIS FUNCTION
    int z = 0;
    double x = 0;
    double y = 0;
    int i = 0;
    int flag = 0;
    char* message;
    char website[100] = "http://localhost:1511/mandelbrot/2/";

    if (sscanf(requestBuffer, "GET /mandelbrot/2/%d/%lf/%lf/tile.bmp HTTP/1.1", &z, &x, &y) == 0) {
        serveHTML(socket);
    } else {
        serveImage(socket,x,y,z);
    }

    // CHANGE VALUES IN THIS TO CHANGE BITMAP IMAGE SENT TO SERVER    


/*    while (i < 36 && flag != 1) {
        if (requestBuffer[i] != website[i]){
            flag = 1;
        } else {
            i++;
        }
    }

    if (flag == 1) {
        message =
           "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>"
           "\n";
          write (socket, message, strlen (message));
    } else {
        sscanf(requestBuffer, "GET /mandelbrot/2/%d/%lf/%lf/tile.bmp HTTP/1.1", &z, &x, &y);
        serveImage(socket, x, y, z);
    }*/

}

// Serve the tile image
void serveImage(int socket, double x, double y, int z) {
    // Create tiles
    pixel pixels[TILE_SIZE][TILE_SIZE];

    complex center;
    center.re = x;
    center.im = y;
    drawMandelbrot(pixels, center, z);

    // Send the image to the client
    sendImage(socket, pixels);
}

// Send a HTTP headers for BMP
void sendBitmapHeader (int socket) {
    const char* message =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: image/bmp\r\n"
        "Connection: close\r\n"
        "Cache-Control: no-cache\r\n"
        "\r\n";
    send (socket, message, strlen(message), MSG_MORE);
}

// Writes the pixels as a BMP file using the specification from
// https://en.wikipedia.org/wiki/BMP_file_format
void sendImage(int socket, pixel pixels[TILE_SIZE][TILE_SIZE]) {
    sendBitmapHeader(socket);

    // Create a buffer to put the bitmap header data in
    char headerBuffer[PIXEL_START] = {'\0'};

    // Write headers
    // Initial BM bytes
    headerBuffer[0] = 'B';
    headerBuffer[1] = 'M';

    // File size
    unsigned int rowSize = TILE_SIZE * PIXEL_BYTES;
    unsigned int rowPadding = 0;
    if (rowSize % PIXEL_ALIGN != 0) {
        // Pad pixel to align properly
        rowPadding = PIXEL_ALIGN - (rowSize % PIXEL_ALIGN);
        rowSize += rowPadding;
    }
    unsigned int pixelData = (rowSize * TILE_SIZE);

    // We use memcpy so you don't have to
    unsigned int fileSize = PIXEL_START + pixelData;
    memcpy(&(headerBuffer[2]), &fileSize, sizeof(fileSize));

    // start of pixel data
    // pixels start immediately after header
    unsigned int pixelStart = PIXEL_START;
    memcpy(&(headerBuffer[10]), &pixelStart, sizeof(pixelStart));

    // Size of header
    unsigned int headerSize = HEADER_SIZE;
    memcpy(&(headerBuffer[14]), &headerSize, sizeof(headerSize));

    // Image width and height
    unsigned short size = TILE_SIZE;
    memcpy(&(headerBuffer[18]), &size, sizeof(size));
    memcpy(&(headerBuffer[20]), &size, sizeof(size));

    // Number of image planes (1)
    unsigned short planes = 1;
    memcpy(&(headerBuffer[22]), &planes, sizeof(planes));

    // Number of bits per pixel (24)
    unsigned short bitsPerPixel = PIXEL_BITS;
    memcpy(&(headerBuffer[24]), &bitsPerPixel, sizeof(bitsPerPixel));

    // Send the header
    send (socket, headerBuffer, PIXEL_START, MSG_MORE);

    // Write each of the pixels
    unsigned char *pixelBuffer = malloc(pixelData);
    if (pixelBuffer == NULL) {
        exit(EXIT_FAILURE);
    }

    int y = 0;
    while (y < TILE_SIZE) {
        int x = 0;
        while (x < TILE_SIZE) {
            // Write the blue, green, then red pixels
            pixel pixel = pixels[y][x];
            int byteIndex = (y * rowSize) + (x * PIXEL_BYTES);
            pixelBuffer[byteIndex + 0] = pixel.blue;
            pixelBuffer[byteIndex + 1] = pixel.green;
            pixelBuffer[byteIndex + 2] = pixel.red;
            x++;
        }
        y++;
    }

    // Send the header
    send (socket, pixelBuffer, pixelData, 0);
}



static void serveHTML (int socket) {
   char* message;
 
   // first send the http response header
   message =
      "HTTP/1.0 200 Found\n"
      "Content-Type: text/html\n"
      "\n";
   printf ("about to send=> %s\n", message);
   write (socket, message, strlen (message));
 
   message =
      "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>"
      "\n";
   write (socket, message, strlen (message));
}


