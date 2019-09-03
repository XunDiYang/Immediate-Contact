/**************************************************/
/*名称：gmessage.h
/*描述：实现对gmessage数据表的有关操作的头文件
/*作成日期： 2019/9/2
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#ifndef SEVEN_CHAT_GMESSAGE_H
#define SEVEN_CHAT_GMESSAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "string"
using namespace std;

class Gmessage
{
public:
    //  修改数据表，返回的结果，1:失败， 2：成功
    int res;

    //参数含义: 与gmessage数据表之间建立的联系;
    MYSQL conn_gmessage;

    //一共取了多少条消息
    int num;

    struct GMessageLise
    {
        int gm_id; //消息发送者
        //char* gm_name;//发送者昵称
        int owner;	 //消息拥有者
        int gm_status; //消息状态
        int gm_type;   //消息类型
        char *detail;  //具体消息内容
        char *gm_time; //消息时间
    } GMList[200];

    /*输入群id,将查询到的消息保存到结构体中，按时间顺序,最新的在前面，num为一共有多少条消息*/
    bool gMessageSelect(int g_id);

    // 描述：与gmessage数据表建立联系
    bool connectGmessageDatabase();

    // 描述：发送群消息记录
    bool gmessageInsert(int gm_id,int g_id,int gm_type,char *detail,int owner);

    // 描述：删除群消息
    bool gmessageDelete(int gm_id,int g_id,char *gm_time);

};

#endif
