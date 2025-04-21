#include <iostream>
using namespace std;
struct node
{
    int val;
    node *prnt;
    node *left;
    node *right;
    node(int a)
    {
        val = a;
        prnt = left = right = nullptr;
    }
};
class bst
{
public:
    node *root = nullptr;
    void insert(node *&root, int k)
    {
        if (!root)
        {
            root = new node(k);
        }
        else
        {
            if (k < root->val)
            {
                insert(root->left, k);
            }
            else
            {
                insert(root->right, k);
            }
        }
    }
    void inorder(node *root)
    {
        if (!root)
            return;
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
};
int main()
{

    bst t;
    t.insert(t.root, 10);
    t.insert(t.root, 5);
    t.insert(t.root, 15);
    t.insert(t.root, 3);
    t.insert(t.root, 7);

    cout << "In-order traversal:\n";
    t.inorder(t.root); // Output: 3 5 7 10 15
    return 0;
}