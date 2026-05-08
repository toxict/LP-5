#include <iostream>
#include <stdlib.h>
#include <queue>
#include <omp.h>
using namespace std;


class node 
{
    public:
    node *left,*right;
    int data;
};

node *insert(node *root , int data)
{
    if (!root)
    {
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }
    queue<node *> q;
    q.push(root);
    
    while(!q.empty())
    {
        node *temp = q.front();
        q.pop();
        
        if (temp->left == NULL)
        {
            temp->left = new node;
            temp->left->left = NULL;
            temp->left->right = NULL;
            temp->left->data = data;
            return root;
        }
        else
        {
            q.push(temp->left);
        }
        
        if (temp->right == NULL)
        {
            temp->right = new node;
            temp->right->left = NULL;
            temp->right->right = NULL;
            temp->right->data = data;
            return root;
        }
        else
        {
            q.push(temp->right);
        }
    }
    return root;
    
};

void bfs(node *head)
{
    if(head == NULL) return;
    
    queue<node *> q;
    q.push(head);
    
    int qSize;
    int level = 0;
    while(!q.empty())
    {
        qSize = q.size();
        level++;
        cout << "Level " << level << ": " << endl;
        #pragma omp parallel for
        for(int i=0 ; i < qSize ; i++)
        {
            node* currnode;
            #pragma omp critical
            {
                currnode = q.front();
                q.pop();
                cout << "current node " << currnode->data << endl;
            }
            #pragma omp critical
            {
                if(currnode->left)
                    q.push(currnode->left);
                if(currnode->right)
                    q.push(currnode->right);
            }
            
            
        }
            
        
    }
}
int main()
{
    node *root = NULL;
    int data;
    char ans;
    
    do
    {
        cout<<"enter node value";
        cin>>data;
        
        root = insert(root,data);
        
        cout<<"for continue type y else n";
        cin>>ans;
    }while (ans == 'y' || ans == 'Y');
    
    bfs(root);
    
    return 0;
};