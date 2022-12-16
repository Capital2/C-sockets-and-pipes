#include "Server_Client.h"
#define MAXTEST 3
#include <sys/wait.h>
int count = 0;
void handler(){
    printf("Process time out.\n");
    kill(getpid(), SIGKILL);
}

void fault_handler(){
    printf("fault in test\n");
    kill(getpid(), SIGKILL);
}
int main(){
    signal(SIGUSR2, fault_handler);
    int n;
    for (int i = 0; i < MAXTEST; i++)
    {
        if ((n = fork()) == 0)
        {
            signal(SIGALRM, handler);
            alarm(1);
            int status = system("./Client > /dev/null");
            if (status != 0)
            {
                kill(getppid(), SIGUSR2);
                exit(status);
            }
            
            exit(0);
        }
        if (n<0)
        {
            perror("cannot fork");
            exit(1);
        }

    }
    alarm(2);
    for (int i = 0; i < MAXTEST; i++)
    {
        wait(0);
    }

    return 0;
}