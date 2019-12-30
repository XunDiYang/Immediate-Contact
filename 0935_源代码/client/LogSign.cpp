//
// Created by mawencong on 2019/9/3.
//

#include "LogSign.h"
//

//登录注册界面合并
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

extern int judgeLogin;
extern int judgeSign;
extern int current_id;//current user
extern int talk_to_user; //ID
extern int current_friend_num;
extern int current_group_num;

GtkWidget* windowLog;
GtkWidget* windowSign;
GtkWidget* windowDate;
GtkWidget* mainWindow;
extern GtkWidget *chooser;
string strY = to_string(year);
string strM = to_string(month+1);
string strD = to_string(day);
unsigned int birthdayPass = 0;
GtkWidget *buttonSelectDate;

regex r("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+\\\\.[a-zA-Z0-9_-]+$");
/************************************************************************
*名称:createErrorDialog
*描述:创建一个错误对话框
*作成日期:2019.08.30
*参数:gchar *message
*返回值:void
*作者:李心志
************************************************************************/
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
/************************************************************************
*名称:createErrorDialog
*描述:创建一个错误对话框
*作成日期:2019.08.30
*参数:gchar *message
*返回值:void
*作者:李心志
************************************************************************/
void createMessageDialog(gchar *message)
{
    GtkDialog* dialog;
    GtkMessageType type;
    type = GTK_MESSAGE_INFO;
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
/************************************************************************
*名称:selectGender
*描述:相应性别选择按钮，修改male与female值
*作成日期:2019.09.02
*参数:gpointer data
*返回值:void
*作者:李心志
************************************************************************/
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
/************************************************************************
*名称:dateBtn
*描述:相应日期选择，并记录选择的日期
*作成日期:2019.09.02
*参数:GtkWidget* button,GtkCalendar* data
*返回值:void
*作者:李心志
************************************************************************/
void dateBtn(GtkWidget* button,GtkCalendar* data)
{
    gtk_calendar_get_date(GTK_CALENDAR(data),&year,&month,&day);
    //对按钮显示的内容进行修改，使按钮显示选择的日期
    strY = to_string(year);
    strM = to_string(month+1);
    strD = to_string(day);
    string ll=strY+"年"+strM+"月"+strD+"日";
    birthdayPass = 2019 - year;

    gtk_button_set_label(GTK_BUTTON(buttonSelectDate),ll.c_str());
    gtk_widget_hide(windowDate);
}

/************************************************************************
*名称:selectDate
*描述:相应日期选择按钮
*作成日期:2019.08.31
*参数:GtkWidget* buttonS,GtkCalendar* data
*返回值:void
*作者:李心志
************************************************************************/
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
/************************************************************************
*名称:on_button_clicked_L
*描述:登录按钮按下后的相应函数
*作成日期:2019.08.31
*参数:GtkWidget* button,GtkCalendar* data
*返回值:void
*作者:李心志
************************************************************************/
void on_button_clicked_L(GtkWidget* button,gpointer data)
{
    judgeLogin = 0;
    judgeSign = 0;
    current_id = 0;//current user
    talk_to_user = 0; //ID
    current_friend_num = 0;
    current_group_num = 0;
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry1));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entry2));
    printf("username:%s \n",username);
    printf("password:%s \n",password);
    int user_id = atoi(username);

    char *password_trns = const_cast<char *>(password);
    login(user_id, password_trns);
    while(1){
        if(judgeLogin == 1 && current_friend_num >= 0)
        {
            current_id = user_id;
            g_print("yes~");
            createFriendsList();//创建好友列表
            createGroupList();
            createMessageList();

            createInputWindow(); //创建聊天输入框
            createChatWindow_(); //创建聊天对话框
//            createInfoDetailVbox();
            gtk_widget_hide(GTK_WIDGET(data));
            gtk_widget_show_all(mainWindow);
            hideMessageLists();
            hideFriendsLists();
            showGroupLists();
            break;
        }
        else if(judgeLogin == -1){
            createErrorDialog("ID or password error!");
            break;
        }
    }


}
//Signup when clicked
/************************************************************************
*名称:on_button_clicked_L
*描述:注册按钮按下后的相应函数
*作成日期:2019.08.31
*参数:GtkWidget* button,GtkCalendar* data
*返回值:void
*作者:李心志
************************************************************************/
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
    else if(strlen(password)<1)
    {
        createErrorDialog("密码长度至少为8位！");
    }
    else
    {
        int op = 1;
        char* usernameClient = const_cast<char *>(username);
        char* passwordClient = const_cast<char *>(password);
        char* emailClient = const_cast<char *>(email);
        //gchar* uri = gtk_file_chooser_get_uri(GTK_FILE_CHOOSER(chooser));
        regist(usernameClient, passwordClient ,emailClient);
        //g_print("%s\n",uri);
        g_print("%d%s%s%s\n",op,usernameClient,passwordClient,emailClient);
        g_print("%d 岁\n",birthdayPass);
    }
}
/************************************************************************
*名称:windowChangeToLog
*描述:切换为登录界面
*作成日期:2019.08.31
*参数:GtkWidget* button,GtkCalendar* data
*返回值:void
*作者:李心志
************************************************************************/
void windowChangeToLog(GtkWidget* button,gpointer data)
{
    gtk_widget_hide(GTK_WIDGET(data));
    gtk_widget_show_all(windowLog);
}
/************************************************************************
*名称:windowChangeToLog
*描述:切换为注册界面
*作成日期:2019.08.31
*参数:GtkWidget* button,GtkCalendar* data
*返回值:void
*作者:李心志
************************************************************************/
void windowChangeToSign(GtkWidget* button,gpointer data)
{
    gtk_widget_hide(GTK_WIDGET(data));
    gtk_widget_show_all(windowSign);
}
/************************************************************************
*名称:createLogWindow
*描述:创建登录界面，包括其中的必要控件
*作成日期:2019.08.31
*参数:无
*返回值:GtkWidget*
*作者:李心志
************************************************************************/
GtkWidget* createLogWindow()
{
    GtkWidget *window;
    GtkWidget *loginFixed;
    GtkImage *lgBgImg;
    GtkWidget *box;

    GtkWidget *button;
    GtkWidget *buttonC;
//    GtkWidget *sep;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size(GTK_WINDOW(window),500,500);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"LOGIN");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),0);

    loginFixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),loginFixed);

    lgBgImg = reinterpret_cast<GtkImage *>(gtk_image_new());
    gtk_image_set_from_file(lgBgImg,"images/login_bg.png");
    gtk_fixed_put(GTK_FIXED(loginFixed), reinterpret_cast<GtkWidget *>(lgBgImg), 0, 0);

    box = gtk_vbox_new(FALSE,0);
    gtk_widget_set_size_request(box,240,95);
    gtk_fixed_put(GTK_FIXED(loginFixed), box, 160, 153);

    entry1 = gtk_entry_new();
    gtk_widget_set_size_request(entry1,240,36);
    gtk_box_pack_start(GTK_BOX(box),entry1,FALSE,FALSE,0);

    entry2 = gtk_entry_new();
    gtk_widget_set_size_request(entry2,240,36);
    gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
    gtk_box_pack_start(GTK_BOX(box),entry2,FALSE,FALSE,20);


    button = gtk_button_new();
    GtkImage *loginLog;
    loginLog = reinterpret_cast<GtkImage *>(gtk_image_new());
    gtk_image_set_from_file(loginLog,"images/login_log.png");
    gtk_button_set_image(GTK_BUTTON(button),GTK_WIDGET(loginLog));
    gtk_fixed_put(GTK_FIXED(loginFixed), button, 175, 290);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked_L),window);

    buttonC = gtk_button_new();
    GtkImage *loginSign;
    loginSign = reinterpret_cast<GtkImage *>(gtk_image_new());
    gtk_image_set_from_file(loginSign,"images/login_sign.png");
    gtk_button_set_image(GTK_BUTTON(buttonC),GTK_WIDGET(loginSign));
    gtk_fixed_put(GTK_FIXED(loginFixed), buttonC, 340, 28);
    g_signal_connect(G_OBJECT(buttonC),"clicked",G_CALLBACK(windowChangeToSign),window);

    return window;

}
/************************************************************************
*名称:createLogWindow
*描述:创建注册界面，包括其中的必要控件
*作成日期:2019.08.31
*参数:无
*返回值:GtkWidget*
*作者:李心志
************************************************************************/
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
    GtkWidget *sep;
//窗口创建
    windowL = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(windowL),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(windowL),"SIGNUP");
    gtk_window_set_position(GTK_WINDOW(windowL),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(windowL),500,500);
    gtk_window_set_resizable(GTK_WINDOW(windowL), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(windowL),0);
//控件定义
    GtkWidget* signFixed;
    signFixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(windowL),signFixed);

    GtkImage *sgBgImg = reinterpret_cast<GtkImage *>(gtk_image_new());
    gtk_image_set_from_file(sgBgImg,"images/sign_bg.png");
    gtk_fixed_put(GTK_FIXED(signFixed), reinterpret_cast<GtkWidget *>(sgBgImg), 0, 0);

    box = gtk_vbox_new(FALSE,0);
    gtk_widget_set_size_request(box,240,95);
    gtk_fixed_put(GTK_FIXED(signFixed), box, 160, 153);

    entryS1 = gtk_entry_new();
    gtk_widget_set_size_request(entryS1,240,36);
    gtk_box_pack_start(GTK_BOX(box),entryS1,FALSE,FALSE,0);

    entryS2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entryS2),FALSE);
    gtk_widget_set_size_request(entryS2,240,36);
    gtk_box_pack_start(GTK_BOX(box),entryS2,FALSE,FALSE,20);

    entryS3 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entryS3),FALSE);
    gtk_widget_set_size_request(entryS3,240,36);
    gtk_box_pack_start(GTK_BOX(box),entryS3,FALSE,FALSE,0);

    entryMail = gtk_entry_new();
    gtk_widget_set_size_request(entryMail,240,36);
    gtk_box_pack_start(GTK_BOX(box),entryMail,FALSE,FALSE,20);

    GtkWidget* buttonSe;
    GtkWidget* boxGender;
    boxGender = gtk_hbox_new(TRUE,0);
    GSList* group = NULL;
    buttonSe = gtk_radio_button_new_with_label(group,"male");
    g_signal_connect(G_OBJECT(buttonSe),"released",G_CALLBACK(selectGender),(gpointer)1);
    group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(buttonSe));
    gtk_box_pack_start(GTK_BOX(boxGender),buttonSe,FALSE,FALSE,5);
    buttonSe = gtk_radio_button_new_with_label(group,"female");
    g_signal_connect(G_OBJECT(buttonSe),"released",G_CALLBACK(selectGender),(gpointer)2);
    gtk_box_pack_start(GTK_BOX(boxGender),buttonSe,FALSE,FALSE,5);
    gtk_widget_set_size_request(boxGender,240,36);
    gtk_box_pack_start(GTK_BOX(box),boxGender,FALSE,FALSE,0);


    buttonSelectDate = gtk_button_new_with_label("请选择日期");
    g_signal_connect(G_OBJECT(buttonSelectDate),"clicked",
                     G_CALLBACK(selectDate),NULL);
    gtk_widget_set_size_request(boxGender,240,36);
    gtk_box_pack_start(GTK_BOX(box),buttonSelectDate,FALSE,FALSE,20);

    button = gtk_button_new();
    GtkImage *signSign;
    signSign = reinterpret_cast<GtkImage *>(gtk_image_new());
    gtk_image_set_from_file(signSign,"images/signup_sign.png");
    gtk_button_set_image(GTK_BUTTON(button),GTK_WIDGET(signSign));
    gtk_fixed_put(GTK_FIXED(signFixed), button, 175, 500);
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_button_clicked_S),NULL);

    buttonC = gtk_button_new();
    GtkImage *signLog;
    signLog = reinterpret_cast<GtkImage *>(gtk_image_new());
    gtk_image_set_from_file(signLog,"images/signup_log.png");
    gtk_button_set_image(GTK_BUTTON(buttonC),GTK_WIDGET(signLog));
    gtk_fixed_put(GTK_FIXED(signFixed), buttonC, 340, 28);
    g_signal_connect(G_OBJECT(buttonC),"clicked",G_CALLBACK(windowChangeToLog),windowL);

    return windowL;
}