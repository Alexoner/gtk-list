#include "define.h"

char *city_member_name[CNUM]={"县市编号","县市名称","省自治区编号","森林面积",\
        "木材蓄积量","沙漠面积","土地面积","当年阔叶林造林面积"\
            ,"当年针叶林造林面积","当年经济林造林面积","当年造林资金","累计造林资金",\
            "当年伐木面积","当年木材收益","累计木材收益","当年经济林收益",\
            "累计经济林收益","人口","下辖林场数"};
char *province_member_name[PNUM]={"编号","名称","林木面积",\
        "木材蓄积量","沙漠面积","当年造林面积","当年造林资金","总造林资金",\
            "当年伐木面积","当年木材收益","总木材收益",\
            "当年经济林收益","总经济林收益"};

char *tree_member_name[TNUM]={"林木编号","林木名称","县市编号","省自治区编号",\
        "林木类别","林木面积","木材蓄积量","当年造林面积"\
            ,"当年造林资金","累计造林资金","当年收益","累计收益"};

char *feature_name[]=
{
    "省/自治区","县市","林木面积最大林木","木材蓄积量最多的阔叶林林木",
    "累计造林资金最大针叶林林木","收益最大的林木","总森林面积",
    "总沙漠面积","当年总造林面积","当年总造林资金",
    "该省当年阔叶林造林面积","该省当年针叶林造林面积",
    "该省当年经济林造林面积","该省林木种类数","木材蓄积量前三名的县市",
};

extern void (*function[])(GtkWidget *widget,gpointer data);

/*interfaces: */
void main_menu()
{
    GtkWidget *scrolled_window,*button[MAXINT],*vbox,*box,\
        *entry[MAXINT],*separator;
    GtkObject *adj;
    struct datalist *list[4];
    void *ptr=NULL;
    int i;

    window_main=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_unmaximize(GTK_WINDOW(window_main));
    adj=gtk_adjustment_new(0,0,101,0,0.1,1.0);
    g_signal_connect(window_main,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window_main),"三北防护林信息管理系统");
    gtk_window_set_default_size(GTK_WINDOW(window_main),600,200);
    gtk_window_set_position(GTK_WINDOW(window_main),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window_main),TRUE);

    scrolled_window=gtk_scrolled_window_new(NULL,GTK_ADJUSTMENT(adj));
    gtk_container_add(GTK_CONTAINER(window_main),scrolled_window);
    vbox=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),vbox);



    box=make_label_entry_button(entry+0,button+0,"省/自治区","查询");
    g_signal_connect(button[0],"clicked",G_CALLBACK(query_province),entry[0]);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,TRUE,0);

    box=make_label_entry_button(entry+1,button+1,"县市","查询");
    ptr=malloc(sizeof(GtkWidget*)*2);
    memcpy(ptr,entry,sizeof(GtkWidget*));
    memcpy(ptr+sizeof(GtkWidget*),entry+1,sizeof(GtkWidget*));
    g_signal_connect(button[1],"clicked",G_CALLBACK(query_city),ptr);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,TRUE,0);

    for(i=2;i<6;i++)
    {
        box=make_label_entry_button(entry+i,button+i,
                feature_name[i],"查询");
        g_signal_connect(button[i],"clicked",
                G_CALLBACK(function[i]),entry[i]);
        gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    }

    box=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    separator=gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box),separator,FALSE,FALSE,0);
    gtk_widget_show(separator);
    gtk_widget_show(box);

    for(i=6;i<10;i++)
    {
        box=make_label_entry_button(entry+i,button+i,
                feature_name[i],"统计");
        g_signal_connect(button[i],"clicked",
                G_CALLBACK(function[i]),entry[i]);
        gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    }

    box=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    separator=gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box),separator,FALSE,FALSE,0);
    gtk_widget_show(separator);
    gtk_widget_show(box);

    for(i=10;i<14;i++)
    {
        box=make_label_entry_button(entry+i,button+i,feature_name[i],"统计");
        list[i-10]=(struct datalist*)malloc(sizeof(struct datalist));
        list[i-10]->next=NULL;
        list[i-10]->data=malloc(sizeof(GtkWidget*)*2);
        memcpy(list[i-10]->data,entry,sizeof(GtkWidget*));
        memcpy(list[i-10]->data+sizeof(GtkWidget*),
                entry+i,sizeof(GtkWidget*));
        g_signal_connect(button[i],"clicked",
                G_CALLBACK(function[i]),list[i-10]->data); gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    }

    box=make_label_entry_button(entry+14,button+14,
    "收益为前三名的林木","统计");
    g_signal_connect(button[14],"clicked",
            G_CALLBACK(first_three_tree_of_max_rev),entry[14]);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    box=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    separator=gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box),separator,FALSE,FALSE,0); gtk_widget_show(separator); gtk_widget_show(box);

    box=make_label_entry_button(entry+15,button+15,
            "木材蓄积量前三名的县市","统计");
    g_signal_connect(button[15],"clicked",
            G_CALLBACK(first_three_cities_of_max_timber),entry[15]);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);



    box=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    button[0]=gtk_button_new_with_label("录入数据");
    g_signal_connect(button[0],"clicked",G_CALLBACK(record_data),NULL);
    gtk_box_pack_start(GTK_BOX(box),button[0],TRUE,FALSE,0);
    gtk_widget_show(button[0]);

    button[1]=gtk_button_new_with_label("  保存  ");
    g_signal_connect(button[1],"clicked",G_CALLBACK(main_menu_save),NULL);
    gtk_box_pack_start(GTK_BOX(box),button[1],TRUE,FALSE,0);
    gtk_widget_show(button[1]);

    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    gtk_widget_show(box);
    gtk_widget_show(vbox);
    gtk_widget_show(scrolled_window);
    gtk_widget_show(window_main);
}



void insert_province(Province *ptr)
{
    current_province=ptr;
    GtkWidget *vbox,*box;
    GtkWidget *entry[13],*button[5];
    int i;
    gchar title[64]="insert province";
    window_insert_province=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window_insert_province),title);
    gtk_window_unmaximize(GTK_WINDOW(window_insert_province));
    g_signal_connect(window_insert_province,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    vbox=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window_insert_province),vbox);

    box=make_province_box(entry,PNUM);
    for(i=0;i<PNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),TRUE);
    }
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    button[0]=gtk_button_new_with_label("市");
    g_signal_connect(button[0],"clicked",G_CALLBACK(insert_province_city),NULL);
    gtk_box_pack_start(GTK_BOX(box),button[0],TRUE,TRUE,0);
    gtk_widget_show(box);
    gtk_widget_show(button[0]);

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    button[1]=gtk_button_new_with_label("头结点");
    g_signal_connect(button[1],"clicked",G_CALLBACK(insert_province_make_head),entry);
    gtk_box_pack_start(GTK_BOX(box),button[1],TRUE,TRUE,0);
    gtk_widget_show(button[1]);

    button[2]=gtk_button_new_with_label("next");
    g_signal_connect(button[2],"clicked",G_CALLBACK(insert_province_next),entry);
    gtk_box_pack_start(GTK_BOX(box),button[2],TRUE,TRUE,0);
    gtk_widget_show(button[2]);

    button[3]=gtk_button_new_with_label("finish");
    g_signal_connect(button[3],"clicked",G_CALLBACK(insert_province_finish),entry);
    gtk_box_pack_start(GTK_BOX(box),button[3],TRUE,TRUE,0);
    gtk_widget_show(button[3]);


    gtk_widget_show(box);
    gtk_widget_show(vbox);
    gtk_widget_show(window_insert_province);
    gtk_main();//somehow,very important
}

 void insert_city(Province **pp)
{//show the interface of insertint city node
    GtkWidget *vbox,*box,*entry[CNUM],*button[5],*scrolled_window;
    GtkObject *adj=gtk_adjustment_new(0,0,101,0,0.1,1.0);
    gint i;
    gchar title[64]="Province:";
    if(!head_province)
    {
        g_print("No province added\n");
        return;
    }
    strcat(title,current_province->num);
    strcat(title,"  insert city");
    //window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    window_insert_city=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window_insert_city),400,300);
    gtk_window_set_title(GTK_WINDOW(window_insert_city),title);
    gtk_window_unfullscreen(GTK_WINDOW(window_insert_city));
    g_signal_connect(window_insert_city,"delete-event",
            G_CALLBACK(gtk_main_quit),NULL);
    scrolled_window=gtk_scrolled_window_new(NULL,GTK_ADJUSTMENT(adj));
    gtk_container_add(GTK_CONTAINER(window_insert_city),scrolled_window);
    vbox=gtk_vbox_new(FALSE,0);/*the box container is usually set to
                                 (FALSE,0),for formatting*/
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(\
                scrolled_window),vbox);

    box=make_city_box(entry);
    for(i=0;i<CNUM;i++)
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),TRUE);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    gtk_widget_show(box);

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    button[0]=gtk_button_new_with_label("林木");
    g_signal_connect(button[0],"clicked",G_CALLBACK(insert_city_tree),entry);
    gtk_box_pack_start(GTK_BOX(box),button[0],FALSE,TRUE,0);
    gtk_widget_show(button[0]);
    gtk_widget_show(box);

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);


    button[2]=gtk_button_new_with_label("下一步");
    g_signal_connect(button[2],"clicked",G_CALLBACK(insert_city_next),entry);
    gtk_box_pack_start(GTK_BOX(box),button[2],TRUE,TRUE,0);
    gtk_widget_show(button[2]);

    button[3]=gtk_button_new_with_label("完成");
    g_signal_connect(button[3],"clicked",G_CALLBACK(insert_city_finish),entry);
    gtk_box_pack_start(GTK_BOX(box),button[3],TRUE,TRUE,0);
    gtk_widget_show(button[3]);

    //button[4]=gtk_button_new_with_label("");

    gtk_widget_show_all(window_insert_city);
    gtk_main();
}

void insert_tree()
{
    GtkWidget *vbox,*box,*label[TNUM],*entry[TNUM],*button[5];
    gint i;
    gchar title[64]="Province:";
    if(!head_city)
    {
        g_print("No city added\n");
        return;
    }
    strcat(title,current_city->province_num);
    strcat(title," city ");
    strcat(title,current_city->num);
    strcat(title," insert tree");

    window_insert_tree=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window_insert_tree),title);
    gtk_window_unmaximize(GTK_WINDOW(window_insert_tree));
    g_signal_connect(window_insert_tree,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    vbox=gtk_vbox_new(TRUE,0);
    gtk_container_add(GTK_CONTAINER(window_insert_tree),vbox);
    for(i=0;i<TNUM;i++)
    {
        box=gtk_hbox_new(TRUE,0);
        gtk_box_pack_start(GTK_BOX(vbox),box,TRUE,FALSE,0);
        label[i]=gtk_label_new(tree_member_name[i]);
        gtk_box_pack_start(GTK_BOX(box),label[i],TRUE,FALSE,0);

        entry[i]=gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(box),entry[i],TRUE,FALSE,0);

        gtk_widget_show(label[i]);
        gtk_widget_show(entry[i]);
        gtk_widget_show(box);
    }

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,TRUE,TRUE,0);

    button[1]=gtk_button_new_with_label("下一步");
    g_signal_connect(button[1],"clicked",G_CALLBACK(insert_tree_next),entry);
    gtk_box_pack_start(GTK_BOX(box),button[1],TRUE,TRUE,0);
    gtk_widget_show(button[1]);

    button[2]=gtk_button_new_with_label("完成");
    g_signal_connect(button[2],"clicked",G_CALLBACK(insert_tree_finish),entry);
    gtk_box_pack_start(GTK_BOX(box),button[2],TRUE,TRUE,0);
    gtk_widget_show(button[2]);


    gtk_widget_show(box);
    gtk_widget_show(vbox);
    gtk_widget_show(window_insert_tree);
    gtk_main();
}

void view_province(Province *p)
{
    GtkWidget *vbox,*box,*entry[PNUM],*button[MAXINT];
    gchar str[64]="view Province";
    window_view_province=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window_view_province),str);
    gtk_window_unmaximize(GTK_WINDOW(window_view_province));
    g_signal_connect(window_view_province,
            "delete-event",G_CALLBACK(gtk_main_quit),NULL);
    vbox=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window_view_province),vbox);
    box=make_province_box(entry,PNUM);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    show_province_node(p,entry);

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    button[0]=gtk_button_new_with_label("查询市");
    g_signal_connect(button[0],"clicked",
            G_CALLBACK(view_province_city),current_province);
    gtk_box_pack_start(GTK_BOX(box),button[0],TRUE,TRUE,0);
    gtk_widget_show(button[0]);
    gtk_widget_show(box);

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);
    button[1]=gtk_button_new_with_label("修改");
    g_signal_connect(button[1],"clicked",
            G_CALLBACK(view_province_modify),entry);
    gtk_box_pack_start(GTK_BOX(box),button[1],TRUE,TRUE,0);
    gtk_widget_show(button[1]);

    button[2]=gtk_button_new_with_label("确定");
    g_signal_connect(button[2],"clicked",G_CALLBACK(view_province_confirm),entry);
    gtk_box_pack_start(GTK_BOX(box),button[2],TRUE,TRUE,0);
    gtk_widget_show(button[2]);
    gtk_widget_show(box);

    button[3]=gtk_button_new_with_label("插入");
    g_signal_connect(button[3],"clicked",G_CALLBACK(view_province_insert),p);
    gtk_box_pack_start(GTK_BOX(box),button[3],TRUE,TRUE,0);
    gtk_widget_show(button[3]);

    button[4]=gtk_button_new_with_label("删除");
    g_signal_connect(button[4],"clicked",G_CALLBACK(view_province_delete),NULL);
    gtk_box_pack_start(GTK_BOX(box),button[4],TRUE,TRUE,0);
    gtk_widget_show(button[4]);

    button[5]=gtk_button_new_with_label("上一个");
    g_signal_connect(button[5],"clicked",G_CALLBACK(view_province_prior),entry);
    gtk_box_pack_start(GTK_BOX(box),button[5],TRUE,TRUE,0);
    gtk_widget_show(button[5]);

    button[6]=gtk_button_new_with_label("下一个");
    g_signal_connect(button[6],"clicked",G_CALLBACK(view_province_next),entry);
    gtk_box_pack_start(GTK_BOX(box),button[6],TRUE,TRUE,0);
    gtk_widget_show(button[6]);


    gtk_widget_show(vbox);
    gtk_widget_show(window_view_province);
    gtk_main();
}

void view_city(City *p)
{
    GtkWidget *vbox,*box,*entry[CNUM],*button[MAXINT],*scrolled_window;
    GtkObject *adj;
    gchar str[64]="Province ";
    strcat(str,current_province->num);
    strcat(str," view city");
    adj=gtk_adjustment_new(0,0,101,0,0.1,1.0);
    window_view_city=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window_view_city),400,300);
    gtk_window_set_title(GTK_WINDOW(window_view_city),str);
    gtk_window_unmaximize(GTK_WINDOW(window_view_city));
    g_signal_connect(window_view_city,"delete-event",
            G_CALLBACK(gtk_main_quit),NULL);
    scrolled_window=gtk_scrolled_window_new(NULL,GTK_ADJUSTMENT(adj));
    gtk_container_add(GTK_CONTAINER(window_view_city),scrolled_window);
    vbox=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),vbox);

    box=make_city_box(entry);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    show_city_node(p,entry);


    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    button[0]=gtk_button_new_with_label("查询林木");
    g_signal_connect(button[0],"clicked",G_CALLBACK(view_city_tree),p);
    gtk_box_pack_start(GTK_BOX(box),button[0],TRUE,TRUE,0);
    gtk_widget_show(button[0]);
    gtk_widget_show(box);

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    button[1]=gtk_button_new_with_label("修改");
    g_signal_connect(button[1],"clicked",G_CALLBACK(view_city_modify),entry);
    gtk_box_pack_start(GTK_BOX(box),button[1],TRUE,TRUE,0);
    gtk_widget_show(button[1]);

    button[2]=gtk_button_new_with_label("确定");
    g_signal_connect(button[2],"clicked",G_CALLBACK(view_city_confirm),entry);
    gtk_box_pack_start(GTK_BOX(box),button[2],TRUE,TRUE,0);
    gtk_widget_show(button[2]);

    button[3]=gtk_button_new_with_label("插入");
    g_signal_connect(button[3],"clicked",G_CALLBACK(view_city_insert),entry);
    gtk_box_pack_start(GTK_BOX(box),button[3],TRUE,TRUE,0);
    gtk_widget_show(button[3]);

    button[4]=gtk_button_new_with_label("删除");
    g_signal_connect(button[4],"clicked",G_CALLBACK(view_city_delete),entry);
    gtk_box_pack_start(GTK_BOX(box),button[4],TRUE,TRUE,0);
    gtk_widget_show(button[4]);

    button[5]=gtk_button_new_with_label("上一个");
    g_signal_connect(button[5],"clicked",G_CALLBACK(view_city_prior),entry);
    gtk_box_pack_start(GTK_BOX(box),button[5],TRUE,TRUE,0);
    gtk_widget_show(button[5]);

    button[6]=gtk_button_new_with_label("下一个");
    g_signal_connect(button[6],"clicked",G_CALLBACK(view_city_next),entry);
    gtk_box_pack_start(GTK_BOX(box),button[6],TRUE,TRUE,0);
    gtk_widget_show(button[6]);


    gtk_widget_show_all(window_view_city);
    gtk_main();
}

void view_tree(Tree *p)
{
    GtkWidget *vbox,*box,*entry[TNUM],*button[MAXINT];
    gchar str[64]="Province:";
    strcat(str,current_province->num);
    strcat(str,"City:");
    strcat(str,current_city->num);
    strcat(str,"view tree");
    window_view_tree=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_unmaximize(GTK_WINDOW(window_view_tree));
    gtk_window_set_title(GTK_WINDOW(window_view_tree),str);
    g_signal_connect(window_view_tree,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    vbox=gtk_vbox_new(FALSE,0); gtk_container_add(GTK_CONTAINER(window_view_tree),vbox);
    box=make_tree_box(entry);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    show_tree_node(p,entry);


    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    box=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),box,FALSE,FALSE,0);

    button[0]=gtk_button_new_with_label("修改");
    g_signal_connect(button[0],"clicked",G_CALLBACK(view_tree_modify),entry);
    gtk_box_pack_start(GTK_BOX(box),button[0],TRUE,TRUE,0);
    gtk_widget_show(button[0]);

    button[1]=gtk_button_new_with_label("确定");
    g_signal_connect(button[1],"clicked",G_CALLBACK(view_tree_confirm),entry);
    gtk_box_pack_start(GTK_BOX(box),button[1],TRUE,TRUE,0);
    gtk_widget_show(button[1]);

    button[2]=gtk_button_new_with_label("插入");
    g_signal_connect(button[2],"clicked",G_CALLBACK(view_tree_insert),entry);
    gtk_box_pack_start(GTK_BOX(box),button[2],TRUE,TRUE,0);
    gtk_widget_show(button[2]);

    button[3]=gtk_button_new_with_label("删除");
    g_signal_connect(button[3],"clicked",G_CALLBACK(view_tree_delete),entry);
    gtk_box_pack_start(GTK_BOX(box),button[3],TRUE,TRUE,0);
    gtk_widget_show(button[3]);

    button[4]=gtk_button_new_with_label("上一个");
    g_signal_connect(button[4],"clicked",G_CALLBACK(view_tree_prior),entry);
    gtk_box_pack_start(GTK_BOX(box),button[4],TRUE,TRUE,0);
    gtk_widget_show(button[4]);

    button[5]=gtk_button_new_with_label("下一个");
    g_signal_connect(button[5],"clicked",G_CALLBACK(view_tree_next),entry);
    gtk_box_pack_start(GTK_BOX(box),button[5],TRUE,TRUE,0);
    gtk_widget_show(button[5]);


    gtk_widget_show(box);
    gtk_widget_show(vbox);
    gtk_widget_show(window_view_tree);
    gtk_main();
}




/*interfaces.*/

int main(int argc,char **argv)
{
    current_province=head_province=NULL;
    current_city=head_city=NULL;
    current_tree=head_tree=NULL;
    window_main=window_insert_province=window_insert_city=window_insert_tree=NULL;
    gtk_init(&argc,&argv);
    load("province.dat","city.dat","tree.dat");
    current_province=NULL;
    current_city=head_city=NULL;
    current_tree=head_tree=NULL;
    //save("province.dat","city.dat","tree.dat");
    main_menu();
    gtk_main();
    return 0;
}
