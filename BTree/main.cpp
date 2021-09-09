/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-09-09 23:05:10
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-10 03:02:36
 */

#include <iostream>

#include "BTreeNode.h"

using namespace std;

/*
 * 创建出来的树图：
                    0
                 /     \
                1       2
               /      /   \
              3      4     5
               \    /     /
                6  7     8
 */

template < typename T >
BTreeNode<T>* createTree()
{
    static BTreeNode<T> ns[9];

    for (int i = 0; i < 9; i++) {
        ns[i].value = i;
        ns[i].parent = NULL;
        ns[i].left = NULL;
        ns[i].right = NULL;
    }

    ns[0].left = &ns[1];
    ns[0].right = &ns[2];
    ns[1].parent = &ns[0];
    ns[2].parent = &ns[0];

    ns[1].left = &ns[3];
    ns[3].parent = &ns[1];

    ns[3].right = &ns[6];
    ns[6].parent = &ns[3];

    ns[2].left = &ns[4];
    ns[2].right = &ns[5];
    ns[4].parent = &ns[2];
    ns[5].parent = &ns[2];

    ns[4].left = &ns[7];
    ns[7].parent = &ns[4];

    ns[5].left = &ns[8];
    ns[8].parent = &ns[5];

    return ns;
}

/* 中序遍历 */
template < typename T >
void printInOrder(BTreeNode<T>* node)
{
    if ( node != NULL )
    {
        printInOrder(node->left);

        cout << node->value << " ";

        printInOrder(node->right);
    }
}

/* 二叉树结点包含指向父结点的指针 */
template < typename T >
BTreeNode<T>* delOdd1(BTreeNode<T>* node)
{
    BTreeNode<T>* ret = NULL;

    if ( node != NULL )
    {
        if ( ((node->left != NULL) && (node->right == NULL)) ||
             ((node->left == NULL) && (node->right != NULL)) ) {
            BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
            BTreeNode<T>* node_child = (node->left != NULL) ? node->left : node->right;

            if ( parent != NULL ) {
                BTreeNode<T>*& parent_child = (parent->left == node) ? parent->left : parent->right;

                parent_child = node_child;
                node_child->parent = parent;
            } else {
                node_child->parent = NULL;
            }

            /* 当前结点node度为1，需要被删除，遍历到最后，返回最后一个结点 */
            ret = delOdd1(node_child);
        } else {
            delOdd1(node->left);
            delOdd1(node->right);

            /* 当前结点node度为0或者2，此结点需要保留，因此需要保存返回值 */
            ret = node;
        }
    }

    return ret;
}

/* 二叉树结点只包含指向左右孩子的指针 */
template < typename T >
void delOdd2(BTreeNode<T>*& node)
{
    if ( node != NULL ) {
        if ( ((node->left != NULL) && (node->right == NULL)) ||
             ((node->left == NULL) && (node->right != NULL)) ) {
            node = (node->left != NULL) ? node->left : node->right;
            delOdd2(node);
        } else {
            delOdd2(node->left);
            delOdd2(node->right);
        }
    }
}

/* 中序遍历退回时进行线索化, 注意pre是个指针引用，因为递归返回时需要更新后的pre值 */
template < typename T >
void inOrderThread(BTreeNode<T>* node, BTreeNode<T>*& pre)
{
    if ( node != NULL ) {
        inOrderThread(node->left, pre);

        node->left = pre;

        if ( pre != NULL ) {
            pre->right = node;
        }

        pre = node;

        inOrderThread(node->right, pre);
    }
}

/* 中序遍历线索化，借助辅助指针 */
template < typename T >
BTreeNode<T>* inOrderThread1(BTreeNode<T>* node)
{
    BTreeNode<T>* pre = NULL;

    inOrderThread(node, pre);

    while ( (node != NULL) && (node->left != NULL) ) {
        node = node->left;
    }

    return node;
}

/* 将结点node的左右子树转换为双向链表，再进行连接 */
template < typename T >
void inOrderThread(BTreeNode<T>* node, BTreeNode<T>*& head, BTreeNode<T>*& tail)
{
    if ( node != NULL ) {
        BTreeNode<T>* h = NULL;
        BTreeNode<T>* t = NULL;

        inOrderThread(node->left, h, t);

        node->left = t;

        if ( t != NULL ) {
            t->right = node;
        }

        head = (h != NULL) ? h : node;

        h = NULL;
        t = NULL;

        inOrderThread(node->right, h, t);

        node->right = h;

        if ( h != NULL ) {
            h->left = node;
        }

        tail = ( t != NULL ) ? t : node;
    }
}

template < typename T >
BTreeNode<T>* inOrderThread2(BTreeNode<T>* node)
{
    BTreeNode<T>* head = NULL;
    BTreeNode<T>* tail = NULL;

    inOrderThread(node, head, tail);

    return head;
}

int main()
{
    BTreeNode<int>* node = NULL;

    node = createTree<int>();

    printInOrder<int>(node);
    cout << endl;

    /* test delOdd1 begin */
    // node = delOdd1<int>(node);
    // printInOrder<int>(node);
    // cout << endl;

    // int a[] = {6, 7, 8};
    // for (int i = 0; i < 3; i++) {
    //     TreeNode<int>* n = node + a[i];

    //     while ( n != NULL ) {
    //         cout << n->value << " ";
    //         n = n->parent;
    //     }
    //     cout << endl;
    // }
    /* test delOdd1 end */
    
    /* test delOdd2 begin */
    delOdd2(node);
    printInOrder<int>(node);
    cout << endl;
    /* test delOdd2 begin */

    /* test inOrderThread1 begin */
    // node = inOrderThread1(node);
    // for (; node != NULL; node = node->right) {
    //     cout << node->value << " ";
    // }
    // cout << endl;
    /* test inOrderThread1 begin */

    /* test inOrderThread2 begin */
    node = inOrderThread2(node);
    for (; node != NULL; node = node->right) {
        cout << node->value << " ";
    }
    cout << endl;
    /* test inOrderThread2 begin */

    return 0;
}
