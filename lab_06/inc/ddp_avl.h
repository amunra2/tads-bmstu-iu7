#include<stdio.h>
#include<stdlib.h>
#include"../inc/structs.h"


#ifndef DDP_AVL_H
#define DDP_AVL_H

#define OK_FILL_DDP 0

int fill_ddp(node_t **ddp, arr_t arr);

int fill_avl(node_t **avl, arr_t arr);

void print_tree(node_t *tree, int place);

void free_tree(node_t *tree);

node_t *add_ddp(node_t *ddp, int data, int *height, int *comp);

node_t *add_avl(node_t *avl, int data, int *height, int *comp);

#endif
