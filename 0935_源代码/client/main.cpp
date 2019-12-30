#include "client.h"

#include <string.h>


int serverfd;
struct sockaddr_in server;
char timestr[64];
char message_buffer[BUFFER_SIZE], send_buffer[BUFFER_SIZE];


int judgedeletefriend;
int judgequitgroup;
int judgejoingroup;
int judgecreategroup;
int judgeLogin;
int judgeSign;
int judgeaddfriends;
int current_id;//current user
int talk_to_user; //ID
int friend_id; //add feiends
int current_friend_num; //friend number
int current_friend_id[20]; //id
char current_friend_name[20][20]; //
int current_group_num;
int current_group_id[20];
char current_group_name[20][20];

//套接字转换==================================
struct Sock_ntop_Transform temp_transform_information;

/**************************************************/
/*名称：init_client()
/*描述：初始化客户端的套接字描述符
/*作成日期：2019.9.3
/*参数：无
/*返回值：初始化成功返回1
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
int init_client()
{
    struct hostent *he;
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(LISTEN_PORT);
    //server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server.sin_zero), 8);
    if ( (serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("create socket");
        return 0;
    }

    if ( (connect(serverfd, (struct sockaddr *)(&server), sizeof(struct sockaddr))) == -1)
    {
        perror("connect");
        return 0;
    }
    printf("init_client()");
    return 1;
}


/**************************************************/
/*名称：send_function
/*描述：客户端向服务器端发送数据包
/*作成日期：2019.9.3
/*参数：参数名：message，参数类型const char *，参数含义：发送的信息
/*返回值：int
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
int send_function(const char *message)
{
    memset(send_buffer, '\0', sizeof(send_buffer));
    strcpy(send_buffer, message);
    printf("sending message to server:\n%s\n", send_buffer);
    printf("%d", &serverfd);
    if (send(serverfd, send_buffer, BUFFER_SIZE, 0)<0)
    {

        perror("send error!");

        exit(1);

    }
}


/**************************************************/
/*名称：recv_thread()
/*描述：客户端接收服务器端数据包
/*作成日期：2019.9.3
/*参数：无
/*返回值：无
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void recv_thread() {
    int numbytes;
    while(1) {
        printf("recv serverfd = %d\n", serverfd);
        memset(message_buffer, '\0', BUFFER_SIZE);
        numbytes = recv(serverfd, message_buffer, BUFFER_SIZE, 0);
        printf(" recv_thread()\n");
        printf("%s", message_buffer);
        if(numbytes == 0){
            printf("server offline.\n");
            exit(1);
        }
        if(numbytes == -1){
            perror("error receiving message\n");
            exit(1);
        }

        handle_message(message_buffer, serverfd);

    }
}

/**************************************************/
/*名称：regist
/*描述：点击注册后的回调函数
/*作成日期：2019.9.3
/*参数：
	char *username 用户名称
	char *password 用户密码
    char *email 用户邮箱
/*返回值：int 1表示登陆成功
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
int regist(const char *username, const char *password ,const char *email)
{
    init_client();
    client_main();
    printf("regist %s %s\n", username, password);
    exec_cmd(1, 0, username, password, email, serverfd);
    return 1;
}


/**************************************************/
/*名称：login
/*描述：点击登陆后的回调函数
/*作成日期：2019.9.3
/*参数：
	char *username 用户名称
	char *password 用户密码
/*返回值：int 1表示登陆成功
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
int login(int user_id, const char *password)
{
    init_client();
    client_main();
    printf("login %d %s\n", user_id, password);
    exec_cmd(2, user_id, NULL, password,NULL, serverfd);
    exec_cmd(7, user_id, NULL, NULL, NULL, serverfd);
    exec_cmd(12, user_id, NULL, NULL, NULL, serverfd);
    return 1;
}


/**************************************************/
/*名称：confirm_friend_callback
/*描述：加一个好友的函数
/*作成日期：2019.9.3
/*参数：VOID
/*返回值：VOID
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void confirm_friend_callback(int fid) {
    printf("confirm friend callback %d\n", fid);
    exec_cmd(6, fid, NULL, NULL, NULL, serverfd);
}

/**************************************************/
/*名称：get_friend_list(int fid)
/*描述：得到好友信息列表
/*作成日期：2019.9.3
/*参数：VOID
/*返回值：VOID
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void get_friend_list(int fid) {
    printf("get friend list\n");
    exec_cmd(7, fid, NULL, NULL, NULL, serverfd);
}


/**************************************************/
/*名称：send_message_callback
/*描述：点击发送之后的回调函数
/*作成日期：2019.9.3
/*参数：
	char *message 发送的信息
/*返回值：VOID
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void send_message_callback(const char *message) {
    printf("send message callback %s\n", message);
    exec_cmd(4, talk_to_user, NULL, message, NULL, serverfd);
}


/**************************************************/
/*名称： get_UI_state()
/*描述： 获取当前用户的ui信息，和界面的接口
/*作成日期：2019.9.3
/*参数：界面传递给客户端的姓名
/*返回值：
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
int get_UI_state(int name) {
    talk_to_user = name;
    return talk_to_user;
}

/**************************************************/
/*名称： logout_action()
/*描述： 用户端登出函数
/*作成日期： 2019.9.3
/*参数：无
/*返回值：
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void logout_action() {
    printf("logout_action");

    current_id = 0;
}


/**************************************************/
/*名称：create_group
/*描述：创建群
/*作成日期：2019.9.3
/*参数：参数名：groupname, groupintro，参数类型char* char * 
/*返回值：VOID
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void create_group(char* groupname, char *groupintro){
    printf("create_group\n");
    exec_cmd(8, 0, groupname, groupintro, NULL, serverfd);
}

/**************************************************/
/*名称：join_group
/*描述：加入群
/*作成日期：2019.9.3
/*参数：群ID
/*返回值：VOID
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void join_group(int groupid){
    printf("join_group\n");
    exec_cmd(9, groupid, NULL, NULL, NULL, serverfd);
}

/**************************************************/
/*名称：quit_group
/*描述：退出群
/*作成日期：2019.9.3
/*参数：群ID
/*返回值：VOID
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void quit_group(int userid, int groupid){
    printf("quit_group\n");
    exec_cmd(11, groupid, NULL, NULL, NULL, serverfd);
}

/**************************************************/
/*名称：get_group_list
/*描述：得到群消息列表
/*作成日期：2019.9.3
/*参数：群ID
/*返回值：VOID
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void get_group_list(int groupid) {
    printf("get_group_list\n");
    exec_cmd(12, groupid, NULL, NULL, NULL, serverfd);
}

/**************************************************/
/*名称：send_group_message_callback
/*描述：点击群消息发送之后的回调函数
/*作成日期：2019.9.3
/*参数：群ID，消息
/*返回值：VOID
/*作者：马文聪、常欣煜、丁颖
/***************************************************/
void send_group_message_callback(int groupid, char *message) {
    printf("send message callback %s\n", message);
    exec_cmd(13, groupid, NULL, message, NULL, serverfd);
}


















/**************************************************/
/*名称： main()
/*描述： 界面启动时启动
/*作成日期： 2019.9.3
/*参数：界面传递给客户端的姓名
/*返回值：
/*作者：
/***************************************************/
void client_main()
{
    char message[BUFFER_SIZE];

    g_thread_create((GThreadFunc)recv_thread, NULL, FALSE, NULL);
}

const char *get_formatted_time(){
    time_t t = time(0);
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return timestr;
}