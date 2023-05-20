#ifndef CURL_LIB_H
#define CURL_LIB_H

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 3000
char BUFFER[3000];

struct total{
    struct hostent *host;
    struct sockaddr_in address;
};

#endif //CURL_LIB_H