#include "header/serv_cli_socket.h"
void main(){
	int socketfd,conn;
	struct sockaddr_in adresseServeur;
	int newSocket;
	struct sockaddr_in newAddr;
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
			recv(newSocket,&randomNum,sizeof(int),0);
			srand(time(NULL));
			printf("serveur a recu %d \n",randomNum);
			for (int i = 0; i < randomNum; ++i)
			{
				randomNums[i] =rand()	;
			}
			send(newSocket,randomNums,sizeof(randomNums),0);
			bzero(randomNums,sizeof(randomNums));
		}
	close(newSocket);
	}
}