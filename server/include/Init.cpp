//
// Created by mawencong on 2019/9/2.
//
//
// Created by changxinyu on 2019/8/31.
//

#include "server.h"

int listen_fd,connect_fd;
struct sockaddr_in client,server;
struct User client_prop[MAX_CONN];
int send_q_head , send_q_tail;
Message send_queue[MAX_MESSAGE_COUNT];
static pthread_mutex_t queue_lock;

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
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1235);
    server.sin_addr.s_addr = inet_addr("0.0.0.0");;
    bzero(&(server.sin_zero), 8);
    if((listen_fd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

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
        if((connect_fd = accept(listen_fd,(struct sockaddr *)&server,&size))==-1)
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
    printf("prop: %d %s\n", prop->user_fd, inet_ntoa(prop->addr.sin_addr));
    char buf[BUFFER_SIZE];
    int numbytes;

    while(1) {
        printf("recv.....\n");
        numbytes = recv(prop->user_fd, buf, BUFFER_SIZE, 0);
        printf("%d", prop->user_fd);
        if(0 >= numbytes) {
            perror("recv error!");
            printf("user %s is offline.\n", inet_ntoa(prop->addr.sin_addr));
            break;
        }
        buf[numbytes] = '\0';
        handle_client_message(prop, buf);
    }
    delete_client(prop); //这里删除套接字，登出删去用户名
    pthread_exit(NULL);
    return NULL;
}

void* send_thread_function(void *arg) {
    printf("send_thread_function\n");
    struct Message msg;
    char send_buffer[BUFFER_SIZE];
    while (1) {
        pthread_mutex_lock(&queue_lock);
        if (send_q_head != send_q_tail)
        {
            msg = send_queue[send_q_head];
            send_q_head = (send_q_head + 1) % MAX_SEND_QUEUE_SIZE;
            //判断用户是否在线
            int fd = get_user_fd(msg.sendto)->user_fd;
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



/**************************************************/
/*名称：send_single_message
/*描述：解析要发送的信息的发送方、接收方和内容
/*作成日期：2019.9.3
/*参数:char *message（要解析的内容）
/*返回值：无
/*作者：马文聪
/***************************************************/
void send_single_message(char *message) {
    cJSON *root = cJSON_Parse(message);
    int sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valueint;
    int sendto = cJSON_GetObjectItem(root, "sendto")->valueint;
    char *content = cJSON_GetObjectItem(root, "content")->valuestring;
    send_message_by_userid(sendto, sendfrom, content);
}


/**************************************************/
/*名称：send_single_file
/*描述：解析要发送的文件的发送方、接收方和内容，获取IP地址后，打包发送
/*作成日期：2019.9.3
/*参数:char *message（要解析的内容）
/*返回值：无
/*作者：常欣煜
/***************************************************/
void send_single_file(char *message){
    cJSON *root = cJSON_Parse(message);
    int sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valueint;
    int sendto = cJSON_GetObjectItem(root, "sendto")->valueint;
    char *content = cJSON_GetObjectItem(root, "content")->valuestring;

    char *ipfd = get_user_ip(sendto);
    cJSON *Root = cJSON_CreateObject();
    if(ipfd == NULL){
        printf("get ip fail\n");
        return;
    }
    cJSON_AddStringToObject(Root, "type","return-message-filetransform");
    cJSON_AddStringToObject(Root, "Ipfd", ipfd);
    cJSON_AddNumberToObject(Root, "sendto", sendfrom);
    cJSON_AddNumberToObject(Root, "sendfrom", sendfrom);
    cJSON_AddStringToObject(Root, "content", content);
    send_message_by_userid(sendto, sendfrom, cJSON_Print(Root));
}

/**************************************************/
/*名称：send_message_by_userid
/*描述：将要发送的信息存入发送队列
/*作成日期：2019.9.3
/*参数:sendto：发送人name, sendfrom：接收人name, content：发送内容
/*返回值：无
/*作者：马文聪
/***************************************************/
void send_message_by_userid(int sendto, int sendfrom, char *msg) {
    pthread_mutex_lock(&queue_lock);
    if((send_q_tail + 1) % MAX_SEND_QUEUE_SIZE == send_q_head)
        return ;

    strcpy(send_queue[send_q_tail].detail, msg);
    send_queue[send_q_tail].sendfrom = sendfrom;
    send_queue[send_q_tail].sendto = sendto;
    send_q_tail = (send_q_tail + 1) % MAX_SEND_QUEUE_SIZE;
    pthread_mutex_unlock(&queue_lock);
}

/**************************************************/
/*名称：send_message_to_local
/*描述：收到本地命令，若执行成功，则返回本地
/*作成日期：2016-8-31
/*参数：参数1：参数名称 user_fd、参数类型 int、输入参数、参数含义：用户名
       参数2：参数名称 buffer、参数类型 char*、输入参数、参数含义：服务器端发送的消息
/*返回值：无
/*作者：马文聪
/***************************************************/
void send_message_to_local(int user_fd, char* buffer){
    if(send(user_fd, buffer, sizeof(buffer), 0) < 0){
        printf("send_message_to_local fail!\n");
    }
}




void delete_client(struct User * prop) {
    close(prop->user_fd);
    prop->user_fd = -1;
    prop->is_online = 0;
    memset(prop->u_name, '\0', sizeof(prop->u_name));
}

/**************************************************/
/*名称：get_user_fd
/*描述：获取用户的文件描述符
/*作成日期：2019.9.3
/*参数：参数1：参数名称 userid、参数类型 int、输入参数、参数含义：用户ID
/*返回值：返回值名称 client_prop[i].u_fd;、类型 int、含义 用户的文件描述符
/*作者：马文聪
/***************************************************/
User* get_user_fd(int userid) {
    int i;
    for(i = 0; i < MAX_CONN; i++) {
        if(userid == client_prop[i].u_id) {
            return &client_prop[i];
        }
    }
    return 0;
}

/**************************************************/
/*名称：get_user_ip
/*描述：通过用户的ID,获取IP地址
/*作成日期：2019.9.3
/*参数:int userid（用户ID）
/*返回值：无
/*作者：常欣煜
/***************************************************/
char *get_user_ip(int userid){
    int i;
    char *str;
    for( i = 0;i< MAX_CONN;i++){
        if(userid==client_prop[i].u_id){
            return sock_ntop(reinterpret_cast<const sockaddr *>(&client_prop[i].addr));
        }
    }
}

/**************************************************/
/*名称：sock_ntop
/*描述：套接字转换成ip
/*作成日期：2019.9.3
/*参数：参数1：参数名称 sa、参数类型 const struct sockaddr *、输入参数、参数含义：套接字
/*返回值：返回值名称 str、类型 char *、含义 ip字符串
/*作者：常欣煜
/***************************************************/
char *sock_ntop(const struct sockaddr *sa)
{
    static char str[128];
    struct sockaddr_in *sin = (struct sockaddr_in *)sa;
    if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str))==NULL)
        return NULL;
    return str;
}



