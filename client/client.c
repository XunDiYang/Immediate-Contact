
//初始化
int init_client() {
	if(-1 == (serverfd = socket(AF_INET, SOCK_STREAM, 0))) {
		perror("create socket");
		return 0;
	}

	struct hostent *he;
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(LISTEN_PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY)

	if(-1 == connect(serverfd, (struct sockaddr *)(&server), sizeof(struct sockaddr))) {
		perror("connect");
		return 0;
	}
	return 1;
	/*
	int numbytes;
	//receive the welcome message from server
	
	if((numbytes=recv(serverfd,buffer,BUFFER_SIZE,0))==-1){
		perror("recv");
		exit(1);
	}
	buffer[numbytes]='\0';
	return (strcmp(buffer, "welcome") == 0);
	*/
}



//与ui的连接端口
void exec_cmd(int op, void *arg1, void *arg2,void *arg3) {
    cJSON *root = cJSON_CreateObject();
	printf("exec_cmdinit==============\n");
    if(root == NULL){
        printf("create json object failed\n");
        return;
    }
    if(op >= 3 && strlen(current_username) == 0){
        printf("haven't logged in");
        return ;
    }
	printf("%d===================\n",op);
    switch(op){
	printf("exec_cmdinit switch==============\n");
    //send to server:      0 <any string>
    case 0:
    send_function((char *) arg1);
    break;

	//register:            1 <username> <password>
	case 1:
    cJSON_AddStringToObject(root, "type", "register-message");
    cJSON_AddStringToObject(root, "username", (char *) arg1);
    cJSON_AddStringToObject(root, "password", (char *) arg2);
    cJSON_AddStringToObject(root, "emailaddress", (char *) arg3);
    send_function(cJSON_Print(root));
    break;

	//login:               2 <username> <password>
	case 2:
    cJSON_AddStringToObject(root, "type", "login-message");
    cJSON_AddStringToObject(root, "username", (char *) arg1);
    cJSON_AddStringToObject(root, "password", (char *) arg2);
    send_function(cJSON_Print(root));
    break;

	//logout:              3\n
	case 3:
    cJSON_AddStringToObject(root, "type", "logout-message");
    cJSON_AddStringToObject(root, "username", current_username);
	send_function(cJSON_Print(root));
	logout_action();
    break;

	//add friend:          4 <username>
	case 4:
    cJSON_AddStringToObject(root, "type", "add-to-contact-request");
    cJSON_AddStringToObject(root, "username", current_username);
    cJSON_AddStringToObject(root, "contact", (char *) arg1);
    send_function(cJSON_Print(root));
    break;


	//text message:        5 <sendto> <content>
	case 5:
	if(strlen((char*)arg2) > 1024){
		return;
	}
    cJSON_AddStringToObject(root, "type", "message/text");
    cJSON_AddStringToObject(root, "sendto", (char *) arg1);
    cJSON_AddStringToObject(root, "sendfrom", current_username);
    cJSON_AddStringToObject(root, "sendtime", get_formatted_time());
    cJSON_AddStringToObject(root, "content", (char *) arg2);
    send_function(cJSON_Print(root));
	//save the chat record while sending message
	save_chatrecord_single(cJSON_Print(root));
    break;

	//show friend list:    6
	case 6:
	cJSON_AddStringToObject(root, "type", "friend-list-request");
    cJSON_AddStringToObject(root, "username", current_username);
    send_function(cJSON_Print(root));
    break;

	//show group list:     7
	case 7:
	cJSON_AddStringToObject(root, "type", "group-list-request");
    cJSON_AddStringToObject(root, "username", current_username);
    send_function(cJSON_Print(root));
    break;

	//show group profile:  8 <groupID>
	case 8:
    cJSON_AddStringToObject(root, "type", "group-profile-request");
    cJSON_AddStringToObject(root, "username", current_username);
    cJSON_AddNumberToObject(root, "groupID", *(int*)arg1);
    send_function(cJSON_Print(root));
    break;

	//create new group:    9
	case 9:
    cJSON_AddStringToObject(root, "type", "group-create-request");
    cJSON_AddStringToObject(root, "username", current_username);
    send_function(cJSON_Print(root));
    break;

	//join group:          10 <groupID>
	case 10:
    cJSON_AddStringToObject(root, "type", "group-join-request");
    cJSON_AddStringToObject(root, "username", current_username);
    cJSON_AddNumberToObject(root, "groupID", *(int*)arg1);
    send_function(cJSON_Print(root));
    break;

	//quit group:          11 <groupID>
	case 11:
    cJSON_AddStringToObject(root, "type", "group-quit-request");
    cJSON_AddStringToObject(root, "username", current_username);
    cJSON_AddNumberToObject(root, "groupID", *(int*)arg1);
    send_function(cJSON_Print(root));
    break;

	//send group message:  12 <content>
	case 12:
	if(strlen((char*)arg2) > 1024){
		return;
	}
    cJSON_AddStringToObject(root, "type", "message/text/group");
    cJSON_AddNumberToObject(root, "sendto", *(int*)arg1);
    cJSON_AddStringToObject(root, "sendfrom", current_username);
    cJSON_AddStringToObject(root, "sendtime", get_formatted_time());
    cJSON_AddStringToObject(root, "content", (char *)arg2);
	cJSON_AddStringToObject(root, "msgID", "segmentfault");
    send_function(cJSON_Print(root));
    break;

	//show history message:13 <group|single> <groupID|username>
	case 13:
	if(strcmp((char *)arg1, "single") == 0) {
		show_chatrecord_single((char *)arg2);
	} else if(strcmp((char *)arg1, "group") == 0) {
		show_chatrecord_group(*(int*)arg2);
	}
    break;
	
	case 14:
//	printf("%s=============================\n",(char *)arg1);
	if(strlen((char *)arg1)>1024){
		return ;	
	}
	
    cJSON_AddStringToObject(root, "type", "message/file");
    cJSON_AddStringToObject(root, "sendto", (char *) arg1);//发给谁
	printf("=========%s==========\n",(char *)arg1);
    cJSON_AddStringToObject(root, "sendfrom", current_username);//当前发送人
    cJSON_AddStringToObject(root, "sendtime", get_formatted_time());//当前时间
    cJSON_AddStringToObject(root, "content", (char *) arg2);//文件名
    send_function(cJSON_Print(root));
	//save the chat record while sending message
	save_chatrecord_single(cJSON_Print(root));
    break;

	case 15:
	if(strlen((char *)arg1)>1024)
		return ;
	cJSON_AddStringToObject(root,"type","friend-image-request");
	cJSON_AddStringToObject(root,"friendname",(char *) arg1);
	cJSON_AddStringToObject(root,"myname",current_username);
	send_function(cJSON_Print(root));
	save_chatrecord_single(cJSON_Print);
	break;

	case 16:
	if(strlen((char *)arg1)>1024)
		return;
	cJSON_AddStringToObject(root,"type","image-modify-request");
	cJSON_AddStringToObject(root,"username",(char *)arg1);
	cJSON_AddNumberToObject(root,"userimage",*(int *)arg2);

	send_function(cJSON_Print(root));

    default:break;
	};
}


//发送信息
int send_function(char *message) {
    memset(send_buffer, '\0', sizeof(send_buffer));
    strcpy(send_buffer, message);
    printf("sending message to server:\n%s\n", send_buffer);
	return send(serverfd, send_buffer, BUFFER_SIZE, 0);
}




//登录
int login(char *username, char *password) {
	printf("login %s %s\n", username, password,NULL);
	exec_cmd(2, username, password);
	return 1;
}

//注册
int regist(char *username, char *password，char *email) {
	printf("regist %s %s\n", username, password, email );
	exec_cmd(1, username, password);
	return 1;
}

void sendA(int op1,char *un,char *pw,char *ea )
{
    init_client(server_ip);
    switch (op1)
    {
    case 1:
        regist(un, pw，ea);
        break;
    case 2:
        login(un, pw);
        break;
    
    default:
        break;
    }
}


