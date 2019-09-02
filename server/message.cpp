/**************************************************/
/*名称：message.cpp
/*描述：实现对message数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "include/message.h"
#include "string"

/**************************************************/
/*名称：Message::connectMessageDatabase
/*描述：与message数据表建立联系
/*作成日期： 2019/8/31                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
/*参数： 
    参数1: 参数名称:conn_message; 参数类型: Mysql; 全局变量; 参数含义:  与message数据表之间建立的联系;
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示连接成功  false:表示连接失败
/*作者：杨训迪
/***************************************************/
bool Message::connectMessageDatabase()
{
    mysql_init(&conn_message);
    if (mysql_real_connect(&conn_message, "localhost", "root", "20190120", "seven_chat", 0, NULL, CLIENT_FOUND_ROWS))
    {
        printf("CONNECTION SECCUSS \n");
        return true;
    }
    else
    {
        fprintf(stderr, "Connection failed \n");

        if (mysql_errno(&conn_message))
        {
            fprintf(stderr, "Connection erro %d: %sn \n", mysql_errno(&conn_message), mysql_error(&conn_message));
        }
        return false;
    }
}

/**************************************************/
/*名称：messageInsert
/*描述：记录发送消息
/*作成日期：2019-9-1
/*参数：
    参数1：参数名称 u_id、参数类型 char *、输入参数、参数含义：用户名称
    参数2：参数名称 f_id、参数类型 int、输入参数、参数含义：用户密码
    参数3：参数名称 owner、参数类型 int、输入参数、参数含义：消息发送者
    参数4：参数名称 m_status、参数类型 int、输入参数、参数含义：信息是否已读
    参数5：参数名称 m_type、参数类型 int、输入参数、参数含义：信息类别
    参数6：参数名称 detail、参数类型 char *、输入参数、参数含义：信息内容
    参数1： 参数名称:conn_message; 参数类型: MYSQL;全局变量; 参数含义: 与message数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
/*返回值：BOOL、是否插入成功
/*作者：李可
/***************************************************/

bool Message::messageInsert(int u_id, int f_id, int m_status, int m_type, char *detail)
{
    char sql_insert[2048];
    sprintf(sql_insert, "insert into message (u_id,f_id,owner,m_status,m_type,detail) values (\'%d\', \'%d\',\'%d\',\'%d\',\'%d\',\'%s\')", u_id, f_id, u_id, 1, m_type, detail);
    sprintf(sql_insert, "insert into message (u_id,f_id,owner,m_status,m_type,detail) values (\'%d\', \'%d\',\'%d\',\'%d\',\'%d\',\'%s\')", f_id, u_id, f_id, m_status, m_type, detail);
    if (connectMessageDatabase())
    {
        res = mysql_query(&conn_message, sql_insert); //执行SQL语句
        if (!res && (unsigned long)mysql_affected_rows(&conn_message) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_message));
            mysql_close(&conn_message);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_message), mysql_error(&conn_message));
            mysql_close(&conn_message);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：messageDelete
/*描述：删除消息
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
       参数2：参数名称 f_id、参数类型 int、输入参数、参数含义：好友id
       参数3：参数名称：m_time、参数类型 char *、输入参数、参数含义：消息发送的时间
/*返回值：BOOL、是否删除成功
/*作者：李可
/***************************************************/

bool Message::messageDelete(int u_id, int f_id, char *m_time)
{
    string q = m_time;
    q = "delete from Message where u_id=" + to_string(u_id) + " and f_id=" + to_string(f_id) + " and m_time between " + "'" + q + ".000" + "'" + " and " + "'" + q + ".999" + "'";
    const char *query = q.c_str();
    if (connectMessageDatabase())
    {
        res = mysql_query(&conn_message, query); //执行SQL语句
        if (!res && (unsigned long)mysql_affected_rows(&conn_message) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_message));
            mysql_close(&conn_message);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_message), mysql_error(&conn_message));
            mysql_close(&conn_message);
            return false;
        }
    }
    return false;
}
