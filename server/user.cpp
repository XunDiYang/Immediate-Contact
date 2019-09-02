/**************************************************/
/*名称：user.cpp
/*描述：实现对user数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "include/user.h"
#include "string"

/**************************************************/
/*名称： User::connectUserDatabase
/*描述：与user数据表建立联系
/*作成日期： 2019/8/31                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
/*参数： 
    参数1: 参数名称:conn_user; 参数类型: MYSQL; 全局变量; 参数含义:  与user数据表之间建立的联系;
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示连接成功  false:表示连接失败
/*作者：杨训迪
/***************************************************/
bool User::connectUserDatabase()
{
    mysql_init(&conn_user);
    if (mysql_real_connect(&conn_user, "localhost", "root", "20190120", "seven_chat", 0, NULL, CLIENT_FOUND_ROWS))
    {
        printf("CONNECTION SECCUSS\n");
        return true;
    }
    else
    {
        fprintf(stderr, "Connection failed\n");

        if (mysql_errno(&conn_user))
        {
            fprintf(stderr, "Connection erro %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
        }
        return false;
    }
}

/**************************************************/
/*名称：User::userUnameUpdate
/*描述：更改user数据表中的u_name(用户名称)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 用户id
    参数4：参数名称:u_name; 参数类型: char* 输入参数; 参数含义: 用户的名称
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool User::userUnameUpdate(char u_name[], int u_id)
{
    string q = u_name;
    q = "UPDATE user SET u_name = \"" + q + "\" WHERE u_id = " + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userUpasswdUpdate
/*描述：更改user数据表中的u_passwd(用户密码)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 用户id
    参数4：参数名称:u_passwd; 参数类型: char* 输入参数; 参数含义: 用户的密码
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool User::userUpasswdUpdate(char u_passwd[], int u_id)
{
    string q = u_passwd;
    q = "UPDATE user SET u_passwd = \"" + q + "\" WHERE u_id = " + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userUiconUpdate
/*描述：更改user数据表中的u_icon(用户头像)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 用户id
    参数4：参数名称:u_icon; 参数类型: char* 输入参数; 参数含义: 用户头像
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool User::userUiconUpdate(char u_icon[], int u_id)
{
    string q = u_icon;
    q = "UPDATE user SET u_icon = \"" + q + "\" WHERE u_id = " + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userUageUpdate
/*描述：更改user数据表中的u_age(用户年龄)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 用户id
    参数4：参数名称:u_age; 参数类型: int 输入参数; 参数含义: 用户年龄
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool User::userUageUpdate(int u_age, int u_id)
{
    string q = "UPDATE user SET u_age = \"" + to_string(u_age) + "\" WHERE u_id = " + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userUsexUpdate
/*描述：更改user数据表中的u_sex(性别)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 用户id
    参数4：参数名称:u_sex; 参数类型: int 输入参数; 参数含义: 用户性别
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool User::userUsexUpdate(int u_sex, int u_id)
{
    string q = "UPDATE user SET u_sex = \"" + to_string(u_sex) + "\" WHERE u_id = " + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userUsignatureUpdate
/*描述：更改user数据表中的u_signature(用户签名)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 用户id
    参数4：参数名称:u_signature; 参数类型: char* 输入参数; 参数含义: 用户签名
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool User::userUsignatureUpdate(char u_signature[], int u_id)
{
    string q = u_signature;
    q = "UPDATE user SET u_signature = \"" + q + "\" WHERE u_id = " + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userUemilUpdate
/*描述：更改user数据表中的u_email(用户邮箱)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 用户id
    参数4：参数名称:u_email; 参数类型: char* 输入参数; 参数含义: 用户邮箱
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool User::userUemilUpdate(char u_email[], int u_id)
{
    string q = u_email;
    q = "UPDATE user SET u_email = \"" + q + "\" WHERE u_id = " + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userUmodelUpdate
/*描述：更改user数据表中的u_mode(用户模式)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:u_id; 参数类型: int; 输入参数; 参数含义: 用户id
    参数4：参数名称:u_mode; 参数类型: int 输入参数; 参数含义: 用户模式
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool User::userUmodelUpdate(int u_mode, int u_id)
{
    string q = "UPDATE user SET u_model = \"" + to_string(u_mode) + "\" WHERE u_id = " + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userRegister
/*描述：用户注册
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_name、参数类型 char *、输入参数、参数含义：用户名称
       参数2：参数名称 u_passwd、参数类型 char *、输入参数、参数含义：用户密码
       参数3：参数名称 u_email、参数类型 char *、输入参数、参数含义：用户邮箱
       参数4： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
       参数5：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
/*返回值：BOOL、是否插入成功
/*作者：李可
/***************************************************/
bool User::userRegister(char *u_name, char *u_passwd,  char *u_email)
{
    int ret;
    char sql_insert[2048];
    sprintf(sql_insert, "insert into user (u_name,u_passwd,u_email) values(\'%s\', \'%s\',\'%s\')", u_name, u_passwd, u_email);
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, sql_insert);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：User::userDelete
/*描述：注销账户
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
       参数2： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
       参数3：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
/*返回值：BOOL、是否删除成功
/*作者：李可
/***************************************************/

bool User::userDelete(int u_id)
{
    string q = "delete from user where u_id=" + to_string(u_id);
    const char *query = q.c_str();
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return true;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return false;
        }
    }
    return false;
}

