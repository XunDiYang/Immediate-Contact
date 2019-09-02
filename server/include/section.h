/**************************************************/
/*名称：section.h
/*描述：实现对section数据表的有关操作的头文件
/*作成日期： 2019/8/31
/*作者：杨训迪  邵雨洁 李可
/***************************************************/
#ifndef SECTION_H
#define SECTION_H
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
using namespace std;
class Section
{
public:
    //  修改数据表，返回的结果，1:失败， 2：成功
    int res;

    //参数含义: 与section数据表之间建立的联系;
    MYSQL conn_section;

    // 描述：与section数据表建立联系
    bool connectSectionDatabase();

    // 描述：更改section数据表中的s_name(分组名称)
    bool sectionSnameUpdate(char s_name[], int s_id);

    // 描述：建立分组
    bool sectionInsert( int u_id, char *s_name);

    // 描述：删除分组
    bool sectionDelete(int s_id);
};
#endif