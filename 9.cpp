#include <iostream>
using namespace std;

class node
{
    int data;
    int height;
    node *left;
    node *right;
    public:
    node()
    {
        data=0;
        height=1;
        left=NULL;
        right=NULL;
    }
    friend class avl;
};

class avl
{
    node *root;
    public:
    avl()
    {
        root=NULL;
    }
    int Update_height(node *c);
    int balance_factor(node *c);
    node* balance(node *c);
    node* insert(node *&c,int key);
    node* LLrotation(node *c);
    node* RRrotation(node *c);
    node* LRrotation(node *c);
    node* RLrotation(node *c);
    void inorder(node *c);
    bool search(node *c,int key);
    void level_traverse(node *c);
    node* get_root();
};

//avl functions

node* avl::get_root()
{
    return root;
}

int avl::Update_height(node *c)
{
    if(c==NULL)
    {
        return 0;
    }
    c->height=(max((Update_height(c->left)),(Update_height(c->right)))+1);
    return c->height;
}

int avl::balance_factor(node *c)
{
    if(c==NULL)
    {
        return 0;
    }
    return ((Update_height(c->left))-(Update_height(c->right)));
}

node* avl::balance(node *c)
{
    if(balance_factor(c)==2)
    {
        if(balance_factor(c->left)<0)
        {
            c=LRrotation(c);
        }
        else
        {
            c=LLrotation(c);
        }
    }
    else if(balance_factor(c)==-2)
    {
        if(balance_factor(c->right)>0)
        {
            c=RLrotation(c);
        }
        else
        {
            c=RRrotation(c);
        }
    }
    Update_height(c);
    return c;
}

node* avl::insert(node *&c,int key)
{
    if(c==NULL)
    {
        c=new node;
        c->data=key;
        return c;
    }
    if(c->data<key)
    {
        c->right=insert(c->right,key);
    }
    else if(c->data>key)
    {
        c->left=insert(c->left,key);
    }
    cout<<c->height<<endl;
    return balance(c);
    // return c;
}

node* avl::LLrotation(node *c)
{
    node *new1=c->left;
    c->left=new1->right;
    new1->right=c;
    Update_height(c);
    Update_height(new1);
    return new1;
}

node* avl::RRrotation(node *c)
{
    node *new1=c->right;
    c->right=new1->left;
    new1->left=c;
    Update_height(c);
    Update_height(new1);
    return new1;
}

node* avl::LRrotation(node *c)
{
    c->left=RRrotation(c->left);
    return LLrotation(c);
}

node* avl::RLrotation(node *c)
{
    c->right=LLrotation(c->right);
    return RRrotation(c);
}

void avl::inorder(node *c)
{
    if(c==NULL)
    {
        return;
    }
    inorder(c->left);
    cout<<c->data<<" ";
    inorder(c->right);
}

bool avl::search(node *c,int key)
{
    if(c==NULL)
    {
        return false;
    }
    else if(c->data<key)
    {
        return search(c->right,key);
    }
    else if(c->data>key)
    {
        return search(c->left,key);
    }
    else
    {
        return true;
    }
}

// void avl::level_traverse(node *c)
// {
//     if(c==NULL)
//     {
//         return;
//     }
//     node *queue[1000];
//     int front=0;
//     int rear=0;
//     queue[rear++]=c;
//     while(front!=rear)
//     {
//         node *new1=queue[front++];
//         cout<<new1->data<<" ";
//         if(new1->left!=NULL)
//         {
//             queue[rear++]=new1->left;
//         }
//         if(new1->right!=NULL)
//         {
//             queue[rear++]=new1->right;
//         }
//     }
// }

int main()
{
    int c=1;
    avl t;
    int key;
    // node *p=t.get_root();
    node *p=NULL;
    while(c>0)
    {
        cout<<"MENU"<<endl;
        cout<<"1.Insert"<<endl;
        cout<<"2.Search"<<endl;
        cout<<"3.Inorder"<<endl;
        // cout<<"4.Level Order Traversing"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"Enter Your Choice:";
        cin>>c;
        if(c==1)
        {
            cout<<"Enter data"<<endl;
            cin>>key;
            p=t.insert(p,key);

        }
        else if(c==2)
        {
            cout<<"Enter key to search"<<endl;
            cin>>key;
            if(t.search(p,key))
            {
                cout<<"Key Found"<<endl;
            }
            else
            {
                cout<<"Key not found"<<endl;
            }
        }
        else if(c==3)
        {
            t.inorder(p);
            cout<<endl;
        }
        // else if(c==4)
        // {
        //     t.level_traverse(p); 
        //     cout<<endl;   
        // }
        else if(c==4)
        {
            cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}
