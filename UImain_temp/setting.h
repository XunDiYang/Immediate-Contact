//
// Created by mawencong on 2019/9/3.
//

#ifndef UIMAIN_TEMP_SETTING_H
#define UIMAIN_TEMP_SETTING_H
#include <gtk/gtk.h>
extern GtkWidget *chooser;

void show_hide();//隐藏和展示下端按键
void deall_pressed(GtkButton *button, gpointer data);//按上下左按钮的回调函数
void dealr_pressed(GtkButton *button, gpointer data);//按下上右按钮的回调函数
void model1_pressed(GtkButton *button, gpointer data);//按下日间模式
void model2_pressed(GtkButton *button, gpointer data);//按下夜间模式
void size1_pressed(GtkButton *button, gpointer data);//按下大字体
void size2_pressed(GtkButton *button, gpointer data);//按下中字体
void size3_pressed(GtkButton *button, gpointer data);//按下小字体
void creatSettingWindow();


#endif //UIMAIN_TEMP_SETTING_H
