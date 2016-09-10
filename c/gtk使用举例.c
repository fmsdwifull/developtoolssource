//hello.c
#include <gtk/gtk.h>

void  on_button_clicked(GtkWidget* button, gpointer userdata)
{
    GtkWidget *dialog;
//创建带确认按钮的对话框，父控件为空
    dialog = gtk_message_dialog_new(NULL, 
            GTK_DIALOG_MODAL |GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            (gchar*)userdata);
    gtk_dialog_run(GTK_DIALOG(dialog));//显示并运行对话框
    gtk_widget_destroy(dialog);//销毁对话框
}
//主函数
int main(int argc, char* argv[])
{
    GtkWidget *window, *button;
    //初始化GTK+程序
    gtk_init(&argc, &argv);
    //创建窗口，并为窗口的关闭信号加回调函数以便退出
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"delete_event",
            G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"Hello World!");
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    //创建按钮控件，为单击信号加回调函数，将其放入窗口中
    button=gtk_button_new_with_label("Hello World!");
    g_signal_connect(G_OBJECT(button),"clicked",
            G_CALLBACK(on_button_clicked),(gpointer)"你好！\n自由的世界。");
    gtk_container_add(GTK_CONTAINER(window),button);
    //下面函数显示窗口控件同时显示其中的所有其它控件
    gtk_widget_show_all(window);
    gtk_main();
    return FALSE;
}
 


