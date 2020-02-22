#include <iostream>
#include <algorithm>
#include <vector>
// define Nodes
using namespace std;

class AVLNode{
public:
    int val;
    AVLNode* left;
    AVLNode* right;
    // record tree height
    int height;
    AVLNode(int val, AVLNode* left, AVLNode* right): val(val), left(left), right(right), height(0){};

};

class AVLTree{
public:
    // use the def from wiki where a null leaf node's height is zero
    static int getHeight(AVLNode* T){
        return T == nullptr ? 0 : T->height;
    }
    static int getNewHeight(AVLNode* T){
        return T == nullptr? 0: max(getHeight(T->left), getHeight(T->right))+1;
    }
    // right rotate
    // for the left left situation
    static AVLNode* LL_Rotate(AVLNode* preRoot){
        AVLNode* newRoot = preRoot->left;
        preRoot->left = newRoot->right;
        newRoot->right = preRoot;
        // After rotate, recalculate the height of the preRoot and the newRoot;
        newRoot->height = getNewHeight(newRoot);
        preRoot->height = getNewHeight(preRoot);
        return newRoot;
    }

    // left rotate
    // for the right right situation
    static AVLNode* RR_Rotate(AVLNode* preRoot){
        AVLNode* newRoot = preRoot->right;
        preRoot->right = newRoot->left;
        newRoot->left = preRoot;
        // After rotate, recalculate the height of the preRoot and the newRoot;
        newRoot->height = getNewHeight(newRoot);
        preRoot->height = getNewHeight(preRoot);
        return newRoot;
    }

    // for the left right situation
    static AVLNode* LR_Rotate(AVLNode* preRoot) {
        // at this moment its left node is in a right right situation
        // first left rotate its left child
        preRoot->left = RR_Rotate(preRoot->left);
        // then itself is in a left left situation
        // do a right rotation
        return LL_Rotate(preRoot);
    }

    // for the right left situation
    static AVLNode* RL_Rotate(AVLNode* preRoot) {
        // at this moment its right node is in a left left situation
        // first right rotate its right child
        preRoot->right = LL_Rotate(preRoot->right);
        // then itself is in a left left situation
        // do a right rotation
        return RR_Rotate(preRoot);
    }

    // insert
    static AVLNode* insert(AVLNode* &root, int val){
        if(!root){
            root = new AVLNode(val, nullptr, nullptr);
            return root;
        }
        if(val < root->val){
            root->left = insert(root->left, val);
            // if the balance is broken after the insertion
            if(getHeight(root->left) - getHeight(root->right) == 2){
                if(val < root->left->val)
                    root = LL_Rotate(root);
                else
                    root = LR_Rotate(root);
            }
        }
        else if (val > root->val) {
            root->right = insert(root->right, val);
            // if the balance is broken after the insertion
            if (getHeight(root->right) - getHeight(root->left) == 2){
                if (val > root->right->val)
                    root = RR_Rotate(root);
                else
                    root = RL_Rotate(root);
            }
        }
        // we currently do not allow adding val that already exists
        else{
            // do nothing
            cout << "invalid insert" << endl;
        }

        // update tree height after insertion
        root->height = getNewHeight(root);
        return root;
    }
};

void inorder(AVLNode* root){
    if(!root) return;
    inorder(root->left);
    cout << root->val << ' ';
    inorder(root->right);
}




int main() {
    vector<int> arr = {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
//    vector<int> arr = {0,1,2,3};
    auto root = new AVLNode(arr[0], nullptr, nullptr);
    for(unsigned int i = 1; i < arr.size(); i++){
        AVLTree::insert(root, arr[i]);
    }
    inorder(root);
    return 0;
}