//
// Created by mawencong on 2019/9/2.
//

#ifndef SERVER_TEMP_SERVER_H
#define SERVER_TEMP_SERVER_H

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
#include "cJSON.h"

#define MAX_SEND_QUEUE_SIZE 10
#define MAX_CONN 10 //最大连接数量
#define BUFFER_SIZE 1024
#define MAX_MESSAGE_COUNT 1024


struct User
{
    struct sockaddr_in addr;
    int u_id;      //用户id
    int user_fd;   //用户描述字
    char u_name[20]; //用户名
    int is_online; //存储是否在线
};

struct Message
{
    int sendto;      //用户id
    int sendfrom;   //用户描述字
    int m_type;       //0:文字；1：文件
    char detail[1024]; //文字：内容；文件：路径
};

void handle_client_message(struct User *prop, char *message);
void *client_thread_function(void *arg);
int init_socket();

int init_server();

void *listen_func(void *);
void* send_thread_function(void *arg);

void add_client(int connect_fd, struct sockaddr_in addr);

void send_message_to_local(int user_fd, char* buffer);



void delete_client(struct User *prop);

struct User *get_user_fd(int userid);

char *sock_ntop(const struct sockaddr *sa);

char *get_user_ip(int userid);
void send_single_message(char *message);
void send_message_by_userid(int sendto, int sendfrom, char *msg);

void send_single_file(char *message);

void user_register(char *message);
void user_logout(struct User * prop);
#endif //SERVER_TEMP_SERVER_H
