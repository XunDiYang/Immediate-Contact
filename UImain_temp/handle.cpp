//
// Created by mawencong on 2019/9/3.
//

//
// Created by mawencong on 2019/9/3.
//
#include "client.h"


extern int judgeLogin;
extern int judgeSign;
extern int judgeaddfriends;
extern int current_id;//current user
extern int talk_to_user; //ID
extern int friend_id; //add feiends
extern int current_friend_num;
extern int current_friend_id[20];
extern char current_friend_name[20][20];

/**************************************************/
/*名称：handle_message
/*描述：发送线程与服务器端的交互
/*作成日期：2016.8.31
/*参数：
	char *message 处理发过来信息
/*返回值：VOID
/*作者：
/***************************************************/


void handle_message(const char *message, int serverfd){
    //gdk_threads_enter();
    printf("handle message start, serverfd = %d\n", serverfd);
    printf("%s\n", message);
    cJSON *root = cJSON_Parse(message);
    if(root == NULL){
        printf("json parse error, message is \"%s\"\n", message);
        return ;
    }
    char *type = cJSON_GetObjectItem(root, "type")->valuestring;

    if(strcmp(type, "register-message") == 0){
        int status = cJSON_GetObjectItem(root, "status")->valueint;
        int userid = cJSON_GetObjectItem(root, "userid")->valueint;
        if(status == 1 ){
            printf("registered new user %d successfully\n", userid);
            current_id = userid;
        }
        else {
            printf("register new user %d fail\n", userid);

        }

    }
    else if(strcmp(type, "login-message") == 0){
        //received the login receipt from server
        int status = cJSON_GetObjectItem(root, "status")->valueint;
        int userid = cJSON_GetObjectItem(root, "userid")->valueint;
        //int userimage = cJSON_GetObjectItem(root, "image")->valueint;
        if(status == 1 && userid != 0){
            judgeLogin = 1;
        }
        else {
            printf("login failed\n");
            judgeLogin = -1;
        }
    }
    else if(strcmp(type, "message/text") == 0){
        int sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valueint;
        char *sendtime = cJSON_GetObjectItem(root, "sendtime")->valuestring;
        char *content = cJSON_GetObjectItem(root, "content")->valuestring;
        char*sendfromname = "fg";
//        for(int i = 0; i < current_friend_num; ++i){
//            if(current_friend_id[i] == sendfrom) {
//                strcpy(sendfromname, current_friend_name[i]);
//                break;
//            }
//
//        }

        updateGetInfo(sendfromname, sendtime, content);
        printf("user %d sent a message to you at %s, \nmessage is %s\n",
               sendfrom, sendtime, content);
    }
    else if(strcmp(type, "logout-message") == 0){
        int userid = cJSON_GetObjectItem(root, "userid")->valueint;

        printf("you logout\n");
    }
    else if(strcmp(type, "message/text/group") == 0){
        printf("[%d]\n", root == NULL);
        int sendto = cJSON_GetObjectItem(root, "sendto")->valueint;
        printf("%d\n", sendto);
        int groupid = cJSON_GetObjectItem(root, "groupid")->valueint;
        int sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valueint;
        printf("%s\n", sendfrom);
        current_id = cJSON_GetObjectItem(root, "sendfrom")->valueint;
        char *sendtime = cJSON_GetObjectItem(root, "sendtime")->valuestring;
        printf("%s\n", sendtime);
        char *content = cJSON_GetObjectItem(root, "content")->valuestring;
        printf("%s\n", content);
        //和界面联系，调用界面这个群的界面，并将消息显示，界面那边可以设置一个函数保存所有发过来的消息

    }
    else if(strcmp(type, "group-create-request") == 0){
        int status = cJSON_GetObjectItem(root, "status")->valueint;
        int groupownerid = cJSON_GetObjectItem(root, "groupownerid")->valueint;
        if(status == 1) {
            //
            printf("create group success, new group ID is %d\n", groupownerid);
        }
        else {
            printf("create group failed");
        }
    }
    else if(strcmp(type, "group-join-request") == 0){
        int status = cJSON_GetObjectItem(root, "status")->valueint;
        if(status == 1) {
            int groupid = cJSON_GetObjectItem(root, "groupid")->valueint;
            printf("join group %d %s\n", groupid, (status ? "success" : "fail"));
            ///
        }
        else{
            printf("join group fail\n");
            ///
        }
    }
    else if(strcmp(type, "group-quit-request") == 0){
        int groupid = cJSON_GetObjectItem(root, "groupid")->valueint;
        int status = cJSON_GetObjectItem(root, "status")->valueint;
        //printf("quit group %d %s\n", groupID, (status ? "success" : "fail"));
        //
    }

    else if(strcmp(type, "add-to-contact-request") == 0){
        int status = cJSON_GetObjectItem(root, "status")->valueint;
        if(status == 1){
            char*contactUsername = cJSON_GetObjectItem(root, "contactUsername")->valuestring;
            judgeaddfriends = 1;
        }
        else{
            judgeaddfriends = -1;
        }
    }
    else if(strcmp(type, "friend-list-request") == 0){
        //friend list
        int size = cJSON_GetObjectItem(root, "size")->valueint;
        cJSON *list = cJSON_GetObjectItem(root, "list");
        int i;
        printf("friend list of user %d:\n", current_id);
        for(i = 0; i < size; i++){
            cJSON *item = cJSON_GetArrayItem(list, i);
            current_friend_id[i] = cJSON_GetObjectItem(item, "userid")->valueint;
            strcpy(current_friend_name[i], cJSON_GetObjectItem(item, "friendsUserName")->valuestring);
            //int status = cJSON_GetObjectItem(item, "status")->valueint;//status:online,offline
            //int userimage = cJSON_GetObjectItem(root, "image")->valueint;
        }
        current_friend_num = size;
    }


    printf("handle message over, serverfd = %d\n", serverfd);
    //gdk_threads_leave();
}