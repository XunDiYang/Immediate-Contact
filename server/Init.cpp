//
// Created by changxinyu on 2019/8/31.
//

#include "include/server.h"

int listen_fd,connect_fd;
struct sockaddr_in client,server;
struct User client_prop[MAX_CONN];
int send_q_head , send_q_tail;
Message send_queue[MAX_MESSAGE_COUNT];
static pthread_mutex_t queue_lock;
void handle_client_message(struct client_property * prop, char * message) {
    cJSON *root = cJSON_Parse(message);
    if (root == NULL)
        return;
    char *type = cJSON_GetObjectItem(root, "type")->valuestring;
    char message_json[BUFFER_SIZE];
    if (strcmp(type, "register-message") == 0) {
        //TODO: the strings'space might be freed
        /*char *userid = cJSON_GetObjectItem(root, "userid")->valuestring;
        char *password = cJSON_GetObjectItem(root, "password")->valuestring;
        user_register(prop, userid, password);*/
        user_register(message);
    }
}
int init_server()
{
    send_q_head = send_q_tail = 0;
    memset(send_queue, 0, sizeof(send_queue));
    memset(client_prop, 0, sizeof(client_prop));
    int i;
    for(i = 0; i < MAX_CONN; i++)
        client_prop[i].user_fd = -1;

    //initialize multithread lock
    pthread_mutex_init(&queue_lock, NULL);
    if(!init_socket())
    {
        printf("init_socket error!!!\n");
        return 0;
    }
    return 1;
}

int init_socket()
{
    if((listen_fd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(6666);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listen_fd,(struct sockaddr *)&server,sizeof(struct sockaddr))==-1)
    {
        printf("bind error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    if(listen(listen_fd,10))
    {
        printf("listen error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    return 1;
}

void* listen_func(void *)
{
    printf("listening...\n");
    while(1)
    {
        socklen_t size= sizeof(struct sockaddr_in);
        if((connect_fd=accept(listen_fd,(struct sockaddr *)&server,&size))==-1)
        {
            printf("accept error: %s(errno: %d)\n",strerror(errno),errno);
            exit(1);
        }

        //加入了新用户
        add_client(connect_fd, client);
    }
    return NULL;
}

void add_client(int connect_fd, struct sockaddr_in addr) {
    int idx = 0;
    for(idx = 0; idx < MAX_CONN; idx++) {
        if(client_prop[idx].user_fd == -1) {
            break;
        }
    }
    if(client_prop[idx].user_fd != -1) {
        printf("failed to create new thread for connect %s\n", inet_ntoa(addr.sin_addr));
        return ;
    }
    client_prop[idx].user_fd = connect_fd;
    client_prop[idx].addr = addr;
    pthread_t tid;
    pthread_create(&tid, NULL, client_thread_function, &client_prop[idx]);
    printf("created new thread for connect %s\n", inet_ntoa(addr.sin_addr));
}

void* client_thread_function(void *arg) {
    struct User * prop = (struct User *) arg;
    //when in pressure test mode, send welcome message after some command rather than automatically.
    //if(!PRESSURE_TEST)
    //	send(prop->client_fd, welcome_message, sizeof(char) * (strlen(welcome_message) + 1), 0);
    printf("prop: %d %s\n", prop->user_fd, inet_ntoa(prop->addr.sin_addr));
    char buf[BUFFER_SIZE];
    int numbytes;

    while(1) {
        printf("recv.....\n");
        numbytes = recv(prop->user_fd, buf, BUFFER_SIZE, 0);
		/*
		buf里面是类似于
		*/
        if(0 >= numbytes) {
            printf("user %s is offline.\n", inet_ntoa(prop->addr.sin_addr));
            break;
        }
        buf[numbytes] = '\0';
        handle_client_message(prop, buf);
        //log when receive a message
        //sprintf(log_buffer, "recv %s\n", buf);
        //write_log(logfile, log_buffer);
    }
    delete_client(prop);
    pthread_exit(NULL);
    return NULL;
}
void* send_thread_function(void *arg) {
	struct Message msg;
	char send_buffer[BUFFER_SIZE];
	while (1) {
		pthread_mutex_lock(&queue_lock);
		if (send_q_head != send_q_tail) {
			msg = send_queue[send_q_head];
			send_q_head = (send_q_head + 1) % MAX_SEND_QUEUE_SIZE;
			//判断用户是否在线
			int fd = get_user_fd(msg.to_id)->user_fd;
			if (fd != -1) {
				memset(send_buffer, '\0', sizeof(send_buffer));
				strcpy(send_buffer, msg.detail);
				send(fd, send_buffer, sizeof(send_buffer), 0);
				//free(msg.detail);
			}
			else {
				// save_offline_message(msg);
			}
			pthread_mutex_unlock(&queue_lock);
		}
		else {
			pthread_mutex_unlock(&queue_lock);
			//sleep here to avoid high CPU usagelogin
			sleep(1);
		}

	}
    return NULL;
}


void delete_client(struct User *prop)
{
    prop->user_fd=-1;
    prop->is_online=0;
    close(prop->user_fd);
}

//huoquyonghutaojiezi
User* get_user_fd(int userid) {
    int i;
    for(i = 0; i < MAX_CONN; i++) {
        if(userid == client_prop[i].u_id) {
            return &client_prop[i];
        }
    }
    return 0;
}

