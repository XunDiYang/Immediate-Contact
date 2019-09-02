/**************************************************/
/*名称：gmessage.cpp
/*描述：实现对gmessage数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "include/gmessage.h"
#include "string"

/**************************************************/
/*名称：Group::connectGmessageDatabase
/*描述：与gmessage数据表建立联系
/*作成日期： 2019/8/31                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
/*参数： 
    参数1: 参数名称:conn_gmessage; 参数类型: Mysql; 全局变量; 参数含义:  与group_数据表之间建立的联系;
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示连接成功  false:表示连接失败
/*作者：杨训迪
/***************************************************/
bool Gmessage::connectGmessageDatabase()
{
    mysql_init(&conn_gmessage);
    if (mysql_real_connect(&conn_gmessage, "localhost", "root", "20190120", "seven_chat", 0, NULL, CLIENT_FOUND_ROWS))
    {
        printf("CONNECTION SECCUSS \n");
        return true;
    }
    else
    {
        fprintf(stderr, "Connection failed \n");

        if (mysql_errno(&conn_gmessage))
        {
            fprintf(stderr, "Connection erro %d: %sn \n", mysql_errno(&conn_gmessage), mysql_error(&conn_gmessage));
        }
        return false;
    }
}

/**************************************************/
/*名称：gmessageInsert
/*描述：发送群消息记录
/*作成日期：2019-9-1
/*参数：
    参数1： 参数名称:conn_gmessage; 参数类型: MYSQL;全局变量; 参数含义: 与gmessage数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称 gm_id、参数类型 int、输入参数、参数含义：用户id
    参数4：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
    参数5：参数名称 gm_type、参数类型 int、输入参数、参数含义：消息类别
    参数6：参数名称 detail、参数类型 char *、输入参数、参数含义：消息内容
/*返回值：BOOL、是否插入成功
/*作者：李可
/***************************************************/
bool Gmessage::gmessageInsert(int gm_id, int g_id, int gm_type, char *detail,int owner)
{
    char sql_insert[2048];
    sprintf(sql_insert, "insert into GMessage (gm_id,g_id,gm_type,detail,owner) values (\'%d\', \'%d\',\'%d\',\'%s\')", gm_id, g_id, gm_type, detail);
    if (connectGmessageDatabase())
    {
        res = mysql_query(&conn_gmessage, sql_insert); //执行SQL语句
        if (!res && (unsigned long)mysql_affected_rows(&conn_gmessage) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_gmessage));
            mysql_close(&conn_gmessage);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_gmessage), mysql_error(&conn_gmessage));
            mysql_close(&conn_gmessage);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：gmessage_delete
/*描述：删除群消息 
/*作成日期：2019-9-1 
/*参数： 
    参数1： 参数名称:conn_gmessage; 参数类型: MYSQL;全局变量; 参数含义: 与gmessage数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称 gm_id、参数类型 int、输入参数、参数含义：用户id
    参数4：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
    参数5：参数名称 gm_time、参数类型 char *、输入参数、参数含义：群消息发送时间
/*返回值：BOOL、是否删除成功
/*作者：李可
/***************************************************/

bool Gmessage::gmessageDelete(int gm_id, int g_id, char *gm_time)
{
    string q = gm_time;
    q = "delete from GMessage where gm_id=" + to_string(gm_id) + " and g_id=" + to_string(g_id) + " and gm_time between " + "'" + q + ".000" + "'" + " and " + "'" + q + ".999" + "'";
    const char *query = q.c_str();
    if (connectGmessageDatabase())
    {
        res = mysql_query(&conn_gmessage, query); //执行SQL语句
        if (!res && (unsigned long)mysql_affected_rows(&conn_gmessage) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_gmessage));
            mysql_close(&conn_gmessage);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_gmessage), mysql_error(&conn_gmessage));
            mysql_close(&conn_gmessage);
            return false;
        }
    }
    return false;
}
