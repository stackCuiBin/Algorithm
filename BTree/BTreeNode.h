/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-09-01 01:47:14
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-10 02:44:52
 */

#ifndef BTREENODE_H
#define BTREENODE_H

template < typename T >
class BTreeNode
{
protected:
    BTreeNode(const BTreeNode<T>&);
    BTreeNode& operator = (const BTreeNode<T>&);

public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;
    BTreeNode<T>* parent;
    T value;
    
    BTreeNode()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

#endif // BTREENODE_H