//
// Created by mawencong on 2019/9/3.
//

#include "UImain.h"
#include <string>
using namespace std;

int toolBarTypeFlag = 2;

//控件声明
GtkWidget *mainFixed; //主面板
GtkImage *bgImg; //背景图片

//工具栏
GtkWidget *toolBarVbox; //工具栏(Vbox)
GtkWidget *messageBtn;
GtkWidget *friendBtn;
GtkWidget *groupBtn;
GtkWidget *settingBtn;
GtkWidget *helpBtn;
GtkWidget *addBtn;

//聊天对话框
GtkTextBuffer *chatBuffer; //聊天框文本缓冲区
GtkWidget *chatScroll; //聊天对话框滚动栏
GtkWidget *popOutBtn; //弹出当前对话窗口
GtkWidget *chatName; //聊天对象的名字
GtkWidget *chatHead; //聊天对象头像
GtkWidget *chatHeadCover; //聊天对象头像遮罩
char getChatInfo[500];

//聊天输入框
GtkWidget *vbox; //输入框容器
GtkWidget *text_view; //输入框
GtkWidget *statusbar; //当前输入状态显示
GtkWidget *sendBtn; //发送消息按钮
GtkTextBuffer *buffer; //输入框文本缓冲区
GtkWidget *inputView; //输入框
GtkWidget *chatView;  //文本框聊天窗口

//信息列表
GtkWidget *infoListsLabel; //信息列表当前显示的列表信息,默认为消息列表
GtkWidget *messageScroll;
GtkWidget *messageVbox;

GtkWidget *groupScroll;
GtkWidget *groupVbox;

GtkWidget *friendsScroll;
GtkWidget *friendsVBox;

//当前好友 / 群组 / 消息 数目
int MESSAGE_NUM = 20;

//创建增删好友/群组界面
GtkWidget *addWindow;
GtkWidget *addFixed;

GtkWidget *search_box;
GtkWidget *search_text;
GtkWidget *search_entry; //好友ID
GtkWidget *friends_box;
GtkWidget *addbutton;
GtkWidget *delbutton;
GtkWidget *gsearch_box;
GtkWidget *gsearch_text;
GtkWidget *gsearch_entry; //群ID
GtkWidget *gfriends_box;
GtkWidget *gaddbutton;
GtkWidget *gdelbutton;

GtkWidget *cgsearch1_box;
GtkWidget *cgsearch1_text;
GtkWidget *cgsearch1_entry; //群组名称
GtkWidget *cgsearch2_box;
GtkWidget *cgsearch2_text;
GtkWidget *cgsearch2_entry; //群组介绍
GtkWidget *cgfriends_box;
GtkWidget *cgaddbutton;

extern int judgedeletefriend;
extern int judgequitgroup;
extern int judgejoingroup;
extern int judgecreategroup;
extern int judgeaddfriends;
extern int current_id;//current user
extern int friend_id; //add feiends
extern int current_friend_num;
extern int current_friend_id[20];
extern char current_friend_name[20][20];

extern int current_group_num;
extern int current_group_id[20];
extern char current_group_name[20][20];

extern int talk_to_user;

//当按下该按钮时，显示对应的聊天框，这里传输的是gint64的ID
void on_button_clicked_Chat(GtkWidget* button,gpointer data)
{
    g_print("=====flag===============%d",toolBarTypeFlag);
    g_print("============data===================%d\n",(gint64)data);
    switch(toolBarTypeFlag)
    {
        case 0:

            break;
        case 1:
            talk_to_user = current_friend_id[(gint64)data];
            break;
        case 2:
            talk_to_user = current_group_id[(gint64)data];
            break;
        default:g_print("What happend? you can't choose this one!");break;
    }

    createChatWindow((gint64)data);
}

/************************************************************************
*名称:getNowTime
*描述:得到当前系统时间并存储在nowTime内
*作成日期:2019.09.01
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void getNowTime(char *nowTime)
{
    time_t tmpcal_ptr; //长整型long int,适合存储日历时间类型。
    time(&tmpcal_ptr); //获取从1970-1-1,0时0分0秒到现在时刻的秒数。
    struct tm *tmp_ptr = NULL; //用来保存时间和日期的结构。
    tmp_ptr = localtime(&tmpcal_ptr);//把从1970-1-1,0时0分0秒到当前时间系统所偏移的秒数时间转换为本地时间
    sprintf(nowTime,"%d:%d:%d", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec); //将内容写入nowTime;
}

/************************************************************************
*名称:creatMainWindow
*描述:创建主界面窗口
*作成日期:2019.08.31
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void creatMainWindow()
{
    //主窗口
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(mainWindow),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(mainWindow),"SevenChat");
    gtk_window_set_default_size(GTK_WINDOW(mainWindow),1200,800);
    gtk_window_set_resizable(GTK_WINDOW(mainWindow), FALSE);
    //gtk_window_set_decorated(GTK_WINDOW(mainWindow), FALSE); // 设置无边框
    gtk_window_set_position(GTK_WINDOW(mainWindow),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(mainWindow),0);

    mainFixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(mainWindow),mainFixed);

    bgImg = reinterpret_cast<GtkImage *>(gtk_image_new());
    gtk_image_set_from_file(bgImg,"images/bg.png");
    gtk_fixed_put(GTK_FIXED(mainFixed), reinterpret_cast<GtkWidget *>(bgImg), 0, 0);

}

/************************************************************************
*名称:createToolbarBtn
*描述：创建工具栏按钮列表
*作成日期:2019.08.31
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void createToolbarBtn()
{
    //消息列表_btn
    char imgPath[200]; //图片路径
    strcpy(imgPath,"images/message.png");
    messageBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(messageBtn),"clicked",G_CALLBACK(buttonPressMessageLists),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),messageBtn,10,50);

    //好友列表_btn
    strcpy(imgPath,"images/user.png");
    friendBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(friendBtn),"clicked",G_CALLBACK(buttonPressFriendsLists),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),friendBtn,10,110);

    //群组列表_btn
    strcpy(imgPath,"images/group.png");
    groupBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(groupBtn),"clicked",G_CALLBACK(buttonPressGroupLists),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),groupBtn,10,170);

    //设置_btn
    strcpy(imgPath,"images/setting.png");
    settingBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(settingBtn),"clicked",G_CALLBACK(buttonPressSetting),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),settingBtn,10,290);

    //帮助_btn
    strcpy(imgPath,"images/help.png");
    helpBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(helpBtn),"clicked",G_CALLBACK(buttonPressHelp),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),helpBtn,10,720);

    //添加好友_btn
    strcpy(imgPath,"images/add.png");
    addBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(addBtn),"clicked",G_CALLBACK(buttonPressAdd),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),addBtn,10,230);
}


/************************************************************************
*名称:creatHelpWindow
*描述:创建帮助窗口
*作成日期:2019.08.31
*参数:无
*返回值:window
*作者:肖成文
************************************************************************/
GtkWidget *creatHelpWindow()
{
    GtkWidget *window;
    GtkWidget *label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"帮助");
    gtk_window_set_default_size(GTK_WINDOW(window),400,200);
    gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS );

    label = gtk_label_new("这里显示SevenChat的说明信息");
    gtk_container_add(GTK_CONTAINER(window),label);

    return window;
}

/************************************************************************
*名称:add_pressed等
        *描述:创建增加/删除好友/群组的窗口的功能按键
        *作成日期:2019.09.03
*参数:无
        *返回值:window
        *作者:李可
************************************************************************/
void add_pressed(GtkButton *button, gpointer data)
{
    int fid;
    const gchar *userID = gtk_entry_get_text(GTK_ENTRY(search_entry));
    fid=atoi(userID);
    judgeaddfriends = 0;
    current_friend_num = -1;
    memset(current_friend_id, 0, sizeof(current_friend_id));
    memset(current_friend_name, '\0', sizeof(current_friend_name));
    confirm_friend_callback(fid);
    while(1){
        if(judgeaddfriends == 1){
            get_friend_list(current_id);
            while(1){
                if(current_friend_num >= 0){
                    printf("show friend list success!\n");
                    createMessageDialog("添加成功！");
                    addFriendslist();
                    buttonPressFriendsLists();
                    break;
                }
                else if(current_friend_num == -2){
                    //
                    printf("show friend list fail!\n");
                    createMessageDialog("添加失败！");
                    break;
                }
            }
            break;
        }
        else if(judgeaddfriends == -1){
            //add friend failed!
            printf("add friend failed !\n");
            createMessageDialog("添加失败！");
            break;
        }
    }

}

void del_pressed(GtkButton *button, gpointer data)
{
    int fid;
    const gchar *userID = gtk_entry_get_text(GTK_ENTRY(search_entry));
    fid=atoi(userID);

}

//join group
void gadd_pressed(GtkButton *button, gpointer data)
{
    judgejoingroup = 0;
    int groupid;
    const gchar *sendGroupid = gtk_entry_get_text(GTK_ENTRY(gsearch_entry));
    groupid = atoi(sendGroupid);
    join_group(groupid);
    while(1){
        if(judgejoingroup == 1){
            createMessageDialog("添加成功！");
            addGroupList();
            break;
        }
        else if(judgejoingroup == -1){
            createMessageDialog("添加失败！");
            break;
        }
    }

}
void gdel_pressed(GtkButton *button, gpointer data)
{

}

//create
void cgadd_pressed(GtkButton *button, gpointer data)
{
    judgecreategroup = 0;
    const gchar *sendGroupname = gtk_entry_get_text(GTK_ENTRY(cgsearch1_entry));
    const gchar *sendGroupintro= gtk_entry_get_text(GTK_ENTRY(cgsearch2_entry));
    create_group((char*)sendGroupname, (char*)sendGroupintro);
    while(1){
        if(judgecreategroup == 1){
            createMessageDialog("添加成功！");
            addGroupList();
            break;
        }
        else if(judgecreategroup == -1){
            createMessageDialog("添加失败！");
            break;
        }
    }

}

/************************************************************************
*名称:creatAddWindow
*描述:创建增加/删除好友/群组的窗口
*作成日期:2019.09.03
*参数:无
*返回值:window
*作者:李可
************************************************************************/
void creatAddWindow()
{
    //window设置
    addWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (addWindow), g_locale_to_utf8("添加删除好友",-1,NULL,NULL,NULL));//窗口标题设置
    gtk_window_set_position(GTK_WINDOW(addWindow), GTK_WIN_POS_CENTER_ALWAYS);
    gtk_widget_set_size_request(addWindow,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(addWindow), 10);
    //搜索id框
    search_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    search_text=gtk_label_new("好友id：");
    search_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(search_entry),TRUE);
    gtk_box_pack_start (GTK_BOX (search_box), search_text, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX (search_box), search_entry, TRUE, TRUE, 2);

    //添加删除好友
    friends_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    addbutton= gtk_button_new_with_label("添加");
    delbutton= gtk_button_new_with_label("删除");
    g_signal_connect(addbutton,"pressed",G_CALLBACK( add_pressed),NULL);
    g_signal_connect(delbutton,"pressed",G_CALLBACK( del_pressed),NULL);
    gtk_box_pack_start (GTK_BOX (friends_box), addbutton, TRUE, TRUE, 2);
    gtk_box_pack_start (GTK_BOX (friends_box), delbutton, TRUE, TRUE, 2);

    //搜索群id
    gsearch_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gsearch_text=gtk_label_new("群组id：");
    gsearch_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(gsearch_entry),TRUE);
    gtk_box_pack_start (GTK_BOX (gsearch_box), gsearch_text, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX (gsearch_box), gsearch_entry, TRUE, TRUE, 2);

    //添加删除群
    gfriends_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gaddbutton= gtk_button_new_with_label("添加");
    gdelbutton= gtk_button_new_with_label("删除");
    g_signal_connect(gaddbutton,"pressed",G_CALLBACK( gadd_pressed),NULL);
    g_signal_connect(gdelbutton,"pressed",G_CALLBACK( gdel_pressed),NULL);
    gtk_box_pack_start (GTK_BOX (gfriends_box), gaddbutton, TRUE, TRUE, 2);
    gtk_box_pack_start (GTK_BOX (gfriends_box), gdelbutton, TRUE, TRUE, 2);
//
    cgsearch1_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    cgsearch1_text=gtk_label_new("群组名称：");
    cgsearch1_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(cgsearch1_entry),TRUE);
    gtk_box_pack_start (GTK_BOX (cgsearch1_box), cgsearch1_text, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX (cgsearch1_box), cgsearch1_entry, TRUE, TRUE, 2);
    cgsearch2_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    cgsearch2_text=gtk_label_new("群组介绍：");
    cgsearch2_entry=gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(cgsearch2_entry),TRUE);
    gtk_box_pack_start (GTK_BOX (cgsearch2_box), cgsearch2_text, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX (cgsearch2_box), cgsearch2_entry, TRUE, TRUE, 2);

    cgfriends_box=gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    cgaddbutton= gtk_button_new_with_label("创建");
    g_signal_connect(cgaddbutton,"pressed",G_CALLBACK( cgadd_pressed),NULL);
    gtk_box_pack_start (GTK_BOX (cgfriends_box), cgaddbutton, TRUE, TRUE, 2);

    //创建fix并加入所有box
    addFixed=gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(addWindow) , addFixed);
    gtk_fixed_put(GTK_FIXED(addFixed),search_box,0,0);
    gtk_fixed_put(GTK_FIXED(addFixed),friends_box,170,40);
    gtk_fixed_put(GTK_FIXED(addFixed),gsearch_box,0,100);
    gtk_fixed_put(GTK_FIXED(addFixed),gfriends_box,170,140);
    gtk_fixed_put(GTK_FIXED(addFixed),cgsearch1_box,0,200);
    gtk_fixed_put(GTK_FIXED(addFixed),cgsearch2_box,0,240);
    gtk_fixed_put(GTK_FIXED(addFixed),cgfriends_box,220,280);

    gtk_widget_show_all(addWindow);
}


/************************************************************************
*名称:createPopoutWindow
*描述:创建与当前好友聊天的独立窗口
*作成日期:2019.09.02
*参数:无
*返回值:window
*作者:肖成文
************************************************************************/
GtkWidget *createPopoutWindow()
{
    GtkWidget *window;
    GtkWidget *popMainFixed;
    GtkWidget *popBg;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"聊天窗口");
    gtk_window_set_default_size(GTK_WINDOW(window),700,800);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS );
    gtk_container_set_border_width(GTK_CONTAINER(window),0);

    popMainFixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),popMainFixed);

    popBg = gtk_image_new();
    gtk_image_set_from_file(reinterpret_cast<GtkImage *>(popBg), "images/pop_bg.png");
    gtk_fixed_put(GTK_FIXED(popMainFixed),popBg,0,0);

    //聊天框
    GtkWidget *popChatScroll = gtk_scrolled_window_new(NULL,NULL); //创建滚动栏
    gtk_scrolled_window_set_policy(reinterpret_cast<GtkScrolledWindow *>(popChatScroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (popChatScroll, 700, 498);

    GtkWidget *popChatView = gtk_text_view_new();//设置聊天对话框
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(popChatView), GTK_WRAP_WORD);//设置自动换行
    gtk_widget_set_size_request (popChatView, 700, 200);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(popChatView), FALSE); //设置光标不可见
    gtk_text_view_set_editable(reinterpret_cast<GtkTextView *>(popChatView), FALSE); //设置对话框不可编辑

    gtk_text_view_set_top_margin(reinterpret_cast<GtkTextView *>(popChatView), 30); //设置文本与文本框的边距
    gtk_text_view_set_left_margin(reinterpret_cast<GtkTextView *>(popChatView), 10);
    gtk_text_view_set_right_margin(reinterpret_cast<GtkTextView *>(popChatView), 10);
    GtkWidget *popChatBuffer = reinterpret_cast<GtkWidget *>(gtk_text_view_get_buffer(GTK_TEXT_VIEW(popChatView)));  // 获取文本缓冲区

    //聊天对象名称显示
    GtkWidget *popChatName = gtk_label_new("| CHAT WITH SOMEONE |");
    gtk_fixed_put(GTK_FIXED(popMainFixed), popChatName, 100, 30);

    //聊天对象头像显示 70 70 300 5
    GtkWidget *popChatHead = gtk_image_new(); //头像

    const GdkPixbuf *src_pixbuf;
    GdkPixbuf *dest_pixbuf;
    src_pixbuf = gdk_pixbuf_new_from_file("images/chat_head.jpg",NULL); //读取图片参数
    dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 70, 70, GDK_INTERP_HYPER); //设置图片显示指定大小
    popChatHead = gtk_image_new_from_pixbuf(dest_pixbuf);
    gtk_fixed_put(GTK_FIXED(popMainFixed), popChatHead, 20, 5);

    GtkWidget *popChatHeadCover = gtk_image_new(); //遮罩
    popChatHeadCover = gtk_image_new_from_file("images/chat_cover.png");
    gtk_fixed_put(GTK_FIXED(popMainFixed), popChatHeadCover, 20, 5);
    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(popChatScroll), popChatView);
    gtk_fixed_put(GTK_FIXED(popMainFixed), popChatScroll, 0, 80);

    //输入框
    GtkWidget *popVbox = gtk_vbox_new(FALSE, 0);
    gtk_widget_set_size_request(popVbox,700,216);
    gtk_fixed_put(GTK_FIXED(popMainFixed),popVbox,0,582);

    GtkWidget *popInputScroll; //设置滑动条
    popInputScroll = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(reinterpret_cast<GtkScrolledWindow *>(popInputScroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (popInputScroll, 700, 216);
    gtk_box_pack_start(GTK_BOX(popVbox), popInputScroll, TRUE, TRUE, 0);

    GtkWidget *popInputView = gtk_text_view_new(); //设置文本输入框
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(popInputView), GTK_WRAP_WORD);//设置自动换行
    gtk_widget_grab_focus(popInputView);

    gtk_text_view_set_top_margin(reinterpret_cast<GtkTextView *>(popInputView), 10); //设置文本与文本框的边距
    gtk_text_view_set_left_margin(reinterpret_cast<GtkTextView *>(popInputView), 10);
    gtk_text_view_set_right_margin(reinterpret_cast<GtkTextView *>(popInputView), 10);

    GtkWidget *popBuffer_ = reinterpret_cast<GtkWidget *>(gtk_text_view_get_buffer(GTK_TEXT_VIEW(popInputView))); // 获取文本缓冲区
    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(popInputScroll), popInputView);

    GtkWidget *popSendBtn = gtk_button_new_with_label("Send Message"); //发送消息按钮
    gtk_widget_set_size_request(popSendBtn,60,40);
    g_signal_connect(G_OBJECT(popSendBtn),"clicked",G_CALLBACK(buttonPressSendMessage),NULL);
    gtk_fixed_put(GTK_FIXED(popMainFixed),popSendBtn,580,740);

    return window;

}

/************************************************************************
*名称:createInputWindow
*描述:创建聊天输入框窗口
*作成日期:2019.08.31
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void createInputWindow()
{
    //输入框
    /**************输入框层级关系********************
    * mainFixed->vbox->inputScroll->inputView->
    *          ->sendBtn
    **********************************************/

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_widget_set_size_request(vbox,700,216);
    gtk_fixed_put(GTK_FIXED(mainFixed),vbox,280,582);

    GtkWidget *inputScroll; //设置滑动条
    inputScroll = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(reinterpret_cast<GtkScrolledWindow *>(inputScroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (inputScroll, 700, 216);
    gtk_box_pack_start(GTK_BOX(vbox), inputScroll, TRUE, TRUE, 0);

    inputView = gtk_text_view_new(); //设置文本输入框
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(inputView), GTK_WRAP_WORD);//设置自动换行
    gtk_widget_grab_focus(inputView);

    gtk_text_view_set_top_margin(reinterpret_cast<GtkTextView *>(inputView), 10); //设置文本与文本框的边距
    gtk_text_view_set_left_margin(reinterpret_cast<GtkTextView *>(inputView), 10);
    gtk_text_view_set_right_margin(reinterpret_cast<GtkTextView *>(inputView), 10);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(inputView)); // 获取文本缓冲区
    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(inputScroll), inputView);

    sendBtn = gtk_button_new_with_label("Send Message"); //发送消息按钮
    gtk_widget_set_size_request(sendBtn,60,40);
    g_signal_connect(G_OBJECT(sendBtn),"clicked",G_CALLBACK(buttonPressSendMessage),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),sendBtn,860,740);
}

/************************************************************************
*名称:createIChatWindow
*描述:创建聊天对话框
*作成日期:2019.08.31
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void createChatWindow_()
{
    popOutBtn = gtk_button_new_with_label("Pop Out");
    g_signal_connect(G_OBJECT(popOutBtn),"clicked",G_CALLBACK(buttonPressPopout),NULL);
    gtk_widget_set_size_request(popOutBtn,60,40);
    gtk_fixed_put(GTK_FIXED(mainFixed),popOutBtn,900,20);

    chatScroll = gtk_scrolled_window_new(NULL,NULL); //创建滚动栏
    gtk_scrolled_window_set_policy(reinterpret_cast<GtkScrolledWindow *>(chatScroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (chatScroll, 700, 500);

    chatView = gtk_text_view_new();//设置聊天对话框
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(chatView), GTK_WRAP_WORD);//设置自动换行
    gtk_widget_set_size_request (chatView, 700, 200);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(chatView), FALSE); //设置光标不可见
    gtk_text_view_set_editable(reinterpret_cast<GtkTextView *>(chatView), FALSE); //设置对话框不可编辑

    gtk_text_view_set_top_margin(reinterpret_cast<GtkTextView *>(chatView), 30); //设置文本与文本框的边距
    gtk_text_view_set_left_margin(reinterpret_cast<GtkTextView *>(chatView), 10);
    gtk_text_view_set_right_margin(reinterpret_cast<GtkTextView *>(chatView), 10);
    chatBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatView));  // 获取文本缓冲区
    //聊天对象名称显示
    chatName = gtk_label_new("|CHAT WITH SOMEONE|");
    gtk_fixed_put(GTK_FIXED(mainFixed), chatName, 380, 30);

    //聊天对象头像显示 70 70 300 5
    chatHead = gtk_image_new(); //头像

    const GdkPixbuf *src_pixbuf;
    GdkPixbuf *dest_pixbuf;
    src_pixbuf = gdk_pixbuf_new_from_file("images/chat_head.jpg",NULL); //读取图片参数
    dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 70, 70, GDK_INTERP_HYPER); //设置图片显示指定大小
    chatHead = gtk_image_new_from_pixbuf(dest_pixbuf);
    gtk_fixed_put(GTK_FIXED(mainFixed), chatHead, 300, 5);

    chatHeadCover = gtk_image_new(); //遮罩
    chatHeadCover = gtk_image_new_from_file("images/chat_cover.png");
    gtk_fixed_put(GTK_FIXED(mainFixed), chatHeadCover, 300, 5);


    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(chatScroll), chatView);
    gtk_fixed_put(GTK_FIXED(mainFixed), chatScroll, 280, 80);
}
void createChatWindow(int ID)
{
    gtk_widget_destroy(popOutBtn);
    popOutBtn = gtk_button_new_with_label("Pop Out");
    g_signal_connect(G_OBJECT(popOutBtn),"clicked",G_CALLBACK(buttonPressPopout),NULL);
    gtk_widget_set_size_request(popOutBtn,60,40);
    gtk_fixed_put(GTK_FIXED(mainFixed),popOutBtn,900,20);
    gtk_widget_show(popOutBtn);

    gtk_widget_destroy(chatScroll);
    chatScroll = gtk_scrolled_window_new(NULL,NULL); //创建滚动栏
    gtk_scrolled_window_set_policy(reinterpret_cast<GtkScrolledWindow *>(chatScroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (chatScroll, 700, 500);
    gtk_widget_show(chatScroll);

    gtk_widget_destroy(chatView);
    chatView = gtk_text_view_new();//设置聊天对话框
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(chatView), GTK_WRAP_WORD);//设置自动换行
    gtk_widget_set_size_request (chatView, 700, 200);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(chatView), FALSE); //设置光标不可见
    gtk_text_view_set_editable(reinterpret_cast<GtkTextView *>(chatView), FALSE); //设置对话框不可编辑
    gtk_widget_show(chatView);

    gtk_text_view_set_top_margin(reinterpret_cast<GtkTextView *>(chatView), 30); //设置文本与文本框的边距
    gtk_text_view_set_left_margin(reinterpret_cast<GtkTextView *>(chatView), 10);
    gtk_text_view_set_right_margin(reinterpret_cast<GtkTextView *>(chatView), 10);
    chatBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatView));  // 获取文本缓冲区

    //聊天对象名称显示
    gtk_widget_destroy(chatName);
    string Namestring;
    switch(toolBarTypeFlag)
    {//when you choose messagelist in toolbar,flag will be changed to "0",and now the chatwindow will
        // choose message[20] to select i;
        case 0:

            break;
        case 1:
            Namestring = current_friend_name[ID];
            break;
        case 2:
            Namestring = current_group_name[ID];
            break;
        default:g_print("What happend? you can't choose this one!");break;
    }
    chatName = gtk_label_new(Namestring.c_str());

    gtk_fixed_put(GTK_FIXED(mainFixed), chatName, 380, 30);
    gtk_widget_show(chatName);


    gtk_widget_destroy(chatHead);
    //聊天对象头像显示 70 70 300 5
    chatHead = gtk_image_new(); //头像
    const GdkPixbuf *src_pixbuf;
    GdkPixbuf *dest_pixbuf;
    src_pixbuf = gdk_pixbuf_new_from_file("images/chat_head.jpg",NULL); //读取图片参数
    dest_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, 70, 70, GDK_INTERP_HYPER); //设置图片显示指定大小
    chatHead = gtk_image_new_from_pixbuf(dest_pixbuf);
    gtk_fixed_put(GTK_FIXED(mainFixed), chatHead, 300, 5);
    gtk_widget_show(chatHead);

    gtk_widget_destroy(chatHeadCover);
    chatHeadCover = gtk_image_new(); //遮罩
    chatHeadCover = gtk_image_new_from_file("images/chat_cover.png");
    gtk_fixed_put(GTK_FIXED(mainFixed), chatHeadCover, 300, 5);
    gtk_widget_show(chatHeadCover);

    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(chatScroll), chatView);
    gtk_fixed_put(GTK_FIXED(mainFixed), chatScroll, 280, 80);
}


/************************************************************************
*名称:createInfoScroll&createInfoVbox
*描述:创建信息列表滚动栏&Vbox
*作成日期:2019.09.02
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
GtkWidget *createInfoScroll()
{
    GtkWidget *infoScroll;
    infoScroll = gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(reinterpret_cast<GtkScrolledWindow *>(infoScroll), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    gtk_widget_set_size_request (infoScroll, 200, 700);
    gtk_fixed_put(GTK_FIXED(mainFixed),infoScroll,80,80);

    return infoScroll;
}

GtkWidget *createInfoVbox()
{
    //用于装载列表按钮
    GtkWidget *infoVbox;
    infoVbox = gtk_vbox_new(TRUE,20);
    gtk_widget_set_size_request(infoVbox,200,720);

    return infoVbox;
}

/************************************************************************
*名称:addFriendslist...
*描述:addbutton in info list
*作成日期:2019.09.04
*参数:无
*返回值:void
*作者:肖成文,李心志
************************************************************************/
void addFriendslist()
{

    int i = current_friend_num - 1;
    GtkWidget *friendsHbox;
    GtkWidget *anniuHbox;
    GtkWidget *anniuLabel;
    friendUsername[i] = gtk_button_new();
    char* portraitSrc = "images/chat_head.jpg";//头像的加载
    friendsHbox = gtk_hbox_new(TRUE,5);
    gtk_widget_set_size_request(friendsHbox,85,40);

    GtkWidget* smallPortrait ;
    const GdkPixbuf *srcPixbuf;
    GdkPixbuf *dstPixbuf;
    srcPixbuf = gdk_pixbuf_new_from_file(portraitSrc,NULL);
    dstPixbuf = gdk_pixbuf_scale_simple(srcPixbuf,70,70,GDK_INTERP_HYPER);
    smallPortrait = gtk_image_new_from_pixbuf(dstPixbuf);
    g_object_unref(GDK_PIXBUF(srcPixbuf));
    g_object_unref(GDK_PIXBUF(dstPixbuf));

    gtk_box_pack_start(GTK_BOX(friendsHbox),smallPortrait,FALSE,FALSE,0);
    gtk_widget_set_size_request(friendUsername[i],1,70);
    gtk_widget_show(friendUsername[i]);

    anniuLabel = gtk_label_new(current_friend_name[i]);
    gtk_box_pack_start(GTK_BOX(friendsHbox),anniuLabel,FALSE,FALSE,0);

    gtk_container_add(GTK_CONTAINER(friendUsername[i]),friendsHbox);
    anniuHbox = gtk_hbox_new(FALSE,3);
    gtk_widget_set_size_request(anniuHbox,80,40);

    g_signal_connect(G_OBJECT(friendUsername[i]),"clicked",G_CALLBACK(on_button_clicked_Chat),(gpointer)i);

    gtk_box_pack_start(GTK_BOX(anniuHbox),friendUsername[i],FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(friendsVBox),anniuHbox,TRUE,TRUE,2);


    gtk_widget_show_all(anniuHbox);
    //gtk_widget_show(friendsHbox);
}

void addGroupList()
{
    GtkWidget *groupHbox;
    GtkWidget *anniuHbox;
    GtkWidget *anniuLabel;

    int i = current_group_num - 1;

    grounpName[i] = gtk_button_new();
    char* portraitSrc = "images/chat_head.jpg";//头像的加载
    groupHbox = gtk_hbox_new(FALSE,5);
    GtkWidget* smallPortrait ;
    const GdkPixbuf *srcPixbuf;
    GdkPixbuf *dstPixbuf;
    srcPixbuf = gdk_pixbuf_new_from_file(portraitSrc,NULL);
    dstPixbuf = gdk_pixbuf_scale_simple(srcPixbuf,70,70,GDK_INTERP_HYPER);
    smallPortrait = gtk_image_new_from_pixbuf(dstPixbuf);
    g_object_unref(GDK_PIXBUF(srcPixbuf));
    g_object_unref(GDK_PIXBUF(dstPixbuf));

    gtk_box_pack_start(GTK_BOX(groupHbox),smallPortrait,FALSE,FALSE,0);
    gtk_widget_set_size_request(grounpName[i],1,70);
    gtk_widget_show(grounpName[i]);

    anniuLabel = gtk_label_new(to_string(current_group_id[i]).c_str());
    gtk_box_pack_start(GTK_BOX(groupHbox),anniuLabel,FALSE,FALSE,0);

    gtk_container_add(GTK_CONTAINER(grounpName[i]),groupHbox);
    anniuHbox = gtk_hbox_new(FALSE,3);
    gtk_widget_set_size_request(anniuHbox,80,40);

    g_signal_connect(G_OBJECT(grounpName[i]),"clicked",G_CALLBACK(on_button_clicked_Chat),(gpointer)i);

    gtk_box_pack_start(GTK_BOX(anniuHbox),grounpName[i],FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(groupVbox),anniuHbox,TRUE,TRUE,2);

    gtk_widget_show_all(anniuHbox);
    //gtk_widget_show(friendsHbox);
}

/************************************************************************
*名称:createFriendsList...
*描述:创建信息列表
*作成日期:2019.09.02
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void createFriendsList()
{
    /**************信息列表层级关系********************
    * mainFixed->infoListLabel
    *          ->infoScroll->infoVbox->buttons
    **********************************************/

    GtkWidget *friendsHbox;
    GtkWidget *anniuHbox;
    GtkWidget *anniuLabel;

    friendsScroll = createInfoScroll();
    friendsVBox = createInfoVbox();
    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(friendsScroll), friendsVBox);

    
    //创建好友列表
    for( int i=0 ;i<current_friend_num; i++ )
    {
        friendUsername[i] = gtk_button_new();
        char* portraitSrc = "images/chat_head.jpg";//头像的加载
        friendsHbox = gtk_hbox_new(TRUE,5);
        gtk_widget_set_size_request(friendsHbox,85,40);

        GtkWidget* smallPortrait ;
        const GdkPixbuf *srcPixbuf;
        GdkPixbuf *dstPixbuf;
        srcPixbuf = gdk_pixbuf_new_from_file(portraitSrc,NULL);
        dstPixbuf = gdk_pixbuf_scale_simple(srcPixbuf,70,70,GDK_INTERP_HYPER);
        smallPortrait = gtk_image_new_from_pixbuf(dstPixbuf);
        g_object_unref(GDK_PIXBUF(srcPixbuf));
        g_object_unref(GDK_PIXBUF(dstPixbuf));

        gtk_box_pack_start(GTK_BOX(friendsHbox),smallPortrait,FALSE,FALSE,0);
        gtk_widget_set_size_request(friendUsername[i],1,70);
        gtk_widget_show(friendUsername[i]);

        anniuLabel = gtk_label_new(current_friend_name[i]);
        gtk_box_pack_start(GTK_BOX(friendsHbox),anniuLabel,FALSE,FALSE,0);

        gtk_container_add(GTK_CONTAINER(friendUsername[i]),friendsHbox);
        anniuHbox = gtk_hbox_new(FALSE,3);
        gtk_widget_set_size_request(anniuHbox,80,40);

        g_signal_connect(G_OBJECT(friendUsername[i]),"clicked",G_CALLBACK(on_button_clicked_Chat),(gpointer)i);

        gtk_box_pack_start(GTK_BOX(anniuHbox),friendUsername[i],FALSE,FALSE,10);
        gtk_box_pack_start(GTK_BOX(friendsVBox),anniuHbox,TRUE,TRUE,2);
    }

}
/************************************************************************
*名称:createMessageList
*描述:创建消息列表
*作成日期:2019.09.02
*参数:无
*返回值:void
*作者:肖成文 李心志
************************************************************************/
void createMessageList()
{
    GtkWidget *messageHbox;
    GtkWidget *anniuHbox;
    GtkWidget *anniuLabel;
    //static GdkColor black = {0,0,0,1};
    std::string AAA[3] = {"11111",
                          "2222",
                          "33333"};
    messageScroll = createInfoScroll();
    messageVbox = createInfoVbox();
    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(messageScroll), messageVbox);

    //创建聊天信息列表
    for( int i=0 ;i<3; i++ )
    {
        messageList[i] = gtk_button_new();
        messageHbox = gtk_hbox_new(FALSE,5);

        char* portraitSrc = "images/chat_head.jpg";//头像的加载

        GtkWidget* smallPortrait ;
        const GdkPixbuf *srcPixbuf;
        GdkPixbuf *dstPixbuf;
        srcPixbuf = gdk_pixbuf_new_from_file(portraitSrc,NULL);
        dstPixbuf = gdk_pixbuf_scale_simple(srcPixbuf,70,70,GDK_INTERP_HYPER);
        smallPortrait = gtk_image_new_from_pixbuf(dstPixbuf);
        g_object_unref(GDK_PIXBUF(srcPixbuf));
        g_object_unref(GDK_PIXBUF(dstPixbuf));
        gtk_box_pack_start(GTK_BOX(messageHbox),smallPortrait,FALSE,FALSE,0);
        //gtk_widget_modify_bg(messageList[i],GTK_STATE_NORMAL,&black);
        gtk_widget_set_size_request(messageList[i],1,70);

        anniuLabel = gtk_label_new(AAA[i].c_str());
        gtk_box_pack_start(GTK_BOX(messageHbox),anniuLabel,FALSE,FALSE,0);

        gtk_container_add(GTK_CONTAINER(messageList[i]),messageHbox);
        //gtk__set_markup(GTK_LABEL(messageList[i]),"<span foreground='white'font_desc='12'>| MESSAGE01 | </span>");
        anniuHbox = gtk_hbox_new(FALSE,3);
        gtk_widget_set_size_request(anniuHbox,80,40);
        int aaa = atoi(AAA[i].c_str());
        g_signal_connect(G_OBJECT(messageList[i]),"clicked",G_CALLBACK(on_button_clicked_Chat),(gpointer)aaa);
//        gtk_widget_show(messageList[i]);
        gtk_box_pack_start(GTK_BOX(anniuHbox),messageList[i],FALSE,FALSE,10);
        gtk_box_pack_start(GTK_BOX(messageVbox),anniuHbox,FALSE,FALSE,10);
    }
}

void createGroupList()
{

    GtkWidget *groupHbox;
    GtkWidget *anniuHbox;
    GtkWidget *anniuLabel;

    groupScroll = createInfoScroll();
    groupVbox = createInfoVbox();
    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(groupScroll), groupVbox);

    //创建群组
    for( int i=0 ;i<current_group_num; i++ )
    {
        grounpName[i] = gtk_button_new();
        char* portraitSrc = "images/chat_head.jpg";//头像的加载
        groupHbox = gtk_hbox_new(FALSE,5);
        GtkWidget* smallPortrait ;
        const GdkPixbuf *srcPixbuf;
        GdkPixbuf *dstPixbuf;
        srcPixbuf = gdk_pixbuf_new_from_file(portraitSrc,NULL);
        dstPixbuf = gdk_pixbuf_scale_simple(srcPixbuf,70,70,GDK_INTERP_HYPER);
        smallPortrait = gtk_image_new_from_pixbuf(dstPixbuf);
        g_object_unref(GDK_PIXBUF(srcPixbuf));
        g_object_unref(GDK_PIXBUF(dstPixbuf));

        gtk_box_pack_start(GTK_BOX(groupHbox),smallPortrait,FALSE,FALSE,0);
        gtk_widget_set_size_request(grounpName[i],1,70);
        gtk_widget_show(grounpName[i]);

        anniuLabel = gtk_label_new(current_group_name[i]);
        gtk_box_pack_start(GTK_BOX(groupHbox),anniuLabel,FALSE,FALSE,0);

        gtk_container_add(GTK_CONTAINER(grounpName[i]),groupHbox);
        anniuHbox = gtk_hbox_new(FALSE,3);
        gtk_widget_set_size_request(anniuHbox,80,40);

        g_signal_connect(G_OBJECT(grounpName[i]),"clicked",G_CALLBACK(on_button_clicked_Chat),(gpointer)i);

        gtk_box_pack_start(GTK_BOX(anniuHbox),grounpName[i],FALSE,FALSE,10);
        gtk_box_pack_start(GTK_BOX(groupVbox),anniuHbox,TRUE,TRUE,2);
    }
}

/************************************************************************
*名称:showFriendsLists & hideFriendsLists
*描述:显示 & 隐藏好友列表
*作成日期:2019.09.02
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void showFriendsLists()
{
    for( int i=0; i<current_friend_num; i++ )
    {
        gtk_widget_show(friendUsername[i]);
    }
    //当前列表名称
    gtk_label_set_markup(GTK_LABEL(infoListsLabel),"<span foreground='white'font_desc='14'>| 好友列表 | </span>");
    gtk_widget_show(friendsScroll);
    gtk_widget_show(friendsVBox);
}

void hideFriendsLists()
{

    for( int i=0; i<current_friend_num; i++ )
    {
        gtk_widget_hide(friendUsername[i]);
    }
    gtk_widget_hide(friendsScroll);
    gtk_widget_hide(friendsVBox);
}

/************************************************************************
*名称:showGroupLists & hideGroupLists
*描述:显示 & 隐藏群组列表
*作成日期:2019.09.02
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void showGroupLists()
{
    for( int i=0; i<current_group_num; i++ )
    {
        gtk_widget_show(grounpName[i]);
    }
    //当前列表名称
    gtk_label_set_markup(GTK_LABEL(infoListsLabel),"<span foreground='white'font_desc='14'>| 群组列表 | </span>");
    gtk_widget_show(groupScroll);
    gtk_widget_show(groupVbox);
}

void hideGroupLists()
{
    for( int i=0; i<current_group_num; i++ )
    {
        gtk_widget_hide(grounpName[i]);
    }
    gtk_widget_hide(groupScroll);
    gtk_widget_hide(groupVbox);
}

/************************************************************************
*名称:showMessageLists & hideMessageLists
*描述:显示 & 隐藏消息列表
*作成日期:2019.09.02
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void showMessageLists()
{
    for( int i=0; i<MESSAGE_NUM; i++ )
    {
        gtk_widget_show(messageList[i]);
    }
    //当前列表名称
    gtk_label_set_markup(GTK_LABEL(infoListsLabel),"<span foreground='white'font_desc='14'>| 消息列表 | </span>");
    gtk_widget_show(messageScroll);
    gtk_widget_show(messageVbox);

}

void hideMessageLists()
{
    for( int i=0; i<MESSAGE_NUM; i++ )
    {
        gtk_widget_hide(messageList[i]);
    }
    gtk_widget_hide(messageScroll);
    gtk_widget_hide(messageVbox);
}

/************************************************************************
*名称:buttonPressLists等
*描述:工具栏按钮触发函数_对应弹出消息列表/好友列表/群组列表/设置/帮助界面
*作成日期:2019.08.29
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void buttonPressFriendsLists()
{
    toolBarTypeFlag = 1;
    showFriendsLists();
    hideGroupLists();
    hideMessageLists();
}

void buttonPressGroupLists()
{
    toolBarTypeFlag = 2;
    showGroupLists();
    hideFriendsLists();
    hideMessageLists();
}
void buttonPressMessageLists()
{
    toolBarTypeFlag = 0;
    showMessageLists();
    hideFriendsLists();
    hideGroupLists();
}

void buttonPressSetting()
{
    creatSettingWindow();
}

void buttonPressHelp()
{
    GtkWidget *helpWindow;
    helpWindow = creatHelpWindow();
    gtk_widget_show_all(helpWindow);
}
void buttonPressAdd()
{
    creatAddWindow();
}

/************************************************************************
*名称:buttonPressPopout等
*描述:弹出当前对话窗口
*作成日期:2019.08.31
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/

void buttonPressPopout()
{
    GtkWidget *popWindow;
    popWindow = createPopoutWindow();
    gtk_widget_show_all(popWindow);

}

/************************************************************************
*名称:imgBtnCreate
*描述:创建工具栏图片按钮
*作成日期:2019.08.30
*参数:按钮图片的路径
*返回值:button
*作者:肖成文
************************************************************************/
GtkWidget *imgBtnCreate(char *imgPath)
{
    //创建图片按钮
    GtkWidget *image;
    GtkWidget *button;

    image = gtk_image_new_from_file(imgPath); //加载对应按钮图片
    button = gtk_button_new();
    gtk_button_set_image(reinterpret_cast<GtkButton *>(button), image);

    //根据按钮不同状态更改按钮颜色
    //static GdkColor black = {0x0,0xfff,0xfff,1};
    //gtk_widget_modify_bg(button,GTK_STATE_ACTIVE,&black);

    return button;
}

/************************************************************************
*名称:messagePrint
*描述:打印消息
*作成日期:2019.08.31
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void setScrollPos(int length) //延迟一条消息的位置
{
    //滑动条置于最底端
    GtkAdjustment *adj;
    gdouble upper_value, page_size, max_value;

    adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(chatScroll));
    upper_value = gtk_adjustment_get_upper(adj);
    page_size = gtk_adjustment_get_page_size(adj);
    max_value = upper_value - page_size;

    gtk_adjustment_set_value(GTK_ADJUSTMENT(adj), max_value);
}

/************************************************************************
*名称:messagePrint
*描述:打印消息
*作成日期:2019.08.31
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/

void messagePrint(char *chatInfo)
{
    GtkTextIter start,end;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(chatBuffer),&start,&end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(chatBuffer),&end,chatInfo,strlen(chatInfo));//将消息放入聊天信息框

}

/************************************************************************
*名称:buttonPressSendMessage
*描述:发送消息
*作成日期:2019.08.31
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/

void buttonPressSendMessage()
{
    //send_message_callback(" ");
    //打印发送人的username
    char usernameNow[20];
    strcpy(usernameNow,"Myself");//待更改
    messagePrint(usernameNow);
    messagePrint("      ");

    //打印本机发送信息的系统时间
    char nowTime[20];
    getNowTime(nowTime);
    messagePrint(nowTime);
    messagePrint("\n");

    //打印本机发送的消息
    char chatInfo[2000];
    gint chatInfoLen = 0;
    GtkTextIter start,end;

    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    strcpy(chatInfo,gtk_text_buffer_get_text(buffer,&start,&end,FALSE));
    messagePrint(chatInfo);
    chatInfoLen = strlen(chatInfo)/100+3;

    messagePrint("\n\n");
    switch(toolBarTypeFlag)
    {
        case 0:send_message_callback(chatInfo);break;
        case 1:send_message_callback(chatInfo);break;
        case 2:send_group_message_callback(talk_to_user,chatInfo);
    }



    //清空聊天框缓存区内容
    gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer),&start,&end);
    setScrollPos(chatInfoLen);
}

/************************************************************************
*名称:updateGetInfo
*描述:更新接收到的消息
*作成日期:2019.09.04
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/

void updateGetInfo(char* usernameNow, char* nowTime, char* detail)
{
    //接口函数

    //打印发送人的username
    messagePrint(usernameNow);
    messagePrint("      ");

    getNowTime(nowTime);
    messagePrint(nowTime);
    messagePrint("\n");

    //打印接受到的消息
    // 消息内容（getchatinfo 为字符串）
    strcpy(getChatInfo,detail);
    messagePrint(getChatInfo);
    messagePrint("\n\n");
}

/************************************************************************
*名称:createInfodetailVbox
*描述:显示当前聊天框对象的详细信息
*作成日期:2019.09.02
*参数:无
*返回值:void
*作者:李心志
************************************************************************/
void createInfodetailVbox()
{//w220  h800     980 0
    GtkWidget* infodetailVbox;
    GtkWidget* label;
    int headWidth = 170;
    int headHeight = 170;

    infodetailVbox = gtk_vbox_new(FALSE,0);
    gtk_fixed_put(GTK_FIXED(mainFixed), infodetailVbox, 980, 0);
    //头像设置  w200 h170   990 50
    GtkWidget* fillers = gtk_label_new("");
    gtk_widget_set_size_request(fillers,220,225);
    gtk_box_pack_start(GTK_BOX(infodetailVbox),fillers,FALSE,FALSE,0);

    char* portraitSrc = "images/chat_head.jpg";//头像的加载
    const char* ditu = "images/ditu.png";//底图的加载

    GtkWidget* headPortrait ;
    const GdkPixbuf *srcPixbuf;
    GdkPixbuf *dstPixbuf;
    srcPixbuf = gdk_pixbuf_new_from_file(portraitSrc,NULL);
    dstPixbuf = gdk_pixbuf_scale_simple(srcPixbuf,headWidth,headHeight,GDK_INTERP_HYPER);
    headPortrait = gtk_image_new_from_pixbuf(dstPixbuf);
    g_object_unref(GDK_PIXBUF(srcPixbuf));
    g_object_unref(GDK_PIXBUF(dstPixbuf));
    gtk_fixed_put(GTK_FIXED(mainFixed),headPortrait,992,60);
    GtkWidget* dituG = gtk_image_new_from_file(ditu);
    gtk_fixed_put(GTK_FIXED(mainFixed),dituG,980,47);

    gtk_widget_set_size_request(dituG,220,170);

    const gchar* lUserl = "Chat_head";
    const gchar* lGender = "Female";
    const std::string lBirthday = "2月2日";

    GtkWidget* labelUsename = gtk_label_new(lUserl);
    gtk_widget_set_size_request(labelUsename,220,20);
    GtkWidget* labelGender = gtk_label_new(lGender);
    gtk_widget_set_size_request(labelGender,220,30);
    GtkWidget* labelBirthday = gtk_label_new(lBirthday.c_str());
    gtk_widget_set_size_request(labelBirthday,220,30);

    gtk_box_pack_end(GTK_BOX(infodetailVbox),labelBirthday, TRUE,TRUE, 0);
    gtk_box_pack_end(GTK_BOX(infodetailVbox),labelGender, TRUE,TRUE, 0);
    gtk_box_pack_end(GTK_BOX(infodetailVbox),labelUsename, TRUE,TRUE, 0);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc,&argv);

    creatMainWindow(); //创建主窗口
    createToolbarBtn(); //创建工具栏

    //列表名称
    infoListsLabel = gtk_label_new("list_name");
    gtk_fixed_put(GTK_FIXED(mainFixed),infoListsLabel,130,20);

    windowLog = createLogWindow();
    windowSign = createSignWindow();
    gtk_widget_show_all(windowLog);
    gtk_main();
///////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////




    return FALSE;
}
























