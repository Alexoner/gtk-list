#include<gtk/gtk.h>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define SNUM 15 /*station number*/
#define TNUM 18 /*Train number*/
#define PNUM 14 /*passing Train number*/
#define Max 32
typedef struct Train       /*车次结构*/
{
    char Train_num[8];     /*车次编号*/
    char Train_name[20];   /*车次名称*/
    char Train_type_num[2];/*车次类型编码*/
    char Train_type_name[20];/*车次类型名称*/
    char bureau_num[8];    /*编号所属路局*/
    char bureau_name[20];  /*所属路局名称*/
    char starting_station[10];/*始发站*/
    char starting_time[20];/*始发时间*/
    char ending_station[10];/*终到站*/
    char ending_time[20];  /*终到时间*/
    float hard_sleeper_down_whole_price;/*硬卧下铺全程票价*/
    float hard_sleeper_middle_whole_price;/*硬卧中铺全程票价*/
    float hard_sleeper_up_whole_price;/*硬卧上铺全程票价*/
    float soft_seat_down_whole_price;/*软卧下铺全程票价*/
    float soft_seat_up_whole_price;/*软卧上铺全程票价*/
    float hard_seat_whole_price;/*硬座全程票价*/
    char whole_running_time[10];/*全程运行时间*/
    int whole_running_distance;/*全程运行里程*/
    struct Train *next;/*指向下一个train结点的指针*/
    struct station *head_station;/*指向经停车站头结点的指针*/
}Train;


typedef struct station/*经停车站结构*/
{
    char station_num[8];/*车站编号*/
    char station_name[20];/*车站名称*/
    char bureau_num[8];/*所属路局编号*/
    char Train_num[8];/*车次编号*/
    char arrival_time[10];/*到站时间*/
    char starting_time[10];/*开车时间*/
    char running_time[10];/*运行时间*/
    int distance;/*运行里程*/
    float hard_sleeper_down_price;/*硬卧下铺票价*/
    float hard_sleeper_middle_price;/*硬卧中铺票价*/
    float hard_sleeper_up_price;/*硬卧上铺票价*/
    float soft_seat_down_price;/*软卧下铺票价*/
    float soft_seat_up_price;/*软卧上铺票价*/
    float hard_seat_price;/*硬座全程票价*/
    int remaining_ticket_train_num;/*余票车次数量*/

    struct station *next;/*指向下一个station结点的指针*/
    struct passing_Train *head_passing_Train;/*指向经停车次头结点的指针*/
}station;

typedef struct passing_Train/*经停车次结构*/
{
    char passing_Train_num[8];/*经停车次编号*/
    char passing_Train_name[20];/*经停车次名称*/
    char station_num[8];/*车站编号*/
    char bureau_num[8];/*所属路局编号*/
    char Train_type[6];/*车次类型*/
    char entering_time[10];/*进站时间*/
    char starting_time[10];/*开车时间*/
    float hard_sleeper_down_price;/*硬卧下铺票价*/
    float hard_sleeper_middle_price;/*硬卧中铺票价*/
    float hard_sleeper_up_price;/*硬卧上铺票价*/
    float soft_seat_down_price;/*软卧下铺票价*/
    float soft_seat_up_price;/*软卧上铺票价*/
    float hard_seat_whole_price;/*硬座全程票价*/
    int remaining_ticket_num;/*余票数量*/
    struct passing_Train *next;/*指向下一个passing_train结点的指针*/
}passing_Train;

typedef struct
{
    Train *p;
    GtkWidget **entry;
}tcombination;

typedef struct
{
    station *p;
    GtkWidget **entry;
}scombination;

typedef struct
{
    void *p;
    void **entry;
}p_entry;

typedef struct
{
    GtkWidget **entry;
    GtkWidget **import_entry;
}dentry;

typedef struct count
{
    char *name;
    int num;
    struct count *next;
}count;

Train *head_Train,*current_Train;/*链表train的头指针*/
station *head_station,*current_station;/*链表station的头指针*/
passing_Train *head_passing_Train,*current_passing_Train;/*链表passing_train的头指针*/

const gchar Train_member[TNUM][50]={"车次编号","车次名称","车次类型编码",
    "车次类型名称","所属路局编号","所属路局名称","始发站",
    "始发时间","终到站","终到时间",
"硬卧下铺全程票价","硬卧中铺全程票价",
"硬卧上铺全程票价","软卧下铺全程票价","软卧上铺全程票价","硬座全程票价",
"全程运行时间","全程运行里程"};/*结构train成员的二位数组*/

const gchar station_member[SNUM][50]={"车站编号","车站名称","所属路局编号",
    "车次编号","进站时间","开车时间","运行时间","运行里程","硬卧下铺票价",
        "硬卧中铺票价","硬卧上铺票价","软卧下铺票价","软卧上铺票价","硬座全程票价",
        "余票车次数量"};                                                     /*结构station成员的二位数组*/

const gchar passing_Train_member[PNUM][50]={"经停车次编号","经停车次名称","车站编号",
    "路局编号","车次类型","进站时间","开车时间","硬卧下铺票价","硬卧中铺票价",
        "硬卧上铺票价","软卧下铺票价","软卧上铺票价","硬座全程票价","余票数量"};/*结构passing_train成员的二位数组*/

/*callbacks declaration*/
static gboolean delete_event(GtkWidget *widget,GdkEvent **event,gpointer data);

static void add_Train(GtkWidget *widget,gpointer data);
static void add_station_info(GtkWidget *widget,tcombination *pc);
static void add_passing_Train(GtkWidget *widget,scombination *ps);

static void add_passing_Train_confirm(GtkWidget *widget,scombination *ps);
static void add_station_confirm(GtkWidget *widget,tcombination *pc);
static void add_Train_confirm(GtkWidget *widget,GtkWidget **entry);

static void modify_train(GtkWidget *widget,p_entry *pe);
static void modify_station(GtkWidget *widget,p_entry *pe);
static void modify_passing_train(GtkWidget *widget,p_entry *pe);

static void modify_train_confirm(GtkWidget *widget,p_entry *pe);
static void modify_station_confirm(GtkWidget *widget,p_entry *pe);
static void modify_passing_train_confirm(GtkWidget *widget,p_entry *pe);

static void delete_Train(GtkWidget *widget,p_entry *pe);
static void delete_station(GtkWidget *widget,p_entry *pe);
static void delete_passing_Train(GtkWidget *widget,p_entry *pe);

static void delete_Train_confirm(GtkWidget *widget,p_entry *pe);
static void delete_station_confirm(GtkWidget *widget,p_entry *pe);
static void delete_passing_Train_confirm(GtkWidget *widget,p_entry *pe);

static void view_Train_num(GtkWidget *widget,GtkWidget **import_entry);
static void view_Train_station(GtkWidget *widget,dentry *double_entry);
static void view_pass_Train(GtkWidget *widget,dentry *double_entry2);

static void inquire_info(GtkWidget *widget,gpointer data);

/*callbacks end*/
static GtkWidget *make_Train_box(GtkWidget *vbox,GtkWidget **entry);
static GtkWidget *make_label_entry(const gchar *label_name,GtkWidget **entry);
static GtkWidget *make_station_box(GtkWidget *v_box,GtkWidget **entry);
static GtkWidget *make_passing_Train_box(GtkWidget *box_v,GtkWidget **entry);
static GtkWidget *make_label_entry_button(const char *label_name,GtkWidget **entry,GtkWidget **button,const char *button_name);
static void show_Train_node(Train *p,GtkWidget **entry);
static GtkWidget **show_station_node(station *p,GtkWidget **entry);
static GtkWidget **show_passing_Train_node(passing_Train *p,GtkWidget **entry);

Train *insert_Train_node(Train *current,Train *p);
Train *get_Train_node(GtkWidget **entry);
Train *delete_Train_node(Train *current,Train *p);
passing_Train *insert_passing_Train_node(passing_Train *current,passing_Train *p);
passing_Train *get_passing_Train_node(GtkWidget **entry);
passing_Train *delete_passing_Train_node(passing_Train *current,passing_Train *p);
station *insert_station_node(station *current,station *p);
station *get_station_node(GtkWidget **entry);
station *delete_station_node(station *current,station *p);

gpointer sort(count **head);
static void station_with_most_passing_train(GtkWidget *widget,GtkWidget *entry);
static void Gtrain_num(GtkWidget *widget,GtkWidget *entry);
static void Dtrain_num(GtkWidget *widget,GtkWidget *entry);
static void Ztrain_num(GtkWidget *widget,GtkWidget *entry);
static void num_of_station_without_tickets(GtkWidget *widget,
        GtkWidget *entry);
static void passing_train_with_remaining_ticket(GtkWidget *widget,GtkWidget *entry);
static void first_three_station(GtkWidget *widget,GtkWidget *entry);
static void station_of_specified_num(GtkWidget *widget,GtkWidget *entry);

static int create_list(Train **head_train);
static int save(char *namet,char *names,char *namep);

static int create_list(Train **head_train)
{
    Train *hd=NULL,*ptrain;
    station *pstation;
    passing_Train *ppassingtrain;
    FILE *pfile;
    int re=0;
    if((pfile=fopen("./train_data.dat","rb"))==NULL)
    {
        printf("fail to open file train_data.dat!\n");
        return re;
    }
    printf("succeed in opening file train_data.dat!\n");

    while(!feof(pfile))
    {
        ptrain=(Train *)malloc(sizeof(Train));
        fread(ptrain,sizeof(Train),1,pfile);
        if(feof(pfile))
        {
            g_print("end of file train.dat\n");
            break;
        }
        g_print("new node loaded :%s\n",ptrain->Train_num);
        g_print("[cre]train_type_num:%s\n",ptrain->Train_type_num);
        ptrain->head_station=NULL;
        ptrain->next=hd;
        hd=ptrain;
    }

    fclose(pfile);

    if(hd==NULL)
    {
        printf("fail to load the train infomation!\n");
        return re;
    }
    printf("succeed to load the train infomation!\n");

    *head_train=hd;
    re+=4;




    if((pfile=fopen("station_data.dat","rb"))==NULL)
    {
        printf("fail to open file station_data.dat\n");
        return re;
    }
    printf("succeed to open file station_data.dat\n");
    re+=8;

    while(!feof(pfile))
    {
        pstation=(station *)malloc(sizeof(station));
        fread(pstation,sizeof(station),1,pfile);
        pstation->head_passing_Train=NULL;

        ptrain=hd;
        while(ptrain&&strcmp(ptrain->Train_num,pstation->Train_num))
        {
            ptrain=ptrain->next;
        }

        if(ptrain)
        {
            pstation->next=ptrain->head_station;
            ptrain->head_station=pstation;
        }
        else
        {
            printf("no ptrain\n");
            continue;
        }
        pstation=ptrain->head_station;
        while(pstation)
        {
            g_print("traversing Train:%s\tstation :%s\n",ptrain->Train_num,pstation->Train_num);
            pstation=pstation->next;
        }
    }
    fclose(pfile);




    if((pfile=fopen("passing_train_data.dat","rb"))==NULL)
    {
        printf("fail to open file passing_train_data.dat!\n");
        return re;
    }

    printf("succeed in opening file passing_train_data.dat!\n");
    re+=16;

    while(!feof(pfile))
    {
        ppassingtrain=(passing_Train *)malloc(sizeof(passing_Train));
        fread(ppassingtrain,sizeof(passing_Train),1,pfile);
        if(feof(pfile))
        {
            break;
        }
        ptrain=hd;
        while(ptrain&&strcmp(ptrain->bureau_num,ppassingtrain->bureau_num))
            ptrain=ptrain->next;
        if(ptrain)
        {//found the corresponding train
            pstation=ptrain->head_station;
            while(pstation&&strcmp(pstation->station_num,ppassingtrain->station_num))
            {
                pstation=pstation->next;
            }
            if(!pstation)
            {
                printf("no passing train\n");
                return 0;
            }
            ppassingtrain->next=pstation->head_passing_Train;
            pstation->head_passing_Train=ppassingtrain;
        }
    }
    fclose(pfile);
    return re;
}

static int save(char *namet,char *names,char *namep)
{
    FILE *fp[3];
    Train *p1;
    station *p2;
    passing_Train *p3;
    fp[0]=fopen(namet,"wb");
    fp[1]=fopen(names,"wb");
    fp[2]=fopen(namep,"wb");
    if(!(fp[0]&&fp[1]&&fp[2]))
    {
        printf("[save] error in opening files\n");
        return 0;
    }
    p1=head_Train;
    while(p1)
    {
        fwrite(p1,sizeof(Train),1,fp[0]);
        printf("[save]Train%s\n",p1->Train_num);
        printf("[save]train_type_num:    %s\n",p1->Train_type_num);
        p1=p1->next;
    }
    for(p1=head_Train;p1;p1=p1->next)
        for(p2=p1->head_station;p2;p2=p2->next)
        {
            fwrite(p2,sizeof(station),1,fp[1]);
            printf("[save]train:%s\tstation:%s\n",p2->Train_num,p2->station_num);
        }
    for(p1=head_Train;p1;p1=p1->next)
        for(p2=p1->head_station;p2;p2=p2->next)
            for(p3=p2->head_passing_Train;p3;p3=p3->next)
            {
                fwrite(p3,sizeof(passing_Train),1,fp[2]);
                printf("[save]station:%s\npassing_train:%s\n",p3->station_num,p3->passing_Train_num);
            }
    fclose(fp[0]);
    fclose(fp[1]);
    fclose(fp[2]);
    return 0;
}

gpointer sort(count **head)
{
    count *p,*q;
    int n,i,tmp;
    char *str;
    for(p=*head,n=0;p;p=p->next)
        n++;
    for(i=0;i<n;i++)
        for(p=*head;p;p=p->next)
        {
            q=p->next;
            if(!q)
                break;
            if(p->num<q->num)
            {
                str=p->name;
                p->name=q->name;
                q->name=str;

                tmp=p->num;
                p->num=q->num;
                q->num=tmp;
            }
        }
    return (gpointer)*head;
}
static void show_Train_node(Train *p,GtkWidget **entry)
{
    gchar str[Max];
    gpointer pp=NULL;
    gint i;

    gtk_entry_set_text(GTK_ENTRY(entry[0]),p->Train_num);
    gtk_entry_set_text(GTK_ENTRY(entry[1]),p->Train_name);
    gtk_entry_set_text(GTK_ENTRY(entry[2]),p->Train_type_num);
    g_print("[show_train_node]train_type_num:%s\n",p->Train_type_num);
    gtk_entry_set_text(GTK_ENTRY(entry[3]),p->Train_type_name);
    gtk_entry_set_text(GTK_ENTRY(entry[4]),p->bureau_num);
    gtk_entry_set_text(GTK_ENTRY(entry[5]),p->bureau_name);
    gtk_entry_set_text(GTK_ENTRY(entry[6]),p->starting_station);
    gtk_entry_set_text(GTK_ENTRY(entry[7]),p->starting_time);
    gtk_entry_set_text(GTK_ENTRY(entry[8]),p->ending_station);
    gtk_entry_set_text(GTK_ENTRY(entry[9]),p->ending_time);

    for(i=10,pp=&p->hard_sleeper_down_whole_price;i<TNUM-2;i++)
    {
        sprintf(str,"%f",*((float *)pp));
        gtk_entry_set_text(GTK_ENTRY(entry[i]),str);
     //   gtk_widget_show(entry[i]);
        pp+=sizeof(float);
    }

    gtk_entry_set_text(GTK_ENTRY(entry[TNUM-2]),p->whole_running_time);

    i=TNUM-1;
    pp=&p->whole_running_distance;
    sprintf(str,"%d",*((int *)pp));
    gtk_entry_set_text(GTK_ENTRY(entry[i]),str);
    //gtk_widget_show(entry[i]);

}

static GtkWidget **show_station_node(station *p,GtkWidget **entry)
{
    gchar str[Max];
    gpointer pp=NULL;
    gint i;

    gtk_entry_set_text(GTK_ENTRY(entry[0]),p->station_num);
    gtk_entry_set_text(GTK_ENTRY(entry[1]),p->station_name);
    gtk_entry_set_text(GTK_ENTRY(entry[2]),p->bureau_num);
    gtk_entry_set_text(GTK_ENTRY(entry[3]),p->Train_num);
    gtk_entry_set_text(GTK_ENTRY(entry[4]),p->arrival_time);
    gtk_entry_set_text(GTK_ENTRY(entry[5]),p->starting_time);
    gtk_entry_set_text(GTK_ENTRY(entry[6]),p->running_time);

    i=7;
    pp=&p->distance;
    sprintf(str,"%d",*((int *)pp));
    gtk_entry_set_text(GTK_ENTRY(entry[i]),str);

    for(i=8,pp=&p->hard_sleeper_down_price;i<SNUM-1;i++)
    {
        sprintf(str,"%f",*((float *)pp));
        gtk_entry_set_text(GTK_ENTRY(entry[i]),str);
        gtk_widget_show(entry[i]);
        pp+=sizeof(float);
    }

    i=SNUM-1;
    pp=&p->remaining_ticket_train_num;
    sprintf(str,"%d",*((int *)pp));
    gtk_entry_set_text(GTK_ENTRY(entry[i]),str);

    return entry;
}

static GtkWidget **show_passing_Train_node(passing_Train *p,GtkWidget **entry)
{
    gchar str[Max];
    gpointer pp=NULL;
    gint i;

    gtk_entry_set_text(GTK_ENTRY(entry[0]),p->passing_Train_num);
    gtk_entry_set_text(GTK_ENTRY(entry[1]),p->passing_Train_name);
    gtk_entry_set_text(GTK_ENTRY(entry[2]),p->station_num);
    gtk_entry_set_text(GTK_ENTRY(entry[3]),p->bureau_num);
    gtk_entry_set_text(GTK_ENTRY(entry[4]),p->Train_type);
    gtk_entry_set_text(GTK_ENTRY(entry[5]),p->entering_time);
    gtk_entry_set_text(GTK_ENTRY(entry[6]),p->starting_time);

    for(i=7,pp=&p->hard_sleeper_down_price;i<PNUM-1;i++)
    {
        sprintf(str,"%f",*((float *)pp));
        gtk_entry_set_text(GTK_ENTRY(entry[i]),str);
        gtk_widget_show(entry[i]);
        pp+=sizeof(float);
    }

    i=PNUM-1,pp=&p->remaining_ticket_num;
    sprintf(str,"%d",*((int *)pp));
    gtk_entry_set_text(GTK_ENTRY(entry[i]),str);
    //gtk_widget_show(entry[i]);

    return entry;
}

static void inquire_info(GtkWidget *widget,gpointer data)
{
    GtkWidget *window,*scrolled_window;
    GtkWidget *entry[9];
    GtkWidget *button[9];
    GtkWidget *box_v,*box_h;

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"信息查询");
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);

    box_v=gtk_vbox_new(FALSE,0);

    box_h=make_label_entry_button("车次",entry,button,"查询");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[0],"clicked",G_CALLBACK(view_Train_num),entry);

    box_h=make_label_entry_button("经停车次最多的经停车站",entry+1,button+1,"查询");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[1],"clicked",G_CALLBACK(station_with_most_passing_train),entry[1]);

    box_h=make_label_entry_button("高速动车车次总数",entry+2,button+2,"统计");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[2],"clicked",G_CALLBACK(Gtrain_num),entry[2]);

    box_h=make_label_entry_button("动车车次总数",entry+3,button+3,"统计");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[3],"clicked",G_CALLBACK(Dtrain_num),entry[3]);

    box_h=make_label_entry_button("直达特快车次总数",entry+4,button+4,"统计");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[4],"clicked",G_CALLBACK(Ztrain_num),entry[4]);

    box_h=make_label_entry_button("余票车次数量为0的车站数",entry+5,button+5,"统计");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[5],"clicked",G_CALLBACK(num_of_station_without_tickets),entry[5]);

    box_h=make_label_entry_button("尚有余票的车次数",entry+6,button+6,"统计");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[6],"clicked",G_CALLBACK(passing_train_with_remaining_ticket),entry[6]);

    box_h=make_label_entry_button("指定时间发车数量为前三的车站名称",entry+7,button+7,"统计");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[7],"clicked",G_CALLBACK(first_three_station),entry[7]);

    box_h=make_label_entry_button("有指定数量经停车次的经停车站",entry+8,button+8,"统计");
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    g_signal_connect(button[8],"clicked",G_CALLBACK(station_of_specified_num),entry[8]);

    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),box_v);

    gtk_widget_show_all(window);
    gtk_main();
}

static void delete_train_dialog(GtkWidget *widget,gpointer data)
{
    gtk_widget_destroy(GTK_WIDGET(data));
}

static void delete_Train(GtkWidget *widget,p_entry *pe)
{
    GtkWidget *dialog;
    GtkWidget *button;
    GtkWidget *label;

    dialog=gtk_dialog_new();

    label=gtk_label_new("确认删除？");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),
            label,TRUE,TRUE,0);
    gtk_widget_show(label);

    pe->p=dialog;
    button=gtk_button_new_with_label("确认");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),
                    button,TRUE,TRUE,0);
    gtk_widget_show(button);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_Train_confirm),pe);

    button=gtk_button_new_with_label("取消");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),
            button,TRUE,TRUE,0);
    gtk_widget_show(button);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_train_dialog),dialog);

    gtk_widget_show(dialog);
    //gtk_main();
}

static void delete_Train_confirm(GtkWidget *widget,p_entry *pe)
{
    Train *pt,*pfree;
    pt=(Train *)malloc(sizeof(Train));

    for(pt=head_Train;pt&&pt->next&&strcmp(pt->next->Train_num,
                gtk_entry_get_text(GTK_ENTRY(*(pe->entry))));pt=pt->next);

    if(!strcmp(gtk_entry_get_text(GTK_ENTRY(*(pe->entry))),head_Train->Train_num))
    {
        pt=pfree=head_Train;
        pt=pt->next;
        head_Train=pt;
        free(pfree);
        gtk_widget_destroy(GTK_WIDGET(pe->p));
    }

    else
    {
        if(!pt)
        {
            printf("can not delete train\n");
            return;
        }

        else
        {
            pt->next=pt->next->next;
        }

        pfree=pt->next;
        free(pfree);
        gtk_widget_destroy(GTK_WIDGET(pe->p));
    }
    save("train_data.dat","station_data.dat","passing_train_data.dat");
}

static void delete_passing_Train_dialog(GtkWidget *widget,gpointer data)
{
    gtk_widget_destroy(GTK_WIDGET(data));
}

static void delete_passing_Train(GtkWidget *widget,p_entry *pe)
{
    GtkWidget *dialog;
    GtkWidget *button;
    GtkWidget *label;
    g_print("delete_passing_train:pe:%s\n",
            gtk_entry_get_text(GTK_ENTRY
                (*((GtkWidget **)pe->entry+3))));

    dialog=gtk_dialog_new();

    label=gtk_label_new("确认删除？");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),
            label,TRUE,TRUE,0);
    gtk_widget_show(label);

    pe->p=dialog;
    button=gtk_button_new_with_label("确认");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),
                    button,TRUE,TRUE,0);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_passing_Train_confirm),pe);
    gtk_widget_show(button);

    button=gtk_button_new_with_label("取消");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),
            button,TRUE,TRUE,0);
    gtk_widget_show(button);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_passing_Train_dialog),dialog);

    gtk_widget_show(dialog);
    gtk_main();

}

static void delete_passing_Train_confirm(GtkWidget *widget,
        p_entry *pe)
{
    Train *pt=NULL;
    station *ps=NULL;
    passing_Train *pp=NULL,*pfree=NULL;
    GtkWidget **entry;
    g_print("delete_passing_train:p_entry:%s\n",
            gtk_entry_get_text(GTK_ENTRY(*((GtkWidget **)pe->entry+3))));
    pp=(passing_Train *)malloc(sizeof(passing_Train));

    for(pt=head_Train;pt&&strcmp(pt->bureau_num,\
                gtk_entry_get_text(GTK_ENTRY(*((GtkWidget**)pe->entry+3))));pt=pt->next);

    if(!pt)
    {
        printf("can not delete train,no this train\n");
        return;
    }

    ps=pt->head_station;
    for(;ps&&strcmp(ps->bureau_num,\
                gtk_entry_get_text(GTK_ENTRY(*((GtkWidget**)pe->entry+3))));ps=ps->next);

    if(!ps)
    {
        printf("can not delete station,no this station\n");
        return;
    }

    else
    {
        pp=ps->head_passing_Train;
    }
    if(!pp)
    {
        printf("can not delete passing_train\n");
        return;
    }
    else
    {
        entry=(GtkWidget **)pe->entry;
        for(;pp&&pp->next&&strcmp(pp->next->bureau_num,\
                    gtk_entry_get_text(GTK_ENTRY(*(entry+3))));pp=pp->next)
        {
            g_print("delete_station_confirm:node content:%s\n",pp->passing_Train_num);
        }
        g_print("delete_passing_train_confirm:%s\n",
                gtk_entry_get_text(GTK_ENTRY(*(entry+3))));

        if(!strcmp(gtk_entry_get_text(GTK_ENTRY(*(entry+3))),
                    ps->head_passing_Train->bureau_num))
        {
            g_print("delete station confirm :first node\n");
            pp=pfree=pt->head_station->head_passing_Train;
            pt->head_station->head_passing_Train=pt->head_station->head_passing_Train->next;
            free(pfree);
            gtk_widget_destroy(GTK_WIDGET(pe->p));
        }
        else
        {
            if(!pp)
            {
                printf("can not delete passing train\n");
                return;
            }
            else
            {
                pfree=pp->next;
                pp->next=pp->next->next;
                free(pfree);
            }
            gtk_widget_destroy(GTK_WIDGET(pe->p));
        }
        save("train_data.dat","station_data.dat","passing_train_data.dat");

    }
}
static void delete_station_dialog(GtkWidget *widget,gpointer data)
{
    gtk_widget_destroy(GTK_WIDGET(data));
}

static void delete_station(GtkWidget *widget,p_entry *pe)
{
    GtkWidget *dialog;
    GtkWidget *button;
    GtkWidget *label;

    dialog=gtk_dialog_new();

    label=gtk_label_new("确认删除？");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),
            label,TRUE,TRUE,0);
    gtk_widget_show(label);

    pe->p=dialog;
    button=gtk_button_new_with_label("确认");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),
                    button,TRUE,TRUE,0);
    gtk_widget_show(button);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_station_confirm),pe);

    button=gtk_button_new_with_label("取消");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area),
            button,TRUE,TRUE,0);
    gtk_widget_show(button);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_station_dialog),dialog);

    gtk_widget_show(dialog);
    //gtk_main();
}
static void delete_station_confirm(GtkWidget *widget,p_entry *pe)
{
    Train *pt;
    station *ps,*pfree;
    GtkWidget **entry2;
    pt=(Train *)malloc(sizeof(Train));
    ps=(station *)malloc(sizeof(station));

    for(pt=head_Train;pt&&strcmp(pt->Train_num,gtk_entry_get_text(GTK_ENTRY(*(pe->entry+3))));pt=pt->next);

    if(!pt)
    {
        printf("can not delete train,no this train\n");
        return;
    }

    else
    {
        ps=pt->head_station;
    }
    if(!ps)
    {
        printf("can not delete station,no this station\n");
        return;
    }

    else
    {
        entry2=(GtkWidget **)pe->entry;
        for(;ps&&ps->next&&strcmp(ps->next->station_num,\
                    gtk_entry_get_text(GTK_ENTRY(*entry2)));ps=ps->next)
        {
            g_print("delete_station_confirm:node content:%s\n",ps->station_num);
        }

        if(!strcmp(gtk_entry_get_text(GTK_ENTRY(*entry2)),pt->head_station->station_num))
        {
            g_print("delete station confirm :first node\n");
            ps=pfree=pt->head_station;
            pt->head_station=pt->head_station->next;
            free(pfree);
            gtk_widget_destroy(GTK_WIDGET(pe->p));
        }
        else
        {
            if(!ps)
            {
                printf("can not delete station\n");
                return;
            }
            else
            {
                pfree=ps->next;
                ps->next=ps->next->next;
                free(pfree);
            }
            gtk_widget_destroy(GTK_WIDGET(pe->p));
        }
        save("train_data.dat","station_data.dat","passing_train_data.dat");

    }
}

static void station_with_most_passing_train(GtkWidget *widget,GtkWidget *entry)
{
    Train *pt;
    station *ps;
    passing_Train *pp;
    count *count_station,*p,*head=NULL;
    int i=0;

    for(pt=head_Train;pt;pt=pt->next)
        for(ps=pt->head_station;ps;ps=ps->next)
        {
            for(pp=ps->head_passing_Train;pp;pp=pp->next)
            {
                i++;
            }
            count_station=(count *)malloc(sizeof(count));
            count_station->name=ps->station_name;
            count_station->num=i;
            count_station->next=NULL;
            if(!head)
                head=count_station;
            else
            {
                for(p=head;p->next;p=p->next);
                p->next=count_station;
            }
        }
    sort(&head);
    gtk_entry_set_text(GTK_ENTRY(entry),head->name);
    printf("[sort]station name:%s\n",head->name);
}

static void Gtrain_num(GtkWidget *widget,GtkWidget *entry)
{
    Train *pt;
    int i=0;
    char *text=(char*)malloc(sizeof(int)+1);
    for(pt=head_Train;pt;pt=pt->next)
    {
        if(!strcmp(pt->Train_type_num,"G"))
            i++;
    }
    sprintf(text,"%d",i);
    gtk_entry_set_text(GTK_ENTRY(entry),text);

}

static void Dtrain_num(GtkWidget *widget,GtkWidget *entry)
{
    Train *pt;
    int i=0;
    char *text=(char*)malloc(sizeof(int)+1);
    for(pt=head_Train;pt;pt=pt->next)
    {
        if(!strcmp(pt->Train_type_num,"D"))
            i++;
    }
    sprintf(text,"%d",i);
    gtk_entry_set_text(GTK_ENTRY(entry),text);
}

static void Ztrain_num(GtkWidget *widget,GtkWidget *entry)
{
    Train *pt;
    int i=0;
    char *text=(char*)malloc(sizeof(int)+1);
    for(pt=head_Train;pt;pt=pt->next)
    {
        if(!strcmp(pt->Train_type_num,"Z"))
            i++;
    }
    sprintf(text,"%d",i);
    gtk_entry_set_text(GTK_ENTRY(entry),text);
}

static void num_of_station_without_tickets(GtkWidget *widget,GtkWidget *entry)
{
    int result=0;
    Train *pt;
    station *ps;
    gchar text[Max];
    for(pt=head_Train;pt;pt=pt->next)
        for(ps=pt->head_station;ps;ps=ps->next)
        {
            if(!ps->remaining_ticket_train_num)
                result+=1;
        }
    sprintf(text,"%d",result);
    gtk_entry_set_text(GTK_ENTRY(entry),text);
    g_print("%s\n",text);
}

static void passing_train_with_remaining_ticket(GtkWidget *widget,GtkWidget *entry)
{
    Train *pt;
    station *ps;
    passing_Train *pp;
    int i=0;
    char *text=(char *)malloc(sizeof(int)+1);

    for(pt=head_Train;pt;pt=pt->next)
        for(ps=pt->head_station;ps;ps=ps->next)
            for(pp=ps->head_passing_Train;pp;pp=pp->next)
            {
                if(pp->remaining_ticket_num!=0)
                    i++;
            }
    sprintf(text,"%d",i);
    gtk_entry_set_text(GTK_ENTRY(entry),text);

}

static void first_three_station(GtkWidget *widget,GtkWidget *entry)
{
    gchar *name[3]={NULL,NULL,NULL},text[Max];
    int amount[3]={0,0,0},num=0;
    Train *pt;
    station *ps;
    passing_Train *pp;
    strcpy(text,gtk_entry_get_text(GTK_ENTRY(entry)));
    g_print("[946]%s\n",text);
    if(!strcmp(text,""))
    {
        return;
    }
    for(pt=head_Train;pt;pt=pt->next)
        for(ps=pt->head_station;ps;ps=ps->next)
        {
            if(strcmp(ps->starting_time,text))
                continue;//指定时间
            for(pp=ps->head_passing_Train,num=0;pp;pp=pp->next)
               num++;
            if(!name[0]||num>amount[0])
            {
                name[0]=ps->station_name;
                amount[0]=num;
            }
            else if(!name[1]||num>amount[1])
            {
                name[1]=ps->station_name;
                amount[1]=num;
            }
            else if(!name[2]||num>amount[2])
            {
                name[2]=ps->station_num;
                amount[2]=num;
            }
        }
    if(!name[0])
        return;
    if(name[0])
    {
        sprintf(text,"%s",name[0]);
        if(name[1])
        {
            strcat(text,",");
            strcat(text,name[1]);
            if(name[2])
            {
                strcat(text,",");
                strcat(text,name[2]);
            }
        }
    }
    gtk_entry_set_text(GTK_ENTRY(entry),text);
}

static void station_of_specified_num(GtkWidget *widget,GtkWidget *entry)
{
    gchar text[Max];
    Train *pt;
    station *ps;
    passing_Train *pp;
    int num,key;
    strcpy(text,gtk_entry_get_text(GTK_ENTRY(entry)));
    if(strcmp(text,""))
        return;
    key=atoi(text);
    g_print("sepecified number is %d\n",key);
    strcpy(text,"");
    for(pt=head_Train;pt;pt=pt->next)
        for(ps=pt->head_station;ps;ps=ps->next)
        {
            for(num=0,pp=ps->head_passing_Train;pp;pp=pp->next)
                num++;
            if(num==key)
            {
                if(strcmp(text,""))
                    strcat(text,",");
                strcat(text,ps->station_name);
            }
        }
    if(strcmp(text,""))
        gtk_entry_set_text(GTK_ENTRY(entry),text);
    else
        gtk_entry_set_text(GTK_ENTRY(entry),"NO MATCHES");
}

static GtkWidget *make_label_entry_button(const char *label_name,GtkWidget **entry,GtkWidget **button,const char *button_name)
{
    GtkWidget *box_h,*box_v;
    GtkWidget *label;

    box_v=gtk_vbox_new(FALSE,0);
    box_h=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);

    label=gtk_label_new(label_name);
    gtk_label_set_max_width_chars(GTK_LABEL(label),25);
    gtk_box_pack_start(GTK_BOX(box_h),label,TRUE,FALSE,0);

    *entry=gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box_h),*entry,TRUE,FALSE,0);

//    box_h=make_label_entry(entry,

    *button=gtk_button_new_with_label(button_name);
    gtk_box_pack_start(GTK_BOX(box_h),*button,TRUE,FALSE,0);

    gtk_widget_show_all(box_v);
    return box_v;
}

static GtkWidget *make_station_box(GtkWidget *v_box,GtkWidget **entry)
{
    GtkWidget *h_box;
    gint i;
    for(i=0;i<SNUM;i++)
    {
        h_box=make_label_entry(station_member[i],entry+i);
        gtk_box_pack_start(GTK_BOX(v_box),h_box,TRUE,TRUE,0);
    }
    return NULL;
}

GtkWidget *make_Train_box(GtkWidget *vbox,GtkWidget **entry)
{
    GtkWidget *h_box;
    gint i;
    for(i=0;i<TNUM;i++)
    {
        h_box=make_label_entry(Train_member[i],entry+i);
        gtk_box_pack_start(GTK_BOX(vbox),h_box,FALSE,FALSE,0);
    }
    return NULL;
}

GtkWidget *make_passing_Train_box(GtkWidget *box_v,GtkWidget **entry)
{
    GtkWidget *box_h;
    gint i;
    for(i=0;i<PNUM;i++)
    {
        box_h=make_label_entry(passing_Train_member[i],entry+i);
        gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,TRUE,0);
    }
    return NULL;
}

station *get_station_node(GtkWidget **entry)
{
    const gchar *str;
    station *p;
    p=(station *)malloc(sizeof(station));
    str=gtk_entry_get_text(GTK_ENTRY(entry[0]));
    strcpy(p->station_num,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[1]));
    strcpy(p->station_name,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[2]));
    strcpy(p->bureau_num,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[3]));
    strcpy(p->Train_num,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[4]));
    strcpy(p->arrival_time,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[5]));
    strcpy(p->starting_time,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[6]));
    strcpy(p->running_time,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[7]));
    p->distance=atoi(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[8]));
    p->hard_sleeper_down_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[9]));
    p->hard_sleeper_middle_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[10]));
    p->hard_sleeper_up_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[11]));
    p->soft_seat_down_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[12]));
    p->soft_seat_up_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[13]));
    p->hard_seat_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[14]));
    p->remaining_ticket_train_num=atoi(str);

    printf("get station node: %s\n",p->station_num);

    return p;
}

Train *get_Train_node(GtkWidget **entry)
{
    const gchar *str;
    Train *p;
    p=(Train *)malloc(sizeof(Train));
    strcpy(p->Train_num,gtk_entry_get_text(GTK_ENTRY(entry[0])));

    str=gtk_entry_get_text(GTK_ENTRY(entry[1]));
    strcpy(p->Train_name,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[2]));
    strcpy(p->Train_type_num,str);
    g_print("[get_train_node],train_type_num:%s\n",p->Train_type_num);
    g_print("[get_train_node],str:%s\n",str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[3]));
    strcpy(p->Train_type_name,str);

    g_print("[get_train_node],train_type_num:%s\n",p->Train_type_num);
    str=gtk_entry_get_text(GTK_ENTRY(entry[4]));
    strcpy(p->bureau_num,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[5]));
    strcpy(p->bureau_name,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[6]));
    strcpy(p->starting_station,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[7]));
    strcpy(p->starting_time,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[8]));
    strcpy(p->ending_station,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[9]));
    strcpy(p->ending_time,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[10]));
    p->hard_sleeper_down_whole_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[11]));
    p->hard_sleeper_middle_whole_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[12]));
    p->hard_sleeper_up_whole_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[13]));
    p->soft_seat_down_whole_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[14]));
    p->soft_seat_up_whole_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[15]));
    p->hard_seat_whole_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[16]));
    strcpy(p->whole_running_time,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[17]));
    p->whole_running_distance=atoi(str);

    p->head_station=NULL;
    printf("get Train node: %s\n",p->Train_num);

    g_print("[get_train_node],train_type_num:%s\n",p->Train_type_num);
    return p;
}

Train *insert_Train_node(Train *current,Train *p)
{
    Train *pp=NULL;
    if(!current)
    {/*empty*/
        head_Train=p;
        p->next=NULL;
    }
    else
    {
        p->next=current->next;
        current->next=p;
    }
    current=p;
    pp=head_Train;
    while(pp!=NULL)
    {
        //g_print("node %s\n",pp->Train_num);

        printf("node %s\t",pp->Train_num);
        pp=pp->next;
    }
    printf("\n");

    return current;
}

station *insert_station_node(station *current,station *p)
{
    station *ps=NULL;
    Train *pt=head_Train;

    if(!pt)
    {
        printf("[insert_station_node]:train empty\n");
        return NULL;
    }
    while(pt&&strcmp(pt->Train_num,p->Train_num))
    {
        printf("insert_station_node:train num::%s\n",p->Train_num);
        pt=pt->next;
    }
    if(!pt)
    {
        return NULL;
    }

    if(! current)
    {
        p->next=pt->head_station;
        pt->head_station=p;
    }
    else
    {
        p->next=current->next;
        current->next=p;
    }
    current=p;
    ps=pt->head_station;
    while(ps!=NULL)
    {
        printf("[insert_station_node]node %s\n",ps->station_num);
        ps=ps->next;
    }
    return current;
}

passing_Train *insert_passing_Train_node(passing_Train *current,
        passing_Train *p)
{
    station *ps=NULL;
    Train *pt=head_Train;

    while(pt&&strcmp(pt->bureau_num,p->bureau_num))
    {
        printf("[insert_passing_train_node]train-bureau_num %s\n",p->bureau_num);
        pt=pt->next;
    }
    if(!pt)
    {
        g_print("[insert_passing_train_node]no train matches");
        return NULL;
    }

    ps=pt->head_station;

    while(ps&&strcmp(ps->bureau_num,p->bureau_num))
    {
        printf("[insert_passing_Train_node]station-bureau_num%s\n",p->bureau_num);
        ps=ps->next;
    }
    if(!ps)
    {
        g_print("insert_passing_train_node:no station matches\n");
        return NULL;
    }

    if(!current)
    {/*empty list still*/
        p->next=ps->head_passing_Train;
        ps->head_passing_Train=p;
        //current->next=p;
    }
    else
    {
        p->next=current->next;
        current->next=p;
    }
    current=p;
    return current;
}
passing_Train *get_passing_Train_node(GtkWidget **entry)
{
    const gchar *str;
    passing_Train *p;
    p=(passing_Train*)malloc(sizeof(passing_Train));

    str=gtk_entry_get_text(GTK_ENTRY(entry[0]));
    g_print("[get passing train node]str:%s\n",str);
    strcpy(p->passing_Train_num,gtk_entry_get_text(GTK_ENTRY(entry[0])));
    g_print("[get passing train] passing train num %s\n",
            gtk_entry_get_text(GTK_ENTRY(entry[0])));

    str=gtk_entry_get_text(GTK_ENTRY(entry[1]));
    strcpy(p->passing_Train_name,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[2]));
    strcpy(p->station_num,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[3]));
    strcpy(p->bureau_num,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[4]));
    strcpy(p->Train_type,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[5]));
    strcpy(p->entering_time,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[6]));
    strcpy(p->starting_time,str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[7]));
    p->hard_sleeper_down_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[8]));
    p->hard_sleeper_middle_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[9]));
    p->hard_sleeper_up_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[10]));
    p->soft_seat_down_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[11]));
    p->soft_seat_up_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[12]));
    p->hard_seat_whole_price=atof(str);

    str=gtk_entry_get_text(GTK_ENTRY(entry[13]));
    p->remaining_ticket_num=atoi(str);

    printf("[get passing train node]: %s\n",p->passing_Train_num);

    return p;
}
//the interface to add the infomation of the Train
static void add_Train(GtkWidget *widget,gpointer data)
{
    GtkWidget *window,*scrolled_window,*entry[TNUM],*vbox,
              *button,*hbox;

    tcombination *pc;
    pc=(tcombination *)malloc(sizeof(tcombination));

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);

    vbox=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),vbox);

    make_Train_box(vbox,entry);
    hbox=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
    button=gtk_button_new_with_label("确定");
    g_signal_connect(button,"clicked",G_CALLBACK(add_Train_confirm),entry);
    gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,FALSE,0);

    hbox=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("录入车站");
    gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);

    pc->entry=entry;
    g_signal_connect(button,"clicked",G_CALLBACK(add_station_info),pc);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);

    gtk_widget_show_all(window);
    gtk_main();
}
static void add_passing_Train_info(GtkWidget *widget,gpointer data)
{
    GtkWidget *window,*scrolled_window,*entry[PNUM],*box_v,
              *button,*box_h;
    scombination *ps;

    ps=(scombination *)malloc(sizeof(scombination));
    ps->p=NULL;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);

    box_v=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),box_v);

    make_passing_Train_box(box_v,entry);
    box_h=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    button=gtk_button_new_with_label("确定");
    ps->entry=entry;
    g_signal_connect(button,"clicked",G_CALLBACK(add_passing_Train_confirm),ps);
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE,0);

    gtk_widget_show_all(window);
    gtk_main();
}

static void add_passing_Train(GtkWidget *widget,scombination *ps)
{
    GtkWidget *window,*scrolled_window,*entry[PNUM],*box_v,
              *button,*box_h;
//    station *pstation;
    ps->p=get_station_node(ps->entry);
    ps->p->next=NULL;
    current_station=insert_station_node(current_station,ps->p);
    save("train_data.dat","station_data.dat","passing_train_data.dat");

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);

    box_v=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),box_v);

    make_passing_Train_box(box_v,entry);
    box_h=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);
    button=gtk_button_new_with_label("确定");
    ps->entry=entry;
    g_signal_connect(button,"clicked",G_CALLBACK(add_passing_Train_confirm),ps);
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE,0);

    gtk_widget_show_all(window);
    gtk_main();
}

static void add_station(GtkWidget *widget,gpointer data)
{
    GtkWidget *window,*scrolled_window,
              *entry[SNUM],*v_box,*h_box,*button;
    scombination *ps;
    tcombination *pc;

    pc=(tcombination *)malloc(sizeof(tcombination));
    pc->p=NULL;

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);

    v_box=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),v_box);

    make_station_box(v_box,entry);

    pc->entry=entry;

    h_box=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(v_box),h_box,FALSE,FALSE,0);

    button=gtk_button_new_with_label("确定");
    g_signal_connect(button,"clicked",G_CALLBACK(add_station_confirm),pc);
    gtk_box_pack_start(GTK_BOX(h_box),button,TRUE,FALSE,0);

    h_box=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("录入经停车次");
    gtk_box_pack_start(GTK_BOX(h_box),button,TRUE,TRUE,0);

    ps=(scombination *)malloc(sizeof(scombination));
    ps->entry=entry;
    ps->p=NULL;
    g_signal_connect(button,"clicked",G_CALLBACK(add_passing_Train),ps);
    gtk_box_pack_start(GTK_BOX(v_box),h_box,FALSE,FALSE,0);

    gtk_widget_show(h_box);

    gtk_widget_show_all(window);
    gtk_main();
}


static void add_station_info(GtkWidget *widget,tcombination *pc)
{
    GtkWidget *window,*scrolled_window,
              *entry[SNUM],*v_box,*h_box,*button;
    scombination *ps;

    pc->p=get_Train_node(pc->entry);
    current_Train=insert_Train_node(current_Train,pc->p);
    save("train_data.dat","station_data.dat","passing_train_data.dat");

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);

    v_box=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),v_box);

    make_station_box(v_box,entry);

    pc->entry=entry;

    h_box=gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(v_box),h_box,FALSE,FALSE,0);

    button=gtk_button_new_with_label("确定");
    g_signal_connect(button,"clicked",G_CALLBACK(add_station_confirm),pc);
    gtk_box_pack_start(GTK_BOX(h_box),button,TRUE,FALSE,0);

    h_box=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("录入经停车次");
    gtk_box_pack_start(GTK_BOX(h_box),button,TRUE,TRUE,0);

    ps=(scombination *)malloc(sizeof(scombination));
    ps->entry=entry;
    ps->p=NULL;
    g_signal_connect(button,"clicked",G_CALLBACK(add_passing_Train),ps);
    gtk_box_pack_start(GTK_BOX(v_box),h_box,FALSE,FALSE,0);

    gtk_widget_show(h_box);

    gtk_widget_show_all(window);
    gtk_main();
}


static void add_Train_confirm(GtkWidget *widget,GtkWidget **entry)
{
    Train *p;
    p=get_Train_node(entry);
    current_Train=insert_Train_node(current_Train,p);
    save("train_data.dat","station_data.dat","passing_train_data.dat");

}

static void add_station_confirm(GtkWidget *widget,tcombination *pc)
{
    station *ps;
    ps=get_station_node(pc->entry);
    ps->head_passing_Train=NULL;
    current_station=insert_station_node(current_station,ps);
    //pc->p->head_station=head_station;
    save("train_data.dat","station_data.dat","passing_train_data.dat");

}

static void add_passing_Train_confirm(GtkWidget *widget,scombination *ps)
{
    passing_Train *p;
    p=get_passing_Train_node(ps->entry);
    current_passing_Train=insert_passing_Train_node(current_passing_Train,p);
    save("train_data.dat","station_data.dat","passing_train_data.dat");
}

static GtkWidget *make_label_entry(const gchar *label_name,GtkWidget **entry)
{
    GtkWidget *h_box,*label;
    h_box=gtk_hbox_new(FALSE,0);
    label=gtk_label_new(label_name);
    gtk_label_set_width_chars(GTK_LABEL(label),12);
    gtk_box_pack_start(GTK_BOX(h_box),label,TRUE,TRUE,0);
    *entry=gtk_entry_new();
    //gtk_entry_set_text(GTK_ENTRY(*entry),"hello");
    gtk_box_pack_start(GTK_BOX(h_box),*entry,TRUE,TRUE,0);
    return h_box;
}

GtkWidget *show_Train_box(GtkWidget *box_v,GtkWidget **entry)
{
    GtkWidget *box_h;
    box_h=make_label_entry("车次编号",entry+0);
    box_h=make_label_entry("车次名称",entry+1);
    box_h=make_label_entry("车次类型编码",entry+2);
    box_h=make_label_entry("车次类型名称",entry+3);
    box_h=make_label_entry("所属路局编号",entry+4);
    box_h=make_label_entry("所属路局名称",entry+5);
    box_h=make_label_entry("始发站",entry+6);
    box_h=make_label_entry("始发时间",entry+7);
    box_h=make_label_entry("终到站",entry+8);
    box_h=make_label_entry("终到时间",entry+9);
    box_h=make_label_entry("全程运行时间",entry+10);
    box_h=make_label_entry("全程运行里程",entry+11);
    box_h=make_label_entry("硬卧下铺全程票价",entry+12);
    box_h=make_label_entry("硬卧中铺全程票价",entry+13);
    box_h=make_label_entry("硬卧上铺全程票价",entry+14);
    box_h=make_label_entry("软卧下铺全程票价",entry+15);
    box_h=make_label_entry("软卧上铺全程票价",entry+16);
    box_h=make_label_entry("硬座全程票价",entry+17);
    return box_h;
}


static gboolean delete_event(GtkWidget *widget,GdkEvent **event,gpointer data)
{
    gtk_main_quit();
    return FALSE;
}

static void view_Train_num(GtkWidget *widget,GtkWidget **import_entry)
{
    GtkWidget *window;
    GtkWidget *entry2,*entry[TNUM];
    GtkWidget *scrolled_window;
    GtkWidget *button,*button2;
    GtkWidget *box_v,*box_h;
    const gchar *str2;
    Train *p;
    dentry *double_entry;
    p_entry *pe;
    int i;

    pe=(p_entry *)malloc(sizeof(p_entry));

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"指定车次详情");
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);
    box_v=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),box_v);

    make_Train_box(box_v,entry);

    for(i=0;i<TNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
    }

    p=head_Train;
    str2=gtk_entry_get_text(GTK_ENTRY(*import_entry));
    g_print("[view_train_num]input content:%s p->train_num:%s\n",str2,p->Train_num);
    while(p&&strcmp(p->Train_num,str2))
    {

        printf("train num:%s\n",p->Train_num);
        p=p->next;
    }
    if(!p)
    {
        printf("wrong input!");
        return;
    }
    g_print("[view_train_num]p->train_num:%s",p->Train_num);

    show_Train_node(p,entry);

    box_h=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("插入");
    g_signal_connect(button,"clicked",G_CALLBACK(add_Train),NULL);
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);

    pe->entry=(void **)entry;
    pe->p=p;

    button=gtk_button_new_with_label("删除");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_Train),pe);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    box_h=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("修改");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    g_signal_connect(button,"clicked",G_CALLBACK(modify_train),pe);

    button=gtk_button_new_with_label("修改完成");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE,0);
    g_signal_connect(button,"clicked",G_CALLBACK(modify_train_confirm),pe);

    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    box_h=make_label_entry_button("指定经停站信息",&entry2,&button2,"查询");
    /*unable to use **entry2,with entry2 passed as the
     * argument*/

    double_entry=(dentry *)malloc(sizeof(dentry));
    double_entry->import_entry=&entry2;
    double_entry->entry=entry;
    str2=gtk_entry_get_text(GTK_ENTRY(&entry2));
    g_signal_connect(button2,"clicked",G_CALLBACK(view_Train_station),double_entry);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,FALSE,0);

    gtk_widget_show_all(window);
    gtk_main();
}

static void view_Train_station(GtkWidget *widget,dentry *double_entry)
{
    GtkWidget *window,*scrolled_window;
    GtkWidget *entry[SNUM],*entry2;
    GtkWidget *button;
    GtkWidget *box_v,*box_h;
    Train *pt;
    station *ps;
    const gchar *str2;
    dentry *double_entry2;
    p_entry *pe;
    int i;
    tcombination *pc;

    pe=(p_entry *)malloc(sizeof(p_entry));
    pc=(tcombination *)malloc(sizeof(tcombination));

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"指定车次经停站详情");
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);
    g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);
    box_v=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),box_v);

    box_h=make_label_entry("车站编号",entry);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("车站名称",entry+1);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("所属路局编号",entry+2);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("车次编号",entry+3);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("进站时间",entry+4);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("开车时间",entry+5);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("运行时间",entry+6);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("运行里程",entry+7);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("硬卧下铺票价",entry+8);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("硬卧中铺票价",entry+9);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("硬卧上铺票价",entry+10);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("软铺下铺票价",entry+11);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("软卧上铺票价",entry+12);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("硬座全程票价",entry+13);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    box_h=make_label_entry("余票数量",entry+14);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    for(i=0;i<SNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
    }

    pt=head_Train;
    str2=gtk_entry_get_text(GTK_ENTRY(*(double_entry->import_entry)));
    printf("view_train_station:import_entry:%s\n",str2);
    while(pt&&strcmp(pt->Train_num,gtk_entry_get_text(GTK_ENTRY(*(double_entry->entry)))))
    {
        printf("view_train_station:train_num::%s\n",pt->Train_num);
        pt=pt->next;
    }
    if(!pt)
    {
        printf("no train\n");
        return;
    }
    g_print("[view_train_station]:train num:%s\n",pt->Train_num);

    ps=pt->head_station;
    while(ps&&strcmp(ps->station_num,str2))
    {
        g_print("[view_train_station]:train:%s station:%s\n",\
                ps->Train_num,ps->station_num);
        ps=ps->next;
    }

    if(!ps)
    {
        printf("[view_train_station]no station_num!~\n");
        return;
    }
    else
    {
        show_station_node(ps,entry);
    }

    pc->p=NULL;
    pc->entry=double_entry->entry;
    box_h=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("插入");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    g_signal_connect(button,"clicked",G_CALLBACK(add_station),NULL);

    pe->entry=(void **)entry;
    pe->p=ps;

    button=gtk_button_new_with_label("删除");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_station),pe);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    box_h=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("修改");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    g_signal_connect(button,"clicked",G_CALLBACK(modify_station),pe);

    button=gtk_button_new_with_label("修改完成");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE,0);
    g_signal_connect(button,"clicked",G_CALLBACK(modify_station_confirm),pe);

    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    box_h=gtk_hbox_new(FALSE,0);
    box_h=make_label_entry("指定经停车次信息",&entry2);
    button=gtk_button_new_with_label("查询");

    double_entry2=(dentry *)malloc(sizeof(dentry));
    double_entry2->entry=entry;
    double_entry2->import_entry=&entry2;
    g_signal_connect(button,"clicked",G_CALLBACK(view_pass_Train),double_entry2);
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);
    gtk_widget_show_all(window);
    gtk_main();
}

static void view_pass_Train(GtkWidget *widget,dentry *double_entry)
{
    GtkWidget *window,*scrolled_window,*entry[PNUM];
    GtkWidget *button;
    GtkWidget *box_v,*box_h;
    passing_Train *pp;
    station *ps;
    const gchar *str,*station_num_str,*train_num_str;
    Train *pt;
    p_entry *pe;
    scombination *ppss;
    int i;

    pe=(p_entry *)malloc(sizeof(p_entry));
    pe->p=NULL;

    ppss=(scombination *)malloc(sizeof(scombination));

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"指定车次指定经停站经停车次信息");
    gtk_window_set_default_size(GTK_WINDOW(window),600,300);
    g_signal_connect(window,"delete-event",G_CALLBACK(delete_event),NULL);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window),scrolled_window);

    box_v=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),box_v);


    box_h=make_label_entry("经停车次编号",entry+0);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("经停车次名称",entry+1);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("车站编号",entry+2);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("路局编号",entry+3);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("车次类型",entry+4);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("进站时间",entry+5);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("开车时间",entry+6);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("硬卧下铺全程票价",entry+7);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("硬卧中铺全程票价",entry+8);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("硬卧上铺全程票价",entry+9);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("软卧下铺全程票价",entry+10);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("软卧上铺全程票价",entry+11);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("硬座全程票价",entry+12);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);
    box_h=make_label_entry("余票数量",entry+13);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,TRUE,FALSE ,0);

    for(i=0;i<PNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
    }

    pt=head_Train;
    str=gtk_entry_get_text(GTK_ENTRY(*(double_entry->import_entry)));
    printf("view_pass_train:import_entry:%s\n",str);

    station_num_str=gtk_entry_get_text(GTK_ENTRY(*(double_entry->entry)));
    printf("station_num_str:%s\n",station_num_str);
    printf("pt->train_num:%s\n",pt->Train_num);

    train_num_str=gtk_entry_get_text(GTK_ENTRY(*(double_entry->entry+3)));
    printf("train_num_str:%s\n",train_num_str);

    while(pt&&strcmp(pt->Train_num,train_num_str))
    {
        printf("view_pass_train:train_num:%s\n",pt->Train_num);
        pt=pt->next;
    }
    if(!pt)
    {
        printf("no train\n");
        return;
    }
    g_print("view_pass_train:train num:%s\n",pt->Train_num);

    ps=pt->head_station;
    while(ps&&strcmp(ps->station_num,station_num_str))
    {
        g_print("view_pass_train:train:%s\n   station:%s\n",\
                ps->Train_num,ps->station_num);
        ps=ps->next;
    }
    if(!ps)
    {
        printf("view_pass_train: no station_num!\n");
        return;
    }
    g_print("view_pass_train:%s\n   station:%s\n",\
            ps->Train_num,ps->station_num);

    pp=ps->head_passing_Train;
    while(pp&&strcmp(pp->passing_Train_num,str))
    {
        g_print("view_pass_train:passing_train_num:%s\n",\
                pp->passing_Train_num);
        pp=pp->next;
    }

    if(!pp)
    {
        printf("view_pass_train no passing_train\n");
        return;
    }
    else
    {
        show_passing_Train_node(pp,entry);
        g_print("view_pass train :%s\n",
                gtk_entry_get_text(GTK_ENTRY(entry[3])));
    }


    ppss->p=NULL;
    ppss->entry=double_entry->entry;
    box_h=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("插入");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    g_signal_connect(button,"clicked",G_CALLBACK(add_passing_Train_info),NULL);

    pe->entry=(void **)entry;
    pe->p=pp;

    button=gtk_button_new_with_label("删除");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    g_signal_connect(button,"clicked",G_CALLBACK(delete_passing_Train),pe);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    box_h=gtk_hbox_new(FALSE,0);
    button=gtk_button_new_with_label("修改");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE ,0);
    g_signal_connect(button,"clicked",G_CALLBACK(modify_passing_train),pe);

    button=gtk_button_new_with_label("修改完成");
    gtk_box_pack_start(GTK_BOX(box_h),button,TRUE,FALSE,0);
    g_signal_connect(button,"clicked",G_CALLBACK(modify_passing_train_confirm),pe);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    gtk_widget_show_all(window);
    g_print("view_pass train:pe->entry %s %s\n",
            gtk_entry_get_text(GTK_ENTRY(*((GtkWidget **)pe->entry+3))),
            gtk_entry_get_text(GTK_ENTRY(*(entry+3))));
    gtk_main();
}

static void modify_train(GtkWidget *widget,p_entry *pe)
{
    int i;
    for(i=0;i<TNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(*((GtkWidget **)(pe->entry)+i)),TRUE);
    }
}
static void modify_train_confirm(GtkWidget *widget,p_entry *pe)
{
    Train *pt;
    station *ps;
    passing_Train *pp;
    int i;

    pt=get_Train_node((GtkWidget **)(pe->entry));
    pt->next=((Train *)pe->p)->next;
    pt->head_station=((Train *)pe->p)->head_station;
    *((Train *)pe->p)=*pt;

    for(ps=pt->head_station;ps;ps=ps->next)
    {
        for(pp=ps->head_passing_Train;pp;pp=pp->next)
        {
            strcpy(pp->bureau_num,pt->bureau_num);
        }
        strcpy(ps->bureau_num,pt->bureau_num);
        strcpy(ps->Train_num,pt->Train_num);
    }
    for(i=0;i<TNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(*((GtkWidget **)(pe->entry)+i)),FALSE);
    }

    save("train_data.dat","station_data.dat","passing_train_data.dat");
}

static void modify_station(GtkWidget *widget,p_entry *pe)
{
    int i;
    for(i=0;i<SNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(*((GtkWidget **)(pe->entry)+i)),TRUE);
    }
}

static void modify_station_confirm(GtkWidget *widget,p_entry *pe)
{
    station *ps;
    int i;

    ps=get_station_node((GtkWidget **)(pe->entry));
    ps->next=((station *)pe->p)->next;
    ps->head_passing_Train=((station *)pe->p)->head_passing_Train;
    *((station *)pe->p)=*ps;

    for(i=0;i<SNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(*((GtkWidget **)(pe->entry)+i)),FALSE);
    }
    save("train_data.dat","station_data.dat","passing_train_data.dat");
}

static void modify_passing_train(GtkWidget *widget,p_entry *pe)
{
    int i;
    for(i=0;i<PNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(*((GtkWidget **)(pe->entry)+i)),TRUE);
    }
}

static void modify_passing_train_confirm(GtkWidget *widget,p_entry *pe)
{
    passing_Train *pp;
    int i;

    pp=get_passing_Train_node((GtkWidget **)(pe->entry));
    pp->next=((passing_Train *)pe->p)->next;
    *((passing_Train *)pe->p)=*pp;

    for(i=0;i<PNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(*((GtkWidget **)(pe->entry)+i)),FALSE);
    }
    save("train_data.dat","station_data.dat","passing_train_data.dat");
}
int main(int argc,char **argv)
{
    GtkWidget *window_main,*scrolled_window;
    GtkWidget *button[4],*label;
    GtkWidget *box_v,*box_h;
    int re;
    current_Train=head_Train=NULL;
    current_station=head_station=NULL;
    current_passing_Train=head_passing_Train=NULL;


    gtk_init(&argc,&argv);

    window_main=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window_main),"列车信息管理系统");
    g_signal_connect(window_main,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_default_size(GTK_WINDOW(window_main),270,300);

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
            GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
    gtk_container_add(GTK_CONTAINER(window_main),scrolled_window);

    box_v=gtk_vbox_new(FALSE,0);

    box_h=gtk_hbox_new(FALSE,0);
    label=gtk_label_new("\n\n\nWelcome to the Train system\n");
    gtk_box_pack_start(GTK_BOX(box_h),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    re=create_list(&head_Train);
    box_h=gtk_hbox_new(FALSE,0);
    button[0]=gtk_button_new_with_label("信息查询");
    gtk_box_pack_start(GTK_BOX(box_h),button[0],TRUE,TRUE,0);
    g_signal_connect(button[0],"clicked",G_CALLBACK(inquire_info),NULL);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    box_h=gtk_hbox_new(FALSE,0);
    button[1]=gtk_button_new_with_label("录入数据");
    gtk_box_pack_start(GTK_BOX(box_h),button[1],TRUE,TRUE,0);
    g_signal_connect(button[1],"clicked",G_CALLBACK(add_Train),NULL);
    gtk_box_pack_start(GTK_BOX(box_v),box_h,FALSE,TRUE,0);

    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),box_v);

    gtk_widget_show_all(window_main);

    printf("%d\n",re);
    gtk_main();

    return 0;
}
