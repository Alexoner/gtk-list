#ifndef DEFINE_H
#define DEFINE_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define MAXINT 32
#define PNUM 13//the number of members of Province
#define CNUM 19
#define TNUM 12


typedef struct tree
{
    char num[8];
    char name[7];
    char city_num[8];
    char province_num[4];
    char category[10];
    float forest_area;
    float timber_storage;
    float then_forestation_area;
    float then_forestation_fund;
    float total_forestation_fund;
    float then_revenue;
    float total_revenue;
    struct tree *next;
}Tree;

typedef struct city
{
    char num[8];
    char name[20];
    char province_num[4];
    float forest_area;
    float timber_storage;
    float desert_area;
    float land_area;
    float then_broadleaf_forest_area;//当年阔叶林面积
    float then_aciculiailvae_area;//针叶林
    float then_ecoforest_area;//经济林
    float then_forestation_fund;
    float total_forestation_fund;
    float then_felling_area;
    float then_timber_revenue;//
    float total_timber_revenue;
    float then_ecoforest_revenue;
    float total_ecoforest_revenue;
    int population;
    int forest_amount;
    struct tree *head_tree;
    struct city *next;
}City;

typedef struct Province
{
    char num[4];
    char name[20];
    float forest_area;
    float timber_storage;//木材蓄积量
    float desert_area;
    float then_forestation_area;
    float then_forestation_fund;
    float total_forestation_fund;
    float then_felling_area;//当年伐木收益
    float then_timber_revenue;
    float total_timber_revenue;
    float then_ecoforest_revenue;//当年经济林收益
    float total_ecoforest_revenue;
    struct city *head_city;
    struct Province *next;
}Province;


struct datalist
{/*This structure is defined to be dynamically allocated memory
    and pass arguments*/
    void *data;
    struct datalist *next;
};

//

Province *head_province,*current_province;
City *head_city,*current_city;
Tree *head_tree,*current_tree;
GtkWidget *window_main,*window_insert_province,*window_insert_city,*window_insert_tree,\
              *window_view_province,*window_view_city,*window_view_tree;

extern char *province_member_name[PNUM];
extern char *city_member_name[CNUM];
extern char *tree_member_name[TNUM];

//gboolean province_modify=FALSE;
/*typedef struct
{
    Province *province_ptr;
    GtkWidget **entry;
}*/

//interfaces:
extern void main_menu();
extern void insert_province(Province *ptr); extern void insert_city(Province **ptr);
extern void insert_tree();
extern void view_province(Province *p);
extern void view_city(City *p);
extern void view_tree(Tree *p);
//interfaces,end

//useful interface functions
extern void clear_entry(GtkWidget **entry,int n);
extern GtkWidget *make_label_entry_button(GtkWidget **entry,GtkWidget **button,char *,char *);
extern GtkWidget *make_province_box(GtkWidget **entry,gint n);
extern GtkWidget *make_city_box(GtkWidget **entry);
extern GtkWidget *make_tree_box(GtkWidget **entry);
extern GtkWidget **show_province_node(Province *p,GtkWidget **entry);
extern GtkWidget **show_city_node(City *p,GtkWidget **entry);
extern GtkWidget **show_tree_node(Tree *p,GtkWidget **entry);
//callbacks ,start

extern gboolean delete_event(GtkWidget *widget,GdkEvent *event,gpointer data);
extern void record_data();
extern void main_menu_save(GtkWidget *widget,gpointer data);
extern void insert_province_next(GtkWidget *widget,GtkWidget **entry);
extern void insert_province_finish(GtkWidget *widget,GtkWidget **entry);
extern void insert_province_make_head(GtkWidget *widget,GtkWidget **entry);
extern void insert_province_city(GtkWidget *widget,gpointer data);
extern void insert_city_next(GtkWidget *widget,GtkWidget **entry);
extern void insert_city_finish(GtkWidget *widget,GtkWidget **entry);
extern void insert_city_tree();
//extern void insert_tree_previous(GtkWidget *widget,GtkWidget **entry);
extern void insert_tree_next(GtkWidget *widget,GtkWidget **entry);
extern void insert_tree_finish(GtkWidget *widget,GtkWidget **entry);
extern void view_province_city(GtkWidget *widget,Province *p);
extern void view_province_modify(GtkWidget *widget,GtkWidget **entry);
extern void view_province_confirm(GtkWidget *widget,GtkWidget **entry);
extern void view_province_insert(GtkWidget *widget,gpointer p);
extern void view_province_delete(GtkWidget *widget,Province *p);
extern void view_province_prior(GtkWidget *widget,GtkWidget **entry);
extern void view_province_next(GtkWidget *widget,GtkWidget **entry);
extern void view_city_tree(GtkWidget *widget,City *p);
extern void view_city_modify(GtkWidget *widget,GtkWidget **entry);
extern void view_city_insert(GtkWidget *widget,gpointer p);
extern void view_city_delete(GtkWidget *widget,gpointer data);
extern void view_city_confirm(GtkWidget *widget,GtkWidget **entry);
extern void view_city_prior(GtkWidget *widget,GtkWidget **entry);
extern void view_city_next(GtkWidget *widget,GtkWidget **entry);
extern void view_tree_modify(GtkWidget *widget,GtkWidget **entry);
extern void view_tree_confirm(GtkWidget *widget,GtkWidget **entry);
extern void view_tree_insert(GtkWidget *widget,gpointer p);
extern void view_tree_delete(GtkWidget *widget,gpointer data);
extern void view_tree_prior(GtkWidget *widget,GtkWidget **entry);
extern void view_tree_next(GtkWidget *widget,GtkWidget **entry);
extern void query_province(GtkWidget *widget,gpointer data);//view province
extern void query_city(GtkWidget *widget,gpointer data);//view city
extern void forest_of_max_area(GtkWidget *widget,gpointer data);
extern void broadleaf_timber_of_max_area(GtkWidget *widget,gpointer data);
extern void aciculiailvae_forest_of_max_fund(GtkWidget *widget,gpointer data);
extern void forest_of_max_revenue(GtkWidget *widget,gpointer data);
extern void get_total_forest_area(GtkWidget *widget,gpointer data);
extern void get_total_desert_area(GtkWidget *widget,gpointer data);
extern void get_then_forestation_area(GtkWidget *widget,gpointer data);
extern void get_then_forestation_fund(GtkWidget *widget,gpointer data);
extern void get_then_b_forest_area(GtkWidget *widget,gpointer data);
extern void get_then_a_forest_area(GtkWidget *widget,gpointer data);
extern void get_then_e_forestation_area(GtkWidget *widget,gpointer data);
extern void get_species_number(GtkWidget *widget,gpointer data);
extern void first_three_cities_of_max_timber(GtkWidget *widget,gpointer data);
extern void first_three_tree_of_max_rev(GtkWidget *widget,gpointer data);
//callbacks,end

//linked lists funcitons:
extern void load(char *file_province,char *file_city,char *file_tree);
extern void save(char *file_province,char *file_city,char *file_tree);
//extern void *locate_prior_node( void *q,int flag);
extern void *locate_prior_node(void*head,void*p,size_t offset);
extern void *locate_node(void *head,void *data,size_t next_offset,
        size_t data_offset,size_t n);
extern Province *get_province_node(GtkWidget **entry);
extern Province *insert_province_node(Province *current,Province *ptr);
extern Province *delete_province_node(Province *ptr);
extern City *get_city_node(GtkWidget **entry);
extern City *insert_city_node(City *current,City *ptr);
extern City *delete_city_node(City *ptr);
extern Tree *get_tree_node(GtkWidget **entry);
extern Tree *insert_tree_node(Tree *current,Tree *ptr);
extern Tree *delete_tree_node(Tree *ptr);
extern gpointer sort_list(struct datalist **head,size_t offset);
extern void *delete_list(void **head,size_t offset);
extern gpointer inquire_tree(gchar *catagory,int offset);
extern gpointer inquire_province(size_t offset);
//linked lists funcitons.


#endif

