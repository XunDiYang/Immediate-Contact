
#include "include/server.h"

int main()
{
    init_server();
    printf("zzzzz");
    pthread_t tid;
    pthread_create(&tid, NULL, listen_func, NULL);
    printf("rrrrr");
    pthread_create(&tid, NULL, send_thread_function, NULL);
    printf("tttt");
   // pthread_exit(0);
    char command[1024];
    while(1) {
        scanf("%s", command);
        exec_cmd(command);
    }
}