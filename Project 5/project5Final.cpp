#include <iostream>
using namespace std;
//CS 2413
//Project 5
//Shobey Stanley
//OU ID: 112808884

template <class DT>
class ParentBinaryTree {//Functions as a binary tree using an array
	template <class DT> friend ostream& operator<<(ostream& s, ParentBinaryTree<DT>& tree);
protected:
	DT* ParentArray;//Array with values
	int numNodes;//Number of nodes. Used to set array size
	DT* PositionArray;//Array indicating the position of each element in the tree (L/R)
public:
	ParentBinaryTree();//Default Constructor
	ParentBinaryTree(int newNumNodes);//Parameterized constructor
	ParentBinaryTree(ParentBinaryTree<DT>& newTree);//Copy constructor
	~ParentBinaryTree();//Destructor
	int sizeReturn();//Returns the numNodes
	DT* getParentArray();//Returns the ParentArray holding the values
	void insert(int parent, int left, int right);//Used while reading in from the file
	void setPosition(int left, int right);//Also used while reading in from the file.
	DT* getPositionArray();//Returns position Array
	int getLeft(int parent);//Returns the left node array location of the node indicated
	int getRight(int parent);//Returns the right node array location of the node indicated
	int getHeight(int node);//Returns the height of the tree
	void preorder(int node);//Displays using the preorder traversal method
	void inorder(int node);//displays using the inorder traversal method
	void postorder(int node);//Displays using the postorder traversal method
	int getParent();//returns the first node in the tree
	int getNumNodes();//returns the numNodes in the tree
	void operator=(ParentBinaryTree<DT>& newTree);
};
template <class DT>
ParentBinaryTree<DT>::ParentBinaryTree() {
	ParentArray = NULL;
	numNodes = NULL;
	PositionArray = NULL;
}
template <class DT>
ParentBinaryTree<DT>::ParentBinaryTree(int newNumNodes) {
	ParentArray = new DT[newNumNodes];
	PositionArray = new DT[newNumNodes];
	for (int i = 0; i < newNumNodes; i++) {
		ParentArray[i] = -1;
	}
	for (int i = 0; i < newNumNodes; i++) {
		PositionArray[i] = -1;
	}
	numNodes = newNumNodes;
	cout << "Binary Tree created. Number of nodes is: " << numNodes << endl << endl;
}
template <class DT>
ParentBinaryTree<DT>::ParentBinaryTree(ParentBinaryTree<DT>& newTree) {
	delete[] ParentArray;
	delete[] PositionArray;
	numNodes = newTree.getNumNodes();
	ParentArray = new DT[newTree.getNumNodes()];
	PositionArray = new DT[newTree.getNumNodes()];
	for (int i = 0; i < numNodes; i++) {
		ParentArray[i] = newTree.getParentArray()[i];
	}
	for (int i = 0; i < numNodes;i++) {
		PositionArray[i] = newTree.getPositionArray()[i];
	}
}
template <class DT>
ParentBinaryTree<DT>::~ParentBinaryTree() {
	cout << "ParentBinaryTree Destructor called" << endl;
	if (ParentArray != NULL) {
		delete[] ParentArray;
	}
	numNodes = NULL;
}
template <class DT>
int ParentBinaryTree<DT>::sizeReturn() {
	return numNodes;
}
template <class DT>
DT* ParentBinaryTree<DT>::getParentArray() {
	return ParentArray;
}
template <class DT>
void ParentBinaryTree<DT>::insert(int parent, int left, int right) {
	if (left != -1) {
		ParentArray[left] = parent;
	}
	if (right != -1) {
		ParentArray[right] = parent;
	}
}
template <class DT>
void ParentBinaryTree<DT>::setPosition(int left, int right) {
	PositionArray[left] = 0;
	PositionArray[right] = 1;
}
template <class DT>
DT* ParentBinaryTree<DT>::getPositionArray() {
	return PositionArray;
}
template <class DT>
int ParentBinaryTree<DT>::getLeft(int parent) {
	int child1 = -1;
	int child2 = -1;
	int counter = 0;
	for (int i = 0; i < numNodes; i++) {
		if (ParentArray[i] == parent) {
			if (counter == 0) {
				child1 = i;
				counter++;
				continue;
			}
			if (counter == 1) {
				child2 = i;
				counter++;
				break;
			}
		}
	}
	if (child1 > -1) {
		if (PositionArray[child1] == 0) {
			return child1;
		}
	}
	if (child2 > -1) {
		if (PositionArray[child2] == 0) {
			return child2;
		}
	}
	return -1;//Default return/No left child
}
template <class DT>
int ParentBinaryTree<DT>::getRight(int parent) {
	int child1 = -1;
	int child2 = -1;
	int counter = 0;
	for (int i = 0; i < numNodes; i++) {
		if (ParentArray[i] == parent) {
			if (counter == 0) {
				child1 = i;
				counter++;
				continue;
			}
			if (counter == 1) {
				child2 = i;
				counter++;
				break;
			}
		}
	}
	if (child1 > -1) {
		if (PositionArray[child1] == 1) {
			return child1;
		}
	}
	if (child2 > -1) {
		if (PositionArray[child2] == 1) {
			return child2;
		}
	}
	return -1;//Default return/No right child
}
template <class DT>
int ParentBinaryTree<DT>::getHeight(int node) {
	int height = 0;
	int leftHeight;
	if (node != -1) {
		if (getLeft(node) == -1)
			leftHeight = 0;
		else
			leftHeight = getHeight(getLeft(node));
		if (getRight(node) == -1)
			height = 1 + leftHeight;
		else {
			if (leftHeight < getHeight(getRight(node)))
				height = 1 + getHeight(getRight(node));
			if (leftHeight > getHeight(getRight(node)))
				height = 1 + leftHeight;
			if (leftHeight == getHeight(getRight(node)))
				height = 1 + leftHeight;
		}

	}
	return height;
}
template <class DT>
void ParentBinaryTree<DT>::preorder(int node) {
	if (node == -1)
		return;
	cout << node << " ";
	preorder(getLeft(node));
	preorder(getRight(node));
}
template <class DT>
void ParentBinaryTree<DT>::inorder(int node) {
	if (node == -1) {
		return;
	}
	inorder(getLeft(node));
	cout << node << " ";
	inorder(getRight(node));

}
template <class  DT>
void ParentBinaryTree<DT>::postorder(int node) {
	if (node == -1) {
		return;
	}
	postorder(getLeft(node));
	postorder(getRight(node));
	cout << node << " ";
}
template <class DT>
int ParentBinaryTree<DT>::getParent() {
	int firstNode = -1;
	for (int i = 0; i < numNodes; i++) {
		if (ParentArray[i] == -1) {
			firstNode = i;
		}
	}
	return firstNode;
}
template <class DT>
ostream &operator<<(ostream& s, ParentBinaryTree<DT>& tree) {
	int parentNode = tree.getParent();
	tree.preorder(parentNode);
	return s;
}
template <class DT>
int ParentBinaryTree<DT>::getNumNodes() {
	return numNodes;
}
template <class DT>
void ParentBinaryTree<DT>::operator=(ParentBinaryTree<DT>& newTree) {
	if (ParentArray != NULL) {
		delete[] ParentArray;
	}
	if (PositionArray != NULL) {
		delete[] PositionArray;
	}
	numNodes = newTree.getNumNodes();
	ParentArray = new DT[newTree.getNumNodes()];
	PositionArray = new DT[newTree.getNumNodes()];
	for (int i = 0; i < numNodes; i++) {
		ParentArray[i] = newTree.getParentArray()[i];
	}
	for (int i = 0; i < numNodes; i++) {
		PositionArray[i] = newTree.getPositionArray()[i];
	}
}
int main() {
	int numberOfInput = 0;
	cin >> (numberOfInput);
	ParentBinaryTree<int> tree(numberOfInput);
	int leftChild;
	int rightChild;
	int parent;
	int i = 0;
	int j = 0;
	char blank;
	while (!cin.eof()) {//Reads files until end. Plugs values into the ParentArray of the tree
		cin >> parent;
		cin.get(blank);
		cin >> leftChild;
		cin.get(blank);
		cin >> rightChild;
		tree.insert(parent, leftChild, rightChild);
		tree.setPosition(leftChild, rightChild);
		i++;
	}
	cout << "Testing overloaded << operator using preorder: ";
	cout << tree << endl;
	int parentNode = tree.getParent();
	cout << "Get Height is: " << endl;
	cout << tree.getHeight(parentNode) << endl;
	cout << "Get Size is: " << endl;
	cout << tree.sizeReturn() << endl;
	cout << "Preorder: ";
	tree.preorder(parentNode);
	cout << endl;
	cout << "Inorder: ";
	tree.inorder(parentNode);
	cout << endl;
	cout << "Postorder: ";
	tree.postorder(parentNode);
	cout << endl;
	cout << "Making new tree using copy constructor" << endl;
	ParentBinaryTree<int> newTree(tree);
	cout << "Printing new tree: " << endl;
	newTree.preorder(parentNode);
	cout << endl;
	cout << "Testing overloaded = operator:" << endl;
	ParentBinaryTree<int> tree3;
	tree3 = newTree;
	cout << "Printing new Tree: " << endl;
	tree3.preorder(parentNode);
}