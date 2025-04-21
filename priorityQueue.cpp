#include <iostream>
using namespace std;
struct Node
{
    int priority;
    int value;
    Node *left;
    Node *right;

    Node(int p, int v)
    {
        priority = p;
        value = v;
        left = right = nullptr;
    }
};
class PriorityQueueBST
{
private:
    Node *root;

    Node *insert(Node *root, int priority, int value)
    {
        if (!root)
            return new Node(priority, value);
        if (priority < root->priority)
        {
            root->left = insert(root->left, priority, value);
        }
        else
        {
            root->right = insert(root->right, priority, value);
        }
        return root;
    }

    Node *findMin(Node *root)
    {
        while (root && root->left)
            root = root->left;
        return root;
    }

    Node *deleteMin(Node *root)
    {
        if (!root)
            return nullptr;
        if (!root->left)
        {
            Node *rightChild = root->right;
            delete root;
            return rightChild;
        }
        root->left = deleteMin(root->left);
        return root;
    }

    bool search(Node *root, int value, int &comparisons)
    {
        if (!root)
            return false;
        comparisons++;
        if (root->value == value)
            return true;
        if (value < root->value)
            return search(root->left, value, comparisons);
        return search(root->right, value, comparisons);
    }

    void inorder(Node *root)
    {
        if (!root)
            return;
        inorder(root->left);
        cout << "(" << root->priority << ", " << root->value << ") ";
        inorder(root->right);
    }

public:
    PriorityQueueBST()
    {
        root = nullptr;
    }

    void insert(int priority, int value)
    {
        root = insert(root, priority, value);
    }

    void deleteHighestPriority()
    {
        root = deleteMin(root);
    }

    void search(int value)
    {
        int comparisons = 0;
        bool found = search(root, value, comparisons);
        cout << "Element " << (found ? "found" : "not found")
             << " with " << comparisons << " comparisons.\n";
    }

    void display()
    {
        cout << "Inorder (priority ascending): ";
        inorder(root);
        cout << "\n";
    }
};
int main()
{
    PriorityQueueBST pq;
    pq.insert(4, 100);
    pq.insert(2, 200);
    pq.insert(5, 150);
    pq.insert(1, 300);

    pq.display();

    cout << "\nDeleting highest priority element...\n";
    pq.deleteHighestPriority();
    pq.display();

    cout << "\nSearching for 150:\n";
    pq.search(150);

    cout << "\nSearching for 999:\n";
    pq.search(999);

    return 0;
}
