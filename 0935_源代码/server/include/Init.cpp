#include "server.h"
#include "userGroup.h"

int listen_fd,connect_fd;
struct sockaddr_in client,server;
struct User client_prop[MAX_CONN];
int send_q_head , send_q_tail;
char timestr[64];
Message send_queue[MAX_MESSAGE_COUNT];
static pthread_mutex_t queue_lock;


/**************************************************/
/*名称：init_server
/*描述：
/*作成日期：2019.9.3
/*参数:无
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int init_server()
{
    send_q_head = send_q_tail = 0;
    memset(send_queue, 0, sizeof(send_queue));
    memset(client_prop, 0, sizeof(client_prop));
    int i;
    for(i = 0; i < MAX_CONN; i++)
        client_prop[i].user_fd = -1;

    //initialize multithread lock
    pthread_mutex_init(&queue_lock, NULL);
    if(!init_socket())
    {
        printf("init_socket error!!!\n");
        return 0;
    }
    return 1;
}

/**************************************************/
/*名称：init_socket
/*描述：
/*作成日期：2019.9.3
/*参数:无
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int init_socket()
{
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1235);
    server.sin_addr.s_addr = inet_addr("0.0.0.0");;
    bzero(&(server.sin_zero), 8);
    if((listen_fd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    if(bind(listen_fd,(struct sockaddr *)&server,sizeof(struct sockaddr))==-1)
    {
        printf("bind error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }

    if(listen(listen_fd,10))
    {
        printf("listen error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    for(int idx = 0; idx < MAX_CONN; idx++) {
        client_prop[idx].is_online = 0;
        client_prop[idx].u_id = 0;
        client_prop[idx].user_fd = -1;
    }
    return 1;
}


/**************************************************/
/*名称：listen_func
/*描述：
/*作成日期：2019.9.3
/*参数:void *
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void* listen_func(void *)
{
    printf("listening...\n");
    while(1)
    {
        socklen_t size= sizeof(struct sockaddr_in);
        if((connect_fd = accept(listen_fd,(struct sockaddr *)&server,&size))==-1)
        {
            printf("accept error: %s(errno: %d)\n",strerror(errno),errno);
            exit(1);
        }

        //加入了新用户
        add_client(connect_fd, client);
    }
    return NULL;
}

/**************************************************/
/*名称：add_client
/*描述：
/*作成日期：2019.9.3
/*参数:int connect_fd, struct sockaddr_in addr
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void add_client(int connect_fd, struct sockaddr_in addr) {
    int idx = 0;
    for(idx = 0; idx < MAX_CONN; idx++) {
        if(client_prop[idx].is_online == 0) {
            break;
        }
    }

    client_prop[idx].user_fd = connect_fd;
    client_prop[idx].addr = addr;
    client_prop[idx].is_online = 1;
    pthread_t tid;
    pthread_create(&tid, NULL, client_thread_function, &client_prop[idx]);
    printf("created new thread for connect %s\n", inet_ntoa(addr.sin_addr));
}

/**************************************************/
/*名称：client_thread_function
/*描述：
/*作成日期：2019.9.3
/*参数:void *arg
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void* client_thread_function(void *arg) {
    struct User * prop = (struct User *) arg;
    printf("prop: %d %s\n", prop->user_fd, inet_ntoa(prop->addr.sin_addr));
    char buf[BUFFER_SIZE];
    int numbytes;

    while(1) {
        printf("recv.....\n");
        numbytes = recv(prop->user_fd, buf, BUFFER_SIZE, 0);
        printf("%s\n", buf);
        printf("%d", prop->user_fd);
        if(0 >= numbytes) {
            perror("recv error!");
            printf("user %s is offline.\n", inet_ntoa(prop->addr.sin_addr));
            break;
        }
        buf[numbytes] = '\0';
        handle_client_message(prop, buf);
    }
    delete_client(prop); //这里删除套接字，登出删去用户名
    pthread_exit(NULL);
    return NULL;
}

/**************************************************/
/*名称：send_thread_function
/*描述：
/*作成日期：2019.9.3
/*参数:void *arg
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void* send_thread_function(void *arg) {
    printf("send_thread_function\n");
    struct Message msg;
    char send_buffer[BUFFER_SIZE];
    while (1) {

        pthread_mutex_lock(&queue_lock);
        if (send_q_head != send_q_tail)
        {
            msg = send_queue[send_q_head];
            send_q_head = (send_q_head + 1) % MAX_SEND_QUEUE_SIZE;
            //判断用户是否在线
            int fd = get_user_fd(msg.sendto)->user_fd;
            if (fd != -1) {
                memset(send_buffer, '\0', sizeof(send_buffer));
                strcpy(send_buffer, msg.detail);
                send(fd, send_buffer, sizeof(send_buffer), 0);
                //free(msg.detail);
            }
            pthread_mutex_unlock(&queue_lock);
        }
        else {
            pthread_mutex_unlock(&queue_lock);
            //sleep here to avoid high CPU usagelogin
            sleep(1);
        }

    }
    return NULL;
}



/**************************************************/
/*名称：send_single_message
/*描述：解析要发送的信息的发送方、接收方和内容
/*作成日期：2019.9.3
/*参数:char *message（要解析的内容）
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void send_single_message(char *message) {
    cJSON *root = cJSON_Parse(message);
    int sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valueint;
    int sendto = cJSON_GetObjectItem(root, "sendto")->valueint;
    char *content = cJSON_GetObjectItem(root, "content")->valuestring;
    send_message_by_userid(sendto, sendfrom, message);

}


/**************************************************/
/*名称：send_single_file
/*描述：解析要发送的文件的发送方、接收方和内容，获取IP地址后，打包发送
/*作成日期：2019.9.3
/*参数:char *message（要解析的内容）
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void send_single_file(char *message){
    cJSON *root = cJSON_Parse(message);
    int sendfrom = cJSON_GetObjectItem(root, "sendfrom")->valueint;
    int sendto = cJSON_GetObjectItem(root, "sendto")->valueint;
    char *content = cJSON_GetObjectItem(root, "content")->valuestring;

    char *ipfd = get_user_ip(sendto);
    cJSON *Root = cJSON_CreateObject();
    if(ipfd == NULL){
        printf("get ip fail\n");
        return;
    }
    cJSON_AddStringToObject(Root, "type","return-message-filetransform");
    cJSON_AddStringToObject(Root, "Ipfd", ipfd);
    cJSON_AddNumberToObject(Root, "sendto", sendfrom);
    cJSON_AddNumberToObject(Root, "sendfrom", sendfrom);
    cJSON_AddStringToObject(Root, "content", content);
    send_message_by_userid(sendto, sendfrom, cJSON_Print(Root));
}

/**************************************************/
/*名称：send_group_message
/*描述：发送群组消息
/*作成日期：2019.9.3
/*参数：参数1：参数名称 message、参数类型 char *、输入参数、参数含义：消息
/*返回值：VOID
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int send_group_message(char *message) {
    int i;
    int grouplist[100];
    int num;
    cJSON *root = cJSON_Parse(message);
    int groupid = cJSON_GetObjectItem(root, "groupid")->valueint;
    int sendfrom = cJSON_GetObjectItem(root, "userid")->valueint;
    char *content = cJSON_GetObjectItem(root, "content")->valuestring;
    //得到所有
    UserGroup ug;

    if(ug.userGroupAllMidSelect(groupid))
    {
        //ug.userGroupAllGid[0]; //总人数
        //ug.userGroupAllGid[1]; //群内第一个人
        for(i = 1; i <= ug.userGroupAllMid[0]; ++i){
            if(sendfrom == ug.userGroupAllMid[i])
                continue;
            send_message_by_group(groupid, sendfrom, ug.userGroupAllMid[i], content);
        }
    }
    else{

        return 0;
    }


}

/**************************************************/
/*名称：send_message_by_group
/*描述：将要发送的信息存入发送队列
/*作成日期：2019.9.3
/*参数:sendto：发送人name, sendfrom：接收人name, content：发送内容
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int send_message_by_group(int groupid, int sendfrom, int sendto, char*msg){
    cJSON *sendroot = cJSON_CreateObject();
    cJSON_AddNumberToObject(sendroot, "status", 1);
    cJSON_AddNumberToObject(sendroot, "groupid", groupid);
    cJSON_AddStringToObject(sendroot, "type", "message/text/group");
    cJSON_AddNumberToObject(sendroot, "sendto", sendto);
    cJSON_AddNumberToObject(sendroot, "sendfrom", sendfrom);
    cJSON_AddStringToObject(sendroot, "sendtime", get_formatted_time());
    cJSON_AddStringToObject(sendroot, "content", (char *) msg);
    int fd = get_user_fd(sendto)->user_fd;
    if(send(fd, cJSON_Print(sendroot), BUFFER_SIZE, 0) > 0)
        return 1;
    else
        return 0;

}

/**************************************************/
/*名称：send_message_by_userid
/*描述：将要发送的信息存入发送队列
/*作成日期：2019.9.3
/*参数:sendto：发送人name, sendfrom：接收人name, content：发送内容
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void send_message_by_userid(int sendto, int sendfrom, char *msg) {
    pthread_mutex_lock(&queue_lock);
    if((send_q_tail + 1) % MAX_SEND_QUEUE_SIZE == send_q_head)
        return ;

    strcpy(send_queue[send_q_tail].detail, msg);
    send_queue[send_q_tail].sendfrom = sendfrom;
    send_queue[send_q_tail].sendto = sendto;
    send_q_tail = (send_q_tail + 1) % MAX_SEND_QUEUE_SIZE;
    pthread_mutex_unlock(&queue_lock);
}

/**************************************************/
/*名称：send_message_to_local
/*描述：收到本地命令，若执行成功，则返回本地
/*作成日期：2019.09.03
/*参数：参数1：参数名称 user_fd、参数类型 int、输入参数、参数含义：用户名
       参数2：参数名称 buffer、参数类型 char*、输入参数、参数含义：服务器端发送的消息
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void send_message_to_local(int user_fd, const char* buffer){
    printf("hello\n");
    printf("%s", buffer);
    if(send(user_fd, buffer, BUFFER_SIZE, 0) < 0){
        printf("send_message_to_local fail!\n");
    }
}

/**************************************************/
/*名称：show_server_status
/*描述：show_server_status
/*作成日期：2019.9.3
/*参数：
/*返回值：VOID
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void show_server_status() {
    printf("server status:\n");
    printf("max client count: %d\n", MAX_CONN);
    int i;
    for(i = 0; i < MAX_CONN; i++){
        printf("client %d: %d %s\n", i, client_prop[i].u_id, client_prop[i].u_name);
    }
}

/**************************************************/
/*名称：exec_cmd
/*描述：执行命令内容
/*作成日期：2019.9.3
/*参数：参数1：参数名称 command、参数类型 char *、输入参数、参数含义：命令内容
/*返回值：VOID
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void exec_cmd(char * command) {
    if(strcmp(command, "exit") == 0){
        exit_server();
    }
    if(strcmp(command, "status") == 0){
        show_server_status();
    }
}

/**************************************************/
/*名称：exit_server
/*描述：退出服务器
/*作成日期：2019.9.3
/*参数：
/*返回值：VOID
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void exit_server() {
    pthread_mutex_destroy(&queue_lock);
    exit(0);
}


void delete_client(struct User * prop) {
    close(prop->user_fd);
    prop->user_fd = -1;
    prop->is_online = 0;
    prop->u_id = 0;
    memset(prop->u_name, '\0', sizeof(prop->u_name));
}

/**************************************************/
/*名称：get_user_fd
/*描述：获取用户的文件描述符
/*作成日期：2019.9.3
/*参数：参数1：参数名称 userid、参数类型 int、输入参数、参数含义：用户ID
/*返回值：返回值名称 client_prop[i].u_fd;、类型 int、含义 用户的文件描述符
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
User* get_user_fd(int userid) {
    int i;
    for(i = 0; i < MAX_CONN; i++) {
        if(userid == client_prop[i].u_id) {
            return &client_prop[i];
        }
    }
    return 0;
}

/**************************************************/
/*名称：get_user_ip
/*描述：通过用户的ID,获取IP地址
/*作成日期：2019.9.3
/*参数:int userid（用户ID）
/*返回值：无
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
char *get_user_ip(int userid){
    int i;
    char *str;
    for( i = 0;i< MAX_CONN;i++){
        if(userid==client_prop[i].u_id){
            return sock_ntop(reinterpret_cast<const sockaddr *>(&client_prop[i].addr));
        }
    }
}

/**************************************************/
/*名称：sock_ntop
/*描述：套接字转换成ip
/*作成日期：2019.9.3
/*参数：参数1：参数名称 sa、参数类型 const struct sockaddr *、输入参数、参数含义：套接字
/*返回值：返回值名称 str、类型 char *、含义 ip字符串
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
char *sock_ntop(const struct sockaddr *sa)
{
    static char str[128];
    struct sockaddr_in *sin = (struct sockaddr_in *)sa;
    if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str))==NULL)
        return NULL;
    return str;
}

const char *get_formatted_time(){
    time_t t = time(0);
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return timestr;
}


/**************************************************/
/*名称：add_contact
/*描述：添加好友
/*作成日期：2019.9.3
/*参数：  参数1：参数名称 user_id、参数类型 int、输入参数、参数含义：本地用户ID
		参数1：参数名称 ub、参数类型 char *、输入参数、参数含义：添加好友用户ID
/*返回值：bool
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
bool add_contact(int user_id, int friend_id){
    printf("%d trying to add %d as contact\n", user_id, friend_id);
    TheUser friend_user;
    Friends friends;
    if(friends.friendsInsert(user_id,friend_id,friend_user.userUnameSelect(friend_id),2))
        return true;
    else
        return false;
}

/**************************************************/
/*名称：delete_contact
/*描述：添加好友
/*作成日期：2019.9.3
/*参数：  参数1：参数名称 user_id、参数类型 int、输入参数、参数含义：本地用户ID
		参数1：参数名称 ub、参数类型 char *、输入参数、参数含义：删除好友用户ID
/*返回值：bool
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
bool delete_contact(int user_id, int friend_id){
    TheUser friend_user;
    Friends friends;
    if(friends.friendsDelete(user_id,friend_id))
        return true;
    else
        return false;
}



/**************************************************/
/*名称：send_friend_list
/*描述：发送friend list
/*作成日期：2019.9.3
/*参数：参数1：参数名称 userid、参数类型 int、输入参数、参数含义：用户ID
/*返回值：VOID
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void send_friend_list(int userid) {
    cJSON *root = cJSON_CreateObject();
    //cJSON *list = cJSON_CreateArray();
    Friends friends;
    char a[100], b[100];
    memset(a, '\0', sizeof(a));
    memset(b, '\0', sizeof(b));
    if(friends.friendsFlistSelect(userid)) {
        int i;
        for (i = 1; i <= friends.friendslist[0]; i++) {
            for(int j = 0; j < i; ++j)
                a[j] = 'a';
            for(int j = 0; j < i; ++j)
                b[j] = 'b';
            //printf("%s ", res[nindex]);
            //int status = get_user_fd(friends.friendslist[i])->is_online;
            //cJSON *item;
            //cJSON_AddItemToArray(list, item = cJSON_CreateObject());
            //cJSON_AddNumberToObject(item, "userid", friends.friendslist[i]);
            cJSON_AddNumberToObject(root, a, friends.friendslist[i]);
            TheUser friendUser;
            const char *friendsUserName = friendUser.userUnameSelect(friends.friendslist[i]); //通过朋友id查找朋友姓名
            cJSON_AddStringToObject(root, b, friendsUserName);
            memset(a, '\0', sizeof(a));
            memset(b, '\0', sizeof(b));
            //cJSON_AddStringToObject(item, "friendsUserName", friendsUserName);
            // cJSON_AddNumberToObject(item, "status", status);
        }
        cJSON_AddStringToObject(root, "type", "friend-list-request");
        cJSON_AddNumberToObject(root, "size", friends.friendslist[0]);
        //cJSON_AddItemToObject(root, "list", list);
        cJSON_AddNumberToObject(root, "status", 1);
        send_message_to_local(get_user_fd(userid)->user_fd, cJSON_Print(root));
    }
    else{
        cJSON_AddNumberToObject(root, "status", 1);
        send_message_to_local(get_user_fd(userid)->user_fd, cJSON_Print(root));
    }
}

/**************************************************/
/*名称：store_umessage
/*描述：存储一人对一人的消息（一条）
/*作成日期：2019.9.3
/*参数：  参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：发送消息id
        参数2：参数名称 f_id、参数类型 int、输入参数、参数含义：接收者Id
        参数3：参数名称 m_type、参数类型 int、输入参数、参数含义：类别
        参数4：参数名称 detail、参数类型 const char* 、输入参数、参数含义：消息内容
/*返回值：bool
/*作者：杨训迪
/***************************************************/

bool store_umessage(int u_id, int f_id, int m_type, const char* detail)
{
    Umessage umessage;
    if(umessage.messageInsert(u_id,f_id,0,detail))     //插入消息成功
        return true;
    else                                                               //插入消息失败
        return false;
}

/**************************************************/
/*名称：send_all_umessage
/*描述：发送一人对一人的消息（全部）
/*作成日期：2019.9.3
/*参数：  参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：发送消息id
        参数2：参数名称 f_id、参数类型 int、输入参数、参数含义：接收者Id
/*返回值：bool
/*作者：杨训迪
/***************************************************/
bool send_all_umessage(int u_id, int f_id)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *list = cJSON_CreateArray();

    Umessage umessage;
    umessage.messageSelect(u_id,f_id);

    for(int i = 1; i <= umessage.num; i++)
    {
        cJSON *item;

    }

}


/**************************************************/
/*名称：store_gmessage
/*描述：存储群消息（一条）
/*作成日期：2019.9.3
/*参数：参数1：参数名称 userid、参数类型 int、输入参数、参数含义：用户ID
/*返回值：VOID
/*作者：杨训迪
/***************************************************/
bool store_gmessage(int gm_id, int g_id, int gm_type, const char* detail)
{
    Gmessage gmessage;
    if( gmessage.gmessageInsert(gm_id, g_id, gm_type, detail))     //插入消息成功
        return true;
    else                                                               //插入消息失败
        return false;
}

