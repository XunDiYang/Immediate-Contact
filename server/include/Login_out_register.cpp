//
// Created by mawencong on 2019/9/2.
//

//
// Created by changxinyu on 2019/8/31.
//

#include "server.h"

/**************************************************/
/*名称：user_register
/*描述：用户登录
/*作成日期：2019.9.3
/*参数：参数1：参数名称 prop、参数类型 struct User *、输入参数、参数含义：用户
		参数2：参数名称 userid、参数类型 int、输入参数、参数含义：用户ID
		参数3：参数名称 password、参数类型 char *、输入参数、参数含义：用户密码
/*返回值：int 1-成功，0-失败
/*作者：马文聪
/***************************************************/
int user_register(char *message) {
    cJSON *root = cJSON_Parse(message);
    char *password = cJSON_GetObjectItem(root, "password")->valuestring;
    char *username = cJSON_GetObjectItem(root, "username")->valuestring;
    char *email = cJSON_GetObjectItem(root, "email")->valuestring;
    char *content = cJSON_GetObjectItem(root, "content")->valuestring;
    printf("准备写入数据库啦！\n");
    TheUser user;
    if(user.userRegister(username,password,email))
        return 1;
    else
        return 0;
}

/**************************************************/
/*名称：user_login
/*描述：用户登录
/*作成日期：2019.9.3
/*参数：参数1：参数名称 prop、参数类型 struct User *、输入参数、参数含义：用户
		参数2：参数名称 userid、参数类型 int、输入参数、参数含义：用户ID
		参数3：参数名称 password、参数类型 char *、输入参数、参数含义：用户密码
/*返回值：int 1-成功，0-失败
/*作者：马文聪
/***************************************************/
int user_login(struct User *prop, int userid, char *password)
 {
 	TheUser user;
    const char* passwd = user.userUpasswdSelect(userid);
 	if (strcmp(password, passwd) == 0)
 	{
 		return 1;
 	}
 	else
    {
 		return 0;
 	}
 }
int user_logout(struct User * prop) {
    printf("user %s logout\n", prop->u_name);
    memset(prop->u_name, '\0', sizeof(prop->u_name));
    prop->u_id = 0;
    prop->is_online = 0;
    return 1;
}










