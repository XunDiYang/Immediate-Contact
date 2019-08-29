#include<stdlib.h>
#include<stdio.h>
#include<mysql/mysql.h>

void user_register(struct client_property *prop, char *passwd ,char *name) {
    MYSQL *conn_ptr;
    conn_ptr = mysql_init(NULL);//初始化
    conn_ptr = mysql_real_connect(conn_ptr, "localhost", "root", "lk19991023", "chat_lib", 0, NULL,
                                  0);//连接MySQL chat_lib数据库
    if (conn_ptr) {
        printf("Connection Succeed!\n");
        ret = mysql_query(conn_ptr, "INSERT INTO User(u_passwd,u_name) VALUES(passwd,name)");
    } else printf("Connection Failed!\n");
}

