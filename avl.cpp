#include <iostream>
using namespace std;
struct node
{
    int val;
    int height;
    node *right;
    node *left;
    node *parent;
    node(int key) : val(key), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};
class avl
{
public:
    node *root;
    avl(int a)
    {
        root = new node(a);
    };
    int height(node *n)
    {
        return n ? n->height : 0;
    }
    int isB(node *n)
    {
        return n ? height(n->left) - height(n->right) : 0;
    }
    void updateHeight(node *n)
    {
        if (n)
        {
            n->height = 1 + max(height(n->right), height(n->left));
        }
    }
    node *rightRotate(node *y)
    {
        node *x = y->left;
        node *t1 = x->right;
        x->parent = y->parent;
        y->parent = x;
        y->left = t1;
        x->right = y;
        if (t1)
            t1->parent = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }
    node *leftRotate(node *y)
    {
        node *x = y->right;
        node *x1 = x->left;
        y->right = x1;
        if (x1)
            x1->parent = y;
        x->left = y;
        x->parent = y->parent;
        y->parent = x;
        updateHeight(y);
        updateHeight(x);
        return x;
    }
    node *rightLeftRotate(node *y)
    {
        node *x1 = y->right;
        y->right = rightRotate(x1);
        if (y->right)
            y->right->parent = y;
        return leftRotate(y);
    }
    node *leftRightRotate(node *y)
    {
        node *x1 = y->left;
        y->left = leftRotate(x1);
        if (y->left)
            y->left->parent = y;
        return rightRotate(y);
    }
    node *insert(node *root, int key)
    {
        if (!root)
            return new node(key);
        if (key < root->val)
        {
            root->left = insert(root->left, key);
            if (root->left)
                root->left->parent = root;
        }
        else
        {
            root->right = insert(root->right, key);
            if (root->right)
                root->right->parent = root;
        }
        updateHeight(root);

        int balance = isB(root);
        if (balance > 1 && key < root->left->val)
        {
            return rightRotate(root);
        }
        if (balance > 1 && key > root->left->val)
        {
            return leftRightRotate(root);
        }
        if (balance < -1 && key > root->right->val)
        {
            return leftRotate(root);
        }
        if (balance < -1 && key < root->right->val)
        {
            return rightLeftRotate(root);
        }
        return root;
    }
    node *deleteNode(node *root, int key)
    {
        if (!root)
            return nullptr;

        // Step 1: Normal BST Deletion
        if (key < root->val)
        {
            root->left = deleteNode(root->left, key);
            if (root->left)
                root->left->parent = root;
        }
        else if (key > root->val)
        {
            root->right = deleteNode(root->right, key);
            if (root->right)
                root->right->parent = root;
        }
        else
        {
            // Node with one child or no child
            if (!root->left || !root->right)
            {
                node *temp = root->left ? root->left : root->right;
                if (!temp)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                {
                    temp->parent = root->parent;
                    *root = *temp; // Copy contents
                }
                delete temp;
            }
            else
            {
                // Node with two children: Get inorder successor
                node *temp = root->right;
                while (temp->left)
                    temp = temp->left;
                root->val = temp->val;
                root->right = deleteNode(root->right, temp->val);
                if (root->right)
                    root->right->parent = root;
            }
        }

        if (!root)
            return nullptr;

        // Step 2: Update height
        updateHeight(root);

        // Step 3: Check balance and rotate
        int balance = isB(root);

        // Left Left
        if (balance > 1 && isB(root->left) >= 0)
            return rightRotate(root);

        // Left Right
        if (balance > 1 && isB(root->left) < 0)
            return leftRightRotate(root);

        // Right Right
        if (balance < -1 && isB(root->right) <= 0)
            return leftRotate(root);

        // Right Left
        if (balance < -1 && isB(root->right) > 0)
            return rightLeftRotate(root);

        return root;
    }
};
bool searchNode(node *root, int key)
{
    if (!root)
        return false;
    if (root->val == key)
        return true;
    if (key < root->val)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}
void inorder(node *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// Wrapper (if you want to call it on your avl instance)
void printInorder(avl &tree)
{
    inorder(tree.root);
    cout << "\n";
}
// Simple function to print the tree sideways (root at the left)
void printTree(node *root, int space = 0, int indent = 6)
{
    if (!root)
        return;

    // Increase distance between levels
    space += indent;

    // Print right subtree first (to show top of the tree)
    printTree(root->right, space);

    // Print current node after space
    cout << endl;
    for (int i = indent; i < space; i++)
        cout << " ";
    cout << root->val << "(h=" << root->height << ", p=" << (root->parent ? root->parent->val : -1) << ")" << endl;

    // Print left subtree
    printTree(root->left, space);
}

int main()
{
    avl tree(10);
    cout << "Initial tree:\n";
    printTree(tree.root);

    int to_insert[] = {20, 30, 5, 4, 15, 25, 27};
    for (int k : to_insert)
    {
        cout << "\n--- Inserting " << k << " ---\n";
        tree.root = tree.insert(tree.root, k);
        printTree(tree.root); // Check the tree after each insertion
    }
    cout << "\n--- Deleting 20 ---\n";
    tree.root = tree.deleteNode(tree.root, 20);
    printTree(tree.root);

    cout << "\n--- Deleting 5 ---\n";
    tree.root = tree.deleteNode(tree.root, 5);
    printTree(tree.root);

    return 0;
}
