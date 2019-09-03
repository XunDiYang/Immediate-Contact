//
// Created by mawencong on 2019/9/2.
//

//
// Created by changxinyu on 2019/8/31.
//

#include "server.h"

char buffer[BUFFER_SIZE];

/**************************************************/
/*名称：handle_client_message
/*描述：处理客户端发来的消息
/*作成日期：2019.9.3
/*参数：参数1：参数名称 prop、参数类型 struct User *、输入参数、参数含义：发送请求的用户套接字
		参数2：参数名称 message、参数类型 char *、输入参数、参数含义：客户端发来的消息
/*返回值：VOID
/*作者：马文聪
/***************************************************/
void handle_client_message(struct User * prop, char * message) {
    printf("handle_client_message\n");
    cJSON *root = cJSON_Parse(message);
    if (root == NULL)
        return;
    char *type = cJSON_GetObjectItem(root, "type")->valuestring;
    char message_json[BUFFER_SIZE];
    if (strcmp(type, "register-message") == 0)
    {
        printf("接下来和数据库链接了！\n");
        char *username = cJSON_GetObjectItem(root, "username")->valuestring;
        char *password = cJSON_GetObjectItem(root, "password")->valuestring;
        char *emailaddress = cJSON_GetObjectItem(root, "emailaddress")->valuestring;
        //user_register(message);
        sprintf(buffer, "register successful!\n");
        send_message_to_local(prop->user_fd, buffer);
    }
    else if(strcmp(type, "login-message") == 0)
    {
        char *username = cJSON_GetObjectItem(root, "username")->valuestring;
        char *password = cJSON_GetObjectItem(root, "password")->valuestring;
        //user_login(prop, username, password);
        sprintf(buffer, "register successful!\n");
        send_message_to_local(prop->user_fd, buffer);
    }
    else if(strcmp(type, "logout-message") == 0)
    {
        char *username = cJSON_GetObjectItem(root, "username")->valuestring;
        user_logout(prop);
        sprintf(buffer, "logout successful!\n");
        send_message_to_local(prop->user_fd, buffer);
    }
    else if(strcmp(type, "message/text") == 0)
    {
        printf("message/text\n");
        memset(message_json, '\0', sizeof(message_json));
        strcpy(message_json, message);
        send_single_message(message_json);
    }
    else if(strcmp(type,"message/file") == 0) {
        memset(message_json, '\0', sizeof(message_json));
        strcpy(message_json, message);
        send_single_file(message_json);
    }
}




