/**************************************************/
/*名称：group.cpp
/*描述：实现对group_数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "include/group.h"
#include "string"

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
/*名称：Group::groupGiconUpdat
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
    sprintf(sql_insert, "insert into Groupe (g_adminid,g_name,g_intro,g_icon) values (\'%d\', \'%s\',\'%s\',\'%s\')", g_admin_id, g_name, g_intro, g_icon);
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
    string q = "delete from Groupe where g_id=" + to_string(g_id);
    const char *query = q.c_str();
    res = mysql_query(&conn_group, query); //执行SQL语句
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