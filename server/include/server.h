//
// Created by changxinyu on 2019/8/31.
//

#ifndef TRY_SERVER_H
#define TRY_SERVER_H

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "../util/cJSON.h"

#define MAX_SEND_QUEUE_SIZE 10
#define MAX_CONN 10 //最大连接数量
#define BUFFER_SIZE 1024
#define MAX_MESSAGE_COUNT 1024


struct User
{
    struct sockaddr_in addr;
    int u_id;      //用户id
    int user_fd;   //用户描述字
    int is_online; //存储是否在线
};

struct Message
{
    int from_id;      //发送者id
    int to_id;        //接受者id
    int m_type;       //0:文字；1：文件
    char detail[200]; //文字：内容；文件：路径
};

void handle_client_message(struct User *prop, char *message);
void *client_thread_function(void *arg);
int init_socket();

int init_server();

void *listen_func(void *);
void* send_thread_function(void *arg);

void add_client(int connect_fd, struct sockaddr_in addr);





void delete_client(struct User *prop);

struct User *get_user_fd(int userid);

char *sock_ntop(const struct sockaddr *sa);

char *get_user_ip(char *userid);

void send_s_message(struct User *prop);

void send_s_file(struct User *prop);

void user_register(char *message);
#endif //TRY_SERVER_H
