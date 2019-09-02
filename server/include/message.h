/**************************************************/
/*名称：message.h
/*描述：实现对message数据表的有关操作的头文件
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#ifndef MESSAGE_H
#define MESSAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
using namespace std;

class Message
{
public:
    // 参数含义: 与friends数据表之间建立的联系;
    MYSQL conn_message;

    // 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    int res;

    //描述：与message数据表建立联系
    bool connectMessageDatabase();

    // 描述：记录发送消息
    bool messageInsert(int u_id, int f_id, int m_status, int m_type, char *detail);

    // 描述：删除消息
    bool messageDelete(int u_id, int f_id, char *m_time);
};

#endif