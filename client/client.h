//
// Created by mawencong on 2019/9/2.
//

#ifndef CLIENT_TEMP_CLIENT_H
#define CLIENT_TEMP_CLIENT_H

#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <time.h>
#include <time.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "util/cJSON.h"
//收发文件的端口
#define HELLO_WORLD_SERVER_PORT 9898
//监听队列长度
#define LENGTH_OF_LISTEN_QUEUE 20
//文件名称缓冲区长度
#define FILE_NAME_MAX_SIZE 512
//监听端口
#define LISTEN_PORT 1235
//缓冲区长度
#define BUFFER_SIZE 2048
//Socket转化成ip所用的结构体
#define server_ip 127.0.0.1

#define FILE_BUFFER_SIZE 1024



struct Sock_ntop_Transform
{
    char ip[127];
    char position[1024];
};
//消息列表
struct message_list_item
{
    //sendfrom and time
    char message_prop[64];
    //all message's size doesn't exceed 1024 byte!
    char content[1024];
};

void auto_update_thread();


const char *get_formatted_time();
void logout_action();
int get_UI_state(int name);
void send_message_callback(char *message);
int login(int user_id, char *password);
int regist(char *username, char *password,char *email);
void recv_thread();
int send_function(char *message);
void rev_FILE_thread();
void exec_cmd(int op, int arg1, void *arg11, void *arg2, void *arg3);
int init_client(char *serverIP);

#endif //CLIENT_TEMP_CLIENT_H
