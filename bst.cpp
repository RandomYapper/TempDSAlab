#include <iostream>
#include <string>
using namespace std;

struct node
{
    node *left;
    node *right;
    node *prnt;
    int val;
    node(int key) : val(key), left(nullptr), prnt(nullptr), right(nullptr) {}
};

class bst
{
public:
    node *root = nullptr;

    void insert(int k)
    {
        if (!root)
        {
            root = new node(k);
            return;
        }
        node *ptr = root;
        node *ptrr = nullptr;
        while (ptr)
        {
            ptrr = ptr;
            if (k < ptr->val)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        if (k < ptrr->val)
        {
            ptrr->left = new node(k);
            ptrr->left->prnt = ptrr;
        }
        else
        {
            ptrr->right = new node(k);
            ptrr->right->prnt = ptrr;
        }
    }

    node *search(node *root, int k)
    {
        if (!root)
            return nullptr;
        if (root->val == k)
            return root;
        node *found = search(root->left, k);
        if (found)
            return found;
        return search(root->right, k);
    }

    void inorder(node *root)
    {
        if (!root)
            return;
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
    void deletion(int val)
    {
        node *which = search(root, val);
        node *wl = which->left;
        node *wr = which->right;
        node *wp = which->prnt;
        if (which->right)
        {
            node *ptr = which->right;
            node *ptrr;
            while (ptr->left)
            {
                ptrr = ptr;
                ptr = ptr->left;
            }
            if (wp)
                wp->left == which ? wp->left = ptr : wp->right = ptr;
            ptrr->left == ptr ? ptrr->left = ptr->right : ptrr->right = nullptr;
            ptr->right = wr;
            ptr->left = wl;
            if (which == root)
                root = ptr;
            delete (which);
        }
    }
};

int main()
{
    bst ans;
    int arr[] = {4, 3, 7, 10, 6, 2, 5, 1, 8, 9};
    for (int i = 0; i < 10; i++)
    {
        ans.insert(arr[i]);
        ans.inorder(ans.root);
        cout << endl;
    }

    node *searched = ans.search(ans.root, 5);
    cout << "left of searched is: "
         << (searched->left ? to_string(searched->left->val) : "no val")
         << " and right is: "
         << (searched->right ? to_string(searched->right->val) : "no val")
         << " and parent is: "
         << (searched->prnt ? to_string(searched->prnt->val) : "no val")
         << endl;
    ans.deletion(7);
    ans.inorder(ans.root);
}
