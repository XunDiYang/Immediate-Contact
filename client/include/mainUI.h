//
// Created by mima123456 on 2019/9/2.
//

#ifndef UIMAIN_UIMAIN_H
#define UIMAIN_UIMAIN_H
#include <gtk/gtk.h>
#include <time.h>
#include <glib.h>
#include <string.h>
#include <stdio.h>
#include "LogSign.h"

//控件声明


void getNowTime(char *nowTime); //获取系统时间
GtkWidget *imgBtnCreate(char *imgPath); //图片按钮创建
void setScrollPos(int length); //滑动条位置显示在最底端

void creatMainWindow(); //创建主界面窗口
void createToolbarBtn(); //创建工具栏按钮列表
void createInfoLists();//创建信息列表
void createInputWindow();//创建聊天输入框
void createChatWindow();//创建聊天对话框


//工具栏按钮触发函数_对应弹出消息列表/好友列表/群组列表/设置/帮助界面
void buttonPressLists();
void buttonPressSetting();
void buttonPressHelp();
GtkWidget *creatSettingWindow();
GtkWidget *creatHelpWindow();


void buttonPressPopout(); //对话窗口弹出
void messagePrint(char *chatInfo); //打印消息
void buttonPressSendMessage(); //发送信息

#endif //UIMAIN_UIMAIN_H
