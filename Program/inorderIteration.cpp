#include<iostream>
#include<stack>
using namespace std;
class TreeNode{
    public:
    int val;
    TreeNode *root;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int i):val(i),left(nullptr),right(nullptr){}
};
void inorder(TreeNode* currroot){
    stack<TreeNode*> stk;
    TreeNode* root=currroot;
    while(root!=nullptr || !stk.empty()){
        while(root!=nullptr){
            stk.push(root);
            root=root->left;
        }
        root=stk.top();
        stk.pop();
        cout<<root->val<<endl;
        root=root->right;
    }
}
int main()
{
    TreeNode *root=new TreeNode(1);
    root->left=new TreeNode(2);
    root->right=new TreeNode(3);
    root->left->left=new TreeNode(4);
    root->left->right=new TreeNode(5);
    inorder(root);
}