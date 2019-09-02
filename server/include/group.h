/**************************************************/
/*名称：group_.h
/*描述：实现对group_数据表的有关操作的头文件
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#ifndef GROUP__H
#define GROUP__H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
using namespace std;

class Group
{
public:
    //  修改数据表，返回的结果，1:失败， 2：成功
    int res;

    //参数含义: 与group_数据表之间建立的联系;
    MYSQL conn_group;

    //描述：与group_数据表建立联系
    bool connectGroupDatabase();

    // 描述：更改group_数据表中的g_name(群组名称)
    bool groupGnameUpdate(int g_id, char *g_name);

    // 描述：更改group_数据表中的g_intro(群组的简介)
    bool groupGintroUpdate(int g_id, char *g_intro);

    // 描述：更改group_数据表中的g_admin_id(群组的管理员id)
    bool groupGadminIdUpdate(int g_id, int g_admin_id);

    // 描述：更改group_数据表中的g_num(群组的总人数)
    bool groupGnumUpdate(int g_id, int g_num);

    // 描述：解散群 
    bool groupDelete(int g_id);

    // 描述：建群
    bool groupeInsert(int g_admin_id, char *g_name, char *g_intro,char *g_icon);

    //描述：更改group_数据表中的g_icon(群组头像)
    bool Group::groupGiconUpdate(int g_id, char *g_icon);
};

#endif