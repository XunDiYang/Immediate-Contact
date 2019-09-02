//
// Created by 李心志 on 2019/9/2.
//

#ifndef UIMAIN_LOGSIGN_H
#define UIMAIN_LOGSIGN_H
#include<gtk/gtk.h>
#include<iostream>
#include<string>
#include<string.h>
#include<regex>
extern GtkWidget *windowLog,*windowSign;//登录窗口，注册窗口
extern GtkWidget* windowDate;//日历窗口
extern GtkWidget *mainWindow; //主窗口
void createErrorDialog(gchar *message);

void selectGender(gpointer data);

void dateBtn(GtkWidget* button,GtkCalendar* data);
void selectDate(GtkWidget* buttonS,GtkCalendar* data);

void on_button_clicked_L(GtkWidget* button,gpointer data);
void on_button_clicked_S(GtkWidget* button,gpointer data);
void windowChangeToLog(GtkWidget* button,gpointer data);
void windowChangeToSign(GtkWidget* button,gpointer data);
GtkWidget* createLogWindow();
GtkWidget* createSignWindow();



#endif //UIMAIN_LOGSIGN_H
