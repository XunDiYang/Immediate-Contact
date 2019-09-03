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
void handle_client_message(struct User *prop, char *message)
{
    printf("handle_client_message\n");
    cJSON *root = cJSON_Parse(message);
    cJSON *sendroot = cJSON_CreateObject();
    if (root == NULL)
        return;
    char *type = cJSON_GetObjectItem(root, "type")->valuestring;
    char message_json[BUFFER_SIZE];
    if (strcmp(type, "register-message") == 0)
    {
        char *username = cJSON_GetObjectItem(root, "username")->valuestring;
        char *password = cJSON_GetObjectItem(root, "password")->valuestring;
        char *emailaddress = cJSON_GetObjectItem(root, "emailaddress")->valuestring;
        //user_register(message);
        if (user_register(message))
            cJSON_AddNumberToObject(sendroot, "status", 1);
        else
            cJSON_AddNumberToObject(sendroot, "status", 0);
        cJSON_AddStringToObject(sendroot, "type", "register-message");
        send_message_to_local(prop->user_fd, cJSON_Print(sendroot));
        printf("register successful！\n");
    }
    else if (strcmp(type, "login-message") == 0)
    {
        int userid = cJSON_GetObjectItem(root, "userid")->valueint;
        char *password = cJSON_GetObjectItem(root, "password")->valuestring;
        if (user_login(prop, userid, password))
            cJSON_AddNumberToObject(sendroot, "status", 1);
        else
            cJSON_AddNumberToObject(sendroot, "status", 0);
        cJSON_AddStringToObject(sendroot, "type", "login-message");
        send_message_to_local(prop->user_fd, cJSON_Print(sendroot));
        printf("login-message successful！\n");
    }
    else if (strcmp(type, "logout-message") == 0)
    {
        int userid = cJSON_GetObjectItem(root, "userid")->valueint;
        user_logout(prop);
        cJSON_AddStringToObject(sendroot, "type", "logout-message");
        cJSON_AddNumberToObject(sendroot, "status", 1);
        send_message_to_local(prop->user_fd, cJSON_Print(sendroot));
        printf("logout successful!\n");
    }
    else if (strcmp(type, "message/text") == 0)
    {
        printf("message/text\n");
        memset(message_json, '\0', sizeof(message_json));
        strcpy(message_json, message);
        send_single_message(message_json);
    }
    else if (strcmp(type, "message/file") == 0)
    {
        memset(message_json, '\0', sizeof(message_json));
        strcpy(message_json, message);
        send_single_file(message_json);
    }
    else if (strcmp(type, "group-create-request") == 0)
    {
        memset(message_json, '\0', sizeof(message_json));
        strcpy(message_json, message);
        if (create_group(message_json))
            cJSON_AddNumberToObject(sendroot, "status", 1);
        else
            cJSON_AddNumberToObject(sendroot, "status", 1);
        cJSON_AddStringToObject(sendroot, "type", "group-create-request");
        send_message_to_local(prop->user_fd, cJSON_Print(sendroot));
        printf("logout successful!\n");
    }
    else if (strcmp(type, "group-join-request") == 0)
    {
        int userid = cJSON_GetObjectItem(root, "userid")->valueint;
        int groupid = cJSON_GetObjectItem(root, "groupid")->valueint;
        if (join_group(userid, groupid))
            cJSON_AddNumberToObject(sendroot, "status", 1);
        else
            cJSON_AddNumberToObject(sendroot, "status", 1);
        cJSON_AddNumberToObject(sendroot, "groupid", groupid);
        cJSON_AddStringToObject(sendroot, "type", "group-join-request");
        send_message_to_local(prop->user_fd, cJSON_Print(sendroot));
        printf("group-join-request!\n");
    }
    else if (strcmp(type, "message/text/group") == 0)
    {
        memset(message_json, '\0', sizeof(message_json));
        strcpy(message_json, message);
        send_group_message(message_json);
    }
    else if (strcmp(type, "group-quit-request") == 0)
    {
        int userid = cJSON_GetObjectItem(root, "username")->valueint;
        int groupID = cJSON_GetObjectItem(root, "groupID")->valueint;
        if (quit_group(userid, groupID))
            cJSON_AddNumberToObject(sendroot, "status", 1);
        else
            cJSON_AddNumberToObject(sendroot, "status", 1);
        cJSON_AddStringToObject(sendroot, "type", "group-quit-request");
        send_message_to_local(prop->user_fd, cJSON_Print(sendroot));
        printf("group-quit-request!\n");
    }

    else if(strcmp(type, "friend-list-request") == 0)
    {
        int userid = cJSON_GetObjectItem(root, "userid")->valueint;
        send_friend_list(userid);
    }
    else if(strcmp(type, "add-to-contact-request") == 0) {
       int userid = cJSON_GetObjectItem(root, "userid")->valueint;
       int contact = cJSON_GetObjectItem(root, "contact")->valueint;
        add_contact(userid, contact);
    }
}
