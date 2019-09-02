#include "mainUI.h"
GtkWidget *mainFixed; //主面板
GtkImage *bgImg; //背景图片

//工具栏
GtkWidget *toolBarVbox; //工具栏(Vbox)
GtkWidget *messageBtn;
GtkWidget *friendBtn;
GtkWidget *groupBtn;
GtkWidget *settingBtn;
GtkWidget *helpBtn;

//聊天对话框
GtkTextBuffer *chatBuffer; //聊天框文本缓冲区
GtkWidget *chatScroll; //聊天框滑动条
GtkWidget *popOutBtn; //弹出当前对话窗口

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
GtkWidget *infoScroll; //设置滑动条
GtkWidget *infoVbox; //用于装载列表按钮

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
    time_t tmpcal_ptr;   //长整型long int,适合存储日历时间类型。
    time(&tmpcal_ptr);  //获取从1970-1-1,0时0分0秒到现在时刻的秒数。
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
    g_signal_connect(G_OBJECT(messageBtn),"clicked",G_CALLBACK(buttonPressLists),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),messageBtn,10,50);

    //好友列表_btn
    strcpy(imgPath,"images/user.png");
    friendBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(friendBtn),"clicked",G_CALLBACK(buttonPressLists),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),friendBtn,10,110);

    //群组列表_btn
    strcpy(imgPath,"images/group.png");
    groupBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(groupBtn),"clicked",G_CALLBACK(buttonPressLists),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),groupBtn,10,170);

    //设置_btn
    strcpy(imgPath,"images/setting.png");
    settingBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(settingBtn),"clicked",G_CALLBACK(buttonPressSetting),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),settingBtn,10,230);

    //帮助_btn
    strcpy(imgPath,"images/help.png");
    helpBtn = imgBtnCreate(imgPath);
    g_signal_connect(G_OBJECT(helpBtn),"clicked",G_CALLBACK(buttonPressHelp),NULL);
    gtk_fixed_put(GTK_FIXED(mainFixed),helpBtn,10,720);
}

/************************************************************************
*名称:creatSettingWindow
*描述:创建设置窗口
*作成日期:2019.08.31
*参数:无
*返回值:window
*作者:肖成文
************************************************************************/
GtkWidget *creatSettingWindow()
{
    GtkWidget *window;
    GtkWidget *label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"SevenChat Setting");
    gtk_window_set_default_size(GTK_WINDOW(window),600,400);
    gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS );

    label = gtk_label_new("这里将有系统设置和个人信息设置两个板块");
    gtk_container_add(GTK_CONTAINER(window),label);

    return window;
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
    gtk_window_set_title(GTK_WINDOW(window),"SevenChat Help");
    gtk_window_set_default_size(GTK_WINDOW(window),400,200);
    gtk_window_set_position( GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS );

    label = gtk_label_new("这里显示SevenChat的说明信息");
    gtk_container_add(GTK_CONTAINER(window),label);

    return window;
}

/************************************************************************
*名称:createInputWindow
*描述:创建输入框窗口
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

//    statusbar = gtk_statusbar_new(); //状态栏
//    gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, FALSE, 0);
//    g_signal_connect(buffer, "changed",G_CALLBACK(update_statusbar), statusbar);
//    g_signal_connect_object(buffer, "mark_set", G_CALLBACK(mark_set_callback), statusbar, 0);

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
void createChatWindow()
{
    popOutBtn = gtk_button_new_with_label("Pop Out");
    g_signal_connect(G_OBJECT(popOutBtn),"clicked",G_CALLBACK(buttonPressPopout),NULL);
    gtk_widget_set_size_request(popOutBtn,60,40);
    gtk_fixed_put(GTK_FIXED(mainFixed),popOutBtn,900,20);

    chatScroll = gtk_scrolled_window_new(NULL,NULL);
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

    gtk_scrolled_window_add_with_viewport(reinterpret_cast<GtkScrolledWindow *>(chatScroll), chatView);
    gtk_fixed_put(GTK_FIXED(mainFixed), chatScroll, 280, 80);
}

/************************************************************************
*名称:createInfoLists
*描述:创建信息列表
*作成日期:2019.09.02
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/
void createInfoLists()
{
    //信息列表
    /**************信息列表层级关系********************
    * mainFixed->infoListLabel
    *          ->infoScroll->vbox->buttons
    **********************************************/
    //当前列表名称
    infoListsLabel = gtk_label_new("TYPE");
    gtk_label_set_markup(GTK_LABEL(infoListsLabel),"<span foreground='white'font_desc='14'>| 消息列表 | </span>");
    gtk_fixed_put(GTK_FIXED(mainFixed),infoListsLabel,90,20);
}


/************************************************************************
*名称:buttonPressLists等
*描述:工具栏按钮触发函数_对应弹出消息列表/好友列表/群组列表/设置/帮助界面
*作成日期:2019.08.29
*参数:无
*返回值:void
*作者:肖成文
************************************************************************/

void buttonPressLists()
{
    g_print("ButtonPressLists!!\n");
}

void buttonPressSetting()
{
    GtkWidget *settingWindow;
    settingWindow = creatSettingWindow();
    gtk_widget_show_all(settingWindow);
}

void buttonPressHelp()
{
    GtkWidget *helpWindow;
    helpWindow = creatHelpWindow();
    gtk_widget_show_all(helpWindow);
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
    g_print("buttonPressPopout!!\n");
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
*名称:update_statusbar
*描述:刷新显示文本框的当前输入状态
*作成日期:2019.09.01
*参数:GtkTextBuffer *buffer：对应文本框缓冲区 GtkStatusbar  *statusbar：当前状态栏
*返回值:无
*作者:肖成文
************************************************************************/
//update_statusbar(GtkTextBuffer *buffer,GtkStatusbar  *statusbar)
//{
//  gchar *msg;
//  gint row, col;
//  GtkTextIter iter;
//
//  gtk_statusbar_pop(statusbar, 0);
//
//  gtk_text_buffer_get_iter_at_mark(buffer,
//      &iter, gtk_text_buffer_get_insert(buffer));
//
//  row = gtk_text_iter_get_line(&iter);
//  col = gtk_text_iter_get_line_offset(&iter);
//
//  msg = g_strdup_printf("Col: %d Ln: %d", col+1, row+1);
//
//  gtk_statusbar_push(statusbar, 0, msg);
//
//  g_free(msg);
//}
//
//void mark_set_callback(GtkTextBuffer *buffer,const GtkTextIter *new_location, GtkTextMark *mark, gpointer data)
//{
//
//  update_statusbar(buffer, GTK_STATUSBAR(data));
//}

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
    //接口函数

    //打印发送人的username
    char usernameNow[20];
    strcpy(usernameNow,"USER01");//待更改
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

    //清空聊天框缓存区内容
    gtk_text_buffer_delete(GTK_TEXT_BUFFER(buffer),&start,&end);
    setScrollPos(chatInfoLen);
}


int main(int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    creatMainWindow(); //创建主窗口
    createToolbarBtn(); //创建工具栏
    createInfoLists(); //创建信息列表
    createInputWindow(); //创建聊天输入框
    createChatWindow(); //创建聊天对话框

    windowLog = createLogWindow();

    windowSign = createSignWindow();

    gtk_widget_show_all(windowLog);
    gtk_main();
    return FALSE;
}
