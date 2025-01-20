#include <stdlib.h>
#include <stdio.h>
typedef struct s_data{
   int valor;
   struct s_data *next;
} t_data;


t_data *new_data(int value)
{
   t_data *new = (t_data*)malloc(sizeof(t_data));
   new->valor = value;
   new->next = NULL;
   return new;
}

void addData(struct t_data *data,struct t_data *new)
{
    data->
}
int main()
{
    t_data *head = NULL;
    head = new_data(5);
}