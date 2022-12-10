#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include<netinet/in.h>
#include <arpa/inet.h>

#define port 3333

void main(){
	int socketfd,conn;

	struct sockaddr_in adresseServeur;

	int newSocket;
	struct sockaddr_in newAddr;
	char buffer[1024];

	socklen_t  sockaddr_size;
	int childpid;
	socketfd = socket(AF_INET, SOCK_STREAM,0);
	if(socketfd < 0){
		perror("Erreur dans la creation du socket");
		exit(EXIT_FAILURE);
	}
	printf("la socket serveur est creer aves succée \n");	

	memset(&adresseServeur, '\0',sizeof(adresseServeur));
	adresseServeur.sin_family = AF_INET;
	adresseServeur.sin_port = htons(port);
	adresseServeur.sin_addr.s_addr = inet_addr("127.0.0.1");

	conn = bind(socketfd,(struct sockaddr*)&adresseServeur, sizeof(adresseServeur));

	if(conn < 0){
		perror("Erreur dans la fonction bind");
		exit(EXIT_FAILURE);
	}
	printf("bind de port %d\n",port);
	
	if(listen(socketfd,10)== 0){
		printf("En attente du connexion...\n");
	}else{
		printf("erreur du binding");
		exit(EXIT_FAILURE);
	}
	while(1){
		newSocket = accept(socketfd,(struct sockaddr*)&newAddr,&sockaddr_size);
		if(newSocket< 0){
			exit(1);
		}
		printf("connexion accepter depuis %s:%d\n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
		if((childpid = fork()) == 0){
			
			close(socketfd);
			while(1){
				recv(newSocket,buffer,1024,0);
				if(strcmp(buffer,"exit") == 0){
					printf("client %s:%d est deconnecté \n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
					break;
				}else{
					/*
						here we define what should the server do.
					*/
					printf("serveur a recu %s \n",buffer);
					send(newSocket,buffer,strlen(buffer),0);
					bzero(buffer,sizeof(buffer));
				}
			}
		}

	}
	close(newSocket);


}