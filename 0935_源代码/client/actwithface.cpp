//
// Created by mawencong on 2019/9/3.
//

//
// Created by mawencong on 2019/9/3.
//
//与ui的连接端口
#include "client.h"

extern int current_id;




void exec_cmd(int op, int arg1, const void *arg11, const void *arg2, const void *arg3, int serverfd)
{
    cJSON *root = cJSON_CreateObject();
    printf("exec_cmdinit==============\n");
    if (root == NULL)
    {
        printf("create json object failed\n");
        return;
    }
    printf("%d===================\n", op);
    switch (op)
    {
        printf("exec_cmdinit switch==============\n");
        //send to server:      0 <any string>
        case 0:
            send_function((const char *)arg1);
            break;

            //register:            1 <username> <password>
        case 1:
            printf("1\n");
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
            cJSON_AddStringToObject(root, "type", "message/text");
            cJSON_AddNumberToObject(root, "sendto", arg1);
            cJSON_AddNumberToObject(root, "sendfrom", current_id);
            cJSON_AddStringToObject(root, "sendtime", get_formatted_time());
            cJSON_AddStringToObject(root, "content", (char *) arg2);
            send_function(cJSON_Print(root));
            //save the chat record while sending message
            //save_chatrecord_single(cJSON_Print(root));
            break;

            //发送消息
        case 5:
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
            //send group message:  12 <content>

            //add friends
        case 6:
            cJSON_AddStringToObject(root, "type", "add-to-contact-request");
            cJSON_AddNumberToObject(root, "userid", current_id);
            cJSON_AddNumberToObject(root, "contact", arg1);
            send_function(cJSON_Print(root));
            break;
            //send group message:  12 <content>
        //获取好友列表
        case 7:
            cJSON_AddStringToObject(root, "type", "friend-list-request");
            cJSON_AddNumberToObject(root, "userid", arg1);
            send_function(cJSON_Print(root));
            break;
            //send group message:  12 <content

        case 8:
            cJSON_AddStringToObject(root, "type", "group-create-request");
            cJSON_AddStringToObject(root, "groupname", (char *)arg11);
            cJSON_AddNumberToObject(root, "groupownerid", current_id);
            cJSON_AddStringToObject(root, "groupintro",(char *) arg2);
            //图片cJSON_AddStringToObject(root, "groupicon", (char *) arg3);
            send_function(cJSON_Print(root));
            break;


        case 9:
            cJSON_AddStringToObject(root, "type", "group-join-request");
            cJSON_AddNumberToObject(root, "groupid", arg1);
            cJSON_AddNumberToObject(root, "userid", current_id);
            send_function(cJSON_Print(root));
            break;
            //send group message:
        case 10:
            cJSON_AddStringToObject(root, "type", "message/text/group");
            cJSON_AddNumberToObject(root, "sendto", arg1);
            cJSON_AddNumberToObject(root, "sendfrom", current_id);
            cJSON_AddStringToObject(root, "sendtime", get_formatted_time());
            cJSON_AddStringToObject(root, "content", (char *)arg2);
            send_function(cJSON_Print(root));
            break;
            //group-quit-request
        case 11://群主不退群
            cJSON_AddStringToObject(root, "type", "group-quit-request");
            cJSON_AddNumberToObject(root, "groupid", arg1);
            cJSON_AddNumberToObject(root, "userid", current_id);
            send_function(cJSON_Print(root));
            break;

            //get_group_list
        case 12:
            cJSON_AddStringToObject(root, "type", "group-list-request");
            cJSON_AddNumberToObject(root, "userid", arg1);
            send_function(cJSON_Print(root));
            break;

            //send_group_message_callback
        case 13:
            cJSON_AddStringToObject(root, "type", "message/text/group");
            cJSON_AddNumberToObject(root, "groupid", arg1);
            cJSON_AddNumberToObject(root, "userid", current_id);
            cJSON_AddNumberToObject(root, "userid", current_id);
            cJSON_AddStringToObject(root, "content", (char *) arg2);
            send_function(cJSON_Print(root));
            break;

            //删除好友
        case 14:
            cJSON_AddStringToObject(root, "type", "delete-contact-request");
            cJSON_AddNumberToObject(root, "contact", arg1);
            cJSON_AddNumberToObject(root, "userid", current_id);
            send_function(cJSON_Print(root));
            break;


    };
    cJSON_Delete(root);
}
