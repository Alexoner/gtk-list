/*************************************************************************
    > File Name: gui.h
    > Author: hao
    > Mail: onerhao@gmail.com
    > Created Time: Wed 26 Dec 2012 08:31:31 PM CST
 ************************************************************************/
#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>


extern void clear_entry(GtkWidget **entry,n);
//clear an array of n text entries

extern GtkWidget *make_label_entry_button(
        GtkWidget **entry,
        GtkWidget **button,
        char *label_name,
        char *button_name)
//make a lable,an text entry,a button in a horizonal box


#endif
