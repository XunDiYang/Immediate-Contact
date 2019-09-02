#include "include/server.h"
int main()
{
    init_server();

    pthread_t tid;
    pthread_create(&tid, NULL, listen_func, NULL);
	pthread_create(&tid, NULL, send_thread_function, NULL);
}