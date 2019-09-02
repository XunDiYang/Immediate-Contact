//
// Created by 李心志 on 2019/9/2.
//登录注册界面合并
#include "logSignUI.h"
using namespace std;
static GtkWidget* entry1;
static GtkWidget* entry2;
static GtkWidget* entryS1;//注册用户名
static GtkWidget* entryS2;//注册密码
static GtkWidget* entryS3;//注册密码确认
static GtkWidget* entryMail;//输入的邮箱
static gboolean male = TRUE;
static gboolean female = FALSE;
static guint year=0,month=0,day=0;

GtkWidget* windowLog;
GtkWidget* windowSign;
GtkWidget* windowDate;
GtkWidget* mainWindow;
string strY = to_string(year);
string strM = to_string(month+1);
string strD = to_string(day);
GtkWidget *buttonSelectDate;

regex r("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+\\\\.[a-zA-Z0-9_-]+$");
void createErrorDialog(gchar *message)
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
    gtk_window_set_transient_for(GTK_WINDOW(dialog),GTK_WINDOW(windowSign));
    gtk_dialog_run(dialog);
    gtk_widget_destroy(reinterpret_cast<GtkWidget *>(dialog));
}
void selectGender(gpointer data)
{
    switch((gint64)data)
    {
        case 1:male = TRUE;
            female = FALSE;
            break;
        case 2:female = TRUE;
            male = FALSE;
            break;
        default:
            break;
    }
}
void dateBtn(GtkWidget* button,GtkCalendar* data)
{
    gtk_calendar_get_date(GTK_CALENDAR(data),&year,&month,&day);
    g_print("%d%d%d",year,month+1,day);
    //对按钮显示的内容进行修改，使按钮显示选择的日期
    strY = to_string(year);
    strM = to_string(month+1);
    strD = to_string(day);
    string ll=strY+"年"+strM+"月"+strD+"日";
    gtk_button_set_label(GTK_BUTTON(buttonSelectDate),ll.c_str());
    gtk_widget_hide(windowDate);
}
void selectDate(GtkWidget* buttonS,GtkCalendar* data)
{
    GtkDialog* box;
    GtkWidget* calendar;
    GtkWidget* button;
    windowDate = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(windowDate),"选择日期");
    gtk_window_set_default_size(GTK_WINDOW(windowDate),400,200);
    gtk_window_set_position(GTK_WINDOW(windowDate),GTK_WIN_POS_CENTER_ALWAYS);
    gtk_container_set_border_width(GTK_CONTAINER(windowDate),5);

    box = reinterpret_cast<GtkDialog *>(gtk_vbox_new(FALSE, 0));
    gtk_container_add(GTK_CONTAINER(windowDate), reinterpret_cast<GtkWidget *>(box));
    calendar = gtk_calendar_new();
    gtk_box_pack_start(GTK_BOX(box),calendar,FALSE,FALSE,0);
    button = gtk_button_new_from_stock(GTK_STOCK_OK);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,0);
    g_signal_connect(G_OBJECT(button),"clicked",
                     G_CALLBACK(dateBtn),calendar);

    gtk_widget_show_all(windowDate);

}
//Login when clicked
void on_button_clicked_L(GtkWidget* button,gpointer data)
{
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry1));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry2));
    printf("username:%s \n",username);
    printf("password:%s \n",password);
    gtk_widget_hide(GTK_WIDGET(data));
    gtk_widget_show_all(mainWindow);
}
//Signup when clicked
void on_button_clicked_S(GtkWidget* button,gpointer data)
{
    const char *username = gtk_entry_get_text(GTK_ENTRY(entryS1));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entryS2));
    const gchar *rpassword = gtk_entry_get_text(GTK_ENTRY(entryS3));
    const char *email = gtk_entry_get_text(GTK_ENTRY(entryMail));
    if(strlen(username)==0||strlen(password)==0)
    {
        createErrorDialog("用户名或密码不能为空！");
    }
    else if(g_strcmp0(password,rpassword)!=0)
    {
        createErrorDialog("两次输入的密码不一致!");
    }
    else if(strlen(password)<8)
    {
        createErrorDialog("密码长度至少为8位！");
    }
    else if(!regex_match("email@qq.com",r))
    {
        g_print("!!!!!!!");
    }
    else
    {
        int op = 1;
        const char* usernameClient = username;
        const char* passwordClient = password;
        const char* emailClient = email;
        g_print("%d%s%s%s\n",op,usernameClient,passwordClient,emailClient);
    }
}
void windowChangeToLog(GtkWidget* button,gpointer data)
{
    gtk_widget_hide(GTK_WIDGET(data));
    gtk_widget_show_all(windowLog);
}
void windowChangeToSign(GtkWidget* button,gpointer data)
{
    gtk_widget_hide(GTK_WIDGET(data));
    gtk_widget_show_all(windowSign);
}

GtkWidget* createLogWindow()
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button;
    GtkWidget *buttonC;
    GtkWidget *sep;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"LOGIN");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),20);

    box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),box);
    box1 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,5);
    box2 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);
    sep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,5);

    label1 = gtk_label_new("username:");
    entry1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box1),entry1,FALSE,FALSE,5);

    label2 = gtk_label_new("password:");
    entry2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
    gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),entry2,FALSE,FALSE,5);

    button = gtk_button_new_with_label("Log in");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked_L),window);
    //g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),window);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
    buttonC = gtk_button_new_with_label("Sign up");
    g_signal_connect(G_OBJECT(buttonC),"clicked",G_CALLBACK(windowChangeToSign),window);
    gtk_box_pack_start(GTK_BOX(box),buttonC,FALSE,FALSE,5);
    return window;

}
GtkWidget* createSignWindow()
{
    GtkWidget *windowL;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *box4;
    GtkWidget *boxSe;
    GtkWidget *boxMail;

    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *labelSelectDate;
    GtkWidget *labelSe;
    GtkWidget *labelMail;

    GtkWidget *button;
    GtkWidget *buttonC;
    GtkWidget *chooser;
    GtkWidget *sep;

    windowL = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(windowL),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(windowL),"SIGNUP");
    gtk_window_set_position(GTK_WINDOW(windowL),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(windowL),20);

    box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(windowL),box);
    box1 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box1,FALSE,FALSE,5);
    box2 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);
    box3 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,5);
    boxMail = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),boxMail,FALSE,FALSE,5);
    boxSe = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),boxSe,FALSE,FALSE,5);
    box4 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,5);
    sep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,5);
//添加文件选择按钮，并过滤非图片
    chooser = gtk_file_chooser_button_new("选择你的头像",GTK_FILE_CHOOSER_ACTION_OPEN);
    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter,"*.jpg");
    gtk_file_filter_add_pattern(filter,"*.png");
    gtk_file_filter_add_pattern(filter,"*.gif");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(chooser),GTK_FILE_FILTER(filter));
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(chooser),"/etc");
    gtk_box_pack_start(GTK_BOX(box),chooser,FALSE,FALSE,5);
    gchar* uri = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(chooser));
    cout<<uri<<endl;
    label1 = gtk_label_new("              username:");
    entryS1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box1),entryS1,FALSE,FALSE,5);

    label2 = gtk_label_new("              password:");
    entryS2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entryS2),FALSE);
    gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),entryS2,FALSE,FALSE,5);

    label3 = gtk_label_new("password again:");
    entryS3 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entryS3),FALSE);
    gtk_box_pack_start(GTK_BOX(box3),label3,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box3),entryS3,FALSE,FALSE,5);

    labelMail = gtk_label_new("write your e-mail");
    entryMail = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(boxMail),labelMail,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(boxMail),entryMail,FALSE,FALSE,5);

    labelSe = gtk_label_new("                   gender:");
    gtk_box_pack_start(GTK_BOX(boxSe),labelSe,FALSE,FALSE,5);
    GtkWidget* buttonSe;
    GSList* group = NULL;
    buttonSe = gtk_radio_button_new_with_label(group,"male");
    g_signal_connect(G_OBJECT(buttonSe),"released",G_CALLBACK(selectGender),(gpointer)1);
    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(buttonSe));
    gtk_box_pack_start(GTK_BOX(boxSe),buttonSe,FALSE,FALSE,5);
    buttonSe = gtk_radio_button_new_with_label(group,"female");
    g_signal_connect(G_OBJECT(buttonSe),"released",G_CALLBACK(selectGender),(gpointer)2);
    gtk_box_pack_start(GTK_BOX(boxSe),buttonSe,FALSE,FALSE,5);

    labelSelectDate = gtk_label_new(" select birthday:");
    gtk_box_pack_start(GTK_BOX(box4),labelSelectDate,FALSE,FALSE,5);
    buttonSelectDate = gtk_button_new_with_label("请选择日期");
    gtk_box_pack_start(GTK_BOX(box4),buttonSelectDate,FALSE,FALSE,5);
    g_signal_connect(G_OBJECT(buttonSelectDate),"clicked",
                     G_CALLBACK(selectDate),NULL);

    button = gtk_button_new_with_label("Sign up");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked_S),NULL);
    //g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),windowL);
    gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,5);
    buttonC = gtk_button_new_with_label("Log in");
    g_signal_connect(G_OBJECT(buttonC),"clicked",G_CALLBACK(windowChangeToLog),windowL);
    gtk_box_pack_start(GTK_BOX(box),buttonC,FALSE,FALSE,5);
    return windowL;
}
