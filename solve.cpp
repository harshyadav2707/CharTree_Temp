/*
Write a program to create a custom tree data structure using linked list (tree of characters),
serialize it and store it in a file and deserialize it and load it back to data structure. The program
can accept two command line arguments
1. create
2. load
“create” argument should read words from the csv file, create tree of characters and then
serialize it and save it to the file-path accepted after csv file name
i) Example: ./executable create csv-file.csv serialized-output.bin

“load” argument should read the serialized file, recreate the character tree and print all the
words present in the tree.
ii) Example: ./executable load serialized-output.bin
*/


#include <bits/stdc++.h>
using namespace std;
 
struct Node {
    string data;
    struct Node* left;
    struct Node* right;
};

Node* CreateNode(string data)
{
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* InsertNode(Node* root, string data)
{
    if (root == NULL) {
        root = CreateNode(data);
        return root;
    }
    queue<Node*> q;
    q.push(root);
 
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
 
        if (temp->left != NULL)
            q.push(temp->left);
        else {
            temp->left = CreateNode(data);
            return root;
        }
 
        if (temp->right != NULL)
            q.push(temp->right);
        else {
            temp->right = CreateNode(data);
            return root;
        }
    }
}

void inorder(Node* temp)
{
	if (temp == NULL)
    	return;
 	fstream binfile;
	inorder(temp->left);
    binfile.open("data.bin", ios::app );binfile<<temp->data<<" ";binfile.close();
    inorder(temp->right);
}


void create(){

	fstream csvfile, binfile;
	csvfile.open("data.csv", ios::in);
	if (!csvfile) {
		cout << "File not found!";
	}
	else {
		Node* root=NULL;
		string temp;
		int c=0;
		while(csvfile>>temp){
			temp= to_string(c++) +" "+temp;
			root = InsertNode(root, temp);
		}
		remove("data.bin");//delete previous file before getting strted
		inorder(root);  //serialising file
		csvfile.close();
	}
}
void load(){
	fstream binfile;
	binfile.open("data.bin", ios::in);
	int n,maxx=-1;
	string arr[1000];
	string temp;
	if (!binfile) {
		cout << "File not found! load file first";
	}
	else {
		while(binfile>>n>>temp){
			arr[n] = temp;
			maxx=max(n,maxx);
		}
		binfile.close();
	}
	for(int i=0;i<=maxx;i++)
		cout<<arr[i]<<"\n";
}
int main()
{
	
	cout<<"1. Create (Serialisation) \n2. Load (Deserialisation)\n (press c to exit)\n";
	char ch;
	while(ch != 'c' || ch!= 'C'){
		cin>>ch;
		if(ch=='1'){
			create();
			cout<<"data.bin created";
			break;
		}
		else if(ch =='2'){
			load();
			break;
		}
		else{
			break;
		}
	}
	return 0;
}
