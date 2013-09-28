/*************************************************************************
    > File Name: gui.c
    > Created Time: Tue 02 Oct 2012 06:15:09 PM CST
 ************************************************************************/
#include "define.h"

/*useful gui functions:*/
void clear_entry(GtkWidget **entry,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        gtk_entry_set_text(GTK_ENTRY(entry[i]),"");//not NULL,
        //which is wrong:"assertion "text != NULL" failed"
    }
}

GtkWidget *make_label_entry_button(
        GtkWidget **entry,
        GtkWidget **button,
        char *label_name,
        char *button_name)
{
    GtkWidget *vbox,*box,*label/*,*entry,*button*/;
    vbox=gtk_vbox_new(FALSE,0);
    box=gtk_hbox_new(TRUE,0);/*expand is assigned to TRUE
                               enable the labels share width*/
    gtk_box_pack_start(GTK_BOX(vbox),box,TRUE,FALSE,0);
    label=gtk_label_new(label_name);
    gtk_misc_set_alignment(GTK_MISC(label),0,0);
    gtk_label_set_max_width_chars(GTK_LABEL(label),30);
    gtk_box_pack_start(GTK_BOX(box),label,TRUE,FALSE,0);
    gtk_widget_show(label);
    gtk_widget_show(box);
    /*box=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);*/
    *entry=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box),*entry,TRUE,TRUE,0);
    *button=gtk_button_new_with_label(button_name);
    //g_signal_connect(button[3],"clicked",G_CALLBACK(),NULL);
    gtk_box_pack_start(GTK_BOX(box),*button,FALSE,FALSE,0);
    gtk_widget_show(*entry);
    gtk_widget_show(*button);
    gtk_widget_show(box);
    gtk_widget_show(vbox);
    return vbox;
}

GtkWidget *make_province_box(GtkWidget **entry,int n)
{
    GtkWidget *vbox,*box;
    GtkWidget *label[13];
    int i;
    vbox=gtk_vbox_new(FALSE,0);
    for(i=0;i<n;i++)
    {
        box=gtk_hbox_new(FALSE,0); gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

        label[i]=gtk_label_new(province_member_name[i]);//label of id,etc
        gtk_misc_set_alignment(GTK_MISC(label[i]),0,0);
        gtk_box_pack_start(GTK_BOX(box),label[i],TRUE,FALSE,0);
        gtk_widget_show(label[i]);
        entry[i]=gtk_entry_new();//text entry
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
        gtk_box_pack_start(GTK_BOX(box),entry[i],FALSE,TRUE,0);
        gtk_widget_show(entry[i]);
        gtk_widget_show(box);
    }
    gtk_widget_show(vbox);
    return vbox;
}

GtkWidget *make_city_box(GtkWidget **entry)
{
    GtkWidget *label[CNUM],*vbox,*box;
    gint i;
    vbox=gtk_vbox_new(FALSE,0);

    for(i=0;i<CNUM;i++)
    {
        box=gtk_hbox_new(TRUE,0);
        gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
        label[i]=gtk_label_new(city_member_name[i]);
        gtk_box_pack_start(GTK_BOX(box),label[i],TRUE,FALSE,0);
        entry[i]=gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(box),entry[i],TRUE,TRUE,0);
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
        gtk_widget_show(label[i]);
        gtk_widget_show(entry[i]);
        gtk_widget_show(box);
    }
    gtk_widget_show(vbox);
    return vbox;
}


GtkWidget *make_tree_box(GtkWidget **entry)
{
    GtkWidget *vbox,*box,*label[TNUM];
    gint i;
    vbox=gtk_vbox_new(FALSE,0);
    for(i=0;i<TNUM;i++)
    {
        box=gtk_hbox_new(TRUE,0);
        gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
        label[i]=gtk_label_new(tree_member_name[i]);
        gtk_box_pack_start(GTK_BOX(box),label[i],TRUE,TRUE,0);
        gtk_widget_show(label[i]);

        entry[i]=gtk_entry_new();
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
        gtk_box_pack_start(GTK_BOX(box),entry[i],TRUE,TRUE,0);
        gtk_widget_show(entry[i]);

        gtk_widget_show(box);
    }
    gtk_widget_show(vbox);
    return vbox;
}




GtkWidget **show_province_node(Province *p,GtkWidget **entry)
{
    gchar str[MAXINT];
    gpointer gp=NULL;
    gint i;
    gtk_entry_set_text(GTK_ENTRY(entry[0]),p->num);
    gtk_entry_set_text(GTK_ENTRY(entry[1]),p->name);
    for(i=2,gp=&p->forest_area;i<PNUM;i++)
    {
        sprintf(str,"%f",*((float*)gp));
        gtk_entry_set_text(GTK_ENTRY(entry[i]),str);
        gtk_widget_show(entry[i]);
        gp+=sizeof(float);
        //g_print("the gpointer is %p\n",gp);
    }
    return entry;
}

GtkWidget ** show_city_node(City *p,GtkWidget **entry)
{
    gchar str[MAXINT];
    gpointer ptr=NULL;
    gint i;
    gtk_entry_set_text(GTK_ENTRY(entry[0]),p->num);
    gtk_entry_set_text(GTK_ENTRY(entry[1]),p->name);
    gtk_entry_set_text(GTK_ENTRY(entry[2]),p->province_num);
    for(i=3,ptr=(&p->province_num)+1;i<CNUM-2;i++)/******************
                                                    important pointer utility
                                                    *****************/
    {
        sprintf(str,"%f",*((float*)ptr));/*force cast*/
        gtk_entry_set_text(GTK_ENTRY(entry[i]),str);
        ptr+=sizeof(float);
        //g_print("ptr is %p\n",ptr);
    }
    sprintf(str,"%d",p->population);
    gtk_entry_set_text(GTK_ENTRY(entry[17]),str);
    sprintf(str,"%d",p->forest_amount);
    gtk_entry_set_text(GTK_ENTRY(entry[18]),str);

    return entry;
}

GtkWidget **show_tree_node(Tree *p,GtkWidget **entry)
{
    gint i;
    gpointer ptr=(gpointer)p;
    gchar str[MAXINT];
    gtk_entry_set_text(GTK_ENTRY(entry[0]),p->num);
    gtk_entry_set_text(GTK_ENTRY(entry[1]),p->name);
    gtk_entry_set_text(GTK_ENTRY(entry[2]),p->city_num);
    gtk_entry_set_text(GTK_ENTRY(entry[3]),p->province_num);
    gtk_entry_set_text(GTK_ENTRY(entry[4]),p->category);
    ptr=(&p->forest_area);
    for(i=5;i<TNUM;i++)
    {
        sprintf(str,"%f",*((float*)ptr));
        gtk_entry_set_text(GTK_ENTRY(entry[i]),str);
        ptr+=sizeof(float);
    }
    return entry;
}

/*useful gui funcitons.*/

