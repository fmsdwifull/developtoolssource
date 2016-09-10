//hello.c
#include <gtk/gtk.h>

void  on_button_clicked(GtkWidget* button, gpointer userdata)
{
    GtkWidget *dialog;
//������ȷ�ϰ�ť�ĶԻ��򣬸��ؼ�Ϊ��
    dialog = gtk_message_dialog_new(NULL, 
            GTK_DIALOG_MODAL |GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            (gchar*)userdata);
    gtk_dialog_run(GTK_DIALOG(dialog));//��ʾ�����жԻ���
    gtk_widget_destroy(dialog);//���ٶԻ���
}
//������
int main(int argc, char* argv[])
{
    GtkWidget *window, *button;
    //��ʼ��GTK+����
    gtk_init(&argc, &argv);
    //�������ڣ���Ϊ���ڵĹر��źżӻص������Ա��˳�
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window),"delete_event",
            G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"Hello World!");
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    //������ť�ؼ���Ϊ�����źżӻص�������������봰����
    button=gtk_button_new_with_label("Hello World!");
    g_signal_connect(G_OBJECT(button),"clicked",
            G_CALLBACK(on_button_clicked),(gpointer)"��ã�\n���ɵ����硣");
    gtk_container_add(GTK_CONTAINER(window),button);
    //���溯����ʾ���ڿؼ�ͬʱ��ʾ���е����������ؼ�
    gtk_widget_show_all(window);
    gtk_main();
    return FALSE;
}
 


