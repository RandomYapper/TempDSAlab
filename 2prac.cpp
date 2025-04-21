#include <iostream>
using namespace std;
struct node
{
    int v;
    int p;
    node *left;
    node *right;
    node *prnt;
    node(int a, int b)
    {
        v = a;
        p = b;
        left = right = prnt = nullptr;
    }
};
class pq
{
public:
    node *head = nullptr;
    void insert(node *&head, int v, int p)
    {
        if (!head)
        {
            head = new node(v, p);
        }
        else
        {
            node *ptr = head;
            node *prev = nullptr;
            int j;
            while (ptr)
            {
                prev = ptr;
                if (ptr->p < p)
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
            if (j)
            {
                prev->right = new node(v, p);
                prev->right->prnt = prev;
            }
            else
            {
                prev->left = new node(v, p);
                prev->left->prnt = prev;
            }
        }
    }
    void search(node *head, int val, int &count, int &found, node *&foundptr)
    {
        if (head && found)
        {
            count++;
            search(head->left, val, count, found, foundptr);
            if (head->v == val)
            {
                found = 0;
                foundptr = head;
            }
            search(head->right, val, count, found, foundptr);
        }
    }
    void inorder(node *head)
    {
        if (!head)
            return;
        inorder(head->left);
        cout << '{' << head->v << " " << head->p << '}' << " ";
        inorder(head->right);
    }
    node *treeMin(node *root)
    {
        node *temp = root;
        if (!temp)
            return nullptr;
        while (temp->left)
        {
            temp = temp->left;
        }
        return temp;
    }
    void deleteMin(node *root)
    {
        node *mini = treeMin(root);
        if (mini->right)
        {
            mini->prnt->left = mini->right;
            mini->right->prnt = mini->prnt;
            delete (mini);
        }
        else
        {
            mini->prnt->left = nullptr;
            delete (mini);
        }
    }
};
int main()
{
    pq m;
    node *&root = m.head;

    // Insert elements (value, priority)
    m.insert(root, 50, 3);
    m.insert(root, 20, 1);
    m.insert(root, 70, 5);
    m.insert(root, 10, 0); // Highest priority
    m.insert(root, 40, 2);
    m.insert(root, 60, 4);

    cout << "Initial Priority Queue (in-order by priority):\n";
    m.inorder(root);
    cout << "\n\n";

    // Search for an element
    int comparisons = 0;
    int found = 1;
    node *foundptr = nullptr;
    int searchVal = 60;
    m.search(root, searchVal, comparisons, found, foundptr);

    if (foundptr)
        cout << "Element " << searchVal << " found with priority " << foundptr->p
             << " after " << comparisons << " comparisons.\n";
    else
        cout << "Element " << searchVal << " not found after " << comparisons << " comparisons.\n";

    // Delete minimum (highest priority)
    cout << "\nDeleting element with highest priority (min priority)...\n";
    m.deleteMin(root);

    cout << "Priority Queue after deleting min:\n";
    m.inorder(root);
    cout << "\n";

    return 0;
}
