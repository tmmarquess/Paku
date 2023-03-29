#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define bool int
#define true 1
#define false 0

#define SIZE 21

typedef struct node
{
    char *value;
    char type[5];
    char *name;
    struct node *next;
} node;

typedef node *hash_table[SIZE];

void init_table(hash_table table)
{
    for (int i = 0; i < SIZE; i++)
    {
        table[i] = NULL;
    }
}

node *new_node(char *value, char *name, char type[])
{
    node *new = malloc(sizeof(node));
    new->value = value;
    strcpy(new->type, type);
    new->name = name;
    new->next = NULL;
    return new;
}

int get_hash(char *name)
{
    int len = strlen(name);
    int hash_value = 0;
    for (int i = 0; i < (int)len; i++)
    {
        int pos_value = name[i];
        hash_value += pos_value * (i + 1);
    }
    return hash_value;
}

int get_index(int hash_value)
{
    return hash_value % SIZE;
}

node *get_item_by_name(hash_table table, char *name)
{
    int hash = get_hash(name);
    int index = get_index(hash);

    node *actual = table[index];

    while (actual != NULL)
    {
        if (!strcmp(actual->name, name))
        {
            return actual;
        }
        actual = actual->next;
    }
    return NULL;
}

bool is_name_in_table(hash_table table, char *name)
{
    node *item = get_item_by_name(table, name);
    if (item == NULL)
    {
        return false;
    }
    return true;
}

void insert_value_in_table(hash_table table, char *value, char *name, char type[])
{
    if (!strcmp(type, "char"))
    {
        *value = value[0];
    }

    node *exists = get_item_by_name(table, name);

    if (exists != NULL)
    {
        exists->value = value;
        return;
    }

    int hash_value = get_hash(name);
    int index = get_index(hash_value);
    node *new = new_node(value, name, type);

    if (table[index] == NULL)
    {
        table[index] = new;
    }
    else
    {
        node *actual = table[index];
        while (actual->next != NULL)
        {
            actual = actual->next;
        }
        actual->next = new;
    }
}

bool remove_value_from_table(hash_table table, char *name)
{
    int hash_value = get_hash(name);
    int index = get_index(hash_value);

    bool name_exists = false;
    node *actual = table[index], *before = NULL;
    while (actual != NULL)
    {
        if (!strcmp(actual->name, name))
        {
            name_exists = true;
            break;
        }
        before = actual;
        actual = actual->next;
    }
    if (name_exists)
    {
        if (before == NULL)
        {
            table[index] = actual->next;
        }
        else
        {
            before->next = actual->next;
        }
        free(actual);
        return true;
    }
    else
    {
        return false;
    }
}

void print_table(hash_table table)
{
    for (int i = 0; i < SIZE; i++)
    {
        bool empty = true;
        printf("[%d] ->", i);
        node *actual = table[i];
        while (actual != NULL)
        {
            printf(" %s (%s) = %s ->", actual->name, actual->type, actual->value);
            actual = actual->next;
            empty = false;
        }
        if (empty)
        {
            printf(" ()");
        }
        printf("\n");
    }
    printf("\n");
}