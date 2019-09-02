/**************************************************/
/*名称：friends.cpp
/*描述：实现对friends数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "include/friends.h"
#include "string"

/**************************************************/
/*名称：Friends::connectFriendsDatabase()
/*描述：与friends数据表建立联系
/*作成日期： 2019/8/31                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
/*参数： 
    参数1: 参数名称:conn_friends; 参数类型: Mysql; 全局变量; 参数含义:  与friends数据表之间建立的联系;
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示连接成功  false:表示连接失败
/*作者：杨训迪
/***************************************************/
bool Friends::connectFriendsDatabase()
{
    mysql_init(&conn_friends);
    if (mysql_real_connect(&conn_friends, "localhost", "root", "20190120", "seven_chat", 0, NULL, CLIENT_FOUND_ROWS))
    {
        printf("CONNECTION SECCUSS \n");
        return true;
    }
    else
    {
        fprintf(stderr, "Connection failed \n");

        if (mysql_errno(&conn_friends))
        {
            fprintf(stderr, "Connection erro %d: %sn \n", mysql_errno(&conn_friends), mysql_error(&conn_friends));
        }
        return false;
    }
}

/**************************************************/
/*名称：Friends::friendsFnameUpdate
/*描述：更改friends数据表中的f_name(好友的昵称)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_friends; 参数类型: MYSQL;全局变量; 参数含义: 与friends数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 当前用户id
    参数4：参数名称:f_id; 参数类型: int; 输入参数; 参数含义: 当前用户朋友的id
    参数5：参数名称:f_name; 参数类型: char*; 输入参数; 参数含义: 当前用户设置该朋友的昵称
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool Friends::friendsFnameUpdate(int u_id, int f_id, char f_name[])
{
    string q = f_name;
    q = "UPDATE friends SET f_name = \"" + q +
        "\" WHERE u_id = " + to_string(u_id) + " AND f_id = " + to_string(f_id);
    const char *query = q.c_str();
    if (connectFriendsDatabase())
    {
        res = mysql_query(&conn_friends, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_friends) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_friends));
            mysql_close(&conn_friends);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_friends), mysql_error(&conn_friends));
            mysql_close(&conn_friends);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：Friends::friendsSidUpdate
/*描述：更改friends数据表中的f_name(好友的昵称)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_friends; 参数类型: MYSQL;全局变量; 参数含义: 与friends数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 当前用户id
    参数4：参数名称:f_id; 参数类型: int; 输入参数; 参数含义: 当前用户朋友的id
    参数5：参数名称:s_id; 参数类型: int; 输入参数; 参数含义: 当前用户设置该朋友的分组id
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool Friends::friendsSidUpdate(int u_id, int f_id, int s_id)
{
    string q = "UPDATE friends SET s_id = \"" + to_string(s_id) +
               "\" WHERE u_id = " + to_string(u_id) + " AND f_id = " + to_string(f_id);
    const char *query = q.c_str();
    if (connectFriendsDatabase())
    {
        res = mysql_query(&conn_friends, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_friends) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_friends));
            mysql_close(&conn_friends);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_friends), mysql_error(&conn_friends));
            mysql_close(&conn_friends);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：friendsInsert
/*描述：添加好友
/*作成日期：2019-9-1
/*参数：
    参数1： 参数名称:conn_friends; 参数类型: MYSQL;全局变量; 参数含义: 与friends数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称 f_id、参数类型 int、输入参数、参数含义：好友id
    参数4：参数名称 fname、参数类型 char *、输入参数、参数含义：好友备注
    参数5：参数名称 s_id、参数类型 int、输入参数、参数含义：好友分组
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：李可
/***************************************************/

bool Friends::friendsInsert(int u_id, int f_id, char *f_name, int s_id)
{
    char query[2048];
    sprintf(query, "insert into friends(u_id,f_id,f_name,s_id) values(\'%d\', \'%d\',\'%s\',\'%d\')", u_id, f_id, f_name, s_id);
    if (connectFriendsDatabase())
    {
        res = mysql_query(&conn_friends, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_friends) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_friends));
            mysql_close(&conn_friends);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_friends), mysql_error(&conn_friends));
            mysql_close(&conn_friends);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：Friends::friendsDelete
/*描述：删除好友
/*作成日期：2019-9-1
/*参数：
    参数1： 参数名称:conn_friends; 参数类型: MYSQL;全局变量; 参数含义: 与friends数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
    参数4：参数名称 f_id、参数类型 int、输入参数、参数含义：好友id
/*返回值：BOOL、是否删除成功
/*作者：李可
/***************************************************/
bool Friends::friendsDelete(int u_id, int f_id)
{
    string q = "delete from friends where u_id=" + to_string(u_id) + " and f_id=" + to_string(f_id);
    const char *query = q.c_str();
    if (connectFriendsDatabase())
    {
        res = mysql_query(&conn_friends, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_friends) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_friends));
            mysql_close(&conn_friends);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_friends), mysql_error(&conn_friends));
            mysql_close(&conn_friends);
            return false;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    Friends f1;
    f1.friendsInsert(1,2,"xx",1);
}
