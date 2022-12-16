#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include<netinet/in.h>
#include <time.h>
#include <arpa/inet.h>
#include<signal.h>

#define port 3333
int socketfd;
int randomNum;
int randomNums[100];
