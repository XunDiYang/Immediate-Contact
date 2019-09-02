/**************************************************/
/*名称：user_group.h
/*描述：实现对user_group数据表的有关操作的头文件
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#ifndef USER_GROUP_H
#define USER_GROUP_H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
using namespace std;

class UserGroup
{
public:
    //  修改数据表，返回的结果，1:失败， 2：成功
    int res;

    //参数含义: 与user_group数据表之间建立的联系;
    MYSQL conn_user_group;

    // 描述：与user_group数据表建立联系
    bool connectUserGroupDatabase();

    // 描述：更改user_group数据表中的ug_name(群组中用户的备注名)
    bool userGroupUGnameUpdate(int ug_id, int g_id, char *ug_name);

    // 描述：更改user_group数据表中的ug_status(群组中用户的身份)
    bool userGroupUGstatusUpdate(int ug_id, int g_id, int ug_status);

    // 描述：加群
    bool userGroupInsert(int ug_id, int g_id, char *ug_name, int ug_status);

    // 描述：退群
    bool userGroupDelete(int ug_id,int g_id);
};

#endif