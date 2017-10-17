#include "tree.h"

using namespace std;

int main(){
    Tree<int> my_tree;
    cout << "Enter 10 numbers: ";
    for(int i = 0; i < 10; i++){
        int x;
        cin >> x;
        my_tree.Insert(x);
    }
    
    my_tree.Print_Inorder();
    my_tree.Insert(11);
    cout << endl << "In order: ";
    
    my_tree.Print_Inorder(); cout << " yay " << endl;
    
    int depth = 6;
    cout << endl << "at depth " << depth << ": ";
    my_tree.Print_Nodes_At_Depth(depth);
    cout << endl;
    my_tree.Print_Nodes_By_Depth();
    cout << endl << "Pre Order: ";
    my_tree.Print_Preorder();
    cout << endl << "Post Order: ";
    my_tree.Print_Postorder();
    
    return 0;
}
