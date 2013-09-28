/*************************************************************************
    > File Name: callback.c
    > Created Time: Tue 02 Oct 2012 03:47:38 PM CST
 ************************************************************************/
#include "define.h"
/*callbacks start*/

//pointers to function
void (*function[])(GtkWidget *widget,gpointer data)=
{
    query_province,query_city,
    forest_of_max_area,broadleaf_timber_of_max_area,
    aciculiailvae_forest_of_max_fund,forest_of_max_revenue,
    get_total_forest_area,get_total_desert_area,
    get_then_forestation_area,get_then_forestation_fund,
    get_then_b_forest_area,get_then_a_forest_area,
    get_then_e_forestation_area,get_species_number,
    first_three_cities_of_max_timber
};


gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    g_print("delete event occurred\n");

    return FALSE;
}

void record_data(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    insert_province(current_province);
}

void main_menu_save(GtkWidget *widget,gpointer data)
{
    save("province.dat","city.dat","tree.dat");
}

void insert_province_next(GtkWidget *widget,GtkWidget **entry)
{
    Province *p;
    const char *entry_text=gtk_entry_get_text(GTK_ENTRY(entry[0]));
    if(*entry_text)
    {//base information of the province is supplied
        p=get_province_node(entry);
        current_province=insert_province_node(current_province,p);
        g_print("The newly added province is %s\n",current_province->num);
    }
    else
        g_print("Lacking necessary province information\n");
    clear_entry(entry,12);
    for(p=head_province;p;p=p->next)
    {
        printf("The number of the province is %s \n",p->num);
    }
    g_print("\n");
}

void insert_province_finish(GtkWidget *widget,GtkWidget **entry)
{//appending the list,finished
    Province *p;
    const char *num;
    num=gtk_entry_get_text(GTK_ENTRY(entry[0]));
    if(*num)
    {
        p=get_province_node(entry);
        current_province=insert_province_node(current_province,p);
        g_print("The newly added province's number is %s\n",current_province->num);
    }
    else
        g_print("Lacking necessary province information\n");
    //clear_entry(entry,PNUM);
    gtk_widget_destroy(window_insert_province);
    for(p=head_province;p;p=p->next)
    {
        printf("The number of the province is %s\n",p->num);
    }
    save("province.dat","city.dat","tree.dat");
}

void insert_province_make_head(GtkWidget *widget,GtkWidget **entry)
{
    Province *p=get_province_node(entry);
    if(head_province)
    {
        p->next=head_province;
        head_province=p;
    }
    else
    {
        head_province=p;
        p->next=NULL;
    }
    clear_entry(entry,PNUM);
}

void insert_province_city(GtkWidget *widget,gpointer data)
{
    if(!current_province)
    {
        g_print("No province added\n");
        return;
    }
    current_city=head_city=current_province->head_city;

    g_print("Current province number is :%s\n",current_province->num);
    //gtk_widget_set_sensitive(window_insert_province,FALSE);
    insert_city(&current_province);
}

void insert_city_next(GtkWidget *widget,GtkWidget **entry)
{
    City *p;
    char text[3][16];
    strcpy(text[0],gtk_entry_get_text(GTK_ENTRY(entry[0])));
    strcpy(text[1],gtk_entry_get_text(GTK_ENTRY(entry[1])));
    strcpy(text[2],gtk_entry_get_text(GTK_ENTRY(entry[2])));
    if(text[0][0]&&text[0][0]&&text[2][0])
    {
        p=get_city_node(entry);
        current_city=insert_city_node(current_city,p);
    }
    else
    {
        g_print("[insert_city_next]Lacking necessary city information]\n");
        return;
    }
    clear_entry(entry,CNUM);
    for(p=head_city;p;p=p->next)
    {
        g_print("The city's number is %s\n",p->num);
    }
    g_print("\n");
    //print("The newly added p->num number is %s\n",p->num);
}

void insert_city_finish(GtkWidget *widget,GtkWidget **entry)
{
    char text[3][16];
    City *p;
    strcpy(text[0],gtk_entry_get_text(GTK_ENTRY(entry[0])));
    strcpy(text[1],gtk_entry_get_text(GTK_ENTRY(entry[1])));
    strcpy(text[2],gtk_entry_get_text(GTK_ENTRY(entry[2])));
    if(text[0][0]&&text[1][0]&&text[2][0])
    {
        p=get_city_node(entry);
        current_city=insert_city_node(current_city,p);
    }
    else
    {
        g_print("Lacking necessary city informaiton\n");
        return;
    } for(p=head_city;p;p=p->next)
    {
        g_print("The city's number is %s\n",p->num);
    }
    gtk_widget_destroy(window_insert_city);
    //gtk_widget_set_sensitive(window_insert_province,TRUE);
}

void insert_city_tree()
{
    City *p;
    if(!head_city)
    {
        g_print("No city added\n");
        return ;
    }
    for(p=head_city;p;p=p->next)
    {
        g_print("The city's number is %s\n",p->num);
    }
    insert_tree();
}

void insert_tree_next(GtkWidget *widget,GtkWidget **entry)
{
    char text[3][16]={"","",""};
    Tree *p;
    strcpy(text[0],gtk_entry_get_text(GTK_ENTRY(entry[0])));
    strcpy(text[1],gtk_entry_get_text(GTK_ENTRY(entry[1])));
    strcpy(text[2],gtk_entry_get_text(GTK_ENTRY(entry[2])));
    if(text[0][0]&&*text[1]&&text[2][0])
    {
        g_print("Basic information:%s %s %s\n",text[0],text[1],text[2]);
        p=get_tree_node(entry);
        current_tree=insert_tree_node(current_tree,p);
    }
    else
        g_print("Lacking necessary infomation\n");

    clear_entry(entry,TNUM);
    for(p=head_tree;p;p=p->next)
        g_print("The tree's number is %s\n",p->num);
}

void insert_tree_finish(GtkWidget *widget,GtkWidget **entry) {
    char text[3][16];
    Tree *p;
    strcpy(text[0],gtk_entry_get_text(GTK_ENTRY(entry[0])));
    strcpy(text[1],gtk_entry_get_text(GTK_ENTRY(entry[1])));
    strcpy(text[2],gtk_entry_get_text(GTK_ENTRY(entry[2])));
    if(*text[0]&&*text[1]&&*text[2])
    {
        p=get_tree_node(entry);
        current_tree=insert_tree_node(current_tree,p);
    }
    else
        g_print("Lacking necessary infomation\n");
    for(p=head_tree;p;p=p->next)
    {
        g_print("The number of the tree is %s\n",p->num);
    }
    gtk_widget_destroy(window_insert_tree);
}

void view_province_modify(GtkWidget *widget,GtkWidget **entry)
{
    gint i;
    for(i=0;i<PNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(*(entry+i)),TRUE);
    }
}

void view_province_confirm(GtkWidget *widget,GtkWidget **entry)
{
    Province *pp=get_province_node(entry);
    City *pc;
    Tree *pt;
    //province_modify=FALSE;
    pp->next=current_province->next;
    pp->head_city=current_province->head_city;/*reverse the pointer*/
    gint i;
    *current_province=*pp;
    for(pc=current_province->head_city;pc;pc=pc->next)
    {//update the information in city,tree sub lists
        for(pt=pc->head_tree;pt;pt=pt->next)
            strcpy(pt->province_num,current_province->num);
        strcpy(pc->province_num,current_province->num);
    }
    for(i=0;i<PNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
    }
    g_print("current province's number is %s\n",current_province->num);
}

void view_province_insert(GtkWidget *widget,gpointer p)
{
   insert_province(current_province);
   g_print("called insert_province \n");
}

void view_province_delete(GtkWidget *widget,Province *p)
{
    Province *prior=locate_prior_node(head_province,current_province,offsetof(Province,next)),
             *next=current_province->next;
    City *pc=(City*)malloc(sizeof(City));
    Tree *pt=(Tree*)malloc(sizeof(Tree));
    //size_t offset=(void*)(&pt->next)-(void*)pt;
    size_t offset=offsetof(Tree,next);
    g_print("offset is %ld\n",offset);
    if(!current_province)/*in case it's an empty list*/
        return;
    if(prior)
    {
        prior->next=current_province->next;
    }
    else
    {/*delete the head node*/
        head_province=current_province->next;
    }
    for(pc=current_province->head_city;pc;pc=pc->next)
    {
        delete_list((void**)&pc->head_tree,offset);
    }
    offset=offsetof(City,next);
    delete_list((void**)&current_province->head_city,offset);
    free(current_province);
    free(pc);
    free(pt);
    current_province=prior?prior:next;//reasign the global varible.
    if(!head_province)
        gtk_widget_destroy(window_view_province);
    else
        view_province(head_province);
}


void view_province_prior(GtkWidget *widget,GtkWidget **entry)
{
    if(!current_province)
        return;
    if(current_province!=head_province)
    {
        current_province=locate_prior_node(head_province,
                current_province,offsetof(Province,next));
        show_province_node(current_province,entry);
        current_city=head_city=NULL;/*considerint influence on the list of lower
                            level,reassign it to NULL*/
    }
    else
    {
        g_print("already the first node\n");
    }
}

void view_province_next(GtkWidget *widget,GtkWidget **entry)
{
    if(current_province==NULL)
        return;
    if(current_province->next)
    {
        current_province=current_province->next;
        //g_print("The next province's num is %s\n",current_province->num);
        show_province_node(current_province,entry);
        current_city=head_city=NULL;
    }
    else
    {
        g_print("already the last province\n");
    }
}

void view_province_city(GtkWidget *widget,Province *p)
{
    if(current_province->head_city)
    {
        g_print("current province is %s\n",current_province->num);
        head_city=current_city=current_province->head_city;/*head_city*/
        g_print("The first city:%s\n",current_city->num);
        view_city(current_city);
        //gtk_widget_set_sensitive(window_view_province,FALSE);
    }
    else
    {
        insert_city(&current_province);
        g_print("There is no city added to this province %s\n",p->num);
    }
}

void view_city_tree(GtkWidget *widget,City *p)
{
    if(current_city->head_tree)
    {
        current_tree=head_tree=current_city->head_tree;
        view_tree(head_tree);
    }
    else
    {
        insert_tree(NULL);
        g_print("No tree is added to this city\n");
    }
}

void view_city_modify(GtkWidget *widget,GtkWidget **entry)
{
    gint i;
    for(i=0;i<CNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),TRUE);
    }
}

void view_city_confirm(GtkWidget *widget,GtkWidget **entry)
{
    gint i;
    City *p=get_city_node(entry);
    Tree *pt=NULL;
    p->next=current_city->next;/*reserve the  pointer*/
    p->head_tree=current_city->head_tree;
    *current_city=*p;
    for(pt=current_city->head_tree;pt;pt=pt->next)
    {
        strcpy(pt->city_num,current_city->num);
    }
    g_print("current city updated:%s\n",current_city->num);
    for(i=0;i<CNUM;i++)
    {
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
    }
}


void view_city_insert(GtkWidget *widget,gpointer p)
{
    //gtk_widget_set_sensitive(window_view_city,FALSE);
    insert_city(&current_province);
}


void view_city_delete(GtkWidget *widget,gpointer data)
{
    City *prior=locate_prior_node(head_city,current_city,offsetof(City,next));
    size_t offset=offsetof(Tree,next);
    g_print("offset is :%ld\n",offset);
    if(!current_city)
        return;
    if(prior)
    {
        prior->next=current_city->next;
    }
    else
    {
        g_print("[384]delete the head node of city\n");
        head_city=current_city->next;
        current_province->head_city=head_city;
    }
    delete_list((void**)&current_city->head_tree,offset);
    free(current_city);
    if((current_city=head_city))
        show_city_node(current_city,(GtkWidget**)data);
    else
        gtk_widget_destroy(window_view_city);
}


void view_city_prior(GtkWidget *widget,GtkWidget **entry)
{
    if(!current_city)
        return;/*in case nodes are deleted*/
    City *p=locate_prior_node(head_city,current_city,offsetof(City,next));
    if(p)
    {
        current_city=p;
        show_city_node(current_city,entry);
        current_tree=head_tree=NULL;
    }
}

void view_city_next(GtkWidget *widget,GtkWidget **entry)
{
    if(!current_city)
        return;
    if(current_city->next)
    {
        current_city=current_city->next;
        show_city_node(current_city,entry);
        current_tree=head_tree=NULL;
    }
}



void view_tree_modify(GtkWidget *widget,GtkWidget **entry)
{
    gint i;
    for(i=0;i<TNUM;i++)
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),TRUE);
}

void view_tree_confirm(GtkWidget *widget,GtkWidget **entry)
{
    gint i;
    Tree *p=get_tree_node(entry);
    p->next=current_tree->next;
    *current_tree=*p;
    for(i=0;i<TNUM;i++)
        gtk_entry_set_editable(GTK_ENTRY(entry[i]),FALSE);
}

void view_tree_insert(GtkWidget *widget,gpointer p)
{
    insert_tree(current_tree);
}

void view_tree_delete(GtkWidget *widget,gpointer data)
{
    Tree *prior;
    if(!current_tree)
        return;
    prior=locate_prior_node(head_tree,current_tree,offsetof(Tree,next));
    if(prior)
        prior->next=current_tree->next;
    else
    {/*first node*/
        current_city->head_tree=head_tree=current_tree->next;
    }
    free(current_tree);
    current_tree=head_tree;
    if(head_tree)
        show_tree_node(current_tree,(GtkWidget**)data);
    else
        gtk_widget_destroy(window_view_tree);
}


void view_tree_prior(GtkWidget *widget,GtkWidget **entry)
{
    Tree *prior=locate_prior_node(head_tree,current_tree,offsetof(Tree,next));
    if(prior)
    {
        current_tree=prior;
        show_tree_node(current_tree,entry);
    }
    else
    {
        g_print("already the first node\n");
    }
}

void view_tree_next(GtkWidget *widget,GtkWidget **entry)
{
    if(current_tree->next)
    {
        current_tree=current_tree->next;
        show_tree_node(current_tree,entry);
    }
}

void query_province(GtkWidget *widget,gpointer data)
{
    gchar  text[MAXINT];
    Province *p;
    strcpy(text,gtk_entry_get_text(GTK_ENTRY(data)));
    g_print("[488]:gtk_entry_get_text %p\n",
            gtk_entry_get_text(GTK_ENTRY(data)));
    if(!head_province)
        return;
    for(p=head_province;p&&strcmp(p->num,text);p=p->next);
    if(p)
    {
        current_province=p;
        view_province(p);
    }
    else
        view_province(head_province);
}

void query_city(GtkWidget *widget,gpointer data)
{
    GtkWidget *entry;//=(GtkWidget*)data;
    Province *pp=NULL;
    City *pc=NULL;
    gchar  text[MAXINT];
    memcpy(&entry,data,sizeof(GtkWidget*));
    strcpy(text,gtk_entry_get_text(GTK_ENTRY(entry)));
    pp=locate_node(head_province,text,offsetof(Province,next),
            offsetof(Province,num),4);
    if(!pp)
        return;
    current_province=pp;
    head_city=current_province->head_city;
    g_print("539 found\n");
    memcpy(&entry,data+sizeof(GtkWidget*),sizeof(GtkWidget*));
    strcpy(text,gtk_entry_get_text(GTK_ENTRY(entry)));
    //strcpy(text,gtk_entry_get_text(GTK_ENTRY(data+sizeof(GtkWidget*))));
    g_print("[541]:%s\n",text);
    pc=(City*)locate_node((void*)pp->head_city,text,offsetof(City,next),
            offsetof(City,num),8);
    if(!pc)
    {
        g_print("547 :not found\n");
        return;
    }
    else
    {
        current_city=pc;
        view_city(pc);
    }
}

void forest_of_max_area(GtkWidget *widget,gpointer data)
{
    size_t offset=sizeof(char)*(8+7+8+4+10);
    struct datalist *headlist=inquire_tree(NULL,offset);
    sort_list(&headlist,sizeof(char*));
    gtk_entry_set_text(GTK_ENTRY(data),*(char**)headlist->data);
    g_print("max area forest:%s\n",*(char**)headlist->data);
}


void broadleaf_timber_of_max_area(GtkWidget *widget,gpointer data)
{
    size_t offset=sizeof(char)*(8+7+8+4+10)+sizeof(float)*0;
    struct datalist *hlist=inquire_tree("broadleaf",offset);
    sort_list(&hlist,sizeof(char*));
    gtk_entry_set_text(GTK_ENTRY(data),*(char**)hlist->data);
}

void aciculiailvae_forest_of_max_fund(GtkWidget *widget,
        gpointer data)
{
    int offset;
    offset=sizeof(char)*(8+7+8+4+10)+sizeof(float)*4;
    struct datalist *headlist=inquire_tree("acicul",offset);
    if(!headlist)
        return ;
    gtk_entry_set_text(GTK_ENTRY(data),*(char**)headlist->data);
}

void forest_of_max_revenue(GtkWidget *widget,gpointer data)
{
    int offset=sizeof(char)*37+sizeof(float)*6;
    struct datalist *headlist=inquire_tree(NULL,offset);
    if(!headlist)
        return;
    gtk_entry_set_text(GTK_ENTRY(data),*(char**)headlist->data);
}

void get_total_forest_area(GtkWidget *widget,gpointer data)
{
    char *str=(char*)malloc(sizeof(float)+1);
    float total_area=0;
    Province *pp;
    for(pp=head_province;pp;pp=pp->next)
        total_area+=pp->forest_area;
    sprintf(str,"%f",total_area);
    gtk_entry_set_text(GTK_ENTRY(data),str);
}

void get_total_desert_area(GtkWidget *widget,gpointer data)
{
    float total_area=0;
    Province *pp;
    char *str=(char *)malloc(sizeof(float)+1);
    for(pp=head_province;pp;pp=pp->next)
        total_area+=pp->desert_area;
    sprintf(str,"%f",total_area);
    gtk_entry_set_text(GTK_ENTRY(data),str);
}

void get_then_forestation_area(GtkWidget *widget,gpointer data)
{
    float result=0;
    Province *pp;
    char *str=(char *)malloc(sizeof(float)+1);
    for(pp=head_province;pp;pp=pp->next)
        result+=pp->then_forestation_area;
    sprintf(str,"%f",result);
    gtk_entry_set_text(GTK_ENTRY(data),str);
}

void get_then_forestation_fund(GtkWidget *widget,gpointer data)
{
    float result=0;
    Province *pp;
    char *str=(char*)malloc(sizeof(float)+1);
    for(pp=head_province;pp;pp=pp->next)
        result+=pp->then_forestation_fund;
    sprintf(str,"%f",result);
    gtk_entry_set_text(GTK_ENTRY(data),str);
}

void get_then_b_forest_area(GtkWidget *widget,gpointer data)
{
    char *str=(char*)malloc(sizeof(float)+1);
    float result=0;
    Province *pp;
    City *pc;
    GtkWidget *entry=NULL;
    memcpy((void*)(&entry),data,sizeof(GtkWidget*));
    strcpy(str,gtk_entry_get_text(GTK_ENTRY(entry)));
    //str=gtk_entry_get_text(GTK_ENTRY(entry));
    /*consider an severe error:using str=gtk_entry_get_text(GTK_ENT\
     * RY(entry)) to assign the pointer str
     * if so ,then str is reassigned to point to the buffer
     * of get_entry_get_text() and gtk_entry_set_text(),
     * causing bugs*/

    for(pp=head_province;pp&&strcmp(pp->num,str);pp=pp->next);
    if(!pp)
        return;
    for(pc=pp->head_city;pc;pc=pc->next)
    {
        result+=pc->then_broadleaf_forest_area;
    }
    sprintf(str,"%f",result);
    memcpy((void*)(&entry),data+sizeof(GtkWidget*),sizeof(GtkWidget*));
    gtk_entry_set_text(GTK_ENTRY(entry),str);
}

void get_then_a_forest_area(GtkWidget *widget,gpointer data)
{
    char *str=(char*)malloc(sizeof(float)+1);
    float result=0;
    Province *pp;
    City *pc;
    GtkWidget *entry=NULL;
    memcpy((void*)(&entry),data,sizeof(GtkWidget*));
    strcpy(str,gtk_entry_get_text(GTK_ENTRY(entry)));
    for(pp=head_province;pp&&strcmp(pp->num,str);pp=pp->next);
    if(!pp)
        return;
    for(pc=pp->head_city;pc;pc=pc->next)
    {
        result+=pc->then_aciculiailvae_area;
    }
    sprintf(str,"%f",result);
    memcpy((void*)(&entry),data+sizeof(GtkWidget*),sizeof(GtkWidget*));
    gtk_entry_set_text(GTK_ENTRY(entry),str);
}

void get_then_e_forestation_area(GtkWidget *widget,gpointer data)
{
    char *str=(char*)malloc(sizeof(float)+1);
    float result=0;
    Province *pp;
    City *pc;
    GtkWidget *entry=NULL;
    memcpy((void*)(&entry),data,sizeof(GtkWidget*));
    strcpy(str,gtk_entry_get_text(GTK_ENTRY(entry)));
    for(pp=head_province;pp&&strcmp(pp->num,str);pp=pp->next);
    if(!pp)
        return;
    for(pc=pp->head_city;pc;pc=pc->next)
    {
        result+=pc->then_ecoforest_area;
    }
    sprintf(str,"%f",result);
    memcpy((void*)(&entry),data+sizeof(GtkWidget*),sizeof(GtkWidget*));
    gtk_entry_set_text(GTK_ENTRY(entry),str);
}

void get_species_number(GtkWidget *widget,gpointer data)
{
    char *str=(char*)malloc(sizeof(float)+1);
    char text[MAXINT];
    int species=0;
    GtkWidget *entry=NULL;
    Province *pp=NULL;
    City *pc=NULL;
    Tree *pt=NULL;
    struct datalist *headlist=NULL,*ptr=NULL;
    memcpy((void*)&entry,data,sizeof(GtkWidget*));
    strcpy(text,gtk_entry_get_text(GTK_ENTRY(entry)));
    for(pp=head_province;pp&&strcmp(pp->num,text);pp=pp->next);
    if(!pp)
        return;
    for(pc=pp->head_city;pc;pc=pc->next)
        for(pt=pc->head_tree;pt;pt=pt->next)
        {
            for(ptr=headlist;ptr&&strcmp((char*)ptr->data\
                        ,pt->name);ptr=ptr->next);
            if(!ptr)
            {//no such name added before
                ptr=(struct datalist*)malloc(sizeof(struct datalist));
                ptr->data=(void*)pt->name;
                ptr->next=headlist;
                headlist=ptr;
                species++;//add one species
            }
            else
                continue;
        }
    sprintf(str,"%d",species);
    memcpy(&entry,data+sizeof(void*),sizeof(void*));
    gtk_entry_set_text(GTK_ENTRY(entry),str);
}



void first_three_cities_of_max_timber(GtkWidget *widget,gpointer data)
{
    gchar  text[MAXINT];
    Province *pp;
    City *pc;
    int i;
    float result=0.0;
    struct datalist *headlist=NULL,*ptr=NULL;
    for(pp=head_province;pp;pp=pp->next)
        for(pc=pp->head_city;pc;pc=pc->next)
        {
            strcpy(text,pc->name);
            result=pc->timber_storage;
            ptr=(struct datalist*)malloc(sizeof(struct datalist));
            ptr->data=malloc(sizeof(char*)+sizeof(float));
            memcpy(ptr->data,(void*)&text,sizeof(char*));
            memcpy(ptr->data+sizeof(char*),(void*)&result,sizeof(float));
            ptr->next=headlist;
            headlist=ptr;
        }
    sort_list(&headlist,sizeof(char*));
    memset(text,0,sizeof(text));
    ptr=headlist;
    strcpy(text,(char*)ptr->data);
    for(i=0;i<2;i++)
    {
        ptr=ptr->next;
        if(ptr)
        {
            strcat(text,",");
            strcat(text,(char*)ptr->data);
        }
    }
    gtk_entry_set_text(GTK_ENTRY(data),text);
    g_print("%s\n",text);
}

void first_three_tree_of_max_rev(GtkWidget *widget,gpointer data)
{
    struct datalist *headlist=NULL,*ptr=NULL;
    int i;
    char *str=malloc(sizeof(float)+1);
    headlist=inquire_tree(NULL,offsetof(Tree,total_revenue));
    //sort_list(&headlist,sizeof(char*));
    if(headlist)
    {
        gtk_entry_set_text(GTK_ENTRY(data),*(char**)headlist->data);
        gtk_entry_append_text(GTK_ENTRY(data),":");
        sprintf(str,"%.2f",*(float*)(headlist->data+sizeof(char*)));
        gtk_entry_append_text(GTK_ENTRY(data),str);
    }
    for(ptr=headlist->next,i=0;ptr&&i<2;ptr=ptr->next,i++)
    {
        gtk_entry_append_text(GTK_ENTRY(data),";");
        gtk_entry_append_text(GTK_ENTRY(data),*(char**)ptr->data);
        gtk_entry_append_text(GTK_ENTRY(data),":");
        sprintf(str,"%.2f",*(float*)(headlist->data+sizeof(char*)));
        gtk_entry_append_text(GTK_ENTRY(data),str);
    }
}
/*callbacks end*/

