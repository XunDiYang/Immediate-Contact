/**************************************************/
/*名称：user.h
/*描述：实现对user数据表的有关操作的头文件
/*作成日期： 2019/9/2
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#ifndef SEVEN_CHAT_USER_H
#define SEVEN_CHAT_USER_H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "string"
using namespace std;

class TheUser
{
public:
    // 参数含义: 与user数据表之间建立的联系;
    MYSQL conn_user;

    // 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    int res;

    // 参数含义：根据姓名查询ID，列出所有的ID,[0]:number
    int idList[200];

    //描述：与user数据表建立联系
    bool connectUserDatabase();

    // 描述：更改user数据表中的u_name(用户名称)
    bool userUnameUpdate(char u_name[], int u_id);

    // 描述：更改user数据表中的u_passwd(用户密码)
    bool userUpasswdUpdate(char u_passwd[], int u_id);

    // 描述：更改user数据表中的u_icon(用户头像)
    bool userUiconUpdate(char u_icon[], int u_id);

    // 描述：更改user数据表中的u_age(用户年龄)
    bool userUageUpdate(int u_age, int u_id);

    // 描述：更改user数据表中的u_sex(性别)
    bool userUsexUpdate(int u_sex, int u_id);

    // 描述：更改user数据表中的u_signature(用户签名)
    bool userUsignatureUpdate(char u_signature[], int u_id);

    // 描述：更改user数据表中的u_email(用户邮箱)
    bool userUemilUpdate(char u_email[], int u_id);

    // 描述：更改user数据表中的u_mode(用户模式)
    bool userUmodelUpdate(int u_mode, int u_id);

    // // 描述：用户注册
    // bool userRegister(char *u_name, char *u_passwd, char *u_email);

    // 描述：注销账户
    bool userDelete(int u_id);

    //查询姓名u_name
    const char *userUnameSelect(int u_id);

    //查询密码u_passwd
    const char *userUpasswdSelect(int u_id);

    //查询头像u_icon
    const char *userUiconSelect(int u_id);

    //查询年龄u_sage
    int userUageSelect(int u_id);

    //查询性别u_sage  0：男；1：女
    int userUsexSelect(int u_id);

    //查询签名u_signature
    const char *userUsignatureSelect(int u_id);

    //查询邮箱u_email
    const char *userUemailSelect(int u_id);

    //查询日夜模式u_model   0: 白天，1夜晚 返回类型可以改
    int userUmodelSelect(int u_id);

    //根据姓名查询id
    bool userUidSelect(char u_name[]);

    //验证登陆
    bool idpasswd(int u_id,char u_passwd[]);

    // 描述：用户注册,返回生成的id
    int userRegister(char u_name[], char u_passwd[], char u_email[]);
};

#endif