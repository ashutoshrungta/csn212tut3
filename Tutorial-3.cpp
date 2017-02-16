// interval tree
// language- C++
#include<bits/stdc++.h>
using namespace std;

int type=1;

int maximum(int a, int b){
	return (a>b)?a:b;
}

struct node{
	int low,high,max;
	node* left;
	node* right;
};

node *root=new node();

void insert(node *temp){
	temp->max=temp->high;
	if(root==NULL){
		root=temp;
		root->left=NULL;
		root->right=NULL;
		return;
	}
	node* current=root;
	while(true){
		current->max=maximum(current->max, temp->max);
		if(temp->low <= current->low){
			if(current->left) current=current->left;
			else{
				current->left=temp;
				break;
			}
		}
		else{
			if(current->right) current=current->right;
			else{
				current->right=temp;
				break;
			}
		}
	}
}

//to check whether the two intervals are same or not
bool check(node* node1, node* node2){
	if(node1->low==node2->low && node1->high==node2->high) return true;
	return false;
}
void changeNode(node* node1, node* node2){
	node1->low=node2->low;
	node1->high=node2->high;
}



void deleteInterval(node* temp){
	node* current=root;
	node *parent=root;
	//eleminate the case when we have to delete the root node itself
	//take care of that later
	while(true){
		if(current==NULL){
			cout<<"The interval you requested to delete does not exist.\n";
			break;
		}
		if(temp->low < current->low){
			parent=current; current=current->left;
		}
		else if(temp->low > current->low){
			parent=current; current=current->right;
		}
		else{
			remove(current, parent, false);
			break;
		}
	}
}

//in-order traversal
void showInorder(node* current){
	if(current==NULL) return;
	showInorder(current->left);
	cout<<current->low<<" ";
	showInorder(current->right);
}

node* searchNode(node* temp){
	node* current=root;
	while(true){
		if(current==NULL){
			cout<<"No overlapping interval found.\n";
			return NULL;
		}
		if((temp->low <= current->high) && (temp->high >= current->low)){
			cout<<"An overlapping node found.\n";
			return current;
		}
		if(current->left){
			if(current->left->max >= temp->low) current=current->left;
		}
		else if(current->right){
			if(current->right->max >= temp->low) current=current->right;
		}
		else{
			cout<<"No overlapping interval found.\n";
			return NULL;
		}

	}
}

void remove(node* current, node* parent, bool head){
	
	int child=0;
	bool left=false, right=false;
	if(current->low <= parent->low) left=true;
	else right=true;

	if(current->left) child++;
	if(current->right) child++;
	
	if(child==0){
		if(head){
			parent=NULL;
			return;
		}
		if(left) parent->left=NULL;
		else parent->right=NULL;
	}
	else if(child==1){
		if(head){
			if(current->left) root=root->left;
			else root=root->right;
			return;
		}
		if(left){
			if(current->right) parent->left=current->right;
			else parent->left=current->left;
		}
		else{
			if(current->right) parent->right=current->right;
			else parent->right=current->left;
		}
	}
	else{
		node* temp=current;
		temp=temp->left;
		if(temp->right){
			while(temp->right){
				parent=temp;
				temp=temp->right;
			}
			changeNode(current, temp);
			parent->right=NULL;
		}
		else{
			changeNode(current, temp);
			remove(temp, current, false);
		}
	}
}

int main(){
	cout<<"Select your command:\n";
	cout<<"To insert an interval: \"1 low_value high_Value\"\n";
	cout<<"To delete an interval: \"2 low_value high_Value\"\n";
	cout<<"To searchNode an interval-overlap: \"3 low_value high_Value\"\n";
	cout<<"To stop the execution: \"-1\"\n";
	root=NULL;
	while(type!=-1){
		node *temp=new node();
		cin>>type;
		if(type==1 || type==2 || type==3){
			cin>>temp->low>>temp->high;
			while(temp->high < temp->low){
				cout<<"Not the valid interval. Enter the interval values again:\n";
				cin>>temp->low>>temp->high;
			}
		}
		if(type==1){
			insert(temp);
		}
		else if(type==2){
			deleteInterval(temp);
		}
		else if(type==3){
			node* x=new node();
			x=searchNode(temp);
			cout<<x->low<<endl;
		}
		else if(type!=-1){
			cout<<"Invalid input, please give input again.\n";
		}
		//showInorder(root); cout<<endl;
	}
	return 0;
}