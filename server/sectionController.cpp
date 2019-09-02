/**************************************************/
/*名称：section.cpp
/*描述：实现对section数据表的有关操作
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/

#include "include/section.h"
#include "string"

/**************************************************/
/*名称：Section::connectSectionDatabase
/*描述：与section数据表建立联系
/*作成日期： 2019/8/31                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
/*参数： 
    参数1: 参数名称:conn_section; 参数类型: Mysql; 全局变量; 参数含义:  与section数据表之间建立的联系;
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示连接成功  false:表示连接失败
/*作者：杨训迪
/***************************************************/
bool Section::connectSectionDatabase()
{
    mysql_init(&conn_section);
    if (mysql_real_connect(&conn_section, "localhost", "root", "20190120", "seven_chat", 0, NULL, CLIENT_FOUND_ROWS))
    {
        printf("CONNECTION SECCUSS \n");
        return true;
    }
    else
    {
        fprintf(stderr, "Connection failed \n");

        if (mysql_errno(&conn_section))
        {
            fprintf(stderr, "Connection erro %d: %sn \n", mysql_errno(&conn_section), mysql_error(&conn_section));
        }
        return false;
    }
}

/**************************************************/
/*名称：Section::sectionSnameUpdate
/*描述：更改section数据表中的s_name(分组名称)
/*作成日期： 2019/8/31
/*参数:
    参数1： 参数名称:conn_section; 参数类型: MYSQL;全局变量; 参数含义: 与section数据表之间建立的联系;
    参数2：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
    参数3：参数名称:s_id; 参数类型: int; 输入参数; 参数含义: 分组id
    参数4：参数名称:s_name; 参数类型: char*; 输入参数; 参数含义: 分组名称
/*返回值：返回值名称:无; 类型: bool; 含义:true:表示修改成功  false:表示修改失败
/*作者：杨训迪
/***************************************************/
bool Section::sectionSnameUpdate(char s_name[], int s_id)
{
    string q = s_name;
    q = "UPDATE section SET s_name = \"" + q + "\" WHERE s_id = " + to_string(s_id);
    const char *query = q.c_str();
    if (connectSectionDatabase())
    {
        res = mysql_query(&conn_section, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_section) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_section));
            mysql_close(&conn_section);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_section), mysql_error(&conn_section));
            mysql_close(&conn_section);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：sectionInsert
/*描述：建立分组
/*作成日期：2019-9-1
/*参数：
    参数1：参数名称 s_id、参数类型 char *、输入参数、参数含义：分组id
    参数2：参数名称 u_id、参数类型 char *、输入参数、参数含义：用户id
    参数3：参数名称 s_name、参数类型 char *、输入参数、参数含义：分组名称
    参数4： 参数名称:conn_section; 参数类型: MYSQL;全局变量; 参数含义: 与section数据表之间建立的联系;
    参数5：参数名称:res; 参数类型: int; 全局变量; 参数含义: 修改数据表，返回的结果，1:失败， 2：成功
/*返回值：BOOL、是否插入成功
/*作者：李可
/***************************************************/
bool Section::sectionInsert(int s_id, int u_id, char *s_name)
{
    int ret;
    char sql_insert[2048];
    sprintf(sql_insert, "insert into Section (s_id,u_id,s_name) values(\'%d\', \'%d\',\'%s\')", s_id, u_id, s_name);
    if (connectSectionDatabase())
    {
        res = mysql_query(&conn_section, sql_insert);
        if (!res && (unsigned long)mysql_affected_rows(&conn_section) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_section));
            mysql_close(&conn_section);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_section), mysql_error(&conn_section));
            mysql_close(&conn_section);
            return false;
        }
    }
    return false;
}

/**************************************************/
/*名称：sectionDelete
/*描述：删除分组
/*作成日期：2019-9-1
/*参数：参数1：参数名称 s_id、参数类型 int、输入参数、参数含义：分组id
/*返回值：BOOL、是否删除成功
/*作者：李可
/***************************************************/

bool Section::sectionDelete(int s_id)
{
    string q = "delete from Section where s_id=" + to_string(s_id);
    const char *query = q.c_str();
    if (connectSectionDatabase())
    {
        res = mysql_query(&conn_section, query);
        if (!res && (unsigned long)mysql_affected_rows(&conn_section) != 0)
        {
            printf(" UPDATED %lu rowsn \n", (unsigned long)mysql_affected_rows(&conn_section));
            mysql_close(&conn_section);
            return true;
        }
        else
        {
            fprintf(stderr, " UPDATED error %d: %sn \n", mysql_errno(&conn_section), mysql_error(&conn_section));
            mysql_close(&conn_section);
            return false;
        }
    }
    return false;
}
