
#include <iostream>
using namespace std;

struct node
{
    int v;
    int p;
    node *left;
    node *right;
    node *parent;
    node(int value, int priority)
    {
        v = value;
        p = priority;
        left = right = parent = nullptr;
    }
};

void insertion(node *&root, int val, int priority)
{
    node *temp = new node(val, priority);
    node *ptr = root;
    node *prev = nullptr;
    int j;

    if (root == nullptr)
    {
        root = temp;
        return;
    }
    while (ptr)
    {
        prev = ptr;
        if (ptr->p < priority)
        {
            ptr = ptr->right;
            j = 1;
        }
        else
        {
            ptr = ptr->left;
            j = 0;
        }
    }
    if (j == 1)
    {
        prev->right = temp;
        temp->parent = prev;
    }
    else
    {
        prev->left = temp;
        temp->parent = prev;
    }
}

node *search(node *&root, int val, int &count, int &found, node *&foundptr)
{
    if ((root) && (found == 0))
    {
        count++;
        search(root->left, val, count, found, foundptr);
        if (root->v == val)
        {
            found = 1;
            foundptr = root;
        }
        search(root->right, val, count, found, foundptr);
    }
}

void inorder(node *&root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->v << " " << root->p << endl;
        inorder(root->right);
    }
}
void rinorder(node *&root)
{
    if (root)
    {
        rinorder(root->right);
        cout << root->v << " " << root->p << endl;
        rinorder(root->left);
    }
}

void transplant(node *&toreplace, node *&replacewith)
{
    if (toreplace == nullptr)
    {
        cout << "Nothing to replace." << endl;
        return;
    }
    if (toreplace->parent == nullptr)
    {
        toreplace = replacewith;
    }
    else if (toreplace->parent->left == toreplace)
    {
        toreplace->parent->left = replacewith;
    }
    else
    {
        toreplace->parent->right = replacewith;
    }
    if (replacewith)
    {
        replacewith->parent = toreplace->parent;
    }
}

node *treeMin(node *&root)
{
    node *temp = root;
    if (!temp)
    {
        cout << "cant find min in Empty" << endl;
        return nullptr;
    }
    while (temp->left)
    {
        temp = temp->left;
    }
    return temp;
}

void deletion(node *&root)
{
    node *leftest = treeMin(root);
    transplant(leftest, leftest->right);
}

int main()
{

    node *root = nullptr;
    insertion(root, 10, 10);
    insertion(root, 1, 5);
    insertion(root, 15, 15);
    insertion(root, 12, 12);
    insertion(root, 1, 7);
    insertion(root, 1, 1);
    insertion(root, 17, 17);

    rinorder(root);

    // int count =0 ;
    // int found =0 ;
    // node * foundptr ;
    // search(root , 12 ,count ,found,foundptr);
    // cout<< found << " "<<count <<endl ;
    // cout << foundptr->v <<endl ;
    // deletion(root);
    // deletion(root);
    // rinorder(root);

    return 0;
}
