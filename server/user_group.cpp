/**************************************************/
/*名称：user_group.cpp
/*描述：实现对user数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/
#include "include/user_group.h"
#include "string"

/**************************************************/
/*名称：UserGroup::connectUserGroupDatabase
/*描述：与user_group数据表建立联系
/*作成日期： 2019/8/31                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
/*参数： 
    参数1: 参数名称:conn_user_group; 参数类型: MYSQL; 全局变量; 参数含义:  与user_group数据表之间建立的联系;
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示连接成功  false:表示连接失败
/*作者：杨训迪
/***************************************************/
bool UserGroup::connectUserGroupDatabase()
{
    mysql_init(&conn_user_group);
    if (mysql_real_connect(&conn_user_group, "localhost", "root", "20190120", "seven_chat", 0, NULL, CLIENT_FOUND_ROWS))
    {
        printf("CONNECTION SECCUSS \n");
        return true;
    }
    else
    {
        fprintf(stderr, "Connection failed \n");

        if (mysql_errno(&conn_user_group))
        {
            fprintf(stderr, "Connection erro %d: %sn \n", mysql_errno(&conn_user_group), mysql_error(&conn_user_group));
        }
        return false;
    }
}

/**************************************************/
/*名称：UserGroup::userGroupUGnameUpdate
/*描述：更改user_group数据表中的ug_name(群组中用户的备注名)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user_group; 参数类型: MYSQL;全局变量; 参数含义: 与user_group数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:ug_id; 参数类型: int; 输入参数; 参数含义: 群组中用户的id
    参数4：参数名称:g_id; 参数类型: int; 输入参数; 参数含义: 群组id
    参数5：参数名称:ug_name; 参数类型: char*; 输入参数; 参数含义: 群组中用户的备注名
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool UserGroup::userGroupUGnameUpdate(int ug_id, int g_id, char *ug_name)
{
    string q = ug_name;
    q = "UPDATE user_group SET ug_name = \"" + q +
        "\" WHERE ug_id = " + to_string(ug_id) + " AND g_id = " + to_string(g_id);
    const char *query = q.c_str();
    if (connectUserGroupDatabase())
    {
        res = mysql_query(&conn_user_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user_group) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user_group));
            mysql_close(&conn_user_group);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_user_group), mysql_error(&conn_user_group));
            mysql_close(&conn_user_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：UserGroup::userGroupUGstatusUpdate
/*描述：更改user_group数据表中的ug_status(群组中用户的身份)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user_group; 参数类型: MYSQL;全局变量; 参数含义: 与user_group数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:ug_id; 参数类型: int; 输入参数; 参数含义: 群组中用户的id
    参数4：参数名称:g_id; 参数类型: int; 输入参数; 参数含义: 群组id
    参数5：参数名称:ug_status; 参数类型: char*; 输入参数; 参数含义: 群组中用户的身份
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool UserGroup::userGroupUGstatusUpdate(int ug_id, int g_id, int ug_status)
{
    string q = "UPDATE user_group SET ug_status = \"" + to_string(ug_status) +
               "\" WHERE ug_id = " + to_string(ug_id) + " AND g_id = " + to_string(g_id);
    const char *query = q.c_str();
    if (connectUserGroupDatabase())
    {
        res = mysql_query(&conn_user_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user_group) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user_group));
            mysql_close(&conn_user_group);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_user_group), mysql_error(&conn_user_group));
            mysql_close(&conn_user_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：UserGroup::userGroupInsert
/*描述：加群
/*作成日期：2019-9-1
/*参数：参数1：参数名称 ug_id、参数类型 int、输入参数、参数含义：用户id
       参数2：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
       参数3：参数名称 ug_name、参数类型 char *、输入参数、参数含义：群昵称
       参数4：参数名称 ug_status、参数类型 int、输入参数、参数含义：群组中用户的身份
       参数5： 参数名称:conn_user_group; 参数类型: MYSQL;全局变量; 参数含义: 与user_group数据表之间建立的联系;
       参数6：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功   
/*返回值：BOOL、是否插入成功
/*作者：李可
/***************************************************/

bool UserGroup::userGroupInsert(int ug_id, int g_id, char *ug_name, int ug_status)
{
    int ret;
    char sql_insert[2048];
    sprintf(sql_insert, "insert into UserGroup (ug_id,g_id,ug_name,ug_status) values (\'%d\', \'%d\',\'%s\',\'%d\')", ugid, gid, ugname, ugstatus);
    if (connectUserGroupDatabase())
    {
        res = mysql_query(&conn_user_group, sql_insert);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user_group) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user_group));
            mysql_close(&conn_user_group);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_user_group), mysql_error(&conn_user_group));
            mysql_close(&conn_user_group);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称： UserGroup::userGroupDelete(int ug_id,int g_id)
/*描述：退群
/*作成日期：2019-9-1
/*参数：参数1：参数名称 ug_id、参数类型 int、输入参数、参数含义：用户id
       参数2：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
       参数3： 参数名称:conn_user_group; 参数类型: MYSQL;全局变量; 参数含义: 与user_group数据表之间建立的联系;
       参数4：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功   
/*作者：李可
/***************************************************/

bool UserGroup::userGroupDelete(int ug_id, int g_id)
{
    string q = "delete from UserGroup where ug_id=" + to_string(ug_id) + " and g_id=" + to_string(g_id);
    const char *query = q.c_str();
    if (connectUserGroupDatabase())
    {
        res = mysql_query(&conn_user_group, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user_group) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user_group));
            mysql_close(&conn_user_group);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_user_group), mysql_error(&conn_user_group));
            mysql_close(&conn_user_group);
            return false;
        }
    }
    return false;
}
