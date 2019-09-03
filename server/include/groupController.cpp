//
// Created by mawencong on 2019/9/3.
//

#include "server.h"
/**************************************************/
/*名称：create_group
/*描述：创建群组
/*作成日期：2019.9.3
/*参数：参数1：参数名称 username、参数类型 char *、输入参数、参数含义：用户名首指针
/*返回值：VOID
/*作者：
/***************************************************/
int create_group(char *msg) {
    cJSON *root = cJSON_Parse(msg);
    int groupid;
    int groupownerid = cJSON_GetObjectItem(root, "groupownerid")->valueint;
    char *groupname = cJSON_GetObjectItem(root, "groupname")->valuestring;
    char *groupintro = cJSON_GetObjectItem(root, "password")->valuestring;
    char *groupicon = cJSON_GetObjectItem(root, "groupicon")->valuestring;
    Group group;
    if( (groupid = group.groupeInsert(groupownerid, groupname, groupintro, groupicon)) ) {
        join_group(groupownerid, groupid);
        return 1;
    }
    else
        return 0;

}

/**************************************************/
/*名称：join_group
/*描述：加入群组
/*作成日期：2019.9.3
/*参数：参数1：参数名称 userid、参数类型 char *、输入参数、参数含义：用户ID
		参数2：参数名称 groupID、参数类型 int、输入参数、参数含义：群组ID
/*返回值：VOID
/*作者：
/***************************************************/
int join_group(int userid, int groupid) {
    cJSON *root = cJSON_CreateObject();
    if(root == NULL)
        return 0;
    cJSON_AddStringToObject(root, "type", "group-join-receipt");
    cJSON_AddNumberToObject(root, "userid", userid);
    cJSON_AddNumberToObject(root, "groupid", groupid);
    Group group;
    if(!group.groupGadminidSelect(groupid))
    {
        printf("group %d not exist\n", groupid);
        cJSON_AddNumberToObject(root, "status", 1);
        send_message_to_local(userid, cJSON_Print(root));
        return 0;
    }
    else
    {
        cJSON_AddNumberToObject(root, "status", 0);
        send_message_to_local(userid, cJSON_Print(root));
    }


}


/**************************************************/
/*名称：quit_group
/*描述：退出群组
/*作成日期：2019.9.3
/*参数：参数1：参数名称 username、参数类型 char *、输入参数、参数含义：用户名首指针
		参数2：参数名称 groupID、参数类型 int、输入参数、参数含义：群组ID
/*返回值：VOID
/*作者:
/***************************************************/
int quit_group(int userid, int groupid) {
    // 退群
    int gid = 1; //群id
    int uid = 1; //用户id
    Group group;
    int gnum = group.groupGnumSelect(gid);
    gnum = gnum - 1;
    if(gnum != 0)
    {
        group.groupGnumUpdate(gid,gnum); //群内人数更新
    }
    else
    {
        group.groupDelete(gid);
    }
    UserGroup user;
    //需要升级点：退群人是管理者，群内管理权限移交
    user.userGroupDelete(uid,gid);
    return 1;
}
