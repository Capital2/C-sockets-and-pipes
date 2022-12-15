#include "header/serv_cli_socket.h"
void main(){
	int socketClient,conn;
	struct sockaddr_in adresseServeur;
	int n[100];
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

	srand(time(NULL));
	randomNum = rand()%10;
	
	printf("numéro envoyer au serveur = %d \n",randomNum);

	send(socketClient,&randomNum,sizeof(int),0);

	if(recv(socketClient,randomNums,sizeof(randomNums),0)<0){
		perror("Erreur dans la reception");
	}else{
		printf("voici les %d numeros reçu du serveur\n",randomNum);
		for (int i = 0; i < randomNum; ++i)
		{
			printf("num %d = %d \n",i,randomNums[i]);
		}
	}
	
}

