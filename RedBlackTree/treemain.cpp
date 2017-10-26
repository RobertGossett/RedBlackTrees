#include "tree.h"
#include "redblacktree.h"

using namespace std;

int main(){
    
    RedBlackTree<int> my_tree;
    cout << "Enter 10 numbers: ";
    for(int i = 0; i < 10; i++){
        int x;
        cin >> x;
        my_tree.Red_Black_Insert(x);
    }
    int toDelete = 8;
    cout << "Main output of tree after inserts: " << endl;
    my_tree.Print_Treeorder();
    my_tree.Red_Black_Delete(toDelete);
    cout << "Main output of tree after deleting " << toDelete << ":" << endl;
//    my_tree.Red_Black_Delete(10);
    my_tree.Print_Treeorder();

    
    return 0;
//    RedBlackTree<int> my_tree;
//    cout << "Enter 10 numbers: ";
//    for(int i = 0; i < 10; i++){
//        int x;
//        cin >> x;
//        my_tree.Red_Black_Insert(x);
//    }
//    
//    my_tree.Print_Inorder();
//    my_tree.Red_Black_Insert(11);
//    my_tree.Red_Black_Insert(41);
//    cout << endl << "In order: ";
//    
//    my_tree.Print_Inorder(); cout << " yay " << endl;
//    
//    int depth = 6;
//    cout << endl << "at depth " << depth << ": ";
//    my_tree.Print_Nodes_At_Depth(depth);
//    cout << endl;
//    my_tree.Print_Nodes_By_Depth();
//    cout << endl << "Pre Order: " << endl;
//    my_tree.Print_Preorder();
//    cout << endl << "Post Order: ";
//    my_tree.Print_Postorder();
//    
//    return 0;
}
