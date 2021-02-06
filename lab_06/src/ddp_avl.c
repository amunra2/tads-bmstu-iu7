#include"../inc/ddp_avl.h"


void free_tree(node_t *tree)
{
    if (tree)
    {
        free_tree(tree->left);
        free_tree(tree->right);
    }

    free(tree);
}


node_t *tree_init_node(int num, int height)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
    {
        return NULL;
    }

    node->data = num;
    node->height = height;
    node->left = NULL;
    node->right = NULL;

    return node;
}


node_t *add_ddp(node_t *ddp, int data, int *height, int *comp)
{
    (*height)++;
    (*comp)++;

    if (!ddp)
    {
        ddp = tree_init_node(data, *height);
    }
    else if (data < ddp->data)
    {
        ddp->left = add_ddp(ddp->left, data, height, comp);
    }
    else if (data > ddp->data)
    {
        ddp->right = add_ddp(ddp->right, data, height, comp);
    }

    return ddp;
}


int fill_ddp(node_t **ddp, arr_t arr)
{
    for (int i = 0; i < arr.len; i++)
    {
        int height = -1;

        int comp = 0;

        *ddp = add_ddp(*ddp, arr.data[i], &height, &comp);
    }

    return OK_FILL_DDP;
}


// AVL

unsigned char find_height(node_t *tree)
{
    return tree ? tree->height : 0;
}


int balance_count(node_t *tree)
{
    return find_height(tree->right) - find_height(tree->left);
}


void correct_height(node_t *tree)
{
    unsigned char h_left = find_height(tree->left);
    unsigned char h_right = find_height(tree->right);

    tree->height = (h_left > h_right ? h_left : h_right) + 1;
}


node_t *rotate_right(node_t *root)
{
    node_t *new_root = root->left;

    root->left = new_root->right;
    new_root->right = root;

    correct_height(root);
    correct_height(new_root);

    return new_root;
}


node_t *rotate_left(node_t *root)
{
    node_t *new_root = root->right;

    root->right = new_root->left;
    new_root->left = root;

    correct_height(root);
    correct_height(new_root);

    return new_root;
}


node_t *balance_root(node_t *root)
{
    correct_height(root);

    if (balance_count(root) == 2)
    {
        if (balance_count(root->right) < 0)
        {
            root->right = rotate_right(root->right);
        }

        return rotate_left(root);
    }

    if (balance_count(root) == -2)
    {
        if (balance_count(root->left) > 0)
        {
            root->left = rotate_left(root->left);
        }

        return rotate_right(root);
    }

    return root;
}


node_t *add_avl(node_t *avl, int data, int *height, int *comp)
{
    (*height)++;
    (*comp)++;

    if (!avl)
    {
        avl = tree_init_node(data, *height);
    }
    else if (data < avl->data)
    {
        avl->left = add_avl(avl->left, data, height, comp);
    }
    else if (data > avl->data)
    {
        avl->right = add_avl(avl->right, data, height, comp);
    }

    return balance_root(avl);   
}


int fill_avl(node_t **avl, arr_t arr)
{
    for (int i = 0; i < arr.len; i++)
    {
        int height = -1;

        int comp = 0;

        *avl = add_avl(*avl, arr.data[i], &height, &comp);
    }

    return OK_FILL_DDP;
}


// PRINT
void print_tree(node_t *tree, int place)
{
    int space = 5;

    if (tree)
    {
        place += space;

        print_tree(tree->right, place);
        
        puts("");

        for (int i = space; i < place; i++)
        {
            printf(" ");
        }

        printf("{ %d }\n", tree->data);

        print_tree(tree->left, place);
    }
}