/**************************************************/
/*名称：group.cpp
/*描述：实现对group_数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "group.h"
#include "string"
#include "iostream"

//!!!notice: if you prepare to select something, please check out if it is void pointer!!!

/**************************************************/
/*名称：Group::connectGroupDatabase
/*描述：与group_数据表建立联系
/*作成日期： 2019/8/31
/*参数：
    参数1: 参数名称:conn_group; 参数类型: Mysql; 全局变量; 参数含义:  与group_数据表之间建立的联系;
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示连接成功  false:表示连接失败
/*作者：杨训迪
/***************************************************/
bool Group::connectGroupDatabase()
{
    mysql_init(&conn_group);
    if (mysql_real_connect(&conn_group, "localhost", "root", "20190120", "seven_chat", 0, NULL, CLIENT_FOUND_ROWS))
    {
        printf("CONNECTION SECCUSS \n");
        return true;
    }
    else
    {
        fprintf(stderr, "Connection failed \n");

        if (mysql_errno(&conn_group))
        {
            fprintf(stderr, "Connection erro %d: %sn \n", mysql_errno(&conn_group), mysql_error(&conn_group));
        }
        return false;
    }
}

/**************************************************/
/*名称：Group::groupGnameUpdate
/*描述：更改group_数据表中的g_name(群组名称)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_group; 参数类型: MYSQL;全局变量; 参数含义: 与group_数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:g_id; 参数类型: int; 输入参数; 参数含义: 群组id
    参数4：参数名称:g_name; 参数类型: char* 输入参数; 参数含义: 群组的名称
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool Group::groupGnameUpdate(int g_id, char *g_name)
{
    string q = g_name;
    q = "UPDATE group_ SET g_name = \"" + q +
        "\" WHERE g_id = " + to_string(g_id);
    const char *query = q.c_str();
    if (connectGroupDatabase())
    {
        res = mysql_query(&conn_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_group) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_group));
            mysql_close(&conn_group);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_group), mysql_error(&conn_group));
            mysql_close(&conn_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：Group::groupGintroUpdate
/*描述：更改group_数据表中的g_intro(群组的简介)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_group; 参数类型: MYSQL;全局变量; 参数含义: 与group_数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:g_id; 参数类型: int; 输入参数; 参数含义: 群组id
    参数4：参数名称:g_intro; 参数类型: char* 输入参数; 参数含义: 群组的简介
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool Group::groupGintroUpdate(int g_id, char *g_intro)
{
    string q = g_intro;
    q = "UPDATE group_ SET g_intro = \"" + q +
        "\" WHERE g_id = " + to_string(g_id);
    const char *query = q.c_str();
    if (connectGroupDatabase())
    {
        res = mysql_query(&conn_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_group) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_group));
            mysql_close(&conn_group);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_group), mysql_error(&conn_group));
            mysql_close(&conn_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：Group::groupGadminIdUpdate
/*描述：更改group_数据表中的g_admin_id(群组的管理员id)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_group; 参数类型: MYSQL;全局变量; 参数含义: 与group_数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:g_id; 参数类型: int; 输入参数; 参数含义: 群组id
    参数4：参数名称:g_admin_id; 参数类型: int 输入参数; 参数含义: 群组的管理员id
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool Group::groupGadminIdUpdate(int g_id, int g_admin_id)
{
    string q = "UPDATE group_ SET g_admin_id = " + to_string(g_admin_id) +
               " WHERE g_id = " + to_string(g_id);
    const char *query = q.c_str();
    if (connectGroupDatabase())
    {
        res = mysql_query(&conn_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_group) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_group));
            mysql_close(&conn_group);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_group), mysql_error(&conn_group));
            mysql_close(&conn_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：Group::groupGnumUpdate
/*描述：更改group_数据表中的g_num(群组的总人数)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_group; 参数类型: MYSQL;全局变量; 参数含义: 与group_数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:g_id; 参数类型: int; 输入参数; 参数含义: 群组id
    参数4：参数名称:g_num; 参数类型: int 输入参数; 参数含义: 群组的总人数
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool Group::groupGnumUpdate(int g_id, int g_num)
{
    string q = "UPDATE group_ SET g_num =" + to_string(g_num) +
               " WHERE g_id = " + to_string(g_id);
    const char *query = q.c_str();
    if (connectGroupDatabase())
    {
        res = mysql_query(&conn_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_group) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_group));
            mysql_close(&conn_group);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_group), mysql_error(&conn_group));
            mysql_close(&conn_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：Group::groupGiconUpdate
/*描述：更改group_数据表中的g_icon(群组头像)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_group; 参数类型: MYSQL;全局变量; 参数含义: 与group_数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:g_id; 参数类型: int; 输入参数; 参数含义: 群组id
    参数4：参数名称:g_icon; 参数类型: char* 输入参数; 参数含义: 群组头像
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool Group::groupGiconUpdate(int g_id, char *g_icon)
{
    string q = g_icon;
    q = "UPDATE group_ SET g_icon = \"" + q +
        "\" WHERE g_id = " + to_string(g_id);
    const char *query = q.c_str();
    if (connectGroupDatabase())
    {
        res = mysql_query(&conn_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_group) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_group));
            mysql_close(&conn_group);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_group), mysql_error(&conn_group));
            mysql_close(&conn_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：Group::groupeInsert
/*描述：建群
/*作成日期：2019-9-1
/*参数：
    参数1： 参数名称:conn_group; 参数类型: MYSQL;全局变量; 参数含义: 与group_数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称 g_admin_id、参数类型 int、输入参数、参数含义：群主id
    参数4：参数名称 g_name、参数类型 char *、输入参数、参数含义：群名称
    参数5：参数名称 g_intro、参数类型 char *、输入参数、参数含义：群介绍
/*返回值：BOOL、是否插入成功
/*作者：李可
/***************************************************/

bool Group::groupeInsert(int g_admin_id, char *g_name, char *g_intro, char *g_icon)
{
    char sql_insert[2048];
    sprintf(sql_insert, "insert into group_ (g_admin_id,g_name,g_intro,g_icon,g_num) values (\'%d\', \'%s\',\'%s\',\'%s\',\'%d\')", g_admin_id, g_name, g_intro, g_icon, 1);
    if (connectGroupDatabase())
    {
        res = mysql_query(&conn_group, sql_insert); //执行SQL语句
        if (!res && (unsigned long)mysql_affected_rows(&conn_group) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_group));
            mysql_close(&conn_group);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_group), mysql_error(&conn_group));
            mysql_close(&conn_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：groupDelete
/*描述：解散群
/*作成日期：2019-9-1
/*参数：参数1：参数名称 gid、参数类型 int、输入参数、参数含义：群id
/*返回值：BOOL、是否删除成功
/*作者：李可
/***************************************************/
bool Group::groupDelete(int g_id)
{
    string q = "delete from group_ where g_id=" + to_string(g_id);
    const char *query = q.c_str();
    if (connectGroupDatabase())
    {
        res = mysql_query(&conn_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_group) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_group));
            mysql_close(&conn_group);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_group), mysql_error(&conn_group));
            mysql_close(&conn_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：groupGidSelect
/*描述：根据群名称获取群I
/*作成日期：2019-9-1
/*参数：参数1：参数名称 g_name、参数类型 char*、输入参数、参数含义：群名称
/*返回值：BOOL、是否成功赋值
/*作者：邵雨洁
/***************************************************/
bool Group::groupGidSelect(char g_name[])
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag, id;
    char *ans;
    char *query;
    //连接数据库
    if (connectGroupDatabase())
    {
        string q = g_name;
        q = "select g_id from group_ where g_name=\"" + q + "\"";
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_group, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return false;
        }
        else
        { /*如果查询成功*/
            printf("[select g_id from group_ where g_name=%s] made...\n", g_name);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_group);
            /*mysql_fetch_row检索结果集的下一行*/
            int t = 1;
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                gnameIDlist[t] = atoi(row[0]);
                t = t + 1;
            }
            gnameIDlist[0] = t - 1;
        }
        mysql_close(&conn_group);
        return true;
    }
}

/**************************************************/
/*名称：groupGnumSelect
/*描述：根据群ID获取群人数
/*作成日期：2019-9-1
/*参数：参数1：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
/*返回值：int、含义：返回该群的总人数
/*作者：邵雨洁
/***************************************************/
int Group::groupGnumSelect(int g_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag, num;
    char *ans;
    char *query;
    //连接数据库
    if (connectGroupDatabase())
    {
        string q = "select g_num from group_ where g_id=" + to_string(g_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_group, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return 0;
        }
        else
        { /*如果查询成功*/
            printf("[select g_id from group_ where g_id=%d] made...\n", g_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_group);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_group);
        num = atoi(ans);
        return num;
    }
}

/**************************************************/
/*名称：groupGadminidSelect
/*描述：根据群ID获取群主ID
/*作成日期：2019-9-1
/*参数：参数1：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
/*返回值：int、含义：返回该群的群主ID
/*作者：邵雨洁
/***************************************************/
int Group::groupGadminidSelect(int g_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag, admin_id;
    char *ans;
    char *query;
    //连接数据库
    if (connectGroupDatabase())
    {
        string q = "select g_admin_id from group_ where g_id=" + to_string(g_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_group, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return 0;
        }
        else
        { /*如果查询成功*/
            printf("[select g_admin_id from group_ where g_id=%d] made...\n", g_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_group);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_group);
        admin_id = atoi(ans);
        return admin_id;
    }
}

/**************************************************/
/*名称：roupGnoticeSelect
/*描述：根据群ID获取群公告
/*作成日期：2019-9-1
/*参数：参数1：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
/*返回值：char*、含义：返回该群的公告
/*作者：邵雨洁
/***************************************************/
char *Group::groupGnoticeSelect(int g_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans = NULL;
    char *query;
    //连接数据库
    if (connectGroupDatabase())
    {
        string q = "select g_notice from group_ where g_id=" + to_string(g_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_group, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return ans;
        }
        else
        { /*如果查询成功*/
            printf("[select g_notice from group_ where g_id=%d] made...\n", g_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_group);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_group);
        return ans;
    }
}

/**************************************************/
/*名称：groupGintroSelect
/*描述：根据群ID获取群简介
/*作成日期：2019-9-1
/*参数：参数1：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
/*返回值：char*、含义：返回该群的简介
/*作者：邵雨洁
/***************************************************/
char *Group::groupGintroSelect(int g_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans = NULL;
    char *query;
    //连接数据库
    if (connectGroupDatabase())
    {
        string q = "select g_intro from group_ where g_id=" + to_string(g_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_group, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return ans;
        }
        else
        { /*如果查询成功*/
            printf("[select g_intro from group_ where g_id=%d] made...\n", g_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_group);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_group);
        return ans;
    }
}

/**************************************************/
/*名称：groupGtimeSelect
/*描述：根据群ID获取群建立时间
/*作成日期：2019-9-1
/*参数：参数1：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
/*返回值：char*、含义：返回该群的建立时间
/*作者：邵雨洁
/***************************************************/
char *Group::groupGtimeSelect(int g_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans = NULL;
    char *query;
    //连接数据库
    if (connectGroupDatabase())
    {
        string q = "select g_time from group_ where g_id=" + to_string(g_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_group, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return ans;
        }
        else
        { /*如果查询成功*/
            printf("[select g_time from group_ where g_id=%d] made...\n", g_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_group);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_group);
        return ans;
    }
}

/**************************************************/
/*名称：groupGnameSelect
/*描述：根据群ID获取群名称
/*作成日期：2019-9-1
/*参数：参数1：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
/*返回值：char*、含义：返回该群的名称
/*作者：邵雨洁
/***************************************************/
char *Group::groupGnameSelect(int g_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans = NULL;
    char *query;
    //连接数据库
    if (connectGroupDatabase())
    {
        string q = "select g_name from group_ where g_id=" + to_string(g_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_group, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return ans;
        }
        else
        { /*如果查询成功*/
            printf("[select g_name from group_ where g_id=%d] made...\n", g_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_group);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_group);
        return ans;
    }
}

/**************************************************/
/*名称：groupGiconSelect
/*描述：根据群ID获取群头像地址
/*作成日期：2019-9-1
/*参数：参数1：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
/*返回值：char*、含义：返回该群头像地址
/*作者：邵雨洁
/***************************************************/
char *Group::groupGiconSelect(int g_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans = NULL;
    char *query;
    //连接数据库
    if (connectGroupDatabase())
    {
        string q = "select g_icon from group_ where g_id=" + to_string(g_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_group, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return ans;
        }
        else
        { /*如果查询成功*/
            printf("[select g_icon from group_ where g_id=%d] made...\n", g_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_group);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_group);
        return ans;
    }
}



//int main()
//{
//
//    Group G;
//    printf("IDg_id的检查");
//    char group[] = "yayoo";
//    if (G.groupGidSelect(group))
//        printf("%d %d %d\n", G.gnameIDlist[0], G.gnameIDlist[1], G.gnameIDlist[2]);
//    printf("人数g_num的检查");
//    cout << G.groupGnumSelect(1) << endl;
//    printf("群主g_admin_id的检查");
//    cout << G.groupGadminidSelect(1) << endl;
//    //printf("公告g_notice的检查");
//    //cout << G.groupGnoticeSelect(1) << endl;
//    //printf("简介g_intro的检查");
//    //cout << G.groupGintroSelect(1) << endl;
//    printf("建立时间g_time的检查");
//    cout << G.groupGtimeSelect(1) << endl;
//    printf("名称g_name的检查");
//    cout << G.groupGnumSelect(1) << endl;
//}
