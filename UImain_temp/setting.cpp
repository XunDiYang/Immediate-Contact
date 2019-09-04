//
// Created by mawencong on 2019/9/3.
//


#include <gtk/gtk.h>
#include<string.h>
#include"setting.h"

GtkWidget* chooser;
GtkWidget *settingWindow;
GtkWidget *settingFixed;
GtkWidget *buttonu_box;//上面两个按键所属
GtkWidget *buttonl;//系统设置按键
GtkWidget *buttonr;//个人设置按键
GtkWidget *buttonl_box1;//日夜模式按键所属
GtkWidget *model1;//日按键
GtkWidget *model2;//夜按键
GtkWidget *modeltext;
GtkWidget *buttonl_box2;//字体大小按键所属
GtkWidget *bigsize;
GtkWidget *midsize;
GtkWidget *smasize;
GtkWidget *wordtext;
GtkWidget *buttonr_box1;//头像所属;
GtkWidget *icontext;
GtkWidget *buttonr_box2;//名称所属
GtkWidget *nametext;
GtkWidget *name_entry;
GtkWidget *buttonr_box3;//密码所属
GtkWidget *passwdtext;
GtkWidget *passwd_entry;
GtkWidget *buttonr_box4;//确认密码
GtkWidget *repasswdtext;
GtkWidget *repasswd_entry;
GtkWidget *buttonr_box5;//确认邮箱
GtkWidget *emailtext;
GtkWidget *email_entry;
GtkWidget *con_box;//按钮box
GtkWidget *con_button;//确认
GdkColor color1,color2;//白色和黑色

int shift=1;//栏目代号，1代表系统设置，0表示个人设置
int model=1;//模式代号，1代表日间，0表示夜间

void show_hide()//隐藏和展示下端按键
{
    if(shift==1)
    {
        gtk_widget_show(buttonl_box1);
        gtk_widget_show(buttonl_box2);
        gtk_widget_hide(buttonr_box1);
        gtk_widget_hide(buttonr_box2);
        gtk_widget_hide(buttonr_box3);
        gtk_widget_hide(buttonr_box4);
        gtk_widget_hide(buttonr_box5);
        gtk_widget_hide(con_box);
    }
    else if(shift==0)
    {
        gtk_widget_show(buttonr_box1);
        gtk_widget_show(buttonr_box2);
        gtk_widget_show(buttonr_box3);
        gtk_widget_show(buttonr_box4);
        gtk_widget_show(con_box);
        gtk_widget_show(buttonr_box5);
        gtk_widget_hide(buttonl_box1);
        gtk_widget_hide(buttonl_box2);
    }
}

void screateErrorDialog(gchar *message)
{
    GtkDialog* dialog;
    GtkMessageType type;
    type = GTK_MESSAGE_ERROR;
    dialog= reinterpret_cast<GtkDialog *>(gtk_message_dialog_new(NULL,
                                                                 static_cast<GtkDialogFlags>(GTK_DIALOG_MODAL |
                                                                                             GTK_DIALOG_DESTROY_WITH_PARENT),
                                                                 type,
                                                                 GTK_BUTTONS_OK,
                                                                 message));
    gtk_window_set_transient_for(GTK_WINDOW(dialog),GTK_WINDOW(settingWindow));
    gtk_dialog_run(dialog);
    gtk_widget_destroy(reinterpret_cast<GtkWidget *>(dialog));
}

void con_pressed(GtkButton *button, gpointer data)//确认按键回调函数
{
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(passwd_entry));
    const gchar *rpassword = gtk_entry_get_text(GTK_ENTRY(repasswd_entry));
    if(strlen(password)==0)
    {
        screateErrorDialog("密码不能为空！");
    }
    else if(g_strcmp0(password,rpassword)!=0)
    {
        screateErrorDialog("两次输入的密码不一致!");
    }
    else if(strlen(password)<8)
    {
        screateErrorDialog("密码长度至少为8位！");
    }
    else
    {
        screateErrorDialog("修改成功！");
    }
}

void deall_pressed(GtkButton *button, gpointer data)//按上下左按钮的回调函数
{
    if(shift==0)
    {
        shift=1;
        show_hide();
    }
    return;
}

void dealr_pressed(GtkButton *button, gpointer data)//按下上右按钮的回调函数
{
    if(shift==1)
    {
        shift=0;
        show_hide();
    }
    return;
}

void model1_pressed(GtkButton *button, gpointer data)//按下日间模式
{
    if(model==0)
    {
        model=1;
        gtk_widget_modify_bg(settingWindow,GTK_STATE_NORMAL,&color1);
        gtk_label_set_markup(GTK_LABEL(modeltext),
                             "<span foreground='gray'>日夜模式：</span>");
        gtk_label_set_markup(GTK_LABEL(wordtext),
                             "<span foreground='gray'>字体大小：</span>");
        gtk_label_set_markup(GTK_LABEL(icontext),
                             "<span foreground='gray'>更改头像：</span>");
        gtk_label_set_markup(GTK_LABEL(nametext),
                             "<span foreground='gray'>更改名称：</span>");
        gtk_label_set_markup(GTK_LABEL(passwdtext),
                             "<span foreground='gray'>更改密码：</span>");
        gtk_label_set_markup(GTK_LABEL(repasswdtext),
                             "<span foreground='gray'>确认密码：</span>");
        gtk_label_set_markup(GTK_LABEL(emailtext),
                             "<span foreground='gray'>确认邮箱：</span>");
    }
}

void model2_pressed(GtkButton *button, gpointer data)//按下夜间模式
{
    if(model==1)
    {
        model=0;
        gtk_widget_modify_bg(settingWindow,GTK_STATE_NORMAL,&color2);
        gtk_label_set_markup(GTK_LABEL(modeltext),
                             "<span foreground='white'>日夜模式：</span>");
        gtk_label_set_markup(GTK_LABEL(wordtext),
                             "<span foreground='white'>字体大小：</span>");
        gtk_label_set_markup(GTK_LABEL(icontext),
                             "<span foreground='white'>更改头像：</span>");
        gtk_label_set_markup(GTK_LABEL(nametext),
                             "<span foreground='white'>更改名称：</span>");
        gtk_label_set_markup(GTK_LABEL(passwdtext),
                             "<span foreground='white'>更改密码：</span>");
        gtk_label_set_markup(GTK_LABEL(repasswdtext),
                             "<span foreground='white'>确认密码：</span>");
        gtk_label_set_markup(GTK_LABEL(emailtext),
                             "<span foreground='white'>确认邮箱：</span>");
    }
}

void size1_pressed(GtkButton *button, gpointer data)//按下大字体
{
    gtk_label_set_markup(GTK_LABEL(modeltext),
                         "<span font_desc='14'>日夜模式：</span>");
    gtk_label_set_markup(GTK_LABEL(wordtext),
                         "<span font_desc='14'>字体大小：</span>");
    gtk_label_set_markup(GTK_LABEL(icontext),
                         "<span font_desc='14'>更改头像：</span>");
    gtk_label_set_markup(GTK_LABEL(nametext),
                         "<span font_desc='14'>更改名称：</span>");
    gtk_label_set_markup(GTK_LABEL(passwdtext),
                         "<span font_desc='14'>更改密码：</span>");
    gtk_label_set_markup(GTK_LABEL(repasswdtext),
                         "<span font_desc='14'>确认密码：</span>");
    gtk_label_set_markup(GTK_LABEL(emailtext),
                         "<span font_desc='14'>确认邮箱：</span>");
}

void size2_pressed(GtkButton *button, gpointer data)//按下中字体
{
    gtk_label_set_markup(GTK_LABEL(modeltext),
                         "<span font_desc='11'>日夜模式：</span>");
    gtk_label_set_markup(GTK_LABEL(wordtext),
                         "<span font_desc='11'>字体大小：</span>");
    gtk_label_set_markup(GTK_LABEL(icontext),
                         "<span font_desc='11'>更改头像：</span>");
    gtk_label_set_markup(GTK_LABEL(nametext),
                         "<span font_desc='11'>更改名称：</span>");
    gtk_label_set_markup(GTK_LABEL(passwdtext),
                         "<span font_desc='11'>更改密码：</span>");
    gtk_label_set_markup(GTK_LABEL(repasswdtext),
                         "<span font_desc='11'>确认密码：</span>");
    gtk_label_set_markup(GTK_LABEL(emailtext),
                         "<span font_desc='11'>确认邮箱：</span>");
}

void size3_pressed(GtkButton *button, gpointer data)//按下小字体
{
    gtk_label_set_markup(GTK_LABEL(modeltext),
                         "<span font_desc='8'>日夜模式：</span>");
    gtk_label_set_markup(GTK_LABEL(wordtext),
                         "<span font_desc='8'>字体大小：</span>");
    gtk_label_set_markup(GTK_LABEL(icontext),
                         "<span font_desc='8'>更改头像：</span>");
    gtk_label_set_markup(GTK_LABEL(nametext),
                         "<span font_desc='8'>更改名称：</span>");
    gtk_label_set_markup(GTK_LABEL(passwdtext),
                         "<span font_desc='8'>更改密码：</span>");
    gtk_label_set_markup(GTK_LABEL(repasswdtext),
                         "<span font_desc='8'>确认密码：</span>");
    gtk_label_set_markup(GTK_LABEL(emailtext),
                         "<span font_desc='8'>确认邮箱：</span>");
}

void creatSettingWindow()
{
    //使用settingWindow
    settingWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //settingWindow设置
    gtk_window_set_title (GTK_WINDOW (settingWindow), g_locale_to_utf8("设置",-1,NULL,NULL,NULL));//窗口标题设置
    gtk_window_set_position(GTK_WINDOW(settingWindow), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(settingWindow,600,400);
    gtk_container_set_border_width(GTK_CONTAINER(settingWindow), 10);

    //使用上端的box和button
    buttonu_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttonl = gtk_button_new_with_label("系统设置");
    buttonr = gtk_button_new_with_label("个人信息设置");

    //设置按键并加入box
    gtk_widget_set_size_request(buttonl,300,30);
    gtk_widget_set_size_request(buttonl,300,30);
    gtk_widget_set_size_request(buttonu_box,600,30);
    g_signal_connect(buttonl,"pressed",G_CALLBACK( deall_pressed),NULL);
    g_signal_connect(buttonr,"pressed",G_CALLBACK( dealr_pressed),NULL);
    gtk_container_add(GTK_CONTAINER(buttonu_box),buttonl);
    gtk_container_add(GTK_CONTAINER(buttonu_box),buttonr);

    //日夜模式按键和box
    color1={0,0xffff,0xffff,0xffff};
    color2={0,0,0,0};
    buttonl_box1 = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    model1 = gtk_button_new_with_label("day");
    model2 = gtk_button_new_with_label("night");
    g_signal_connect(model1,"pressed",G_CALLBACK( model1_pressed),NULL);
    g_signal_connect(model2,"pressed",G_CALLBACK( model2_pressed),NULL);
    modeltext=gtk_label_new("日夜模式:");
    gtk_box_pack_start (GTK_BOX (buttonl_box1), modeltext, TRUE, TRUE, 2);
    gtk_box_pack_start (GTK_BOX (buttonl_box1), model1, TRUE, TRUE, 2);
    gtk_box_pack_start (GTK_BOX (buttonl_box1), model2, TRUE, TRUE, 2);

    //字体
    buttonl_box2 = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    bigsize = gtk_button_new_with_label("大");
    midsize= gtk_button_new_with_label("中");
    smasize= gtk_button_new_with_label("小");
    g_signal_connect(bigsize,"pressed",G_CALLBACK( size1_pressed),NULL);
    g_signal_connect(midsize,"pressed",G_CALLBACK( size2_pressed),NULL);
    g_signal_connect(smasize,"pressed",G_CALLBACK( size3_pressed),NULL);
    wordtext=gtk_label_new("字体大小：");
    gtk_box_pack_start (GTK_BOX (buttonl_box2), wordtext, TRUE, TRUE, 2);
    gtk_box_pack_start (GTK_BOX (buttonl_box2), bigsize, TRUE, TRUE, 2);
    gtk_box_pack_start (GTK_BOX (buttonl_box2), midsize, TRUE, TRUE, 2);
    gtk_box_pack_start (GTK_BOX (buttonl_box2), smasize, TRUE, TRUE, 2);

    //用户头像
    buttonr_box1=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    icontext=gtk_label_new("更改头像：");
    gtk_box_pack_start (GTK_BOX (buttonr_box1), icontext, TRUE, TRUE, 2);
    //添加文件选择按钮，并过滤非图片
    chooser = gtk_file_chooser_button_new("选择你的头像",GTK_FILE_CHOOSER_ACTION_OPEN);
    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter,"*.jpg");
    gtk_file_filter_add_pattern(filter,"*.png");
    gtk_file_filter_add_pattern(filter,"*.gif");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(chooser),GTK_FILE_FILTER(filter));
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(chooser),"/etc");
    gtk_box_pack_start(GTK_BOX(buttonr_box1),chooser,TRUE,TRUE,2);

    //用户名
    buttonr_box2=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    nametext=gtk_label_new("更改名称：");
    gtk_box_pack_start (GTK_BOX (buttonr_box2), nametext, TRUE, TRUE, 2);
    name_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(name_entry),TRUE);
    gtk_box_pack_start (GTK_BOX (buttonr_box2), name_entry, TRUE, TRUE, 2);

    //用户密码
    buttonr_box3=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    passwdtext=gtk_label_new("更改密码：");
    gtk_box_pack_start (GTK_BOX (buttonr_box3),passwdtext, TRUE, TRUE, 2);
    passwd_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(passwd_entry),FALSE);
    gtk_box_pack_start (GTK_BOX (buttonr_box3), passwd_entry, TRUE, TRUE, 2);

    //确认密码
    buttonr_box4=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    repasswdtext=gtk_label_new("确认密码：");
    gtk_box_pack_start (GTK_BOX (buttonr_box4),repasswdtext, TRUE, TRUE, 2);
    repasswd_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(repasswd_entry),FALSE);
    gtk_box_pack_start (GTK_BOX (buttonr_box4), repasswd_entry, TRUE, TRUE, 2);

    //确认邮箱
    buttonr_box5=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    emailtext=gtk_label_new("确认邮箱：");
    gtk_box_pack_start (GTK_BOX (buttonr_box5),emailtext, TRUE, TRUE, 2);
    email_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(email_entry),TRUE);
    gtk_box_pack_start (GTK_BOX (buttonr_box5), email_entry, TRUE, TRUE, 2);

    //确认按键
    con_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    con_button = gtk_button_new_with_label("确认");
    g_signal_connect(con_button,"pressed",G_CALLBACK( con_pressed),NULL);
    gtk_box_pack_start (GTK_BOX (con_box), con_button, TRUE, TRUE, 2);

    //创建fix并加入所有box
    settingFixed=gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(settingWindow) , settingFixed);
    gtk_fixed_put(GTK_FIXED(settingFixed),buttonu_box,0,0);
    gtk_fixed_put(GTK_FIXED(settingFixed),buttonl_box1,0,60);
    gtk_fixed_put(GTK_FIXED(settingFixed),buttonl_box2,0,110);
    gtk_fixed_put(GTK_FIXED(settingFixed),buttonr_box1,45,60);
    gtk_fixed_put(GTK_FIXED(settingFixed),buttonr_box2,0,110);
    gtk_fixed_put(GTK_FIXED(settingFixed),buttonr_box3,0,160);
    gtk_fixed_put(GTK_FIXED(settingFixed),buttonr_box4,0,200);
    gtk_fixed_put(GTK_FIXED(settingFixed),buttonr_box5,0,240);
    gtk_fixed_put(GTK_FIXED(settingFixed),con_box,170,300);
    //显示win
    gtk_widget_show_all(settingWindow);	// 显示窗口控件
    show_hide();
}
