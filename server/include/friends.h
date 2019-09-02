/**************************************************/
/*名称：friends.h
/*描述：实现对friends数据表的有关操作的头文件
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#ifndef FRIEND_H
#define FRIEND_H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
using namespace std;

class Friends
{
public:
    // 参数含义: 与friends数据表之间建立的联系;
    MYSQL conn_friends;

    // 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    int res;

    //参数含意：某个用户的所有好友的id [0]表示数目
	int friendslist[200];

	//参数含义：某个用户某个分组的所以成员id [0]表示数目
	int SMList[200];

    //描述：与friends数据表建立联系
    bool connectFriendsDatabase();

    //描述：更改friends数据表中的f_name(好友的昵称)
    bool friendsFnameUpdate(int u_id, int f_id, char name[]);

    //描述：更改friends数据表中的f_name(好友的昵称)
    bool friendsSidUpdate(int u_id, int f_id, int s_id);

    //描述：添加好友
    bool friendsInsert(int u_id, int f_id, char *f_name, int s_id);

    // 描述：删除好友
    bool friendsDelete(int u_id,int f_id);

    //描述：根据双方id查询 昵称
	char* friendsFnameSelect(int u_id, int f_id);

	//描述：传入u_id,查询u_id的所有好友的id,将其填入friendsList[0]表示一共有多少个好友
	bool friendsFlistSelect(int u_id);

	//描述：根据双方 id查询好友所属分组id
	int friendsFsectionidSelect(int u_id, int f_id);

	//描述：根据用户和分组id查询所有组员id
	bool friendsSMidSelect(int u_id, int s_id);
};

#endif