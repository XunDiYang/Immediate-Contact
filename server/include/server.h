//
// Created by mawencong on 2019/9/2.
//

#ifndef SERVER_H
#define SERVER_H

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
#include "group.h"
#include "friends.h"
#include "gmessage.h"
#include "message.h"
#include "user.h"
#include "userGroup.h"
#include "section.h"

#define MAX_SEND_QUEUE_SIZE 10
#define MAX_CONN 10 //最大连接数量
#define BUFFER_SIZE 2048
#define MAX_MESSAGE_COUNT 1024

struct User
{
    struct sockaddr_in addr;
    int u_id;        //用户id
    int user_fd;     //用户描述字
    char u_name[20]; //用户名
    int is_online;   //存储是否在线
};

struct Message
{
    int sendto;        //用户id
    int sendfrom;      //用户描述字
    int m_type;        //0:文字；1：文件
    char detail[1024]; //文字：内容；文件：路径
};

void handle_client_message(struct User *prop, char *message);

int init_socket();
int init_server();
void *listen_func(void *);
void *send_thread_function(void *arg);
void *client_thread_function(void *arg);
void exec_cmd(char *command);
void exit_server();
void show_server_status();
const char *get_formatted_time();

void add_client(int connect_fd, struct sockaddr_in addr);

void delete_client(struct User *prop);

struct User *get_user_fd(int userid);

char *sock_ntop(const struct sockaddr *sa);

char *get_user_ip(int userid);

void send_single_message(char *message);
void send_message_by_userid(int sendto, int sendfrom, char *msg);
void send_single_file(char *message);
int send_group_message(char *message);
void send_message_to_local(int user_fd, const char *buffer);
int send_message_by_group(int groupid, int sendfrom, int sendto, char*msg);

int user_register(char *message);
int user_logout(struct User *prop);
int user_login(struct User *prop, int userid, char *password);
char *userUpasswdSelect(int userid);

int add_contact(int user_id, int friend_id);
void send_friend_list(int userid);



int create_group(char *msg);
int join_group(int userid, int groupid);
int quit_group(int userid, int groupid);
#endif
