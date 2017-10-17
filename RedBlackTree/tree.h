#ifndef TREE_H
#define TREE_H

#include "treenode.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Definition of a Binary Search Tree class
template <typename T>
class Tree{
public:
    // default constructor, sets the root to NULL
    Tree();
    // copy constructor, deep copies the other tree
    Tree(const Tree& other);
    
    // destructor, recursively destroys all nodes
    ~Tree();
    
    // Insert item x into the correct position in the tree
    void Insert(const T& x);
    
    // delets (a copy of) item x from the tree.  Returns true if it's found,
    // False otherwise
    bool Delete(const T& x);
    
    // Determines whether item x is in the tree.  Returns true if found, false
    // otherwise
    bool Find(const T& x) const;
    
    // returns the height of the longest branch
    int Height() const;
    
    // dumps all items in the tree into a sorted vector
    void Dump_To_Vector(vector<T>& V) const;
    
    // prints all the values at a given depth
    void Print_Nodes_At_Depth(int d) const;
    
    // prints all the nodes by there depth
    void Print_Nodes_By_Depth() const;
    
    string Path_To_Item(const T& x) const;
    
    
    // Outputs the nodes of the tree in order (Left subtree, then the node, then
    // the right subtree)
    void Print_Inorder() const;
    
    // Outputs the nodes of the tree in order (Node, then the left sub tree, then
    // the right subtree)
    void Print_Preorder() const;
    
    // Outputs the nodes of the tree in order (Left subtree, then the right subtree, then
    // the node)
    void Print_Postorder() const;
    
private:
    TreeNode<T>* root;
    int leftH;
    int rightH;
    int level;
    string path;
    
    
    
    // here is where we'll put the private helper functions for all of the
    // elements of the tree
    
    // Creates a new set of nodes that is a deep copy of the tree rooted at
    // "source".  Returns a pointer to the root of the copy
    TreeNode<T>* Copy_Tree(TreeNode<T>* source);
    
    // recursively deletes all nodes in the subtree pointed at by "source"
    // This includes the source node itself.
    void Delete_Tree(TreeNode<T>* source);
    
    // Prints the nodes of the tree in LNR order starting wth "source"
    void Print_Inorder_Helper(TreeNode<T>* source) const;
    
    // prints all the nodes at level d
    void Print_Depth_Helper(TreeNode<T>* source, int d) const;
    
    // Prints the nodes of the tree in NLR order starting with source
    void Print_Preorder_Helper(TreeNode<T>* source) const;
    
    // Prints the nodes of the tree in LRN order starting with source
    void Print_Postorder_Helper(TreeNode<T>* source) const;
    
    // semi recursively sets the string to the path
    string Path_Helper(TreeNode<T>* source, const T& x, string path) const;
    
    // Recursievely finds x in the subtree rooted at "source".  Returns true if it's there,
    // false otherwise
    bool Find_Helper(TreeNode<T>* source, const T& x) const;
    
    // recursively initializes the vector for vector dump
    void Vector_Helper(TreeNode<T>* source, vector<T>& v) const;
    
    // Deletes node "kill" with parent "parent" from the tree
    void Delete_Node(TreeNode<T>* parent, TreeNode<T>* kill);
    
    // Returns the parent of the position we'll delete x.  Returns NULL if no node with x exists
    TreeNode<T>* Find_Delete_Position(TreeNode<T>* cur, const T& x) const;
    
    // Finds the position x will be inserted into the search tree.  Returns the parent of that position
    TreeNode<T>* Find_Insert_Position(TreeNode<T>* p, const T& x) const;
    
    
};


// default constructor, sets the root to NULL.
// Note that "root== NULL" will be frequently be used to see if a tree is empty
// So we should make sure our other functions (especially Delete) maintain
// this propoerty
template <typename T>
Tree<T>::Tree(){
    root = NULL;
    leftH = 0;
    rightH = 0;
    level = 0;
    path = "";
}

// copy constructor, calls a deep copy helper function
template <typename T>
Tree<T>::Tree(const Tree<T>& other){
    if(other.root == NULL){ // are they empty?
        root = NULL;
        leftH = other.leftH;
        rightH = other.rightH;
        level = other.level;
    }
    else{
        root = new TreeNode<T>;
        root->set_item(other.root->get_item());
        root->set_left(Copy_Tree(other.root->get_left()));
        root->set_right(Copy_Tree(other.root->get_right()));
        leftH = other.leftH;
        rightH = other.rightH;
        
    }
}

// Destructor, recursively destroys nodes in both subtrees
template <typename T>
Tree<T>::~Tree(){
    if(root != NULL){ // don't delete an empty tree
        Delete_Tree(root->get_left());
        root->set_left(NULL);
        Delete_Tree(root->get_right());
        root->set_right(NULL);
        delete(root);
        root = NULL;
    }
}


// Inerrt: Inserts x into the tree at the position requested.  Keeps the nodes
// in a tree with the binary search tree property
template <typename T>
void Tree<T>::Insert(const T& x){
    if(root == NULL){ // create a new root
        root = new TreeNode<T>;
        root->set_item(x);
        root->set_left(NULL);
        root->set_right(NULL);
        leftH = 1;
        rightH = 1;
        level = 1;
    }
    else{
        TreeNode<T>* parent = Find_Insert_Position(root, x);
        TreeNode<T>* new_guy = new TreeNode<T>;
        new_guy->set_item(x);
        new_guy->set_left(NULL);
        new_guy->set_right(NULL);
        if(parent->get_item() >= x){ // x goes on the left
            parent->set_left(new_guy);
            new_guy->set_level(parent->get_level()+1);
            
//            if(parent->get_right() == NULL)
                leftH++;
            
        }
        else{
            parent->set_right(new_guy);
            new_guy->set_level(parent->get_level()+1);
//            if(parent->get_left() == NULL)
                rightH++;
        }
    }
}




// Deletes a node from the tree with value x.  Returns true if successful.
// If no item was found, returns false.
template <typename T>
bool Tree<T>::Delete(const T& x){
    // case 1: Deleting from an empty tree
    if(root == NULL)
        return false;
    
    // case 2: Deleting the root
    if(root->get_item() == x){
        // Case 2a: Deleting the root when it's the only node in the tree
        if(root->get_left() == NULL && root->get_right() == NULL){
            delete root;
            root = NULL;
            return true;
        }
        // case 2b: Deleting the root when it has one child
        else{
            if(root->get_left() == NULL || root->get_right() == NULL){
                if(root->get_left() != NULL){
                    TreeNode<T>* kill = root;
                    root=root->get_left();
                    kill->set_left(NULL);
                    delete kill;
                }
                else{
                    TreeNode<T>* kill = root;
                    root = root->get_right();
                    kill->set_right(NULL);
                    delete kill;
                }
            }
        }
        // case 2c, where the root will have 2 children, can be handled like any other "the node we're deleting has 2 children"
        // case
        
    }
    // just in case..
    if(!Find(x))
        return false;
    
    // Next, find the node to delete (actually, it's parent)
    TreeNode<T>* parent = Find_Delete_Position(root, x);
    // get a pointer to the node we're actually deleting
    TreeNode<T>* kill;
    
    if(parent->get_item() >= x){
        kill = parent->get_left();
        
    }
    else{
        kill = parent->get_right();
        
    }
    
    Delete_Node(parent, kill);
    return true;
}



// Find: finds a node with item x in the tree.  returns true if it exists,
// returns false otherwise
template <typename T>
bool Tree<T>::Find(const T& x) const{
    return Find_Helper(root, x);
}

template <typename T>
int Tree<T>::Height() const{
    if(leftH < rightH)
        return rightH;
    else if(rightH < leftH)
        return leftH;
    else
        return leftH;
    
    
    
}


// Print-Inirder: Prints the items in the search tree in search tree order
template <typename T>
void Tree<T>::Print_Inorder() const{
    return Print_Inorder_Helper(root);
    cout << endl;
    
}

template <typename T>
void Tree<T>::Dump_To_Vector(vector<T>& v) const{
    return Vector_Helper(root, v);
    
}

template <typename T>
void Tree<T>::Print_Nodes_At_Depth(int d) const{
    return Print_Depth_Helper(root, d - 1);
}

template <typename T>
void Tree<T>::Print_Nodes_By_Depth() const{
    for(int i = 0; i < Height(); i++ ){
        cout << Height() << endl;
        cout << "At depth " << i + 1 << ": ";
        Print_Depth_Helper(root, i);
        cout << endl;
    }
}
template <typename T>
string Tree<T>::Path_To_Item(const T& x) const{
    return Path_Helper(root, x, path);
    
}

template <typename T>
void Tree<T>::Print_Depth_Helper(TreeNode<T>* source, int d) const{
    if(source != NULL){
        Print_Depth_Helper(source->get_left(), d);
        if(source->get_level() == d)
            cout << source->get_item() << " ";
        Print_Depth_Helper(source->get_right(), d);
    }
}

template <typename T>
void Tree<T>::Vector_Helper(TreeNode<T>* source, vector<T>& v) const{
    if(source != NULL){
        Vector_Helper(source->get_left(), v);
        v.push_back(source->get_item());
        
        Vector_Helper(source->get_right(), v);
        
    }
}
// Print_Inorder_Helper: Prints an LNR traversal starting at "source"
template <typename T>
void Tree<T>::Print_Inorder_Helper(TreeNode<T>* source) const{
    if(source != NULL){
        Print_Inorder_Helper(source->get_left());
        cout << source->get_item() << " ";
        Print_Inorder_Helper(source->get_right());
    }
}

// Prints how we visit each item
template <typename T>
void Tree<T>::Print_Preorder() const{
    Print_Preorder_Helper(root);
    cout << endl;
}

// Prints the nodes of the tree in NLR order starting with source
template <typename T>
void Tree<T>::Print_Preorder_Helper(TreeNode<T>* source) const{
    if(source != NULL){
        cout << source->get_item() << " ";
        Print_Preorder_Helper(source->get_left());
        Print_Preorder_Helper(source->get_right());
    }
}

// Prints how we return them
template <typename T>
void Tree<T>::Print_Postorder() const{
    return Print_Postorder_Helper(root);
    cout << endl;
}

// Prints the nodes of the tree in LRN order starting with source
template <typename T>
void Tree<T>::Print_Postorder_Helper(TreeNode<T>* source) const{
    if(source != NULL){
        Print_Postorder_Helper(source->get_left());
        Print_Postorder_Helper(source->get_right());
        cout << source->get_item() << " ";
    }
}

template <typename T>
string Tree<T>::Path_Helper(TreeNode<T>* source, const T& x, string path) const{
    
    if(source == NULL)
        return path;
    else if(source->get_item() == x)
        return path;
    else if(source->get_item() < x){
        path = path + "R, ";
        return Path_Helper(source->get_right(), x, path);
        
    }
    else {
        path = path + "L, ";
        return Path_Helper(source->get_left(), x, path);
    }
    
    
    
}

// Find_Helper: The pointer version of "find", passing the current node
// as a parameter
template <typename T>
bool Tree<T>::Find_Helper(TreeNode<T>* source, const T& x) const{
    
    if(source == NULL)
        return false;
    else if(source->get_item() == x)
        return true;
    else if(source->get_item() < x){
        return Find_Helper(source->get_right(), x);
        
    }
    else {
        
        return Find_Helper(source->get_left(), x);
    }
    
    
    
}




// deletes the node "kill" with parent "parent".
// I made it its own function to isolate the 3 cases
template <typename T>
void Tree<T>::Delete_Node(TreeNode<T>* parent, TreeNode<T>* kill){
    bool test;
    
    if(parent->get_left() == kill)
        test = true;
    else
        test = false;
    
    if(kill->get_left() == NULL && kill->get_right() == NULL){
        if(test){
            parent->set_left(NULL);
            delete kill;
            kill = NULL;
            
        }
        else{
            parent->set_right(NULL);
            delete kill;
            kill = NULL;
        }
    }
    
    else if(kill->get_left() == NULL && kill->get_right()!= NULL){
        if(test){
            parent->set_left(kill->get_right());
            delete kill;
            kill = NULL;
        }
        else{
            parent->set_right(kill->get_right());
            delete kill;
            kill = NULL;
            
            
        }
    }
    else if(kill->get_right() == NULL && kill->get_left() != NULL){
        if(test){
            parent->set_left(kill->get_left());
            delete kill;
            kill = NULL;
        }
        else{
            parent->set_right(kill->get_left());
            delete kill;
            kill = NULL;
            
            
        }
    }
    
    else {
        int check = 0;
        TreeNode<T>* successor = kill->get_right();
        TreeNode<T>* new_parent = kill;
        
        
        
        while(successor->get_left() != NULL){
            new_parent = successor;
            successor = successor->get_left();
            check = 1;
            
            
        }
        
        T temp =successor->get_item();
        //p->set_item(successor->get_item());
        successor->set_item(kill->get_item());
        kill->set_item(temp);
        
        Delete_Node(new_parent, successor);
        
        
    }
    
    
}






// currently does nothing



// Find_Insert_Position: Called by Insert to recursively find
// the place the item should be inserted.
//  Returns the _parent_ of the position in the
// tree x's node should be (because the child on that side will be NULL)


template <typename T>
TreeNode<T>* Tree<T>::Find_Insert_Position(TreeNode<T>* p, const T& x) const{
    if(p == NULL) // shouldn't happen
        return NULL;
    if(p->get_item() >= x){ // look left
        if(p->get_left() == NULL) // then the left child is where the new
            // node should be
            return p;
        else
            return Find_Insert_Position(p->get_left(), x);
    }
    else{ // look right
        if(p->get_right() == NULL) // then the right child is where the new node
            // should be
            return p;
        else
            return Find_Insert_Position(p->get_right(), x);
    }
}



// Find_Delete_Position- finds the parent of the node we want to delete in
// the tree and returns a pointer to it.  Returns NULL if no node matching
// the item exists
template <typename T>
TreeNode<T>* Tree<T>::Find_Delete_Position(TreeNode<T>* cur, const T& x) const{
    if(cur == NULL) // shouldn't happen
        return NULL;
    if(cur->get_item() >= x){ // look left
        if(cur->get_left()->get_item() == x) // then the left child is where the new
            //  should be
            return cur;
        else
            return Find_Delete_Position(cur->get_left(), x);
    }
    else{ // look right
        if(cur->get_right()->get_item() == x) // then the right child is where the new node
            // should be
            return cur;
        else
            return Find_Delete_Position(cur->get_right(), x);
    }
}


// Delete_Tree: Recursively deletes all subtrees of "source", then deletes "source"
template <typename T>
void Tree<T>::Delete_Tree(TreeNode<T>* source){
    TreeNode<T>* p;
    if(source == NULL) // are they empty?
        p = NULL;
    else{
        p = source;
        
        Delete_Tree(source->get_left());
        Delete_Tree(source->get_right());
        
        
    }
    // currently does norhing
    //   cout << " deleteting tree node "  << endl;
}


// deep copies a tree rooted at "source".  Returns a pointer to the root of the copy
template <typename T>
TreeNode<T>* Tree<T>::Copy_Tree(TreeNode<T>* source){
    TreeNode<T>* p;
    if(source == NULL) // are they empty?
        p = NULL;
    else{
        p = new TreeNode<T>;
        p->set_item(source->get_item());
        p->set_left(Copy_Tree(source->get_left()));
        p->set_right(Copy_Tree(source->get_right()));
        p->set_level(source->get_level());
        
    }// does nothing
    return p;
}
#endif
