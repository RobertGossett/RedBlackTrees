//
//  redblacknode.h
//  RedBlackTree
//
//  Created by Robert Gossett on 10/18/17.
//  Copyright © 2017 Robert Gossett. All rights reserved.
//


#ifndef RedBlackTreeNode_H
#define RedBlackTreeNode_H
#include <cstdlib>

using namespace std;

template <typename T>
class RedBlackTreeNode{
public:
    RedBlackTreeNode();
    RedBlackTreeNode(RedBlackTreeNode<T>* other);
    ~RedBlackTreeNode();
    
    // accessors
    T get_item() const;
    RedBlackTreeNode<T>* get_parent();
    RedBlackTreeNode<T>* get_left();
    RedBlackTreeNode<T>* get_right();
    int get_level() const;
    bool is_left() const;
    bool is_right() const;
    
    bool is_black() const;
    int get_black_height() const;
    
    // mutators
    void set_as_left_child();
    void set_as_right_child();
    void set_item(const T& new_item);
    void set_level(const int& L);
    void set_parent(RedBlackTreeNode<T>* new_parent);
    void set_left(RedBlackTreeNode<T>* new_left);
    void set_right(RedBlackTreeNode<T>* new_right);
    
    
    void set_color(const bool& newIsBlack);
    void set_black_height(const int& bh);
    
private:
    T item;
    int level;
    RedBlackTreeNode<T>* parent;
    RedBlackTreeNode<T>* left;
    RedBlackTreeNode<T>* right;
    bool isLeft;
    bool isRight;
    bool isBlack;
    int blackHeight;
};


// default constrctor, sets the pointers to NULL
template <typename T>
RedBlackTreeNode<T>::RedBlackTreeNode(){
    parent = NULL;
    left = NULL;
    right = NULL;
    level = 0;
    blackHeight = 0;
    isBlack = true;
    isLeft = false;
    isRight = false;
}

template <typename T>
RedBlackTreeNode<T>::RedBlackTreeNode(RedBlackTreeNode<T>* other){
    left =  other->get_left();
    right = other->get_right();
    level = other->get_level();
    blackHeight = other->get_black_height();
    isBlack = other->is_black();
    isLeft = other->is_left();
    isRight = other->is_right();
}

// destructor.  I'll keep it like Node and not delete recursvely
template <typename T>
RedBlackTreeNode<T>::~RedBlackTreeNode(){
    left = NULL;
    right = NULL;
}

// accessor functions to get the parts of the node
template <typename T>
T RedBlackTreeNode<T>::get_item() const{
    return item;
}

template <typename T>
RedBlackTreeNode<T>* RedBlackTreeNode<T>::get_parent(){
    return parent;
}

template <typename T>
RedBlackTreeNode<T>* RedBlackTreeNode<T>::get_left(){
    return left;
}

template <typename T>
RedBlackTreeNode<T>* RedBlackTreeNode<T>::get_right(){
    return right;
}

template <typename T>
int RedBlackTreeNode<T>::get_level() const{
    return level;
}

template <typename T>
bool RedBlackTreeNode<T>::is_left() const{
    return isLeft;
}
template <typename T>
bool RedBlackTreeNode<T>::is_right() const{
    return isRight;
}

template <typename T>
bool RedBlackTreeNode<T>::is_black() const{
    return isBlack;
}

template <typename T>
int RedBlackTreeNode<T>::get_black_height() const{
    return blackHeight;
}

// mutator functions to set the parts of the node

template <typename T>
void RedBlackTreeNode<T>::set_as_left_child(){
    
    isLeft = true;
    isRight = false;
    
}

template <typename T>
void RedBlackTreeNode<T>::set_as_right_child(){
    
    isLeft = false;
    isRight = true;

}


template <typename T>
void RedBlackTreeNode<T>::set_item(const T& new_item){
    item = new_item;
}

template <typename T>
void RedBlackTreeNode<T>::set_level(const int& L){
    level = L;
}

template <typename T>
void RedBlackTreeNode<T>::set_parent(RedBlackTreeNode<T>* new_parent){
    parent = new_parent;
}

template <typename T>
void RedBlackTreeNode<T>::set_left(RedBlackTreeNode<T>* new_left){
    left = new_left;
    if(new_left != NULL)
        new_left->set_as_left_child();
    
}

template <typename T>
void RedBlackTreeNode<T>::set_right(RedBlackTreeNode<T>* new_right){
    right = new_right;
    if(new_right != NULL)
        new_right->set_as_right_child();
}

// mutator functions to set the parts of the node
template <typename T>
void RedBlackTreeNode<T>::set_color(const bool& newIsBlack){
    isBlack = newIsBlack;
}


template <typename T>
void RedBlackTreeNode<T>::set_black_height(const int& bh){
    blackHeight = bh;
}

#endif


