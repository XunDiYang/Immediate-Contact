//
// Created by mawencong on 2019/9/3.
//

#ifndef UIMAIN_TEMP_LOGSIGN_H
#define UIMAIN_TEMP_LOGSIGN_H



#include<gtk/gtk.h>
#include<iostream>
#include<string>
#include<string.h>
#include<regex>
#include "client.h"
#include "setting.h"
void createFriendsList();
void createGroupList();
void createMessageList();
void createInputWindow();//创建聊天输入框
void createChatWindow_();//创建聊天对话框
void createChatWindow(int data);
void createInfoDetailVbox();

extern GtkWidget *windowLog,*windowSign;//登录窗口，注册窗口
extern GtkWidget* windowDate;//日历窗口
extern GtkWidget *mainWindow; //主窗口
void createErrorDialog(gchar *message);
void createMessageDialog(gchar *message);

void selectGender(gpointer data);

void dateBtn(GtkWidget* button,GtkCalendar* data);
void selectDate(GtkWidget* buttonS,GtkCalendar* data);

void on_button_clicked_L(GtkWidget* button,gpointer data);
void on_button_clicked_S(GtkWidget* button,gpointer data);
void windowChangeToLog(GtkWidget* button,gpointer data);
void windowChangeToSign(GtkWidget* button,gpointer data);
GtkWidget* createLogWindow();
GtkWidget* createSignWindow();

/********主界面函数**********/
//列表切换的显示与隐藏
void hideFriendsLists();
void showFriendsLists();

void hideGroupLists();
void showGroupLists();

void hideMessageLists();
void showMessageLists();









#endif //UIMAIN_TEMP_LOGSIGN_H
