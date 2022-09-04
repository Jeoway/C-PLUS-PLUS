
#define RED 0
#define BLACK 1

typedef int KET_TYPE;

typedef struct _rb_tree_node
{
    unsigned char color;
    struct _rb_tree_node* left;
    struct _rb_tree_node* right;
    struct _rb_tree_node* parent;
    /* data */

    KET_TYPE key;
    void* value;
}rbtree_node;


typedef struct _rbtree
{
    /* data */
    _rb_tree_node *root;
    _rb_tree_node *nil; //NULL
}rbtree;


void left_rotate(rbtree* T, rbtree_node *x)
{
    //参数判断
    if (x == T->nil)
        return;
    
    rbtree_node *y = x->right;

    //x的右节点指向y的左节点，y的左节点如果不为空，则其父节点指向x
    x->right = y->left;
    if (y->left != T->nil)
    {
        y->left->parent = x;
    }

    //x的父节点指向y
    y->parent = x->parent;
    if (x->parent == T->nil)
    {
        T->root = y;
    }
    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }
    else if (x->parent->right == x)
    {
        x->parent->right = y;
    }

    //y的左节点指向x
    y->left = x;
    x->parent = y;

}

void right_rotate(rbtree* T, rbtree_node *y)
{
    //参数判断
    if (y == T->nil)
        return;
    
    rbtree_node *x = y->left;

    //y的左节点指向x的右节点，x的右节点如果不为空，则其父节点指向y
    y->left = x->right;
    if (x->right != T->nil)
    {
        x->right->parent = y;
    }

    //y的父节点指向x
    x->parent = y->parent;
    if (y->parent == T->nil)
    {
        T->root = x;
    }
    else if (y->parent->right == y)
    {
        y->parent->right = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }

    //x的右节点指向y
    x->right = y;
    y->parent = x;
}

void rbtree_insert(rbtree* T, rbtree_node* z)
{
    rbtree_node* y = T->nil;
    rbtree_node* x = T->root;


    while (x != T->nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else if (z->key > x->key)
        {
            x = x->right;
        }
        else 
        {
            //相等的清空根据实际业务，可做处理或不做处理
        }
    }

    //遍历结束后，此时已确定要插入节点的位置
    z->parent = y;
    if (y == T->nil)
    {
        T->root = z;
    }
    else if (z->key > y->key)
    {
        y->left = z;
    }
    else if (z->key < y->key)
    {
        y->right = z;
    }

    //默认新插入节点的颜色为红色
    z->color = RED;
    z->left = T->nil;
    z->right = T->nil;
}

void rbtree_insert_fixup(rbtree* T, rbtree_node* z)
{
    rbtree_node* y = T->nil;

    while (z->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            //如果叔父节点是红色
            if (y->color == RED)
            {
                //父节点变红，祖父节点变黑，叔父节点变红
                z->parent->color = RED;
                z->parent->parent->color = BLACK;
                y->color = RED;
                //祖父节点指向当前节点
                z = z->parent->parent;
            }
            else
            {
                if (z = z->parent->right)
                {
                    z = z->parent;
                    left_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(T, z->parent->parent);
            }
        }
        else if (z->parent == z->parent->parent->right)
        {
            
        }
    }
}