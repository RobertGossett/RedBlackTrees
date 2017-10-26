#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "redblacktreenode.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Definition of a Binary Search RedBlackTree class
template <typename T>
class RedBlackTree{
public:
    // default constructor, sets the root to NULL
    RedBlackTree();
    // copy constructor, deep copies the other RedBlackTree
    RedBlackTree(const RedBlackTree& other);
    
    // destructor, recursively destroys all nodes
    ~RedBlackTree();
    
    // Insert item x into the correct position in the RedBlackTree and fix the tree with helper
    void Red_Black_Insert(const T& x);
    
    // delets (a copy of) item x from the RedBlackTree.  Returns true if it's found,
    // False otherwise
    bool Red_Black_Delete(const T& x);
    
    // Determines whether item x is in the RedBlackTree.  Returns true if found, false
    // otherwise
    bool Find(const T& x) const;
    
    // returns the height of the longest branch
    int Height() const;
    
    // dumps all items in the RedBlackTree into a sorted vector
    void Dump_To_Vector(vector<T>& V) const;
    
    // prints all the values at a given depth
    void Print_Nodes_At_Depth(int d) const;
    
    // prints all the nodes by there depth
    void Print_Nodes_By_Depth() const;
    
    string Path_To_Item(const T& x) const;
    
    
    // Outputs the nodes of the RedBlackTree in order (Left subRedBlackTree, then the node, then
    // the right subRedBlackTree)
    void Print_Inorder() const;
    
    //outputs the actual tree
    void Print_Treeorder() const;
    
    // Outputs the nodes of the RedBlackTree in order (Node, then the left sub RedBlackTree, then
    // the right subRedBlackTree)
    void Print_Preorder() const;
    
    // Outputs the nodes of the RedBlackTree in order (Left subRedBlackTree, then the right subRedBlackTree, then
    // the node)
    void Print_Postorder() const;
    
private:
    RedBlackTreeNode<T>* root;
    int leftH;
    int rightH;
    int level;
    string path;
    
    
    
    // here is where we'll put the private helper functions for all of the
    // elements of the RedBlackTree
    
    // Fixes the red-black tree after inserting a new node into the tree
    void Red_Black_Insert_Fixup(RedBlackTreeNode<T>* source);
    
    // fixes the red-black tree after deleting a node from the tree
    void Red_Black_Delete_Fixup(RedBlackTreeNode<T>* source, bool childPosition);
    
    // Left rotate. Insert left rotates around source
    void Left_Rotate(RedBlackTreeNode<T>* source);
    
    //right rotate. Insert right rotates around source's grandparen
    void Right_Rotate(RedBlackTreeNode<T>* source);
    
    // Creates a new set of nodes that is a deep copy of the RedBlackTree rooted at
    // "source".  Returns a pointer to the root of the copy
    RedBlackTreeNode<T>* Copy_RedBlackTree(RedBlackTreeNode<T>* source);
    
    // recursively deletes all nodes in the subRedBlackTree pointed at by "source"
    // This includes the source node itself.
    void Delete_RedBlackTree(RedBlackTreeNode<T>* source);
    
    // Prints the nodes of the RedBlackTree in LNR order starting wth "source"
    void Print_Inorder_Helper(RedBlackTreeNode<T>* source) const;
    
    // prints all the nodes at level d
    void Print_Depth_Helper(RedBlackTreeNode<T>* source, int d) const;
    
    // prints the nodes starting from root, then left children, then right children, and so on
    void Print_Treeorder_Helper(RedBlackTreeNode<T>* source, int depth) const;
    
    // Prints the nodes of the RedBlackTree in NLR order starting with source
    void Print_Preorder_Helper(RedBlackTreeNode<T>* source) const;
    
    
    // Prints the nodes of the RedBlackTree in LRN order starting with source
    void Print_Postorder_Helper(RedBlackTreeNode<T>* source) const;
    
    // semi recursively sets the string to the path
    string Path_Helper(RedBlackTreeNode<T>* source, const T& x, string path) const;
    
    // Recursievely finds x in the subRedBlackTree rooted at "source".  Returns true if it's there,
    // false otherwise
    bool Find_Helper(RedBlackTreeNode<T>* source, const T& x) const;
    
    // recursively initializes the vector for vector dump
    void Vector_Helper(RedBlackTreeNode<T>* source, vector<T>& v) const;
    
    // Deletes node "kill" with parent "parent" from the RedBlackTree
    RedBlackTreeNode<T>* Delete_Node(RedBlackTreeNode<T>* parent, RedBlackTreeNode<T>* kill);
    
    // Returns the parent of the position we'll delete x.  Returns NULL if no node with x exists
    RedBlackTreeNode<T>* Find_Delete_Position(RedBlackTreeNode<T>* cur, const T& x) const;
    
    // Finds the position x will be inserted into the search RedBlackTree.  Returns the parent of that position
    RedBlackTreeNode<T>* Find_Insert_Position(RedBlackTreeNode<T>* p, const T& x) const;
    
    
};


// default constructor, sets the root to NULL.
// Note that "root== NULL" will be frequently be used to see if a RedBlackTree is empty
// So we should make sure our other functions (especially Delete) maintain
// this propoerty
template <typename T>
RedBlackTree<T>::RedBlackTree(){
    root = NULL;
    leftH = 0;
    rightH = 0;
    level = 0;
    path = "";
}

// copy constructor, calls a deep copy helper function
template <typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& other){
    if(other.root == NULL){ // are they empty?
        root = NULL;
        leftH = other.leftH;
        rightH = other.rightH;
        level = other.level;
    }
    else{
        root = new RedBlackTreeNode<T>;
        root->set_item(other.root->get_item());
        root->set_left(Copy_RedBlackTree(other.root->get_left()));
        root->set_right(Copy_RedBlackTree(other.root->get_right()));
        leftH = other.leftH;
        rightH = other.rightH;
        
    }
}

// Destructor, recursively destroys nodes in both subRedBlackTrees
template <typename T>
RedBlackTree<T>::~RedBlackTree(){
    if(root != NULL){ // don't delete an empty RedBlackTree
        Delete_RedBlackTree(root->get_left());
        root->set_left(NULL);
        Delete_RedBlackTree(root->get_right());
        root->set_right(NULL);
        delete(root);
        root = NULL;
    }
}


// Red_BlackInsert: Inserts x into the RedBlackTree at the position requested.  Keeps the nodes
// in a RedBlackTree with the RedBlackTree property
template <typename T>
void RedBlackTree<T>::Red_Black_Insert(const T& x){
    RedBlackTreeNode<T>* source = new RedBlackTreeNode<T>();
    if(root == NULL){ // create a new root
        root = new RedBlackTreeNode<T>;
        root->set_item(x);
        root->set_parent(NULL);
        root->set_left(NULL);
        root->set_right(NULL);
        root->set_color(false);
        root->set_black_height(0);
        leftH = 1;
        rightH = 1;
        level = 1;
    }
    else{
        RedBlackTreeNode<T>* parent = Find_Insert_Position(root, x);
        RedBlackTreeNode<T>* new_guy = new RedBlackTreeNode<T>;
        new_guy->set_item(x);
        new_guy->set_parent(parent);
        new_guy->set_left(NULL);
        new_guy->set_right(NULL);
        new_guy->set_color(false);
        if(parent->get_item() >= x){ // x goes on the left
            parent->set_left(new_guy);
            new_guy->set_as_left_child();
            new_guy->set_level(parent->get_level()+1);
            if(parent->is_black())
                new_guy->set_black_height(parent->get_black_height() + 1);
            else
                new_guy->set_black_height(parent->get_black_height());
            
            //            if(parent->get_right() == NULL)
            leftH++;
            source = new RedBlackTreeNode<T>(new_guy);
            
        }
        else{
            parent->set_right(new_guy);
            new_guy->set_as_right_child();
            new_guy->set_level(parent->get_level()+1);
            if(parent->is_black())
                new_guy->set_black_height(parent->get_black_height() + 1);
            else
                new_guy->set_black_height(parent->get_black_height());
            rightH++;
            source = new RedBlackTreeNode<T>(new_guy);
        }
        
        cout << "Before fixup: " << endl;
        Print_Treeorder();
        
        Red_Black_Insert_Fixup(new_guy);
        
        cout << "After fixup: " << endl;
        Print_Treeorder();
    }
    
}

template <typename T>
void RedBlackTree<T>::Red_Black_Insert_Fixup(RedBlackTreeNode<T> *source){
    while(source->get_parent()!=NULL && !source->get_parent()->is_black()){ // while parent is red
        
        if(source->get_parent()->is_left()){ // if the parent is a left child
            RedBlackTreeNode<T>* uncle = source->get_parent()->get_parent()->get_right(); // set the uncle to the grandparent's right child
            if(uncle!=NULL){
                if(!uncle->is_black()){ // if the uncle is red
                    uncle->set_color(true); // make the uncle black
                    source->get_parent()->set_color(true); // make the parent black
                    source = source->get_parent()->get_parent(); // set source to the grandparent
                    source->set_color(false); // make source, the old grandparent, red
                }
                else { // the uncle is black
                    if(source->is_right()){ // if source is a right child
                        source = source->get_parent(); // set source to the parent
                        Left_Rotate(source); // left rotate around source, the old parent
                    }// now source is a left child
                    source->get_parent()->set_color(true); // set sources parent to black
                    source->get_parent()->get_parent()->set_color(false); // set the grandparent to red
                    Right_Rotate(source->get_parent()->get_parent()); // right rotate around the grandparent
                    
                }
            }
            else { // the uncle is black
                if(source->is_right()){ // if source is a right child
                    source = source->get_parent(); // set source to the parent
                    Left_Rotate(source); // left rotate around source, the old parent
                }// now source is a left child
                source->get_parent()->set_color(true); // set sources parent to black
                source->get_parent()->get_parent()->set_color(false); // set the grandparent to red
                Right_Rotate(source->get_parent()->get_parent()); // right rotate around the grandparent
                
            }
        }
        else// the parent is a right child
            if(source->get_parent()->is_right()){
                RedBlackTreeNode<T>* uncle = source->get_parent()->get_parent()->get_left(); // set the uncle to the grandparent's left childc
                if(uncle != NULL){
                    if(!uncle->is_black()){ // if the uncle is red
                        uncle->set_color(true); // make the uncle black
                        source->get_parent()->set_color(true); // make the parent black
                        source = source->get_parent()->get_parent(); // set source to the grandparent
                        source->set_color(false); // make source, the old grandparent, red
                    }
                    else { // the uncle is black
                        if(source->is_left()){ // if source is a left child
                            source = source->get_parent(); // set source to the parent
                            Right_Rotate(source); // left rotate around source, the old parent
                        }// now source is a left child
                        source->get_parent()->set_color(true); // set sources parent to black
                        source->get_parent()->get_parent()->set_color(false); // set the grandparent to red
                        Left_Rotate(source->get_parent()->get_parent()); // right rotate around the grandparent
                        
                    }
                }
                else { // the uncle is black
                    if(source->is_left()){ // if source is a left child
                        source = source->get_parent(); // set source to the parent
                        Right_Rotate(source); // left rotate around source, the old parent
                    }// now source is a left child
                    source->get_parent()->set_color(true); // set sources parent to black
                    source->get_parent()->get_parent()->set_color(false); // set the grandparent to red
                    Left_Rotate(source->get_parent()->get_parent()); // right rotate around the grandparent
                    
                }
                
                
            }
            else{
                root->set_color(true);
            }
    }
    
    root->set_color(true);
}

template <typename T>
void RedBlackTree<T>::Red_Black_Delete_Fixup(RedBlackTreeNode<T> *source, bool childPosition){
    RedBlackTreeNode<T>* realSource;
    if(childPosition){ // if we need the right child for fixup
        //        realSource = source->get_right();
        if(source->get_right() == NULL){ // if the right is equal to null create a new "NULL" node so that we can fixup without errors.
            source->set_right(new RedBlackTreeNode<T>());
            realSource = source->get_right();
            realSource->set_as_right_child();
            realSource->set_parent(source);
            realSource->set_color(true);
            source= realSource;
        }
        else
            source = source->get_right();
    }
    
    else {
        
        if(source->get_left() == NULL){// if the left is equal to null create a new "NULL" node so that we can fixup without null errors.
            source->set_left(new RedBlackTreeNode<T>());
            realSource = source->get_left();
            realSource->set_as_left_child();
            realSource->set_parent(source);
            realSource->set_color(true);
            source= realSource;
        }
        else
            source = source->get_left();
    }
    
    
    
    while(source != root && source->is_black()){ // while the root is
        if(source->is_left()){ // if source is a left child
            RedBlackTreeNode<T>* sibling = source->get_parent()->get_right(); // get sources sibling
            if(!sibling->is_black()){ // if the sibling is red
                sibling->set_color(true); // set it's color to black
                source->get_parent()->set_color(false); // set the parents color to red
                Left_Rotate(source->get_parent()); // left rotate around the parent
                sibling=source->get_parent()->get_right(); // set sibling to sources new sibling
            }
            if((sibling->get_left() == NULL || sibling->get_left()->is_black())
               && (sibling->get_right() == NULL || sibling->get_right()->is_black())){ // if siblings children are black
                sibling->set_color(false); // set siblings color to red
                source = source->get_parent(); // set source to sources parent
            }
            else {// otherwise
                if(sibling->get_right() == NULL || sibling->get_right()->is_black()){ // iff siblings right is black
                    sibling->get_left()->set_color(true); //set it's left to b lack
                    sibling->set_color(false); // set sibling to red
                    Right_Rotate(sibling); // right rotate around the sibling
                    sibling = source->get_parent()->get_right(); // set the sibling to sources new sibling
                }
                bool siblingColor = sibling->is_black();
                sibling->set_color(source->get_parent()->is_black());
                sibling->get_parent()->set_color(true);
                sibling->get_right()->set_color(true);
                Left_Rotate(source->get_parent());
                source=root;
            }
        }
        else{
            RedBlackTreeNode<T>* sibling = source->get_parent()->get_left(); // get sources sibling
            if( !sibling->is_black()){ // if the sibling is red
                sibling->set_color(true); // set it's color to black
                source->get_parent()->set_color(false); // set the parents color to red
                Right_Rotate(source->get_parent()); // right rotate around the parent
                sibling=source->get_parent()->get_left(); // set sibling to sources new sibling
            }
            if((sibling->get_left() == NULL || sibling->get_left()->is_black())
               && (sibling->get_right() == NULL || sibling->get_right()->is_black())){ // if siblings children are black
                sibling->set_color(false); // set siblings color to red
                source = source->get_parent(); // set source to sources parent
            }
            else {// otherwise
                if(sibling->get_left() == NULL || sibling->get_left()->is_black()){ // iff siblings left is black
                    sibling->get_right()->set_color(true); //set it's right to b lack
                    sibling->set_color(false); // set sibling to red
                    Left_Rotate(sibling); // left rotate around the sibling
                    sibling = source->get_parent()->get_left(); // set the sibling to sources new sibling
                }
                bool siblingColor = sibling->is_black();
                sibling->set_color(source->get_parent()->is_black());
                sibling->get_parent()->set_color(true);
                sibling->get_left()->set_color(true);
                Right_Rotate(source->get_parent());
                source=root;
            }
            
        }
        
    }
    source->set_color(true);
    if(realSource != NULL && realSource->is_right()){
        realSource->get_parent()->set_right(NULL);
    }
    else if (realSource != NULL){
        realSource->get_parent()->set_left(NULL);
    }
};

template<typename T>
void RedBlackTree<T>::Left_Rotate(RedBlackTreeNode<T> *source){
    RedBlackTreeNode<T>* old_right = source->get_right();
    
    
    source->set_right(old_right->get_left());
    
    if(old_right->get_left()!= NULL){
        old_right->get_left()->set_parent(source);
    }
    old_right->set_parent(source->get_parent());
    if(source->get_parent() == NULL)
        root = old_right;
    else if(source == source->get_parent()->get_left()){
        source->get_parent()->set_left(old_right);
    }
    else{
        source->get_parent()->set_right(old_right);
        
    }
    old_right->set_left(source);
    if(old_right->get_right() != NULL)
        old_right->get_right()->set_parent(old_right);
    source->set_parent(old_right);
    
    
}


template<typename T>
void RedBlackTree<T>::Right_Rotate(RedBlackTreeNode<T> *source){
    RedBlackTreeNode<T>* old_left = source->get_left();
    
    
    source->set_left(old_left->get_right());
    
    if(old_left->get_left()!= NULL){
        old_left->get_left()->set_parent(source);
    }
    old_left->set_parent(source->get_parent());
    if(source->get_parent() == NULL)
        root = old_left;
    
    else if(source == source->get_parent()->get_left()){
        source->get_parent()->set_left(old_left);
    }
    else{
        source->get_parent()->set_right(old_left);
        
    }
    old_left->set_right(source);
    if(old_left->get_left() != NULL)
        old_left->get_left()->set_parent(old_left);
    source->set_parent(old_left);
    
    
    
}

// Deletes a node from the RedBlackTree with value x.  Returns true if successful.
// If no item was found, returns false.
template <typename T>
bool RedBlackTree<T>::Red_Black_Delete(const T& x){
    // case 1: Deleting from an empty RedBlackTree
    RedBlackTreeNode<T>* child;
    if(root == NULL)
        return false;
    
    // case 2: Deleting the root
    if(root->get_item() == x){
        // Case 2a: Deleting the root when it's the only node in the RedBlackTree
        if(root->get_left() == NULL && root->get_right() == NULL){
            delete root;
            root = NULL;
            return true;
        }
        // case 2b: Deleting the root when it has one child
        
        
        else if(root->get_left() != NULL && root->get_right() == NULL){
            RedBlackTreeNode<T>* kill = root;
            root=root->get_left();
            root->set_color(true); // set the new roots color to black
            root->set_parent(NULL);
            child = root;
            kill->set_left(NULL);
            delete kill;
            return true;
        }
        else if(root->get_left() == NULL && root->get_right()!= NULL){
            RedBlackTreeNode<T>* kill = root;
            root = root->get_right();
            root->set_color(true); // set the new roots color to black
            root->set_parent(NULL);
            child = root;
            kill->set_right(NULL);
            delete kill;
            return true;
        }
        else{
            RedBlackTreeNode<T>* kill = root;
            RedBlackTreeNode<T>* successor = kill->get_right();
            RedBlackTreeNode<T>* new_parent = kill;
            
            
            
            while(successor->get_left() != NULL){
                new_parent = successor;
                successor = successor->get_left();
            }
            
            new_parent->set_left(NULL);
            root = successor;
            successor->set_parent(NULL);
            successor->set_right(kill->get_right());
            successor->set_left(kill->get_left());
            if(successor->get_right()!=NULL)
                successor->get_right()->set_parent(successor);
            if(successor->get_left()!=NULL)
                successor->get_left()->set_parent(successor);
            root->set_color(true);
            delete kill;
            
            return true;
        }
        
        
        // case 2c, where the root will have 2 children, can be handled like any other "the node we're deleting has 2 children"
        // case
        
        
    }
    // just in case..
    if(!Find(x))
        return false;
    
    // Next, find the node to delete (actually, it's parent)
    RedBlackTreeNode<T>* parent = Find_Delete_Position(root, x);
    // get a pointer to the node we're actually deleting
    RedBlackTreeNode<T>* kill;
    
    if(parent->get_item() >= x){
        kill = parent->get_left();
        
    }
    else{
        kill = parent->get_right();
        
    }
    
    child = Delete_Node(parent, kill); // sets child to the replacement node, or the left child of kill.
    return true;
}



// Find: finds a node with item x in the RedBlackTree.  returns true if it exists,
// returns false otherwise
template <typename T>
bool RedBlackTree<T>::Find(const T& x) const{
    return Find_Helper(root, x);
}

template <typename T>
int RedBlackTree<T>::Height() const{
    if(leftH < rightH)
        return rightH;
    else if(rightH < leftH)
        return leftH;
    else
        return leftH;
    
    
    
}


// Print-Inirder: Prints the items in the search RedBlackTree in search RedBlackTree order
template <typename T>
void RedBlackTree<T>::Print_Inorder() const{
    return Print_Inorder_Helper(root);
    cout << endl;
    
}

template <typename T>
void RedBlackTree<T>::Dump_To_Vector(vector<T>& v) const{
    return Vector_Helper(root, v);
    
}

template <typename T>
void RedBlackTree<T>::Print_Nodes_At_Depth(int d) const{
    return Print_Depth_Helper(root, d - 1);
}

template <typename T>
void RedBlackTree<T>::Print_Nodes_By_Depth() const{
    for(int i = 0; i < Height(); i++ ){
        cout << Height() << endl;
        cout << "At depth " << i + 1 << ": ";
        Print_Depth_Helper(root, i);
        cout << endl;
    }
}
template <typename T>
string RedBlackTree<T>::Path_To_Item(const T& x) const{
    return Path_Helper(root, x, path);
    
}

template <typename T>
void RedBlackTree<T>::Print_Depth_Helper(RedBlackTreeNode<T>* source, int d) const{
    if(source != NULL){
        Print_Depth_Helper(source->get_left(), d);
        if(source->get_level() == d)
            cout << source->get_item() << " ";
        Print_Depth_Helper(source->get_right(), d);
    }
}

template <typename T>
void RedBlackTree<T>::Vector_Helper(RedBlackTreeNode<T>* source, vector<T>& v) const{
    if(source != NULL){
        Vector_Helper(source->get_left(), v);
        v.push_back(source->get_item());
        
        Vector_Helper(source->get_right(), v);
        
    }
}
// Print_Inorder_Helper: Prints an LNR traversal starting at "source"
template <typename T>
void RedBlackTree<T>::Print_Inorder_Helper(RedBlackTreeNode<T>* source) const{
    if(source != NULL){
        Print_Inorder_Helper(source->get_left());
        cout << source->get_item() << " ";
        Print_Inorder_Helper(source->get_right());
    }
}

// Prints how a readable tree
template <typename T>
void RedBlackTree<T>::Print_Treeorder() const{
    Print_Treeorder_Helper(root, 0);
    cout << endl;
}

// Prints the nodes of the RedBlackTree in NLR order starting with source
template <typename T>
void RedBlackTree<T>::Print_Treeorder_Helper(RedBlackTreeNode<T>* source, int depth) const{
    if(source != NULL){
        char color;
        for(int i = 0; i <= depth; i++)
            cout << " ";
        if(source->is_black())
            color = 'B';
        else
            color = 'R';
        
        
        depth++;
        cout << source->get_item()
        << "-" << color
        << "-" << source->get_black_height() << endl;
        
        Print_Treeorder_Helper(source->get_left(), depth);
        
        Print_Treeorder_Helper(source->get_right(), depth);
        
    }
}
// Prints how we visit each item
template <typename T>
void RedBlackTree<T>::Print_Preorder() const{
    Print_Preorder_Helper(root);
    cout << endl;
}

// Prints the nodes of the tree in NLR order starting with source
template <typename T>
void RedBlackTree<T>::Print_Preorder_Helper(RedBlackTreeNode<T>* source) const{
    if(source != NULL){
        cout << source->get_item() << " ";
        Print_Preorder_Helper(source->get_left());
        Print_Preorder_Helper(source->get_right());
    }
}



// Prints how we return them
template <typename T>
void RedBlackTree<T>::Print_Postorder() const{
    return Print_Postorder_Helper(root);
    cout << endl;
}

// Prints the nodes of the RedBlackTree in LRN order starting with source
template <typename T>
void RedBlackTree<T>::Print_Postorder_Helper(RedBlackTreeNode<T>* source) const{
    if(source != NULL){
        Print_Postorder_Helper(source->get_left());
        Print_Postorder_Helper(source->get_right());
        cout << source->get_item() << " ";
    }
}

template <typename T>
string RedBlackTree<T>::Path_Helper(RedBlackTreeNode<T>* source, const T& x, string path) const{
    
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
bool RedBlackTree<T>::Find_Helper(RedBlackTreeNode<T>* source, const T& x) const{
    
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
RedBlackTreeNode<T>* RedBlackTree<T>::Delete_Node(RedBlackTreeNode<T>* parent, RedBlackTreeNode<T>* kill){
    RedBlackTreeNode<T>* fixPoint;
    bool position;
    bool originalColor = kill->is_black();
    if(kill->get_left() == NULL && kill->get_right() == NULL){
        if(kill->is_right())
            parent->set_right(NULL);
        else
            parent->set_left(NULL);
        
        delete kill;
        return NULL;
    }
    
    else if(kill->get_left() == NULL && kill->get_right()!= NULL){
        fixPoint = kill;
        position = true; // need right child for fixup
        if(kill->is_right()){
            
            parent->set_right(kill->get_right());
            parent->get_right()->set_parent(parent);
            delete kill;
        }
        else{
            parent->set_left(kill->get_right());
            parent->get_left()->set_parent(parent);
            delete kill;
        }
        
        
        
        
    }
    else if(kill->get_right() == NULL && kill->get_left() != NULL){
        fixPoint = kill;
        position = false;// need the left child for fixup
        if(kill->is_right()){
            parent->set_right(kill->get_left());
            parent->get_right()->set_parent(parent);
            delete kill;
        }
        else{
            parent->set_left(kill->get_left());
            parent->get_left()->set_parent(parent);
            delete kill;
        }
        
    }
    
    else {
        
        RedBlackTreeNode<T>* successor = kill->get_right();
        RedBlackTreeNode<T>* new_parent = kill;
        while(successor->get_left() != NULL){
            new_parent = successor;
            successor = successor->get_left();
        }
        
        fixPoint = successor;
        position = true; // need the right child for fixup
        originalColor = successor->is_black();
        successor->set_color(kill->is_black());
        
        
        if(kill->is_right()){
            parent->set_right(successor);
            successor->set_parent(parent);
            if(kill->get_right() != successor){
                successor->set_right(kill->get_right());
                new_parent->set_left(NULL);
            }
            
            successor->set_left(kill->get_left());
            if(successor->get_right()!=NULL)
                successor->get_right()->set_parent(successor);
            if(successor->get_left()!=NULL)
                successor->get_left()->set_parent(successor);
        }
        else{
            
            parent->set_left(successor);
            successor->set_parent(parent);
            if(kill->get_right() != successor){
                successor->set_right(kill->get_right());
                new_parent->set_left(NULL);
            }
            
            successor->set_left(kill->get_left());
            if(successor->get_right()!=NULL)
                successor->get_right()->set_parent(successor);
            if(successor->get_left()!=NULL)
                successor->get_left()->set_parent(successor);
        }
        delete kill;
        
        
        
    }
    
    if(originalColor)
        Red_Black_Delete_Fixup(fixPoint, position);
    
    return parent;
}






// currently does nothing



// Find_Insert_Position: Called by Insert to recursively find
// the place the item should be inserted.
//  Returns the _parent_ of the position in the
// RedBlackTree x's node should be (because the child on that side will be NULL)


template <typename T>
RedBlackTreeNode<T>* RedBlackTree<T>::Find_Insert_Position(RedBlackTreeNode<T>* p, const T& x) const{
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
// the RedBlackTree and returns a pointer to it.  Returns NULL if no node matching
// the item exists
template <typename T>
RedBlackTreeNode<T>* RedBlackTree<T>::Find_Delete_Position(RedBlackTreeNode<T>* cur, const T& x) const{
    if(cur == NULL) // shouldn't happen
        return NULL;
    if(cur->get_item() == x)
        return cur;
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


// Delete_RedBlackTree: Recursively deletes all subRedBlackTrees of "source", then deletes "source"
template <typename T>
void RedBlackTree<T>::Delete_RedBlackTree(RedBlackTreeNode<T>* source){
    RedBlackTreeNode<T>* p;
    if(source == NULL) // are they empty?
        p = NULL;
    else{
        p = source;
        
        Delete_RedBlackTree(source->get_left());
        Delete_RedBlackTree(source->get_right());
        
        
    }
    // currently does norhing
    //   cout << " deleteting RedBlackTree node "  << endl;
}


// deep copies a RedBlackTree rooted at "source".  Returns a pointer to the root of the copy
template <typename T>
RedBlackTreeNode<T>* RedBlackTree<T>::Copy_RedBlackTree(RedBlackTreeNode<T>* source){
    RedBlackTreeNode<T>* p;
    if(source == NULL) // are they empty?
        p = NULL;
    else{
        p = new RedBlackTreeNode<T>;
        p->set_item(source->get_item());
        p->set_left(Copy_RedBlackTree(source->get_left()));
        p->set_right(Copy_RedBlackTree(source->get_right()));
        p->set_level(source->get_level());
        
    }// does nothing
    return p;
}
#endif
