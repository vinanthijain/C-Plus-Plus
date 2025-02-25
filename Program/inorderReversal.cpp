#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
class TreeNode{
    public:
    int val;
    TreeNode *root;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int i):val(i),left(nullptr),right(nullptr){}
};
void inorder(TreeNode* root){
    if(root==nullptr)
        return;
    inorder(root->left);
    cout<<root->val<<endl;
    inorder(root->right);
}
TreeNode* insert(TreeNode* node, int val){
    if(node == nullptr)
        return new TreeNode(val);
    if(val<node->val){
        node->left=insert(node->left,val);
    }else
    {
        root->right=insert(node->right,val);
    }
    return node;
}
int main(){
    /*TreeNode* root=new TreeNode(1);
    root->left=new TreeNode(2);
    root->right=new TreeNode(3);
    root->left->left=new TreeNode(4);
    root->left->right=new TreeNode(5);
    inorder(root);*/

    TreeNode* root=nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    inorder(root);
}