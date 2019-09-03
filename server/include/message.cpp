/**************************************************/
/*名称：message.cpp
/*描述：实现对message数据表的有关操作
/*作成日期： 2019/9/2
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "message.h"

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
    参数5：参数名称 m_type、参数类型 int、输入参数、参数含义：信息类别 0:text 1:picture 2:file
    参数6：参数名称 detail、参数类型 char *、输入参数、参数含义：信息内容
    参数1： 参数名称:conn_message; 参数类型: MYSQL;全局变量; 参数含义: 与message数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
/*返回值：BOOL、是否插入成功
/*作者：李可
/***************************************************/

bool Message::messageInsert(int u_id, int f_id, int m_status, int m_type, char *detail)
{
    char sql_insert1[2048];
    char sql_insert2[2048];
    sprintf(sql_insert1, "insert into message (u_id,f_id,owner,m_status,m_type,detail) values (\'%d\', \'%d\',\'%d\',\'%d\',\'%d\',\'%s\')", u_id, f_id, u_id, 1, m_type, detail);
    sprintf(sql_insert2, "insert into message (u_id,f_id,owner,m_status,m_type,detail) values (\'%d\', \'%d\',\'%d\',\'%d\',\'%d\',\'%s\')", u_id, f_id, f_id, m_status, m_type, detail);
    if (connectMessageDatabase())
    {
        res = mysql_query(&conn_message, sql_insert1); //执行SQL语句
        res = mysql_query(&conn_message, sql_insert2); //执行SQL语句
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
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：发送者id
       参数2：参数名称 f_id、参数类型 int、输入参数、参数含义：接收者id
       参数3：参数名称：m_time、参数类型 char *、输入参数、参数含义：消息发送的时间
/*返回值：BOOL、是否删除成功
/*作者：李可
/***************************************************/

bool Message::messageDelete(int u_id, int f_id, char *m_time)
{
    string q = m_time;
    q = "delete from message where u_id=" + to_string(u_id) + " and f_id=" + to_string(f_id) + " and m_time between " + "'" + q + ".000" + "'" + " and " + "'" + q + ".999" + "'";
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


/**************************************************/
/*名称：messageSelect
/*描述：输入两个人id ,将查询到的消息保存到结构体中，按时间顺序，最新的在前面，num为一共有多少条消息
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	    参数2：参数名称 f_id、参数类型 int、输入参数、参数含义：好友id
	    参数3：参数名称：m_time、参数类型 char *、输入参数、参数含义：消息发送的时间
/*返回值：BOOL、是否赋值成功
/*作者：邵雨洁
/***************************************************/
bool Message::messageSelect(int u_id, int f_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char* query;
    if (connectMessageDatabase())
    {   /*新消息在前面 */
        string q = "select m_time,detail,owner,m_status,m_type from message where ((u_id=" + to_string(u_id) + " and f_id=" + to_string(f_id) + ")" + " or (u_id = " + to_string(f_id) + " and f_id= " + to_string(u_id) + " )) and owner=u_id ORDER BY m_time DESC";
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_message, query);
        if (flag)
        {  /*如果查询失败*/
            printf("Guery failed!\n");
            return false;
        }
        else
        {  /*如果查询成功*/
            printf("[select message from message between %d and %d ] made...\n", u_id, f_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_message);
            /*mysql_fetch_row检索结果集的下一行*/
            int t = 0;
            while (row = mysql_fetch_row(res_ptr))
            {
                /*printf ("%s  %s  %s  %s  %s \t ", row[0],row[1],row[2],row[3],row[4]);*/
                /*时间赋值*/
                MList[t].m_time = row[0];
                /*消息内容赋值*/
                MList[t].detail = row[1];
                /*消息拥有者赋值*/
                MList[t].sender = atoi(row[2]);
                /*消息状态赋值*/
                MList[t].m_status = atoi(row[3]);
                /*消息类型赋值*/
                MList[t].m_type = atoi(row[4]);
                t = t + 1;
            }
            num = t;
        }
        mysql_close(&conn_message);
        return true;
    }
}