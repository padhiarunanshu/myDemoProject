/*
 * File : 00_BST_Operations.cpp
 * author : apadhi
 * data   : 19th August 2020
 */

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
	int data;
	struct Node* left;
	struct Node* right;

	Node(int d) : data(d), left(NULL), right(NULL) {}
};

// create a tree!
void create(Node*& root, int x) {
	if(root == NULL) {	
		root = new Node(x);
	} else if(root->data > x) {
		create(root->left, x);
	} else {
		create(root->right, x);
	}
}

// heightOfTree
int heightOfTree(Node* root) {
    if(root == NULL) return 0;
    
    int lh = heightOfTree(root->left);
    int rh = heightOfTree(root->right);
    
    return 1 + std::max(lh, rh);
}

// 5. Print left view of a binary tree.
void leftViewUtil(Node* root, int level, int& maxLevel) {
	if(root == NULL) return;

	if(maxLevel < level) {
		cout << root->data;
		maxLevel = level;
	}
	leftViewUtil(root->left, level + 1, maxLevel);
	leftViewUtil(root->right, level + 1, maxLevel);
}

void printLeftView(Node* root) {
	int maxLevel = 0;

	leftViewUtil(root, 1, maxLevel);
}

// 6. Print right view of a binary tree.
void rightViewUtil(Node* root, int level, int& maxLevel) {
	if(root == NULL) return;

	if(maxLevel < level) {
		cout << root->data << " ";
		maxLevel = level;
	}
	rightViewUtil(root->right, level + 1, maxLevel);
	rightViewUtil(root->left, level + 1, maxLevel);
}

void rightView(Node* root) {
	int maxLevel = 0;
	rightViewUtil(root, 0, maxLevel);
}

// --------------------------------------------------------------------------------------
// Tree Problems...
// --------------------------------------------------------------------------------------

// 1. find the lowest common ancestor of two nodes in a tree.
Node* lowestCommonAncestor(Node* root, int n1, int n2) {
	if(root == NULL) return NULL;

	if(root->data == n1 || root->data == n2) return root;

	Node* left  = lowestCommonAncestor(root->left, n1, n2);
	Node* right = lowestCommonAncestor(root->right, n1, n2);

	if(left != NULL && right != NULL) return root;
	if(left == NULL && right == NULL) return NULL;

	return left != NULL ? left : right;
}

// --------------------------------------------------------------------------------------

// 2. Find the distance bwetween two nodes.
int findDistance(Node* root, Node* n1, Node* n2) {

}

// --------------------------------------------------------------------------------------

// 3. Check if the given binary tree is a Binary search tree?
bool IsBST(Node* root, int min, int max) {
	if (root == NULL) return true;
	
	if(root->data >= min && root->data < max
	     && IsBST(root->left, min, root->data) 
	     && IsBST(root->right, root->data, max) ) { // root->data - 1 -> to allow only distinct values! 
		return true;
	} else {
		return false;
	}
}

// --------------------------------------------------------------------------------------

// 4. Invert a binary tree.
// recurssively
Node* invertTree(Node* root) {
    if(root == NULL) {
        return NULL;
    } else {
        Node* temp;
        root->left = invertTree(root->left);
        root->right = invertTree(root->right);
        
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    return root;
}

// iteratively
void mirror(Node* root) 
{ 
    if (root == NULL) 
        return;
  
    queue<Node*> q; 
    q.push(root); 

    // Do BFS. While doing BFS, keep swapping 
    // left and right children 
    while (!q.empty()) 
    { 
        // pop top node from queue 
        Node* curr = q.front(); 
        q.pop(); 
  
        // swap left child with right child 
        swap(curr->left, curr->right); 
  
        // push left and right children 
        if (curr->left) 
            q.push(curr->left); 
        if (curr->right) 
            q.push(curr->right); 
    } 
}

// create a mirror tree from a given tree
void mirrorify(Node* root, Node** mirror) 
{ 
    if (root == NULL) { 
        mirror = NULL; 
        return; 
    } 
  
    // Create new mirror node from original tree node 
    *mirror = new Node(root->data); 
    mirrorify(root->left, &((*mirror)->right)); 
    mirrorify(root->right, &((*mirror)->left)); 
}

// --------------------------------------------------------------------------------------

/**********************************/
int main() {	
	// your code goes here
	Node* root = NULL;
	create(root, 30);
	create(root, 20);
	create(root, 25);
	create(root, 10);
	create(root, 40);
	create(root, 45);
	create(root, 50);
	create(root, 70);

    
	if(IsBST(root, -1000, 1000)) { cout << "Yes! The tree is a BST\n" ; }
	else { cout << "No, it's not a BST! \n"; }
    
	Node* res = lowestCommonAncestor(root, 40, 45);
	if(res != NULL) cout << res->data << endl;
	
	return 0;
}

/**********************************/