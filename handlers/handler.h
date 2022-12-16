void interrupt(int sig){
    close(socketfd);
    shutdown(socketfd, SHUT_RDWR);
	printf("Serveur a terminé son travail\n");
	exit(0);
}