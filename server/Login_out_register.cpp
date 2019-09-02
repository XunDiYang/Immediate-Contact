 //
// Created by changxinyu on 2019/8/31.
//

#include "include/server.h"
#include "../util/cJSON.h"

void user_register(char *message) {

    char sqlcmd[2048];
    memset(sqlcmd, '\0', sizeof(sqlcmd));
    cJSON *root = cJSON_Parse(message);
    char *password = cJSON_GetObjectItem(root, "password")->valuestring;
    char *username = cJSON_GetObjectItem(root, "username")->valuestring;
    char *email = cJSON_GetObjectItem(root, "email")->valuestring;
    char *content = cJSON_GetObjectItem(root, "content")->valuestring;
    // FILE *file_fp = fopen(content, "w+");
    // if(NULL == file_fp)
    // {
    //     printf(" open 01.file_fp failure\n" );
    //     // exit(1);void user_register(char *message) 

    // }
    // else
    // {
    //     int new_fd = get_user_fd(sendfrom)->user_fd;
    //     fprintf(file_fp,"%d\n",new_fd);
    //     fclose(file_fp);
    // }

    // int pthread_id;
    // // int ret = pthread_create((pthread_t *)&pthread_id,NULL,net_thread,(void *)&new_fd);
    // // if(ret==-1) {
    // //     perror("pthread_create");
    // //     close(new_fd);
    // //     return;
    // }
}


// void user_login(struct client_property *prop, int userid, char *password) 
// {
// 	char buffer[1024];
// 	User* user;
// 	int fd;
// 	if (strcmp(password, userUpasswdSelect(userid)) == 0) {
// 		user = get_user_fd(char *userid);
// 		fd = user->user_fd;
// 		buffer = "password verified\n";
// 		send(fd, buffer, sizeof(buffer), 0);
// 		//send_offline_message(userid);
// 	}
// 	else {
// 		user = get_user_fd(char *userid);
// 		fd = user->user_fd;
// 		buffer = "password error!";
// 		send(fd, buffer, sizeof(buffer), 0);
// 	}
// }
// void user_logout(struct client_property *prop, int userid) {
// 	User* user = get_user_fd(char *userid)
// 	user->is_online = 0;
// }










	

	


