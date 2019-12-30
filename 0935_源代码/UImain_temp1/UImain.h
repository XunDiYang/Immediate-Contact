//
// Created by mawencong on 2019/9/3.
//

//

#ifndef UIMAIN_UIMAIN_H
#define UIMAIN_UIMAIN_H
#include <gtk/gtk.h>
#include <time.h>
#include <glib.h>
#include <string.h>
#include <stdio.h>
#include "LogSign.h"
#include "setting.h"
#include "client.h"


void getNowTime(char *nowTime); //获取系统时间
GtkWidget *imgBtnCreate(char *imgPath); //图片按钮创建
void setScrollPos(int length); //滑动条位置显示在最底端

void creatMainWindow(); //创建主界面窗口
void createToolbarBtn(); //创建工具栏按钮列表
void createInputWindow();//创建聊天输入框
void createChatWindow();//创建聊天对话框
void createChatWindow(int data);

//工具栏按钮触发函数_对应弹出消息列表/好友列表/群组列表/设置/帮助界面
void buttonPressFriendsLists();
void buttonPressGroupLists();
void buttonPressMessageLists();
void buttonPressSetting();
void buttonPressHelp();
void buttonPressAdd();

GtkWidget *creatHelpWindow();
void creatAddWindow();
GtkWidget *createPopoutWindow();
void createInfoDetailVbox();


void buttonPressPopout(); //对话窗口弹出

void buttonPressSendMessage(); //发送信息
void buttonPressSendFile();

//信息列表
GtkWidget *friendUsername[20]; //好友列表
GtkWidget *grounpName[20]; //群组列表
GtkWidget *messageList[20]; //消息列表



//信息列表的滑动栏和Vbox
GtkWidget *createInfoVbox();
GtkWidget *createInfoScroll();

void createFriendsList();
void createGroupList();
void createMessageList();

//增删好友/群组界面
void add_pressed(GtkButton *button, gpointer data);
void del_pressed(GtkButton *button, gpointer data);
void gadd_pressed(GtkButton *button, gpointer data);
void gdel_pressed(GtkButton *button, gpointer data);
void cgadd_pressed(GtkButton *button, gpointer data);

//当前好友 / 群组 / 消息 数目
const int GROUPS_NUM = 20;
const int MESSAGE_NUM = 20;

#endif //UIMAIN_TEMP_UIMAIN_H
