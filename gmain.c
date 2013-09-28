#include <gtk/gtk.h>
#include <stdio.h>
int main(int argc,char **argv)
{
    gtk_init(&argc,&argv);
    char *str=NULL;
    float num;
    num=atof("");
    window();
    gtk_main();
    return 0;
}
