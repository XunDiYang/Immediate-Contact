/**************************************************/
/*名称：message.h
/*描述：实现对message数据表的有关操作的头文件
/*作成日期： 2019/9/2
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#ifndef SEVEN_CHAT_MESSAGE_H
#define SEVEN_CHAT_MESSAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "string"
using namespace std;

class Message
{
public:
    // 参数含义: 与friends数据表之间建立的联系;
    MYSQL conn_message;

    // 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    int res;

    //一共取了多少条消息
    int num;

    //获取消息的结构体数组
    struct MessageLise
    {
        char *m_time; //消息时间
        char *detail; //具体消息内容
        int sender;    //消息拥有者
        int m_status; //消息状态
        int m_type;
    } MList[200];

    //描述：与message数据表建立联系
    bool connectMessageDatabase();

    // 描述：记录发送消息
    bool messageInsert(int u_id, int f_id, int m_status, int m_type, char *detail);

    // 描述：删除消息
    bool messageDelete(int u_id, int f_id, char *m_time);

    //输入两个人id ,将查询到的消息保存到结构体中，按时间顺序，最新的在前面，num为一共有多少条消息
    bool messageSelect(int u_id, int f_id);
};

#endif //SEVEN_CHAT_MESSAGE_H
