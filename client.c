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
	int socketClient,conn;
	struct sockaddr_in adresseServeur;
	char buffer[1024];
	socketClient = socket(AF_INET, SOCK_STREAM, 0); //create socket
	if(socketClient < 0){
		perror("Erreur dans la creattion du socket");
		exit(EXIT_FAILURE);
	}
	printf("la socket client est creer avec succée \n");

	memset(&adresseServeur, '\0',sizeof(adresseServeur));
	adresseServeur.sin_family = AF_INET;
	adresseServeur.sin_port = htons(port);
	adresseServeur.sin_addr.s_addr = inet_addr("127.0.0.1");

	conn = connect(socketClient, (struct sockaddr*) &adresseServeur, sizeof(adresseServeur));

	if(conn < 0){
		perror("Erreur de connexion");
		exit(EXIT_FAILURE);
	}
	printf("connexion etablit avec le serveur\n");

	while(1){
		printf("Clinet:");
		scanf("%s",&buffer[0]);
		send(socketClient,buffer,strlen(buffer),0);

		if(strcmp(buffer, "exit") == 0){
			close(socketClient);
			printf("deconnecté");
			exit(0);
		}
		if(recv(socketClient,buffer,1024,0)<0){
			perror("Erreur dans la reception");
		}else{
			printf("Serveur: %s\n",buffer);
		}
	}
}

