/**************************************************/
/*名称：friends.cpp
/*描述：实现对friends数据表的有关操作
/*作成日期： 2019/9/01
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "friends.h"

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

bool Friends::friendsInsert(int u_id, int f_id, const char *f_name, int s_id)
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

/**************************************************/
/*名称：Friends::ffriendsFnameSelect
/*描述：根据双方id查询好友昵称
/*作成日期：2019-9-1
/*参数：
	参数1： 参数名称:conn_friends; 参数类型: MYSQL;全局变量; 参数含义: 与friends数据表之间建立的联系;
	参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
	参数3：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	参数4：参数名称 f_id、参数类型 int、输入参数、参数含义：好友id
/*返回值：char*、含义：返回昵称，没查到返回NULL
/*作者：邵雨洁
/***************************************************/
const char *Friends::friendsFnameSelect(int u_id, int f_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans;
    char *query;
    if (connectFriendsDatabase())
    {
        string q = "select f_name from friends where u_id=" + to_string(u_id) + " and f_id=" + to_string(f_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_friends, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return 0;
        }
        else
        { /*如果查询成功*/
            printf("[select f_name from friends where u_id=%d  and f_id=%d] made...\n", u_id, f_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_friends);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_friends);
        return ans;
    }
}

/*根据双方 id查询好友所属分组id*/
/**************************************************/
/*名称：Friends::friendsFsectionidSelect
/*描述：根据双方id查询好友的分组id
/*作成日期：2019-9-1
/*参数：
	参数1： 参数名称:conn_friends; 参数类型: MYSQL;全局变量; 参数含义: 与friends数据表之间建立的联系;
	参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
	参数3：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	参数4：参数名称 f_id、参数类型 int、输入参数、参数含义：好友id
/*返回值：char*、含义：返回昵称，没查到返回NULL
/*作者：邵雨洁
/***************************************************/
int Friends::friendsFsectionidSelect(int u_id, int f_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    int ans;
    char *query;
    if (connectFriendsDatabase())
    {
        string q = "select group_id from friends where u_id=" + to_string(u_id) + " and f_id=" + to_string(f_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_friends, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return 0;
        }
        else
        { /*如果查询成功*/
            printf("[select group_id from Friends where u_id=%d  and f_id=%d] made...\n", u_id, f_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_friends);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = atoi(row[0]);
            }
        }
        mysql_close(&conn_friends);
        return ans;
    }
}

/**************************************************/
/*名称：Friends::friendsFlistSelec
/*描述：传入u_id,查询u_id的所有好友的id,将其填入friendsList[0]表示一共有多少个好友
/*作成日期：2019-9-1
/*参数：
	参数1： 参数名称:conn_friends; 参数类型: MYSQL;全局变量; 参数含义: 与friends数据表之间建立的联系;
	参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
	参数3：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	参数4：参数名称 friendslist、参数类型 int、全局变量、参数含义：[0]:好友数，[1...]好友id列表
/*返回值：bool、含义：true:赋值成功 false:赋值失败
/*作者：邵雨洁
/***************************************************/
bool Friends::friendsFlistSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ansch;
    char *query;
    if (connectFriendsDatabase())
    {
        string q = "select f_id from friends where u_id=" + to_string(u_id)+" ORDER BY f_time ASC";
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_friends, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            friendslist[0] = -1;
            return false;
        }
        else
        { /*如果查询成功*/
            printf("[select f_id from friends where u_id=%d ] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_friends);
            /*mysql_fetch_row检索结果集的下一行*/
            int t = 1;
            while (row = mysql_fetch_row(res_ptr))
            { /*printf ("%s\t ", row[0]); */
                ansch = row[0];
                /*转换成int型*/
                friendslist[t] = atoi(ansch);
                t = t + 1;
            }
            friendslist[0] = t - 1;
        }
        /*printf("\n人数：%d\n",ans[0]);*/
        /*printf("ans[1]=%d  ans[2]=%d  ",ans[1],ans[2]);*/
        mysql_close(&conn_friends);
        return true;
    }
}

//描述：根据用户和分组id查询所有组员id
bool Friends::friendsSMidSelect(int u_id, int s_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ansch;
    char *query;
    if (connectFriendsDatabase())
    {
        string q = "select f_id from friends where u_id=" + to_string(u_id) + " and s_id=" + to_string(s_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_friends, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            SMList[0] = -1;
            return false;
        }
        else
        { /*如果查询成功*/
            printf("[select f_id from friends where u_id=%d ] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_friends);
            /*mysql_fetch_row检索结果集的下一行*/
            int t = 1;
            while (row = mysql_fetch_row(res_ptr))
            { //printf ("%s\t ", row[0]);
                ansch = row[0];
                /*转换成int型*/
                SMList[t] = atoi(ansch);
                t = t + 1;
            }
            SMList[0] = t - 1;
        }
        /*printf("\n人数：%d\n",ans[0]);*/
        /*printf("ans[1]=%d  ans[2]=%d  ",ans[1],ans[2]);*/
        mysql_close(&conn_friends);
        return true;
    }
}

