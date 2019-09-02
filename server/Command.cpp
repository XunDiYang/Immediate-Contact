//
// Created by changxinyu on 2019/8/31.
//

#include "include/server.h"


void handle_client_message(struct User * prop, char * message) {
    cJSON *root = cJSON_Parse(message);
    if (root == NULL)
        return;
    char *type = cJSON_GetObjectItem(root, "type")->valuestring;
    char message_json[BUFFER_SIZE];
    if (strcmp(type, "register-message") == 0) {
        user_register(message);
    }
}



