#ifndef TREENODE_H
#define TREENODE_H
#include <cstdlib>

using namespace std;

template <typename T>
class TreeNode{
public:
    TreeNode();
    ~TreeNode();
    
    // accessors
    T get_item() const;
    TreeNode<T>* get_left() const;
    TreeNode<T>* get_right() const;
    int get_level() const;
    
    // mutators
    void set_item(const T& new_item);
    void set_level(const int& L);
    void set_left(TreeNode<T>* new_left);
    void set_right(TreeNode<T>* new_right);
    
private:
    T item;
    int level;
    TreeNode<T>* left;
    TreeNode<T>* right;
};


// default constrctor, sets the pointers to NULL
template <typename T>
TreeNode<T>::TreeNode(){
    left = NULL;
    right = NULL;
    level = 0;
}

// destructor.  I'll keep it like Node and not delete recursvely
template <typename T>
TreeNode<T>::~TreeNode(){
    left = NULL;
    right = NULL;
}

// accessor functions to get the parts of the node
template <typename T>
T TreeNode<T>::get_item() const{
    return item;
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_left() const{
    return left;
}

template <typename T>
TreeNode<T>* TreeNode<T>::get_right() const{
    return right;
}

template <typename T>
int TreeNode<T>::get_level() const{
    return level;
}

// mutator functions to set the parts of the node
template <typename T>
void TreeNode<T>::set_item(const T& new_item){
    item = new_item;
}

template <typename T>
void TreeNode<T>::set_level(const int& L){
    level = L;
}

template <typename T>
void TreeNode<T>::set_left(TreeNode<T>* new_left){
    left = new_left;
}

template <typename T>
void TreeNode<T>::set_right(TreeNode<T>* new_right){
    right = new_right;
}

#endif
