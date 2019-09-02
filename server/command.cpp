#include "server.h"





void handle_client_message(struct client_property * prop, const char * message) {
	cJSON *root = cJSON_Parse(message);
	if (root == NULL)
		return;
	char *type = cJSON_GetObjectItem(root, "type")->valuestring;
	char message_json[BUFFER_SIZE];
	if (strcmp(type, "register-message") == 0) {
		//TODO: the strings'space might be freed
		/*char *userid = cJSON_GetObjectItem(root, "userid")->valuestring;
		char *password = cJSON_GetObjectItem(root, "password")->valuestring;
		user_register(prop, userid, password);*/
        user_register(message);
	}
	// else if (strcmp(type, "login-message") == 0) {
	// 	char *userid = cJSON_GetObjectItem(root, "userid")->valuestring;
	// 	char *password = cJSON_GetObjectItem(root, "password")->valuestring;
	// 	user_login(prop, userid, password);
	// }
	// else if (strcmp(type, "logout-message") == 0) {
	// 	char *userid = cJSON_GetObjectItem(root, "userid")->valuestring;
	// 	user_logout(prop, userid);
	// }
	// else if (strcmp(type, "message/text") == 0) {
	// 	memset(message_json, '\0', sizeof(message_json));
	// 	strcpy(message_json, message);
	// 	send_s_message(message_json);
	// }
	// else if (strcmp(type, "message/file") == 0) {
	// 	memset(message_json, '\0', sizeof(message_json));
	// 	strcpy(message_json, message);
	// 	send_s_file();
	// }
	// else if (strcmp(type, "image-modify-request") == 0) {
	// 	char *userid = cJSON_GetObjectItem(root, "userid")->valuestring;
	// 	int user_image = cJSON_GetObjectItem(root, "userimage")->valueint;
	// 	user_image_modify(userid, user_image);
	// }
	free(root);
	printf("handle client message over\n");
}


// void send_s_message(char *message) {
// 	cJSON *root = cJSON_Parse(message);
// 	int sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valuestring;
// 	int sendto = cJSON_GetObjectItem(root, "sendto")->valuestring;
// 	char *content = cJSON_GetObjectItem(root, "content")->valuestring;
// 	/*char sqlcmd[2048];
// 	memset(sqlcmd, '\0', sizeof(sqlcmd));
// 	sprintf(sqlcmd, "select username from alluser where username=\'%s\'", sendto);
// 	sqlite3_exec(db, sqlcmd, send_single_message_callback, message, NULL);
// 	*/
// 	for (int i = 0; i < MAX_CONN; ++i) {
// 		if (strcmp(strUser[i]->u_id, *sendto) == 0)
// 			send_message_by_userid(sendfrom, sendto, message);
// 	}
// }


// void send_s_file(char *message)
// {
//     cJSON *root = cJSON_Parse(message);
//     int sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valueint;
//     int sendto = cJSON_GetObjectItem(root, "sendto")->valueint;
//     char *content = cJSON_GetObjectItem(root, "content")->valuestring;
//     //int new_fd=get_user_fd(userid)->user_fd;
//     FILE *file_fp = fopen(content, "w+");
//     if(NULL == file_fp)
//     {
//         printf(" open 01.file_fp failure\n" );
//         exit(1);
//     }
//     else
//     {
//         int new_fd = get_user_fd(sendfrom)->user_fd;
//         fprintf(file_fp,"%d\n",new_fd);
//         fclose(file_fp);
//     }

//     int pthread_id;
//     int ret = pthread_create((pthread_t *)&pthread_id,NULL,net_thread,(void *)&new_fd);
//     if(ret==-1) {
//         perror("pthread_create");
//         close(new_fd);
//         return;
//     }
// }


// void *net_thread(void * arg) {
//     pthread_detach(pthread_self()); //线程分离
//     int new_fd = *((int *) arg);
//     int file2_fp;

//     while (1) {
//         // recv函数接收数据到缓冲区buffer中
//         char buffer[BUFFER_SIZE];
//         memset(buffer, 0, sizeof(buffer));
//         if (read(new_fd, buffer, sizeof(buffer)) < 0) {
//             perror("Server Recieve Data Failed:");
//             break;
//         }

//         // 然后从buffer(缓冲区)拷贝到file_name中
//         char file_name[FILE_SIZE];
//         memset(file_name, 0, sizeof(file_name));
//         strncpy(file_name, buffer, strlen(buffer) > FILE_SIZE ? FILE_SIZE : strlen(buffer));
//         memset(buffer, 0, sizeof(buffer));
//         printf("%s\n", file_name);

//         if (strcmp(file_name, "null") == 0) {
//             break;
//             close(new_fd);
//         }

//         // 打开文件并读取文件数据
//         file2_fp = open(file_name, O_RDONLY, 0777);
//         if (file2_fp < 0) {
//             printf("File:%s Not Found\n", file_name);
//         } else {
//             int length = 0;
//             memset(buffer, 0, sizeof(buffer));
//             // 每读取一段数据，便将其发送给客户端，循环直到文件读完为止
//             while ((length = read(file2_fp, buffer, sizeof(buffer))) > 0) {
//                 if (write(new_fd, buffer, length) < 0) {
//                     printf("Send File:%s Failed.\n", file_name);
//                     break;
//                 }
//                 memset(buffer, 0, sizeof(buffer));
//             }
//             // 关闭文件
//             close(file2_fp);

//         }
//     }
// }

// void send_message_by_userid(int sendfrom, int sendto, char *msg) {
//     pthread_mutex_lock(&queue_lock);

//     if ((send_q_tail + 1) % MAX_SEND_QUEUE_SIZE == send_q_head)
//         return;
//     char *message = copy_string(msg);

//     send_queue[send_q_tail].message = message;
//     strcpy(send_queue[send_q_tail].from_id, sendfrom);
//     strcpy(send_queue[send_q_tail].to_id, sendto);
//     send_q_tail = (send_q_tail + 1) % MAX_SEND_QUEUE_SIZE;
//     free(msg);
//     pthread_mutex_unlock(&queue_lock);
// }


