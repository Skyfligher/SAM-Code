#include "binarysearchtree.h"
//#include <node.h>


using namespace std;


BinarySearchTree::BinarySearchTree(int temp)
{
    tree = new node[temp];
    count = 0;
}
node* BinarySearchTree::firstNode(){
    node* temp = &tree[0];
    while(tree[0].lvalue != NULL){
        temp = temp->lvalue;
    }
    return temp;
}

void BinarySearchTree::InsertBinarySearchTree(string temp1, string temp2){
    node * root = &tree[0];
    if(count == 0){
        tree[0].name = temp1;
        tree[0].number = temp2;
        count++;
    }
    else{
        bool search = true;
        while(search){
            if(root->name > temp1){
                if(root->lvalue != NULL){
                    root = root->lvalue;
                }
                else{
                    tree[count].name = temp1;
                    tree[count].number = temp2;
                    tree[count].rthread = root;
                    tree[count].lthread = root->lthread;
                    root->lthread = &tree[count];
                    root->lvalue = &tree[count];
                    search = false;
                    count++;
                }
            }
            else if(root->name < temp1){
                if(root->rvalue != NULL){
                    root = root->rvalue;
                }
                else{
                    tree[count].name = temp1;
                    tree[count].number = temp2;
                    tree[count].lthread = root;
                    tree[count].rthread = root->rthread;
                    root->rthread = &tree[count];
                    root->rvalue = &tree[count];
                    search = false;
                    count++;
                }
            }
            else if(root->name == temp1){
                tree[count].name = temp1;
                tree[count].number = temp2;
                tree[count].lthread = root;
                tree[count].rthread = root->rthread;
                root->rthread = &tree[count];
                root->rvalue = &tree[count];
                search = false;
                count++;
            }

        }
    }

}
node* BinarySearchTree::FindCustomerIterative(node* root, string temp){
    while(root->name != temp){
        if(root->name > temp){
            if(root->lvalue != NULL){
                root = root->lvalue;
            }
            else{
                cout<<"This Customer does not exist.\n";
                return NULL;
            }

        }
        else if(root->name < temp){
            if(root->rvalue != NULL){
                root = root->rvalue;
            }
            else{
                cout<<"This Customer does not exist.\n";
                return NULL;
            }
        }
    }
    cout<<root->name<<"s number is "<<root->number<<"\n";
    return root;

}
node* BinarySearchTree::FindCustomerIterative(string temp){
    node * root = &tree[0];
    while(root->name != temp){
        if(root->name > temp){
            if(root->lvalue != NULL){
                root = root->lvalue;
            }
            else{
                cout<<"This Customer does not exist.\n";
                return NULL;
            }

        }
        else if(root->name < temp){
            if(root->rvalue != NULL){
                root = root->rvalue;
            }
            else{
                cout<<"This Customer does not exist.\n";
                return NULL;
            }
        }
    }
    cout<<root->name<<"s number is "<<root->number<<"\n";
    return root;

}
node* BinarySearchTree::FindCustomerRecursive(node* root, string temp){
    if(root->name > temp){
        if(root->lvalue != NULL){
            return this->FindCustomerRecursive(root->lvalue, temp);
        }
        else{
            cout<<"This Customer does not exist.\n";
            return NULL;

        }

    }
    else if(root->name < temp){
        if(root->rvalue != NULL){
            return this->FindCustomerRecursive(root->rvalue, temp);
        }
        else{
            cout<<"This Customer does not exist.\n";
            return NULL;
        }
    }
    else{
        cout<<root->name<<"s number is "<<root->number<<"\n";
        return root;
    }
}
node* BinarySearchTree::FindCustomerRecursive(string temp){
    node * root = &tree[0];
    if(root->name > temp){
        if(root->lvalue != NULL){
            return this->FindCustomerRecursive(root->lvalue, temp);
        }
        else{
            cout<<"This Customer does not exist.\n";
            return NULL;
        }

    }
    else if(root->name < temp){
        if(root->rvalue != NULL){
            return this->FindCustomerRecursive(root->rvalue, temp);
        }
        else{
            cout<<"This Customer does not exist.\n";

            return NULL;
        }
    }
    else{
        cout<<root->name<<"s number is "<<root->number<<"\n";
        return root;
    }
}
void BinarySearchTree::DeleteRandomNode(node* toDelete){
    node* temp;
    temp = toDelete;
    if( toDelete->name > tree[0].name){
        while(temp->lvalue != NULL){
            temp = temp->lvalue;
        }
        toDelete->rthread->lthread = temp;
        temp->lthread->rthread = temp;
        temp->lthread->rvalue = temp;
        temp->rthread = toDelete->rthread;
        temp->lvalue = toDelete->lvalue;
        temp->rvalue = toDelete->rvalue;
    }
    else if( toDelete->name < tree[0].name){
        while(temp->rvalue != NULL){
            temp = temp->rvalue;
        }

        temp->rthread = toDelete->rthread;
        temp->lvalue = toDelete->lvalue;
        temp->rvalue = toDelete->rvalue;
    }
}
node* BinarySearchTree::InOrderSuccessor(node *temp){
    return temp->rthread;
}
string BinarySearchTree::CustomerName(node *temp){
    return temp->name;
}
string BinarySearchTree::CustomerPhone(node *temp){
    return temp->number;
}
void BinarySearchTree::InOrder(node *temp){
    node* temp2 = temp;
    while(temp2->rthread != temp){
        cout<<temp2->name<<" "<<temp2->number<<"\n";
        if(temp2->rthread != NULL){
            temp2 = temp2->rthread;
        }
        else{
            temp2 = this->firstNode();
        }
    }
}
void BinarySearchTree::InOrder(){
    this->InOrder(&tree[0]);
}
void BinarySearchTree::ReverseInOrder(node *temp){
    node* temp2 = temp;
    while(!stack.empty()){
        stack.pop();
    }
    while(temp2->rthread != temp){
            stack.push(*temp2);
        if(temp2->rthread != NULL){
            temp2 = temp2->rthread;
        }
        else{
            temp2 = this->firstNode();
        }
    }
    for(int i=0;i<count;i++){
        cout<<stack.top().name<<" ";
        stack.pop();
        cout<<stack.top().number<<"\n";
        stack.pop();
    }
}
void BinarySearchTree::PreOrder(node *temp){
    if(temp == NULL){
        return;
    }
    cout<<temp->name<<" "<<temp->number<<"\n";
    this->PreOrder(temp->lvalue);
    this->PreOrder(temp->rvalue);
}
void BinarySearchTree::PostOrderIterative(node *temp){
    if(temp == NULL){
        return;
    }

    while(!stack.empty()){
        stack.pop();
    }
    while(temp != NULL){
        if(temp->rvalue != NULL){
            stack.push(*temp->rvalue);
        }
        else{
            stack.push(*temp);
            temp = temp->lvalue;
        }
    }
    temp = &stack.top();
    stack.pop();
    if(&temp->rvalue == &temp->rvalue && stack.top() == &temp->rvalue){
        stack.pop();
        stack.push(*temp);
        temp = temp->rvalue;
    }
    else{
        cout<<temp->name<<" "<<temp->number<<"\n";
        temp = NULL;
    }
}
void BinarySearchTree::PostOrderRecursive(node *temp){
    if(temp == NULL){
        return;
    }
    this->PostOrderRecursive(temp->lvalue);

    this->PostOrderRecursive(temp->rvalue);

    cout<<temp->name<<" "<<temp->number<<"\n";
}



