//
// Created by mawencong on 2019/9/2.
//

//
// Created by changxinyu on 2019/8/31.
//

#include "server.h"


void user_register(char *message) {
    char sqlcmd[2048];
    memset(sqlcmd, '\0', sizeof(sqlcmd));
    cJSON *root = cJSON_Parse(message);
    char *password = cJSON_GetObjectItem(root, "password")->valuestring;
    char *username = cJSON_GetObjectItem(root, "username")->valuestring;
    char *email = cJSON_GetObjectItem(root, "email")->valuestring;
    char *content = cJSON_GetObjectItem(root, "content")->valuestring;
    printf("准备写入数据库啦！\n");
}


void user_logout(struct User * prop) {
    printf("user %s logout\n", prop->u_name);
    memset(prop->u_name, '\0', sizeof(prop->u_name));
    prop->u_id = 0;
    prop->is_online = 0;
}










