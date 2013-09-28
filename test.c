#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#define in y
typedef struct
{
    float a;
    char b;
    int c;
}Data;

struct datalist
{
    void *data;
    struct datalist *next;
};

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


int main()
{
    Province *p=(Province*)malloc(sizeof(Province));
    Tree *q=(Tree*)malloc(sizeof(Tree));
    struct datalist *list=(struct datalist*)malloc(sizeof(struct datalist));
    list->data=malloc(sizeof(char)+sizeof(float));
    *(char*)list->data='c';
    while(1)
        printf("\a");
    printf("%c\n",*(char*)list->data);


    printf("char* %ld float* %ld double* %ld datalist* %ld\n",sizeof(char*),
            sizeof(float*),sizeof(double*),sizeof(struct datalist*));
    printf("sizeof(Province) %ld offset of  next:%ld\t timber_storage:%ld\n",
            sizeof(Province),(void*)&p->next-(void*)p,
            (void*)&p->name-(void*)p);
    printf("total_eco.. %p\thead_city %p\n",&p->total_ecoforest_revenue,
            &p->head_city);
    printf("%ld\n",(void*)q-(void*)&q->next);
    printf("%s\n",(char*)0x0);
/*    int i;
    Data a={1,2,3};
    char str[]="helloworld";
    Data *p=&a;
    int x=(int)&p->a; float f=0.1;
    void *p2=(void *)&f;
    printf("subduction of &a.c-&a.a:%ld\n",&a.c-&a.a);
//    printf("sizeof(float):%ld\tsizeof(int):%ld\tsizeof(char):%ld\n",
            sizeof(float),sizeof(int),sizeof(char));
    printf("&a:%p\t&a.a:%p\t&a.b:%p\t&b-&a:%ld\n",&a,&a.a,&a.b,(void*)&a.b-(void*)&a.a);*/

    return 0;
}
