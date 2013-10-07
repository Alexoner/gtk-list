#include "define.h"
/*linked lists operation,start*/


void *locate_prior_node(void*head,void*p,size_t offset)
{
    void *ptr=head;
    for(ptr=head;ptr&&*(void**)(ptr+offset)!=p;memcpy(&ptr,ptr+offset,sizeof(void*)));
    return ptr;
}

void *locate_node(void* head,void *data,size_t next_offset,
        size_t data_offset,size_t n)
{
    void *ptr=head;
    for(ptr=head;ptr&&strcmp((char*)(ptr+data_offset),(char*)data/*,n*/);\
            memcpy(&ptr,ptr+next_offset,sizeof(void*)))
    {
        g_print("[19]%d\n",memcmp(ptr+data_offset,data,n));
        g_print("%s\n",(char*)data);
    }
    return ptr;
}

void *delete_list(void **head,size_t offset)
{//offset is the offset of the member next from the structure
    void *ptr=NULL,*q=NULL;
    memcpy(&ptr,head,sizeof(void*));
    while(ptr)
    {
        memcpy(&q,ptr+offset,sizeof(void*));//assign the *next
        free(ptr);
        ptr=q;
    }
    q=NULL;
    memset(head,0,sizeof(void*));
    return NULL;
}


gpointer sort_list(struct datalist **head,size_t offset)
{
    struct datalist *p,*q;
    int n,i;
    void *ptr;
    for(p=*head,n=0;p;p=p->next)
        n++;
    for(i=0;i<n;i++)
        for(p=*head;p;p=p->next)
        {
            q=p->next;
            if(!q)
                break;
            if(*(float*)(&p->data+offset)<*(float*)(&p->data+offset))
            {
               ptr=p->data;
               p->data=q->data;
               q->data=ptr;
            }
        }
    return (gpointer)*head;
}


void save(char *namep,char *namec,char *namet)
{//the filename of province,city,tree
    FILE *fp[3];//fp[0],province...
    Province *p1;
    City *p2;
    Tree *p3;
    fp[0]=fopen(namep,"wb");
    fp[1]=fopen(namec,"wb");
    fp[2]=fopen(namet,"wb");
    if(!(fp[0]&&fp[1]&&fp[2]))
    {
        g_print("ERROR in opening files\n");
        return;
    }
    p1=head_province;
    while(p1)
    {
        fwrite(p1,sizeof(Province),1,fp[0]);
        g_print("province %s\n",p1->num);
        p1=p1->next;
    }
    for(p1=head_province;p1;p1=p1->next)
        for(p2=p1->head_city;p2;p2=p2->next)
        {
            fwrite(p2,sizeof(City),1,fp[1]);
            g_print("province:%s\tcity:%s\n",p2->province_num,p2->num);
        };
    for(p1=head_province;p1;p1=p1->next)
        for(p2=p1->head_city;p2;p2=p2->next)
            for(p3=p2->head_tree;p3;p3=p3->next)
            {
                fwrite(p3,sizeof(Tree),1,fp[2]);
                g_print("province :%s\tcity:%s\ttree:%s\n",p3->province_num,p3->city_num,p3->num);
            }
    fclose(fp[0]);
    fclose(fp[1]);
    fclose(fp[2]);
}

void load(char *namep,char *namec,char *namet)
{
    FILE *fp[3];
    Province *p1=NULL;
    City *p2=NULL;
    Tree *p3=NULL;
    fp[0]=fopen(namep,"rb");
    fp[1]=fopen(namec,"rb");
    fp[2]=fopen(namet,"rb");
    if(!(fp[0]||fp[1]||fp[2]))
    {
        g_print("ERROR in opening files\n");
        return;
    }
	if(fp[0])
	{
		while(!feof(fp[0])&&!ferror(fp[0]))/*when to stop reading*/
		{//load province linked list
			p1=(Province *)malloc(sizeof(Province));
			fread(p1,sizeof(Province),1,fp[0]);
			if(feof(fp[0])||ferror(fp[0]))
			{/*check whether the eof is read*/
				//g_print("eof or error\n");
				break;
			}
			g_print("province :%s\n",p1->num);
			if(current_province)
			{
				current_province->next=p1;
			}
			else
			{
				current_province=head_province=p1;
			}
			p1->next=NULL;
			p1->head_city=NULL;
			current_province=p1;
		}
	}

    p1=head_province;
	if(fp[1])
	{
		while(!feof(fp[1])&&!ferror(fp[1]))
		{//load city linked list
			p2=(City *)malloc(sizeof(City));
			fread(p2,sizeof(City),1,fp[1]);
			if(feof(fp[1])||ferror(fp[1]))
			{/*check what has been read*/
				//g_print("eof or error\n");
				break;
			}
			g_print("province:%s\tcity:%s\n",p2->province_num,p2->num);
			if(current_city)
			{
				current_city->next=p2;
			}
			else
			{
				head_city=current_city=p2;
			}
			if(p2->next==NULL)
			{/*the last node appears,then link city with province*/
				for(p1=head_province;p1&&strcmp(p1->num,p2->province_num);p1=p1->next);
				if(p1)
				{
					g_print("[161]Found province,num is %s\n",p1->num);
					p1->head_city=head_city;
				}
				current_city=head_city=NULL;/*new linked list*/
			}
			else
			{
				p2->next=NULL;
				current_city=p2;/*reassign the current_city pointer*/
			}
			p2->head_tree=NULL;/*initiallize the pointer to tree list*/
		}//end of city
	}

	if(fp[2])
	{
		while(!feof(fp[2])&&!ferror(fp[2]))
		{//load tree linked list
			p3=(Tree *)malloc(sizeof(Tree));
			fread(p3,sizeof(Tree),1,fp[2]);
			if(feof(fp[2])||ferror(fp[2]))
			{
				//g_print("eof or error\n");
				break;
			}
			g_print("province:%s\tcity:%s\ttree:%s\n",p3->province_num,p3->city_num,p3->num);
			if(current_tree)
			{
				current_tree->next=p3;
			}
			else
				head_tree=current_tree=p3;
			if(p3->next==NULL)
			{//the last node of the linked list
				for(p1=head_province;p1&&strcmp(p1->num,p3->province_num);p1=p1->next);
				if(p1)//located the province
				{
					g_print("Found province,num is %s\n",p1->num);
					for(p2=p1->head_city;p2&&strcmp(p2->num,p3->city_num);p2=p2->next);
					if(p2)//located the city
					{
						g_print("found city,num is %s\n",p2->num);
						p2->head_tree=head_tree;
					}
					else
					{
						g_print("city not found,address is %p\n",p2);
					}
				}
				head_tree=current_tree=NULL;
			}
			else
			{
				p3->next=NULL;
				current_tree=p3;
			}
		}
	}
    fclose(fp[0]);
    fclose(fp[1]);
    fclose(fp[2]);
}




Province *get_province_node(GtkWidget **entry)
{
    gint i;
    gpointer gp=NULL;
    Province *p=(Province *)malloc(sizeof(Province));
    strcpy(p->num,gtk_entry_get_text(GTK_ENTRY(entry[0])));
    strcpy(p->name,gtk_entry_get_text(GTK_ENTRY(entry[1])));
    for(i=2,gp=&p->forest_area;i<PNUM;i++)
    {
        *((float*)gp)=atof(gtk_entry_get_text(GTK_ENTRY(entry[i])));
        gp+=sizeof(float);
    }
    p->head_city=NULL;/*This a critical statement,uninitialized pointer
                        may lead to segmentation fault.*/
    p->next=NULL;
    return p;
}

City* get_city_node(GtkWidget **entry)
{
    City *p=(City *)malloc(sizeof(City));
    gpointer gp=NULL;
    gint i;
    strcpy(p->num,gtk_entry_get_text(GTK_ENTRY(entry[0])));
    strcpy(p->name,gtk_entry_get_text(GTK_ENTRY(entry[1])));
    strcpy(p->province_num,gtk_entry_get_text(GTK_ENTRY(entry[2])));
    for(i=3,gp=&p->forest_area;i<CNUM-2;i++)
    {
        *((float*)gp)=atof(gtk_entry_get_text(GTK_ENTRY(entry[i])));
        gp+=sizeof(float);//void pointer self increase by sizeof(float).
    }
    p->population=atoi(gtk_entry_get_text(GTK_ENTRY(entry[17])));
    p->head_tree=NULL;//CRITICAL
    p->next=NULL;
    g_print("%d\n",p->forest_amount=atoi(gtk_entry_get_text(GTK_ENTRY(entry[18]))));
    return p;
}

Tree *get_tree_node(GtkWidget **entry)
{
    Tree *p=(Tree *)malloc(sizeof(Tree));
    gpointer gp=NULL;
    gint i;
    strcpy(p->num,gtk_entry_get_text(GTK_ENTRY(entry[0])));
    strcpy(p->name,gtk_entry_get_text(GTK_ENTRY(entry[1])));
    strcpy(p->city_num,gtk_entry_get_text(GTK_ENTRY(entry[2])));
    strcpy(p->province_num,gtk_entry_get_text(GTK_ENTRY(entry[3])));
    strcpy(p->category,gtk_entry_get_text(GTK_ENTRY(entry[4])));
    for(i=5,gp=&p->forest_area;i<TNUM;i++)
    {
        *((float*)gp)=atof(gtk_entry_get_text(GTK_ENTRY(entry[i])));
        gp+=sizeof(float);
    }
    p->next=NULL;
    //g_print("The newly added tree number is %s\n",p->num);
    return p;
}


Province *insert_province_node(Province *current,Province *ptr)
{//insert after current
    if(current)//not the head pointer of province node
    {
        ptr->next=current->next;
        current->next=ptr;
    }
    else
    {
        head_province=ptr;
        ptr->next=NULL;
    }
    return ptr;
}

City *insert_city_node(City  *current,City  *p)
{
    if(current)
    {
        p->next=current->next;
        current->next=p;
    }
    else
    {//still empty lists
        current_province->head_city=head_city=p;
        p->next=NULL;
    }
    return head_city;
}

Tree *insert_tree_node(Tree *current,Tree *p)
{
    if(current)
    {
        p->next=current->next;
        current->next=p;
    }
    else
    {
        current_city->head_tree=head_tree=p;
        p->next=NULL;
    }
    return p;
}

gpointer inquire_tree(gchar *catagory,int offset)
{
    gchar  *str;
    Province *pp;
    City *pc;
    Tree *pt;
    float amount;
    struct datalist *headlist=NULL,*p,*q;
    for(pp=head_province;pp;pp=pp->next)
        for(pc=pp->head_city;pc;pc=pc->next)
            for(pt=pc->head_tree;pt;pt=pt->next)
            {/*traversing the whole list*/
                if(catagory&&strcmp(pt->category,catagory))
                    continue;//catagory required
               str=pt->name;
               amount=*(float*)((void*)pt+offset);
               for(p=headlist;p&&strcmp((char*)p->data,str);p=p->next);
               if(p)
               {//added to the list before
                   *(float*)(p->data+sizeof(char*))+=amount;
               }
               else
               {//insert this new node
                   p=(struct datalist*)malloc(sizeof\
                           (struct datalist));
                   //allocate memory for datalist struct

                   p->data=malloc(sizeof(char*)+sizeof(float));
                   *(char**)(p->data)=str;
                   *(float*)(p->data+sizeof(char*))=amount;
                   p->next=NULL;
                   if(!headlist)
                       headlist=p;
                   else
                   {
                       for(q=headlist;q->next;q=q->next);
                       q->next=p;
                   }
               }
            }
    sort_list(&headlist,sizeof(char*));//sort by the float variable
    return headlist;
}

gpointer inquire_province(size_t offset)
{
    float result;
    Province *pp;
    gchar *str;
    struct datalist *headlist=NULL,*p=NULL,*q=NULL;
    for(pp=head_province;pp;pp=pp->next)
    {
        result=*(float*)((gpointer)pp+offset);
        str=pp->name;
        p=(struct datalist*)malloc(sizeof(struct datalist));
        *(char**)p->data=str;
        *(float*)(p->data+sizeof(char*))=result;
        if(!headlist)
        {
            headlist=p;
        }
        else
        {
            for(q=headlist;q->next;q=q->next);
            q->next=p;
        }
        p->next=NULL;
    }
    sort_list(&headlist,sizeof(char*));
    return headlist;
}

/*linked lists operation,end*/
