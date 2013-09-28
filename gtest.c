#include <gtk/gtk.h>

void window()
{
    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_show(window);
}
