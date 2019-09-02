/**************************************************/
/*名称：user.h
/*描述：实现对user数据表的有关操作的头文件
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
using namespace std;

class User
{
public:
    // 参数含义: 与user数据表之间建立的联系;
    MYSQL conn_user;

    // 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    int res;

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

    // 描述：用户注册
   bool userRegister(char *u_name, char *u_passwd,  char *u_email);

    // 描述：注销账户
    bool userDelete(int u_id);
};

#endif