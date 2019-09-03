/**************************************************/
/*名称：gmessage.cpp
/*描述：实现对gmessage数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "gmessage.h"

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
    参数5：参数名称 gm_type、参数类型 int、输入参数、参数含义：消息类别 0:text 1:picture 2:file
    参数6：参数名称 detail、参数类型 char *、输入参数、参数含义：消息内容
/*返回值：BOOL、是否插入成功
/*作者：李可
/***************************************************/
bool Gmessage::gmessageInsert(int gm_id, int g_id, int gm_type, char *detail,int owner)
{
    char sql_insert[2048];
    sprintf(sql_insert, "insert into gmessage (gm_id,g_id,gm_type,detail,owner) values (\'%d\', \'%d\',\'%d\',\'%s\',\'%d\')", gm_id, g_id, gm_type, detail,owner);
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
    q = "delete from gmessage where gm_id=" + to_string(gm_id) + " and g_id=" + to_string(g_id) + " and gm_time between " + "'" + q + ".000" + "'" + " and " + "'" + q + ".999" + "'";
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

/**************************************************/
/*名称：gMessageSelect
/*描述：获取群消息
/*作成日期：2019-9-1
/*参数：
	参数1： 参数名称:conn_gmessage; 参数类型: MYSQL;全局变量; 参数含义: 与gmessage数据表之间建立的联系;
	参数2：参数名称 g_id、参数类型 int、输入参数、参数含义：群id
/*返回值：BOOL、是否成功赋值
/*作者：邵雨洁
/***************************************************/
bool Gmessage::gMessageSelect(int g_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *query;
    if (connectGmessageDatabase())
    { /*新消息在前面 */
        string q = "select gm_id,owner,gm_status,gm_type,detail,gm_time from gmessage where g_id=" + to_string(g_id) + " ORDER BY gm_time DESC";
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_gmessage, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return false;
        }
        else
        { /*如果查询成功*/
            printf("[select message from gmessage where g_id=%d] made...\n", g_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_gmessage);
            /*mysql_fetch_row检索结果集的下一行*/
            int t = 0;
            while (row = mysql_fetch_row(res_ptr))
            {
                /*printf ("%s  %s  %s  %s  %s \t ", row[0],row[1],row[2],row[3],row[4]);*/
                /*发送者id*/
                GMList[t].gm_id = atoi(row[0]);
                /*发送者昵称*/
                //GMList[t].gm_name=row[1];
                /*消息拥有者赋值*/
                GMList[t].owner = atoi(row[1]);
                /*消息状态赋值*/
                GMList[t].gm_status = atoi(row[2]);
                /*消息类型赋值*/
                GMList[t].gm_type = atoi(row[3]);
                /*消息内容赋值*/
                GMList[t].detail = row[4];
                /*时间赋值*/
                GMList[t].gm_time = row[5];
                t = t + 1;
            }
            num = t;
        }
        mysql_close(&conn_gmessage);
        return true;
    }
}
// int main()
// {
//     Gmessage GM;
//     if (GM.gMessageSelect(1))
//         printf("一共有%d条消息:\n", GM.num);
//     printf("gm_time:%s  detail:%s   owner:%d  gm_status:%d  gm_type:%d, gm_id:%d\n", GM.GMList[0].gm_time, GM.GMList[0].detail, GM.GMList[0].owner, GM.GMList[0].gm_status, GM.GMList[0].gm_type, GM.GMList[0].gm_id);
//     printf("gm_time:%s  detail:%s   owner:%d  gm_status:%d  gm_type:%d, gm_id:%d\n",
//            GM.GMList[1].gm_time, GM.GMList[1].detail, GM.GMList[1].owner, GM.GMList[1].gm_status, GM.GMList[1].gm_type, GM.GMList[0].gm_id);
// }
