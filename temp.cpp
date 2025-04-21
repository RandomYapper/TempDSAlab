#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

// ----------- AVL Tree Node and Class ------------
struct Node
{
    int key;
    Node *left;
    Node *right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
public:
    Node *root = nullptr;

    void insert(int key)
    {
        root = insert(root, key);
    }

    void inOrderTraversal(Node *node, vector<int> &result)
    {
        if (!node)
            return;
        inOrderTraversal(node->left, result);
        result.push_back(node->key);
        inOrderTraversal(node->right, result);
    }

    vector<int> getSorted()
    {
        vector<int> sorted;
        inOrderTraversal(root, sorted);
        return sorted;
    }

private:
    int height(Node *n)
    {
        return n ? n->height : 0;
    }

    int getBalance(Node *n)
    {
        return n ? height(n->left) - height(n->right) : 0;
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    Node *insert(Node *node, int key)
    {
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // no duplicates

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }
};

// ----------- Insertion Sort ------------
void insertionSort(vector<int> &arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// ----------- Main Driver Code ------------
int main()
{
    srand(time(0));
    int n0 = -1;

    for (int n = 10; n <= 5000; n += 10)
    {
        // Generate random permutation
        vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            arr[i] = i + 1;
        shuffle(arr.begin(), arr.end(), default_random_engine(rand()));

        vector<int> arr1 = arr;
        vector<int> arr2 = arr;

        // Time insertion sort
        clock_t start1 = clock();
        insertionSort(arr1);
        clock_t end1 = clock();
        double timeInsert = double(end1 - start1) / CLOCKS_PER_SEC;

        // Time AVL sort
        AVLTree tree;
        clock_t start2 = clock();
        for (int x : arr2)
            tree.insert(x);
        vector<int> sorted = tree.getSorted();
        clock_t end2 = clock();
        double timeAVL = double(end2 - start2) / CLOCKS_PER_SEC;

        cout << "n = " << n << ", InsertionSort: " << timeInsert << "s, AVL: " << timeAVL << "s";

        if (timeAVL < timeInsert)
        {
            cout << " --> AVL faster ";
            if (n0 == -1)
                n0 = n;
        }
        cout << endl;
    }

    if (n0 != -1)
        cout << "\n Smallest n where AVL is faster: " << n0 << endl;
    else
        cout << "\n AVL never became faster in this range.\n";

    return 0;
}
