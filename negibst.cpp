#include <iostream>
using namespace std;

class Node
{
public:
    int value;
    Node *left;
    Node *right;
    Node *parent;

    Node(int n)
    {
        value = n;
        left = right = parent = nullptr;
    }
};

void insert(Node *&root)
{
    int n;
    cout << "Enter a number :" << endl;
    cin >> n;
    Node *mover = root;
    Node *newNode = new Node(n);
    if (root == nullptr)
    {
        root = newNode;
        return;
    }
    Node *prev = nullptr;
    int p = 0;
    while (mover)
    {
        prev = mover;
        if (mover->value < n)
        {
            mover = mover->right;
            p = 1;
        }
        else
        {
            mover = mover->left;
            p = 0;
        }
    }
    if (p == 1)
    {
        prev->right = newNode;
    }
    else
        prev->left = newNode;
    newNode->parent = prev;
}

Node *search(Node *&root, int n)
{

    Node *mover = root;
    while (mover && mover->value != n)
    {
        if (mover->value < n)
        {
            mover = mover->right;
        }
        else
        {
            mover = mover->left;
        }
    }
    if (mover == nullptr)
        cout << "Element not found" << endl;
    else
    {
        cout << "Element found : " << endl;
        if (mover->parent != nullptr)
            cout << "\n its parents:" << mover->parent->value;
        if (mover->left != nullptr)
            cout << "\n its left:" << mover->left->value;
        if (mover->right != nullptr)
            cout << "\n its right:" << mover->right->value << endl;
    }
    return mover;
}

void inorder(Node *&root)
{
    if (root)
    {
        inorder(root->left);
        cout << (root->value) << endl;
        inorder(root->right);
    }
}

void preorder(Node *&root)
{
    if (root)
    {
        cout << (root->value) << endl;
        preorder(root->left);

        preorder(root->right);
    }
}

void postorder(Node *&root)
{
    if (root)
    {
        postorder(root->left);

        postorder(root->right);
        cout << (root->value) << endl;
    }
}

void transplant(Node *&root, Node *&toReplace, Node *&newNode)
{
    if (toReplace == nullptr)
    {
        cout << "Cant replace an empty node" << endl;
    }
    if (toReplace->parent == nullptr)
    {
        root = newNode;
    }
    else if (toReplace->parent->left == toReplace)
    {

        toReplace->parent->left = newNode;
    }
    else
    {

        toReplace->parent->right = newNode;
    }
    if (newNode)
        newNode->parent = toReplace->parent;
}

Node *treeMinimum(Node *&root)
{
    Node *mover = root;
    while (mover->left)
    {
        mover = mover->left;
    }
    return mover;
}

void deleteNode(Node *&root, int val)
{

    Node *mover = search(root, val);
    if (mover->left == nullptr)
        transplant(root, mover, mover->right);
    else if (mover->right == nullptr)
        transplant(root, mover, mover->left);
    else
    {
        Node *lastLeft = treeMinimum(mover->right);
        if (lastLeft->parent != mover)
        {
            transplant(root, lastLeft, lastLeft->right);
            lastLeft->right = mover->right;
            mover->right = lastLeft;
        }
        transplant(root, mover, lastLeft);
        lastLeft->left = mover->left;
        mover->left->parent = lastLeft;
    }
}

int main()
{
    cout << "Enter the root node:" << endl;
    int n;
    cin >> n;
    Node *root = new Node(n);
    insert(root);
    insert(root);
    insert(root);
    insert(root);
    insert(root);
    insert(root);
    insert(root);
    insert(root);
    insert(root);

    // search(root,10);

    inorder(root);
    // Node* newNode=new Node(69);
    // transplant(root,root,newNode);

    // cout<<endl;
    // preorder(root);
    // cout<<endl;
    // postorder(root);
    // cout<<endl;
    // inorder(root);
    // cout<<endl;

    deleteNode(root, 70);

    inorder(root);
}