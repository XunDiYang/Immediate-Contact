/**************************************************/
/*名称：user.cpp
/*描述：实现对user数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "user.h"
#include "string"
#include "iostream"

/**************************************************/
/*名称： User::connectUserDatabase
/*描述：与user数据表建立联系
/*作成日期： 2019/8/31
/*参数：
    参数1: 参数名称:conn_user; 参数类型: MYSQL; 全局变量; 参数含义:  与user数据表之间建立的联系;
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示连接成功  false:表示连接失败
/*作者：杨训迪
/***************************************************/
bool TheUser::connectUserDatabase()
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
bool TheUser::userUnameUpdate(char u_name[], int u_id)
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
bool TheUser::userUpasswdUpdate(char u_passwd[], int u_id)
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
bool TheUser::userUiconUpdate(char u_icon[], int u_id)
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
bool TheUser::userUageUpdate(int u_age, int u_id)
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
bool TheUser::userUsexUpdate(int u_sex, int u_id)
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
bool TheUser::userUsignatureUpdate(char u_signature[], int u_id)
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
bool TheUser::userUemilUpdate(char u_email[], int u_id)
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
bool TheUser::userUmodelUpdate(int u_mode, int u_id)
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
        参数6：参数名称 u_icon、参数类型 char *、输入参数、参数含义：用户头像地址
        参数7：参数名称 u_age、参数类型 int、输入参数、参数含义：用户年龄
        参数8：参数名称 u_sex、参数类型 int、输入参数、参数含义：用户年龄
        参数9：参数名称 u_model、参数类型 int、输入参数、参数含义：用户年龄
/*返回值：int 若int=-1插入失败 否则成功
/*作者：李可
/***************************************************/
int TheUser::userRegister(char u_name[], char u_passwd[], char u_email[])
{
    int ret;
    char sql_insert[2048];
    sprintf(sql_insert, "insert into user (u_name,u_passwd,u_email) values(\'%s\', \'%s\',\'%s\')", u_name, u_passwd, u_email);
    if (connectUserDatabase())
    {
        res = mysql_query(&conn_user, sql_insert);
        if (!res && (unsigned long)mysql_affected_rows(&conn_user) != 0)
        {   //查询id
          MYSQL_RES *res_ptr;
          MYSQL_ROW row;
          int flag;
          int ans;
          string q = "select LAST_INSERT_ID()";
          const char *query = q.c_str();
          /*查询，成功则返回0*/
          flag = mysql_query(&conn_user, query);
          if (flag)
          { /*如果查询失败*/
            printf("Guery failed!\n");
            return -1;
          }
          else
          {
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            {  //printf ("%s\t", row[0]);
                ans = atoi(row[0]);
            }
          }
       
            printf(" updated %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_user));
            mysql_close(&conn_user);
            return ans;
        }
        else
        {
            fprintf(stderr, "update error %d: %sn \n", mysql_errno(&conn_user), mysql_error(&conn_user));
            mysql_close(&conn_user);
            return -1;
        }
    }
    return -1;
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

bool TheUser::userDelete(int u_id)
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

/**************************************************/
/*名称：User::userUnameSelect
/*描述：根据用户id查询用户姓名u_name
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	    参数2： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：char*、返回姓名指针，若没查到为NULL
/*作者：邵雨洁
/***************************************************/
const char *TheUser::userUnameSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans;
    char *query;
    //连接数据库
    if (connectUserDatabase())
    {
        string q = "select u_name from user where u_id=" + to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return NULL;
        }
        else
        { /*如果查询成功*/
            printf("[select u_name from user where u_id=%d] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_user);
        return ans;
    }
}

/**************************************************/
/*名称：User::userUpasswdSelect
/*描述：根据用户id查询用户密码u_passwd
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	   参数2： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：char*、返回密码指针，若没查到为NULL
/*作者：邵雨洁
/***************************************************/
const char *TheUser::userUpasswdSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans;
    char *query;
    //连接数据库
    if (connectUserDatabase())
    {
        string q = "select u_passwd from user where u_id=" + to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return NULL;
        }
        else
        { /*如果查询成功*/
            printf("[select u_passwd from user where u_id=%d] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_user);
        return ans;
    }
}

/**************************************************/
/*名称：User::userUiconSelect
/*描述：根据用户id查询用户头像u_icon路径
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	   参数2： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：char*、返回头像地址指针，若没查到为NULL
/*作者：邵雨洁
/***************************************************/
const char *TheUser::userUiconSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans;
    char *query;
    //连接数据库
    if (connectUserDatabase())
    {
        string q = "select u_icon from user where u_id=" + to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return NULL;
        }
        else
        { /*如果查询成功*/
            printf("[select u_icon from user where u_id=%d] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_user);
        return ans;
    }
}

/**************************************************/
/*名称：User::userUageSelect
/*描述：根据用户id查询用户年龄u_age
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	    参数2： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：int、返回用户年龄
/*作者：邵雨洁
/***************************************************/
int TheUser::userUageSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag, age;
    char *ans;
    char *query;
    //连接数据库
    if (connectUserDatabase())
    {
        string q = "select u_age from user where u_id=" + to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return 0;
        }
        else
        { /*如果查询成功*/
            printf("[select u_age from user where u_id=%d] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_user);
        age = atoi(ans);
        return age;
    }
}

/**************************************************/
/*名称：User::userUsexSelect
/*描述：根据用户id查询用户性别u_sex
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
	    参数2： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：int、返回用户性别
/*作者：邵雨洁
/***************************************************/
int TheUser::userUsexSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag, sex;
    char *ans;
    char *query;
    //连接数据库
    if (connectUserDatabase())
    {
        string q = "select u_sex from user where u_id=" + to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return 0;
        }
        else
        { /*如果查询成功*/
            printf("[select u_sex from user where u_id=%d] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_user);
        sex = atoi(ans);
        return sex;
    }
}

/**************************************************/
/*名称：User::userUsignatureSelect
/*描述：根据用户id查询用户签名u_signature
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
		参数2： 参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：char*、如查询到返回内容，否则NULL
/*作者：邵雨洁
/***************************************************/
const char *TheUser::userUsignatureSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans;
    ans = NULL;
    char *query;
    /*连接数据库*/
    if (connectUserDatabase())
    {
        string q = "select u_signature from user where u_id=" + to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return NULL;
        }
        else
        { /*如果查询成功*/
            printf("[select u_signature from user where u_id=%d] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_user);
        return ans;
    }
}

/**************************************************/
/*名称：User::userUemailSelect
/*描述：根据用户id查询用户邮箱u_email
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
		参数2：参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：char*、如查询到返回邮箱，否则NULL
/*作者：邵雨洁
/***************************************************/
const char *TheUser::userUemailSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag;
    char *ans;
    char *query;
    /*连接数据库*/
    if (connectUserDatabase())
    {
        string q = "select u_email from user where u_id=" + to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return NULL;
        }
        else
        { /*如果查询成功*/
            printf("[select u_email from user where u_id=%d] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_user);
        return ans;
    }
}

/**************************************************/
/*名称：User::userUmodelSelect
/*描述：根据用户id查询用户日夜模式u_model
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
		参数2：参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：int、如查询到日夜模式0/1
/*作者：邵雨洁
/***************************************************/
int TheUser::userUmodelSelect(int u_id)
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag, model;
    char *ans;
    char *query;
    //连接数据库
    if (connectUserDatabase())
    {
        string q = "select u_model from user where u_id=" + to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return 0;
        }
        else
        { /*如果查询成功*/
            printf("[select u_model from user where u_id=%d] made...\n", u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                ans = row[0];
            }
        }
        mysql_close(&conn_user);
        model = atoi(ans);
        return model;
    }
}

/*根据姓名查询id*/
/**************************************************/
/*名称：User::userUmodelSelect
/*描述：根据用户昵称查询用用户id
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_name、参数类型 char*、输入参数、参数含义：用户昵称
		参数2：参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：int、如查询到用户id
/*作者：邵雨洁
/***************************************************/
bool TheUser::userUidSelect(char u_name[])
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag, id;
    char *query;
    //连接数据库
    if (connectUserDatabase())
    {
        string q = u_name;
        cout << q << endl;
        q = "select u_id from user where u_name=\"" + q + "\"";
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        { /*如果查询失败*/
            printf("Guery failed!\n");
            return false;
        }
        else
        { /*如果查询成功*/
            printf("[select u_id from user where u_name=%s] made...\n", u_name);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            int t=1;
            while (row = mysql_fetch_row(res_ptr))
            { /* printf ("%s\t", row[0]);*/
                idList[t] = atoi(row[0]);
                t=t+1;
            }
            idList[0]=t-1;
        }
        mysql_close(&conn_user);
        return true;
    }
}

/**************************************************/
/*名称：idpasswd
/*描述：登陆验证
/*作成日期：2019-9-1
/*参数：参数1：参数名称 u_id、参数类型 int、输入参数、参数含义：用户id
        参数2：参数名称 u_passwd、参数类型 char*、输入参数、参数含义：用户密码
        参数3：参数名称:conn_user; 参数类型: MYSQL;全局变量; 参数含义: 与user数据表之间建立的联系;
/*返回值：bool、true:成功登陆  false：id或秘密错误
/*作者：邵雨洁
/***************************************************/
bool  TheUser::idpasswd(int u_id,char u_passwd[])
{
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;
    int flag,model;
    int ans;
    char* query;
    //连接数据库
    if(connectUserDatabase())
    {
        string q=u_passwd;
        q = "select u_id from user where u_passwd=\""+ q + "\"" + " and u_id="+ to_string(u_id);
        const char *query = q.c_str();
        /*查询，成功则返回0*/
        flag = mysql_query(&conn_user, query);
        if (flag)
        {  /*如果查询失败*/
            printf("Guery failed!\n");
            return false;
        }
        else
        {  /*如果查询成功*/
            printf("[select u_model from user where u_id=%d] made...\n",u_id);
            /*mysql_store_result讲全部的查询结果读取到客户端*/
            res_ptr = mysql_store_result(&conn_user);
            /*mysql_fetch_row检索结果集的下一行*/
            ans=0;
            while (row = mysql_fetch_row(res_ptr))
            {    printf ("%s\t", row[0]);
                ans=1;
            }
        }
        mysql_close(&conn_user);
        if(ans==1) return true;
        else if(ans==0) return false;

    }
}

