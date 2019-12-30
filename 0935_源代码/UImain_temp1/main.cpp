#include "client.h"

#include <string.h>


int serverfd;
struct sockaddr_in server;
char timestr[64];
char message_buffer[BUFFER_SIZE], send_buffer[BUFFER_SIZE];


int judgeLogin;
int judgeSign;
int judgeaddfriends;
int current_id;//current user
int talk_to_user; //ID
int friend_id; //add feiends
int current_friend_num; //friend number
int current_friend_id[20]; //id
char current_friend_name[20][20]; //
int is_file_accepted_temp=-1;//确认接收

/*****************
/*名称：init_client
/*描述：初始化客户端
/*作成日期：2019.9.1
/*参数：
/*返回值：int
/*作者：常欣煜，马文聪，丁颖
 *******************/
int init_client()
{
    struct hostent *he;
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(LISTEN_PORT);
    //server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server.sin_zero), 8);
    if ( (serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("create socket");
        return 0;
    }

    if ( (connect(serverfd, (struct sockaddr *)(&server), sizeof(struct sockaddr))) == -1)
    {
        perror("connect");
        return 0;
    }
    printf("init_client()");
    return 1;
}

/*****************
/*名称：send_function
/*描述：向服务器发送信息
/*作成日期：2019.9.1
/*参数：const char *message
/*返回值：int
/*作者：常欣煜，马文聪，丁颖
 *******************/
int send_function(const char *message)
{
    memset(send_buffer, '\0', sizeof(send_buffer));
    strcpy(send_buffer, message);
    printf("sending message to server:\n%s\n", send_buffer);
    printf("%d", &serverfd);
    if (send(serverfd, send_buffer, BUFFER_SIZE, 0)<0)
    {

        perror("send error!");

        exit(1);

    }
}

/*****************
/*名称：recv_thread
/*描述：接收线程
/*作成日期：2019.9.1
/*参数：
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void recv_thread() {
    int numbytes;
    while(1) {
        printf("recv serverfd = %d\n", serverfd);
        memset(message_buffer, '\0', BUFFER_SIZE);
        numbytes = recv(serverfd, message_buffer, BUFFER_SIZE, 0);
        printf(" recv_thread()\n");
        printf("%s", message_buffer);
        if(numbytes == 0){
            printf("server offline.\n");
            exit(1);
        }
        if(numbytes == -1){
            perror("error receiving message\n");
            exit(1);
        }

        handle_message(message_buffer, serverfd);

    }
}

/**************************************************/
/*名称：regist
/*描述：点击注册后的回调函数
/*作成日期：2019.9.3
/*参数：
	char *username 用户名称
	char *password 用户密码
    char *email 用户邮箱
/*返回值：int 1表示登陆成功
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int regist(const char *username, const char *password ,const char *email)
{
//    init_client();
//    client_main();
    printf("regist %s %s\n", username, password);
    exec_cmd(1, 0, username, password, email, serverfd);
    return 1;
}


/**************************************************/
/*名称：login
/*描述：点击登陆后的回调函数
/*作成日期：2019.9.3
/*参数：
	char *username 用户名称
	char *password 用户密码
/*返回值：int 1表示登陆成功
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int login(int user_id, const char *password)
{
//    init_client();
//    client_main();
    printf("login %d %s\n", user_id, password);
    exec_cmd(2, user_id, NULL, password,NULL, serverfd);
    exec_cmd(7, user_id, NULL, NULL,NULL, serverfd);
    return 1;
}


/**************************************************/
/*名称：confirm_friend_callback
/*描述：加一个好友的函数
/*作成日期：2019.9.3
/*参数：VOID
/*返回值：VOID
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void confirm_friend_callback(int fid) {
    printf("confirm friend callback %d\n", fid);
    exec_cmd(6, fid, NULL, NULL, NULL, serverfd);
}

/**************************************************/
/*名称：void get_friend_list(int fid)
/*描述：
/*作成日期：2019.9.3
/*参数：VOID
/*返回值：VOID
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void get_friend_list(int fid) {
    printf("get friend list\n");
    exec_cmd(7, fid, NULL, NULL, NULL, serverfd);
}


/**************************************************/
/*名称：send_message_callback
/*描述：点击发送之后的回调函数
/*作成日期：2019.9.3
/*参数：
	char *message 发送的信息
/*返回值：VOID
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void send_message_callback(const char *message) {
    printf("send message callback %s\n", message);
    exec_cmd(4, talk_to_user, NULL, message, NULL, serverfd);
}


/**************************************************/
/*名称： get_UI_state()
/*描述： 获取当前用户的ui信息，和界面的接口
/*作成日期： 2016.8.22
/*参数：界面传递给客户端的姓名
/*返回值：
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int get_UI_state(int name) {
    talk_to_user = name;
    return talk_to_user;
}


void logout_action() {
    printf("logout_action");

    current_id = 0;
}

/**************************************************/
/*名称： main()
/*描述： 界面启动时启动
/*作成日期： 2019.9.3
/*参数：界面传递给客户端的姓名
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
void client_main()
{
    char message[BUFFER_SIZE];
    g_thread_create((GThreadFunc)recv_thread, NULL, FALSE, NULL);
    g_thread_create((GThreadFunc)auto_update_thread, NULL, FALSE, NULL);
    g_thread_create((GThreadFunc)rev_FILE_thread,NULL, FALSE, NULL);
}

/*****************
/*名称：get_formatted_time
/*描述：把系统时间改为标准时间格式
/*作成日期：2019.9.3
/*参数：
/*返回值：const char*
/*作者：常欣煜，马文聪，丁颖
 *******************/
const char *get_formatted_time(){
    time_t t = time(0);
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return timestr;
}

/*****************
/*名称：auto_update_thread
/*描述：自动更新
/*作成日期：2019.9.3
/*参数：
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void auto_update_thread() {
    while(1) {
        sleep(5);
    }
}

/*****************
/*名称：get_filename_by_path
/*描述：通过路径得到文件名
/*作成日期：2019.9.2
/*参数：char *path,char *name
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void get_filename_by_path(char *path,char *name)
{
    int path_len=strlen(path);
    int i;
    for(i=path_len-1;i>=0;i--)
    {
        if(path[i]=='/') break;
    }
    for(int j=i+1;j<path_len;j++)
    {
        name[j-i-1]=path[j];
    }
}

/*****************
/*名称：send_main
/*描述：客户端把文件发送给服务器
/*作成日期：2019.9.2
/*参数：void *target_temp
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void send_main( void *target_temp )
{  //
    struct Sock_ntop_Transform target = *(struct Sock_ntop_Transform *) target_temp;
    char * target_ip = target.ip;
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);
    client_addr.sin_port = htons(0);
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        printf("Create Socket Failed!\n");
        exit(1);
    }
    if (bind(client_socket, (struct sockaddr*)&client_addr, sizeof(client_addr)))
    {
        printf("Client Bind Port Failed!\n");
        exit(1);
    }
    struct sockaddr_in  server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if (inet_aton(target_ip, &server_addr.sin_addr) == 0)
    {
        printf("Server IP Address Error!\n");
        exit(1);
    }
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
    socklen_t server_addr_length = sizeof(server_addr);
    if (connect(client_socket, (struct sockaddr*)&server_addr, server_addr_length) < 0)
    {
        printf("Can Not Connect To %s!\n", target_ip);
        exit(1);
    }

    char file_name[FILE_NAME_MAX_SIZE + 1];
    bzero(file_name, sizeof(file_name));

    strcpy(file_name,target.position+7);//复制地址

    char buffer[FILE_BUFFER_SIZE];
    bzero(buffer, sizeof(buffer));
    strncpy(buffer, file_name, strlen(file_name) > FILE_BUFFER_SIZE ? FILE_BUFFER_SIZE : strlen(file_name));
    send(client_socket, buffer, FILE_BUFFER_SIZE, 0);
    int length = recv(client_socket, buffer, FILE_BUFFER_SIZE, 0);
    if(buffer[0] == 'O' && buffer[1] == 'K') {
        FILE *fp = fopen(file_name, "r");
        if (fp == NULL)
        {
            printf("File:\t%s Not Found!\n", file_name);
        }
        else
        {
            bzero(buffer, FILE_BUFFER_SIZE);
            int file_block_length = 0;
            while( (file_block_length = fread(buffer, sizeof(char), FILE_BUFFER_SIZE, fp)) > 0)
            {
                printf("file_block_length = %d\n", file_block_length);
                if (send(client_socket, buffer, file_block_length, 0) < 0)
                {
                    printf("Send File:\t%s Failed!\n", file_name);
                    break;
                }
                bzero(buffer, sizeof(buffer));
            }
            fclose(fp);
            printf("File:\t%s Transfer Finished!\n", file_name);
        }
        close(client_socket);
    }
    else {
        close(client_socket);
        printf("send req rej\n");
    }
}

/*****************
/*名称：client_send_file
/*描述：在界面点击发送文件时调用
/*作成日期：2019.9.2
/*参数：int sendfrom,int sendto,const char *arg2
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void client_send_file(int sendfrom,int sendto,const char *arg2)
{
    printf("........\n");
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "message/file");
    cJSON_AddNumberToObject(root, "sendto", sendto);//发给谁
    printf("=========%d==========\n",sendto);
    cJSON_AddNumberToObject(root, "sendfrom", sendfrom);//当前发送人
    cJSON_AddStringToObject(root, "sendtime", get_formatted_time());//当前时间
    cJSON_AddStringToObject(root, "content", arg2);//文件名
    send_function(cJSON_Print(root));
}


/*****************
/*名称：rev_FILE_thread
/*描述：接收文件的线程
/*作成日期：2019.9.4
/*参数：
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void rev_FILE_thread(){
   // printf("xxxxxxxxxxxxxxxxxxxxxxxx\n");
    struct sockaddr_in   server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        printf("Create Socket Failed!\n");
        exit(1);
    }

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
        printf("Server Bind Port: %d Failed!\n", HELLO_WORLD_SERVER_PORT);
        exit(1);
    }
    if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE))
    {
        printf("Server Listen Failed!\n");
        exit(1);
    }
    printf("server init ok\n");
    while(1)
    {

        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr );
        int new_server_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);
        if (new_server_socket < 0)
        {
            printf("Server Accept Failed!\n");
            break;
        }

        char buffer[FILE_BUFFER_SIZE];
        bzero(buffer, sizeof(buffer));
        length = recv(new_server_socket, buffer, FILE_BUFFER_SIZE, 0);
        if (length < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }

        char file_name[FILE_NAME_MAX_SIZE + 1];
        char path[FILE_NAME_MAX_SIZE + 1];
        char file_name_temp[FILE_NAME_MAX_SIZE + 1];
        bzero(file_name, sizeof(file_name));
        bzero(file_name_temp, sizeof(file_name_temp));
        // strncpy(file_name, buffer,
        // strlen(buffer) > FILE_NAME_MAX_SIZE ? FILE_NAME_MAX_SIZE : strlen(buffer));
        strncpy(path, buffer,
                strlen(buffer) > FILE_NAME_MAX_SIZE ? FILE_NAME_MAX_SIZE : strlen(buffer));

        get_filename_by_path(path,file_name_temp);
        strcpy(file_name,"recv_file/");
        for(int i=0;file_name_temp[i];i++)
        {
            file_name[i+10]=file_name_temp[i];
        }
        printf("file_name:%s\n",file_name);
        printf("-------------------------------\n");
        is_file_accepted();
        sleep(1);
        gdk_threads_leave();

        if(is_file_accepted_temp == -1){
            while(is_file_accepted_temp == -1);
        }
        if(is_file_accepted_temp == 0) {
            close(new_server_socket);
            is_file_accepted_temp=-1;
            printf("Rejected!\n");
            continue;
        }
        strncpy(buffer, "OK",  2);//客户端表示阔以我要接收，告诉服务器，服务器开始发送
        send(new_server_socket, buffer, FILE_BUFFER_SIZE, 0);

        FILE *fp = fopen(file_name, "w");

        bzero(buffer, sizeof(buffer));
        int length2 = 0;
        while(length2 = recv(new_server_socket, buffer, FILE_BUFFER_SIZE, 0))
        {
            if (length2 < 0)
            {
                printf("Recieve Data From Server Failed!\n");
                break;
            }

            int write_length = fwrite(buffer, sizeof(char), length2, fp);
            if (write_length < length2)
            {
                printf("File:\t%s Write Failed!\n", file_name);
                break;
            }
            bzero(buffer, FILE_BUFFER_SIZE);
        }

        printf("Recieve File:\t %s From Server Finished!\n", file_name);
        is_file_accepted_temp=-1;
        close(new_server_socket);
        fclose(fp);
    }
    close(server_socket);
}

/*****************
/*名称：is_file_accepted
/*描述：向客户确认是否接收文件
/*作成日期：2019.9.4
/*参数：
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void is_file_accepted() {
    gdk_threads_init();
    gdk_threads_enter();
    g_thread_create((GThreadFunc)is_file_accepted_window, NULL, FALSE, NULL);
}

/*****************
/*名称：buttonPressAccept
/*描述：接收
/*作成日期：2019.9.4
/*参数：GtkWidget* button,gpointer data
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void buttonPressAccept(GtkWidget* button,gpointer data)
{
    is_file_accepted_temp = 1;
    gtk_widget_destroy(GTK_WIDGET(data));
}
/*****************
/*名称：buttonPressRefuse
/*描述：拒绝
/*作成日期：2019.9.4
/*参数：GtkWidget* button,gpointer data
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void buttonPressRefuse(GtkWidget* button,gpointer data)
{
    is_file_accepted_temp = 0;
    gtk_widget_destroy(GTK_WIDGET(data));
}

/*****************
/*名称：is_file_accepted_window
/*描述：确认是否接受的弹窗
/*作成日期：2019.9.4
/*参数：
/*返回值：void
/*作者：常欣煜，马文聪，丁颖
 *******************/
void is_file_accepted_window()
{
//    is_file_accepted_temp=1;
//    //printf("你要接收该文件么？接收输入1\n");
//    //scanf("%d",&is_file_accepted_temp);;
//        printf("ssssssssssssssssssssssssssssssss%d\n",judgeFile);
//        is_file_accepted_temp = judgeFile;
    GtkWidget *judgeWindow;
    GtkWidget *judgeVbox; //存放三个控件
    GtkWidget *judgeHbox; //存放两个按钮

    GtkWidget *judgeLabel;
    GtkWidget *acceptButton;
    GtkWidget *refuseButton;

    //judgeWindow
    judgeWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (judgeWindow), g_locale_to_utf8("文件传输",-1,NULL,NULL,NULL));//窗口标题设置
    gtk_window_set_position(GTK_WINDOW(judgeWindow), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(judgeWindow,600,400);
    gtk_container_set_border_width(GTK_CONTAINER(judgeWindow), 0);

    //box
    judgeVbox = gtk_vbox_new(TRUE,20);
    judgeHbox = gtk_hbox_new(TRUE,20);

    gtk_container_add(GTK_CONTAINER(judgeWindow),judgeVbox);

    //judgeLabel
    judgeLabel = gtk_label_new("Username 向您传输了一个文件，请选择是否接收该文件。");
    gtk_box_pack_start(GTK_BOX(judgeVbox),judgeLabel,FALSE,FALSE,10);

    //button
    acceptButton = gtk_button_new_with_label("接收");
    refuseButton = gtk_button_new_with_label("拒绝");
    g_signal_connect(G_OBJECT(acceptButton),"clicked",G_CALLBACK(buttonPressAccept),judgeWindow);
    g_signal_connect(G_OBJECT(refuseButton),"clicked",G_CALLBACK(buttonPressRefuse),judgeWindow);

    gtk_box_pack_start(GTK_BOX(judgeHbox),acceptButton,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(judgeHbox),refuseButton,FALSE,FALSE,10);

    gtk_box_pack_start(GTK_BOX(judgeVbox),judgeHbox,FALSE,FALSE,10);

    gtk_widget_show_all(judgeWindow);
//    printf("----------------------------is_file_accepted_temp=%d\n",is_file_accepted_temp);
}