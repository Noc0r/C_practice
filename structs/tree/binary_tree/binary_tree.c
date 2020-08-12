#include "binary_tree.h"

typedef struct node
{
    void *data;
    struct node *right;
    struct node *left;
    struct node *father;
} node;

typedef struct bin_tree
{
    unsigned int size;
    node *root;
    int (*compare)(void *, void *);
} bin_tree;

static bin_tree *create_bin_tree(int (*compare)(void *, void *));
static unsigned int count(bin_tree *bin_tree);
static void clear(bin_tree *bin_tree);
static void insert_element(bin_tree *bin_tree, void *data);
static bool remove_element(bin_tree *bin_tree, void *element);
static bool find_value(bin_tree *bin_tree, void *data);
static node *insert(node *father, void *data);
static node *find(bin_tree *root, void *data);
static void deep_clean(node *root);
static void remove(node *rem);
static void preorder(bin_tree *this, void (*func)(void *));
static void inorder(bin_tree *this, void (*func)(void *));
static void postorder(bin_tree *this, void (*func)(void *));

static bin_tree *create_bin_tree(int (*compare)(void *, void *))
{
    bin_tree *new_bin_tree = (bin_tree *)(malloc(sizeof(bin_tree)));
    new_bin_tree->root = NULL;
    new_bin_tree->size = 0;
    new_bin_tree->compare = compare;
    return new_bin_tree;
}

node *create_node(node *father, void *data)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->father = father;
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

static node *insert(node *father, void *data)
{
    node *new_node = create_node(father, data);
    return new_node;
}

static void insert_element(bin_tree *this, void *data)
{
    if (this->root)
    {
        node *next = this->root;
        node *tmp;
        bool left_son;
        do
        {
            tmp = next;
            if (this->compare(tmp->data, data) >= 0)
            {
                next = tmp->left;
                left_son = true;
            }
            else
            {
                next = tmp->right;
                left_son = false;
            }
        } while (next);

        if (left_son)
            tmp->left = insert(tmp, data);
        else
            tmp->right = insert(tmp, data);
    }
    else
    {
        this->root = insert(NULL, data);
    }
    this->size++;
}

static bool remove_element(bin_tree *this, void *data)
{
    node *rem = find(this, data);
    if (rem)
    {
        this->size--;
        remove(rem);
        return true;
    }
    return false;
}

static node *find(bin_tree *root, void *data)
{
    node *tmp = root->root;
    while (tmp)
    {
        if (root->compare(tmp->data, data) > 0)
            tmp = tmp->left;
        else if (root->compare(tmp->data, data) < 0)
            tmp = tmp->right;
        else
            return tmp;
    }
    return NULL;
}

static void remove(node *rem)
{
    if (rem->right && rem->left)
    {
        node *tmp = rem->left;
        while (tmp->right)
        {
            tmp = tmp->right;
        }
        rem->data = tmp->data;
        remove(tmp);
    }
    else
    {
        node *replace = (node *)((unsigned long long)rem->left ^ (unsigned long long)rem->right);
        if (replace)
            replace->father = rem->father;
        if (rem->father)
        {
            if (rem->father->left == rem)
                rem->father->left = replace;
            else
                rem->father->right = replace;
        }
        free(rem);
    }
}

static bool find_value(bin_tree *this, void *data)
{
    if (find(this, data))
        return true;
    return false;
}

static unsigned int count(bin_tree *bin_tree)
{
    return bin_tree->size;
}

static void deep_clean(node *root)
{
    if (root)
    {
        deep_clean(root->left);
        deep_clean(root->right);
        remove(root);
    }
}

static void clear(bin_tree *bin_tree)
{
    deep_clean(bin_tree->root);
}

static void preorder_node(node *this, void (*func)(void *))
{
    if (this)
    {
        func(this->data);
        preorder_node(this->left, func);
        preorder_node(this->right, func);
    }
}

static void preorder(bin_tree *this, void (*func)(void *))
{
    preorder_node(this->root, func);
}

static void inorder_node(node *this, void (*func)(void *))
{
    if (this)
    {
        inorder_node(this->left, func);
        func(this->data);
        inorder_node(this->right, func);
    }
}
static void inorder(bin_tree *this, void (*func)(void *))
{
    inorder_node(this->root, func);
}

static void postorder_node(node *this, void (*func)(void *))
{
    if (this)
    {
        postorder_node(this->left, func);
        postorder_node(this->right, func);
        func(this->data);
    }
}

static void postorder(bin_tree *this, void (*func)(void *))
{
    postorder_node(this->root, func);
}

bin_tree_lib *create_bin_tree_library()
{
    bin_tree_lib *library = (bin_tree_lib *)malloc(sizeof(bin_tree_lib));
    library->clear = clear;
    library->count = count;
    library->find_value = find_value;
    library->insert_element = insert_element;
    library->remove_element = remove_element;
    library->create_bin_tree = create_bin_tree;
    library->preorder = preorder;
    library->inorder = inorder;
    library->postorder = postorder;
    return library;
}