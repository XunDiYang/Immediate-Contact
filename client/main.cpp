#include "client.h"

#include <string.h>

int serverfd;
struct sockaddr_in server;
int current_id = 0;//current user
int talk_to_user;
char timestr[64];
char buffer[BUFFER_SIZE], send_buffer[BUFFER_SIZE];

//套接字转换==================================
struct Sock_ntop_Transform temp_transform_information;
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
    return 1;
}

//与ui的连接端口
void exec_cmd(int op, int arg1, void *arg11, void *arg2, void *arg3)
{
    cJSON *root = cJSON_CreateObject();
    printf("exec_cmdinit==============\n");
    if (root == NULL)
    {
        printf("create json object failed\n");
        return;
    }
    if (op >= 3 && current_id == 0)
    {
        printf("haven't logged in");
        return;
    }
    printf("%d===================\n", op);
    switch (op)
    {
        printf("exec_cmdinit switch==============\n");
        //send to server:      0 <any string>
        case 0:
            send_function((char *)arg1);
            break;

            //register:            1 <username> <password>
        case 1:
            cJSON_AddStringToObject(root, "type", "register-message");
            cJSON_AddStringToObject(root, "username", (char *)arg11);
            cJSON_AddStringToObject(root, "password", (char *)arg2);
            cJSON_AddStringToObject(root, "emailaddress", (char *)arg3);
            send_function(cJSON_Print(root));
            break;

            //login:               2 <username> <password>
        case 2:
            cJSON_AddStringToObject(root, "type", "login-message");
            cJSON_AddNumberToObject(root, "userid", arg1);
            cJSON_AddStringToObject(root, "password", (char *) arg2);
            send_function(cJSON_Print(root));
            break;

            //logout:              3\n
        case 3:
            cJSON_AddStringToObject(root, "type", "logout-message");
            cJSON_AddNumberToObject(root, "userid", current_id);
            send_function(cJSON_Print(root));
            logout_action();
            break;

            //text message:        5 <sendto> <content>
        case 4:
            if(strlen((char*)arg2) > 1024){
                return;
            }
            cJSON_AddStringToObject(root, "type", "message/text");
            cJSON_AddNumberToObject(root, "sendto", arg1);
            cJSON_AddNumberToObject(root, "sendfrom", current_id);
            cJSON_AddStringToObject(root, "sendtime", get_formatted_time());
            cJSON_AddStringToObject(root, "content", (char *) arg2);
            send_function(cJSON_Print(root));
            //save the chat record while sending message
            //save_chatrecord_single(cJSON_Print(root));
            break;
    };
    cJSON_Delete(root);
}

//发送信息
int send_function(char *message)
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
//
void recv_thread() {
    int numbytes;
    while(1) {
        printf("recv serverfd = %d\n", serverfd);
        memset(buffer, 0, BUFFER_SIZE);
        numbytes = recv(serverfd, buffer, BUFFER_SIZE, 0);
        if(numbytes == 0){
            printf("server offline.\n");
            exit(1);
        }
        if(numbytes == -1){
            perror("error receiving message\n");
            exit(1);
        }

        //handle_message(buffer);

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
/*作者：
/***************************************************/
int regist(char *username, char *password ,char *email)
{
    printf("regist %s %s\n", username, password);
    exec_cmd(1, 0, username, password, email);
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
/*作者：
/***************************************************/
int login(int user_id, char *password)
{
    printf("login %d %s\n", user_id, password);
    exec_cmd(2, user_id, NULL, password,NULL);
    return 1;
}

/**************************************************/
/*名称：send_message_callback
/*描述：点击发送之后的回调函数
/*作成日期：2019.9.3
/*参数：
	char *message 发送的信息
/*返回值：VOID
/*作者：
/***************************************************/
void send_message_callback(char *message) {
    printf("send message callback %s\n", message);
    exec_cmd(4, talk_to_user, NULL, message, NULL);
}

/**************************************************/
/*名称： get_UI_state()
/*描述： 获取当前用户的ui信息，和界面的接口
/*作成日期： 2016.8.22
/*参数：界面传递给客户端的姓名
/*返回值：
/*作者：
/***************************************************/
int get_UI_state(int name) {
    talk_to_user = name;
    return talk_to_user;
}


void logout_action() {
    printf("logout_action");

    current_id = 0;
}



/**************************************************/
/*名称： main()
/*描述： 界面启动时启动
/*作成日期： 2019.9.3
/*参数：界面传递给客户端的姓名
/*返回值：
/*作者：
/***************************************************/
int main()
{
    char message[BUFFER_SIZE];
    if(!init_client())
        printf("init_client()error!");
    g_thread_create((GThreadFunc)recv_thread, NULL, FALSE, NULL);
    printf("请输入：\n");
    scanf("%s", message);
    current_id = 1;
    talk_to_user = 19;
    send_message_callback(message);

   // g_thread_create((GThreadFunc)auto_update_thread, NULL, FALSE, NULL);
    //g_thread_create((GThreadFunc)rev_FILE_thread, NULL, FALSE, NULL);
}

const char *get_formatted_time(){
    time_t t = time(0);
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return timestr;
}
