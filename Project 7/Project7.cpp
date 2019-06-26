#include <iostream>
using namespace std;
#include <list>
#include <stack>
#include <vector>
#include <deque>
#include <queue>
//Shobey Stanley
//OU ID: 112808884
//Project 7
template <class DT>
class ParentBinaryTree {//Functions as a binary tree using an array
	template <class DT> friend ostream& operator<<(ostream& s, ParentBinaryTree<DT>& tree);
protected:
	DT* ParentArray;//Array with values
	int numNodes;//Number of nodes. Used to set array size
	DT* PositionArray;//Array indicating the position of each element in the tree (1,2,3...)
public:
	ParentBinaryTree();//Default Constructor
	ParentBinaryTree(int newNumNodes);//Parameterized constructor
	ParentBinaryTree(ParentBinaryTree<DT>& newTree);//Copy constructor
	~ParentBinaryTree();//Destructor
	int sizeReturn();//Returns the numNodes
	DT* getParentArray();//Returns the ParentArray holding the values
	void insert(int parent, int node);//Used while reading in from the file
	void setPosition(int node, int position);//Also used while reading in from the file.
	DT* getPositionArray();//Returns the position Array
	int getNext(int parent, int childPosition);//Returns the child of the node based on the indicated child's position
	int getHeight(int node);//Returns the height of the tree
	void preorder(int node);//Displays using the preorder traversal method
	void levelorder(int node);//Prints out all of the nodes level by level
	int getParent();//returns the first node in the tree
	int getNumNodes();//returns the numNodes in the tree
	int getPosition(int position);//Returns the position of a node (1,2,3,etc...)
	void displayChildren(int node);//Displays all of the children of a node
	void operator=(ParentBinaryTree<DT>& newTree);//Overloaded method for the = operator. Goes to preorder traversal method
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
	for (int i = 0; i < numNodes; i++) {
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
void ParentBinaryTree<DT>::insert(int parent, int node) {
	ParentArray[node] = parent;
}
template <class DT>
void ParentBinaryTree<DT>::setPosition(int node, int position) {
	PositionArray[node] = position;
}
template <class DT>
DT* ParentBinaryTree<DT>::getPositionArray() {
	return PositionArray;
}
template <class DT>
int ParentBinaryTree<DT>::getNext(int parent, int childPosition) {
	for (int i = 0; i < numNodes; i++) {
		if (ParentArray[i] == parent) {
			if (PositionArray[i] == childPosition) {
				return i;
			}
		}
	}
	return -1;//Default return/No left child
}
template <class DT>
int ParentBinaryTree<DT>::getHeight(int node) {//Returns height of the tree
	int childPosition = 1;
	int height = 0;
	while (getNext(node, childPosition) != -1) {
		int leftHeight = getHeight(getNext(node, childPosition));
		if (leftHeight > height)
			height = leftHeight;
		childPosition++;
	}
	return height + 1;
}
template <class DT>
void ParentBinaryTree<DT>::preorder(int node) {
	int childPosition = 1;
	if (node == -1) {
		return;
	}
	cout << node << " ";
	preorder(getNext(node, childPosition));
	childPosition++;
	while (getPosition(childPosition) != -1) {
		preorder(getNext(node, childPosition));
		childPosition++;
	}
}
template <class DT>
void ParentBinaryTree<DT>::levelorder(int node) {
	int* print;
	print = new int[1];
	int* temp;
	int incrementer = 0;
	print[0] = node;
	int counter = 0;
	int size = 1;
	cout << print[0] << endl;
	do {
		counter = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < numNodes; j++) {
				if (ParentArray[j] == print[i]) {
					cout << j << " ";
					counter++;
				}
			}
		}
		cout << endl;
		temp = new int[counter];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < numNodes; j++) {
				if (ParentArray[j] == print[i]) {
					temp[incrementer] = j;
					incrementer++;
				}
			}
		}
		incrementer = 0;
		print = temp;
		size = counter;
	} while (counter > 0);

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
void ParentBinaryTree<DT>::displayChildren(int node) {
	int incrementer = 0;
	for (int i = 0; i < numNodes; i++) {
		if (ParentArray[i] == node) {
			cout << i << " ";
			incrementer++;
		}
	}
	if (incrementer == 0)
		cout << "No children found";
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
template <class DT>
int ParentBinaryTree<DT>::getPosition(int position) {
	for (int i = 0; i < numNodes; i++) {
		if (position == PositionArray[i]) {
			return position;
		}
	}
	return -1;
}
template <class DT>
class GraphAdjList {
	template <class DT> friend ostream& operator<<(ostream& s, GraphAdjList<DT>& graph);
protected:
	list<DT>* adjList;//Array of list data structures containing ints
	int numNodes;//Total vertices
	int numEdges;//Number of edges in the graph
public:
	GraphAdjList();//Default constructor
	GraphAdjList(int newNodes, int newEdges);//Constructor with parameters contains nodes and edges
	void addEdge(int vertice1, int vertice2);//Adds an edge between two vertices
	void display();//Displays each node and connections
	~GraphAdjList();//Destructor
	void dfs(int x, vector<bool>& visited, vector<int> &DFSNum, int depth,stack<int> &s);//Depths first search recursive method used by depthFirstSearch method
	vector<DT> depthFirstSearch(int vertex);//Conducts a depth first search by calling dfs and returning a vector containing the results
	vector<DT> breadthFirstSearch(int vertex);//Conducts a breadth first search and returns a vector containing the results
	vector<DT> neighbors(int node);//Returns the neighboring vertices of the indicated vertex
	ParentBinaryTree<DT> depthFirstSearchTree(int x);//Used to create a multi way tree based on depth first search
	void dfsTree(int x, vector<bool>& visited, vector<int> &DFSNum, int depth,int childPosition);//used by depthFirstSearchTree to create a multiway tree
};
template <class DT>
GraphAdjList<DT>::GraphAdjList() {

}
template <class DT>
GraphAdjList<DT>::GraphAdjList(int newNodes, int newEdges) {
	numNodes = newNodes;
	numEdges = newEdges;
	adjList = new list<DT>[numNodes];
	cout << "GraphAdjList object created. Number of nodes is: " << numNodes;
	cout << " Number of edges is: " << numEdges << endl << endl;
}
template <class DT>
void GraphAdjList<DT>::addEdge(int vertice1, int vertice2) {
	adjList[vertice1].push_front(vertice2);
	adjList[vertice2].push_front(vertice1);
}
template <class DT>
void GraphAdjList<DT>::display() {
	list<DT>::iterator iter;
	list<DT>::iterator end;
	for (int i = 0; i < numNodes; i++) {
		cout << i << ": ";
		iter = adjList[i].begin();
		end = adjList[i].end();
		while (iter != end) {
			cout << *iter << " ";
			iter++;
		}
		cout << endl;
	}
}
template <class DT>
GraphAdjList<DT>::~GraphAdjList() {
	cout << "GraphAdjList destructor called... " << endl;
	delete[] adjList;
	numNodes = NULL;
	numEdges = NULL;
}
template <class DT>
ostream &operator<<(ostream& s, GraphAdjList<DT>& graph) {
	graph.display();
	return s;
}
template <class DT>
vector<DT> GraphAdjList<DT>::depthFirstSearch(int vertex) {
	vector<bool> visited(numNodes, false);
	vector<DT> DFSNum(numNodes,0);
	stack<int> s;
	dfs(vertex,visited, DFSNum, 1,s);
	cout << endl;
	return DFSNum;
}
template <class DT>
void GraphAdjList<DT>::dfs(int vertex, vector<bool>& visited, vector<int> &DFSNum, int depth, stack<int> &s) {
	visited[vertex] = true;
	DFSNum[vertex] = depth;
	vector<int> v = neighbors(vertex);
	for (int i = 0; i < v.size(); i++) {
		if (visited[v[i]] == false) {
			dfs(v[i],visited, DFSNum, depth + 1,s);
		}
	}
	
}
template <class DT>
vector<DT> GraphAdjList<DT>::breadthFirstSearch(int vertex) {
	vector<bool> visited(numNodes, false);
	queue<int> q;
	vector<int> nbors;
	visited[vertex] = true;
	int v;
	int w;
	int bNum= 1;
	vector<int> BFSNum(numNodes, -1);
	BFSNum[vertex] = 1;
	q.push(vertex);
	while (!q.empty()) {
		v = q.front();
		q.pop();
		nbors = neighbors(v);
		for (int i = 0; i < nbors.size(); i++) {
			w = nbors[i];
			if (visited[w] == false) {
				visited[w] = true;
				bNum = bNum + 1;
				BFSNum[w] = bNum;
				q.push(w);
			}
		}
	}
	cout << endl;
	return BFSNum;
}
template<class DT>
vector<DT> GraphAdjList<DT>::neighbors(int node) {
	list<DT>::iterator iter;
	list<DT>::iterator end;
	vector<int> v;
	iter = adjList[node].begin();
	end = adjList[node].end();
	while (iter != end) {
		v.push_back(*iter);
		iter++;
	}
	return v;
}
template <class DT>
ParentBinaryTree<DT> GraphAdjList<DT>::depthFirstSearchTree(int vertex) {
	vector<bool> visited(numNodes, false);
	vector<DT> DFSNum(numNodes, 0);
	int childPosition = 1;
	dfs(vertex, visited, DFSNum, 1,childPosition);
	cout << endl;
	return DFSNum;
}
template <class DT>
void GraphAdjList<DT>::dfsTree(int x, vector<bool>& visited, vector<int> &DFSNum, int depth,int childPosition) {
	visited[vertex] = true;
	DFSNum[vertex] = depth;
	vector<int> v = neighbors(vertex);
	for (int i = 0; i < v.size(); i++) {
		if (visited[v[i]] == false) {
			dfs(v[i], visited, DFSNum, depth + 1,childPosition);
		}
		childPosition++;
	}
}
int main() {
	int vertices;
	int edges;
	char blank;
	int sentinel = 0;
	cin >> vertices;
	cin.get(blank);
	cin >> edges;
	cin.get(blank);
	GraphAdjList<int> graph(vertices, edges);
	int vertice1;
	int vertice2;
	while (sentinel < edges) {//Reads files to create graph
		cin >> vertice1;
		cin.get(blank);
		cin >> vertice2;
		cin.get(blank);
		graph.addEdge(vertice1, vertice2);
		sentinel++;
	}
	cout << "Testing overloaded << operator: " << endl;
	cout << graph;
	cout << endl << endl;
	cout << "Testing depth first search with 0: " << endl;
	vector<int> v = graph.depthFirstSearch(0);
	cout << "Nodes visited are: " << endl;
	int iterator = 1;
	while (iterator <= vertices) {//Iterates to show which nodes where visited and in what order
		for (int i = 0; i < v.size(); i++) {
			if (v[i] == iterator) {
				cout << i << " ";
				iterator++;
				break;
			}
		}
	}
	cout << endl << endl;
	cout << "Testing breadth first search with 0: ";
	v = graph.breadthFirstSearch(0);
	iterator = 1;
	cout << "Nodes visited are: " << endl;
	while (iterator <= vertices) {//Iterates to show which nodes where visited and in what order
		for (int i = 0; i < v.size(); i++) {
			if (v[i] == iterator) {
				cout << i << " ";
				iterator++;
				break;
			}
		}
	}
	cout << endl;
	ParentBinaryTree<int> tree;
}