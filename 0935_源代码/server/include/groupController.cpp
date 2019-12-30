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
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int create_group(char *msg) {
    cJSON *root = cJSON_Parse(msg);
    int groupid;
    int groupownerid = cJSON_GetObjectItem(root, "groupownerid")->valueint;
    char *groupname = cJSON_GetObjectItem(root, "groupname")->valuestring;
    char *groupintro = cJSON_GetObjectItem(root, "groupintro")->valuestring;
    //char *groupicon = cJSON_GetObjectItem(root, "groupicon")->valuestring;
    Group group;
    groupid = group.groupeInsert(groupownerid, groupname, groupintro);
    if( groupid != -1) {
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
/*作者：常欣煜，马文聪，丁颖
/***************************************************/
int join_group(int userid, int groupid) {
    cJSON *root = cJSON_CreateObject();
    if(root == NULL)
        return 0;
    cJSON_AddStringToObject(root, "type", "group-join-receipt");
    cJSON_AddNumberToObject(root, "userid", userid);
    cJSON_AddNumberToObject(root, "groupid", groupid);
    Group group;
    int group_admin = group.groupGadminidSelect(groupid);
    if(group_admin != 0)                     //管理者id是一定存在，通过此判断是否该群存在
    {
        const char*groupname =group.groupGnameSelect(groupid);
        printf("group %d not exist\n", groupid);
        cJSON_AddNumberToObject(root, "status", 1);
        cJSON_AddStringToObject(root, "groupname", groupname);
        send_message_to_local(get_user_fd(userid)->user_fd, cJSON_Print(root));
        UserGroup userGroup;
        if(group_admin = userid)    //如果加群人为管理者
        {
            userGroup.userGroupInsert(userid, groupid,"admin",0);
        } else{                             //如果加群人为成员
            userGroup.userGroupInsert(userid,groupid,"member",1);
        }
        return 1;

    }
    else
    {
        cJSON_AddNumberToObject(root, "status", 0);
        send_message_to_local(userid, cJSON_Print(root));
        return 0;
    }


}


/**************************************************/
/*名称：quit_group
/*描述：退出群组
/*作成日期：2019.9.3
/*参数：参数1：参数名称 username、参数类型 char *、输入参数、参数含义：用户名首指针
		参数2：参数名称 groupID、参数类型 int、输入参数、参数含义：群组ID
/*返回值：VOID
/*作者:常欣煜，马文聪，丁颖
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
/**************************************************/
/*名称：send_group_list
/*描述：发送friend list
/*作成日期：2019.9.3
/*参数：参数1：参数名称 userid、参数类型 int、输入参数、参数含义：用户ID
/*返回值：VOID
/*作者：马文聪
/***************************************************/
void send_group_list(int userid) {

    cJSON *root = cJSON_CreateObject();

    UserGroup userGroup;
    if(userGroup.userGroupAllGidSelect(userid)) {
        int i;
        char a[100], b[100];
        memset(a, '\0', sizeof(a));
        memset(b, '\0', sizeof(b));
        for (i = 1; i <= userGroup.userGroupAllGid[0]; i++) {
            for(int j = 0; j < i; ++j)
                a[j] = 'a';
            for(int j = 0; j < i; ++j)
                b[j] = 'b';
            cJSON_AddNumberToObject(root, a, userGroup.userGroupAllGid[i]);
            Group group;
            const char *groupName = group.groupGnameSelect(userGroup.userGroupAllGid[i]);
            cJSON_AddStringToObject(root, b, groupName);
            memset(a, '\0', sizeof(a));
            memset(b, '\0', sizeof(b));
            // cJSON_AddNumberToObject(item, "status", status);
        }
        cJSON_AddNumberToObject(root, "status", 1);
        cJSON_AddStringToObject(root, "type", "group-list-request");
        cJSON_AddNumberToObject(root, "size", userGroup.userGroupAllGid[0]);
        send_message_to_local(get_user_fd(userid)->user_fd, cJSON_Print(root));
    }
    else{
        cJSON_AddNumberToObject(root, "status", 0);
        send_message_to_local(get_user_fd(userid)->user_fd, cJSON_Print(root));
    }
}
