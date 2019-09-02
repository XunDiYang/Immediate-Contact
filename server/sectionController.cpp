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
bool Section::sectionInsert(int u_id, char *s_name)
{
    int ret;
    char sql_insert[2048];
    sprintf(sql_insert, "insert into section (u_id,s_name) values(\'%d\',\'%s\')",  u_id, s_name);
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
    string q = "delete from section where s_id=" + to_string(s_id);
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
/*名称：sectionDelete
/*描述：根据用户id查询其所有分组s_id,s_name
/*作成日期：2019-9-1
/*参数：参数1：参数名称 s_id、参数类型 int、输入参数、参数含义：分组id
        参数2：参数名称 s_name、参数类型 char*、输入参数、参数含义：分组名称
/*返回值：BOOL、是否成功赋值
/*作者：邵雨洁
/***************************************************/
bool Section::sectionSelect(int u_id)
{
	MYSQL_RES *res_ptr;
	MYSQL_ROW row;
	int flag;
	char *ansch;
	char* query;
	if (connectSectionDatabase())
	{
		string q = "select s_id, s_name from section where u_id=" + to_string(u_id);
		const char *query = q.c_str();
		/*查询，成功则返回0*/
		flag = mysql_query(&conn_section, query);
		if (flag)
		{  /*如果查询失败*/
			printf("Guery failed!\n");
			num = -1;
			return false;
		}
		else
		{  /*如果查询成功*/
			printf("[select s_id, s_name from user_group where u_id=%d ] made...\n", u_id);
			/*mysql_store_result讲全部的查询结果读取到客户端*/
			res_ptr = mysql_store_result(&conn_section);
			/*mysql_fetch_row检索结果集的下一行*/
			int t = 0;
			while (row = mysql_fetch_row(res_ptr))
			{    
				SList[t].s_id = atoi(row[0]);
				SList[t].s_name = row[1];
				t = t + 1;

			}
			num = t;
		}
		mysql_close(&conn_section);
		return true;
	}
}

// int main()
// {
// 	Section S;
// 	printf("输出所有组id：");
// 	if (S.sectionSelect(1))
// 	{
// 		printf("分组个数%d  %d  %s\n", S.num, S.SList[0].s_id, S.SList[0].s_name);
// 	}

// }