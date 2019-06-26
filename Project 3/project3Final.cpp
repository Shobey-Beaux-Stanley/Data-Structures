#include <iostream>
using namespace std;
//CS 2413
//Shobey Stanley
//OU ID: 112808884
//project 3
class ArrayException : public exception {};
class ArrayMemoryException : public ArrayException {};
class ArrayBoundsException : public ArrayException {};
#ifndef _ABSTRACTARRAY_H
#define _ABSTRACTARRAY_H
//Abstract Array Class
template <class DT>
class AbstractArrayClass {//abstract class for arrayClass
public:
	virtual int sizeReturn() const = NULL;
	virtual DT& operator [](int k) = NULL;
};
#endif
#ifndef _ARRAYCLASS_H
#define _ARRAYCLASS_H
const int ARRAY_CLASS_DEFAULT_SIZE = 1;
//Array Class
template <class DT>
class ArrayClass : virtual public AbstractArrayClass<DT> {
protected:
	DT* paObject;
	int _size;
	void copy(const ArrayClass<DT>& ac);
public:
	ArrayClass();//daulat constructor 
	ArrayClass(int n);//constructor with one parameter
	ArrayClass(int n, const DT& val);//constructor with 2 parameters
	ArrayClass(const ArrayClass<DT>& ac);//copy constructor
	virtual ~ArrayClass();//destructor
	virtual int sizeReturn() const;//returns size of the array
	virtual DT& operator [](int k);//overloaded [] operator
	void operator= (const ArrayClass<DT>& ac);//overloaded = operator
};

//Methods and Constructors
template <class DT>
ArrayClass<DT>::ArrayClass() {
	_size = 0;
	paObject = new DT[ARRAY_CLASS_DEFAULT_SIZE];
	if (paObject == NULL)
		throw ArrayMemoryException();
	_size = ARRAY_CLASS_DEFAULT_SIZE;
}
template <class DT>
ArrayClass<DT>::ArrayClass(int n) {
	_size = 0;
	paObject = new DT[n];
	if (paObject == NULL)
		throw ArrayMemoryException();
	_size = n;
}
template <class DT>
ArrayClass<DT>::ArrayClass(int n, const DT& val) {
	_size = 0;
	paObject = new DT[n];
	if (paObject == NULL)
		throw ArrayMemoryException();
	_size = n;
	for (int i = 0; i < n; i++)
		paObject[i] = val;
}
template <class DT>
ArrayClass<DT>::ArrayClass(const ArrayClass<DT>& ac) {
	if (&ac != this) {
		copy(ac);
	}
}
template <class DT>
void ArrayClass<DT>::copy(const ArrayClass<DT>& ac) {
	_size = 0;
	paObject = new DT[ac._size];
	if (paObject == NULL)
		throw ArrayMemoryException();
	_size = ac._size;
	for (int i = 0; i < _size; i++) {
		paObject[i] = ac.paObject[i];
	}
}
template <class DT>
void ArrayClass<DT>::operator=(const ArrayClass<DT>& ac) {
	if (&ac != this) {
		if (paObject != NULL)
			delete[] paObject;
		copy(ac)
	}
}
template <class DT>
ArrayClass<DT>::~ArrayClass() {
	if (paObject != NULL)
		delete[] paObject;
	paObject = NULL;
	_size = 0;
}
template<class DT>
int ArrayClass<DT>::sizeReturn() const {
	return _size;
}
template <class DT>
DT& ArrayClass<DT>::operator[] (int k) {
	//cout << "here";
	//if ((k < 0) || (k > sizeReturn())) {
	//	throw ArrayBoundsException();
	//}
	return paObject[k];
}
#endif

//Abstract Vector class
template <class DT>
class AbstractVector :virtual public AbstractArrayClass<DT> {//AbstractVector class used by vector class
public:
	virtual void insert(const DT& item, int index) = NULL;
	virtual void remove(int index) = NULL;
	virtual void add(const DT& item) = NULL;
};
#ifndef _VECTOR_H
#define _VECTOR_H
//Vector Class
template <class DT>
class Vector :virtual public ArrayClass<DT>, virtual public AbstractVector<DT> {//subclass of arrayClass and abstractVector class
private:
	int currentSize;
	int incFactor;
public:
	Vector();//Default constructor
	Vector(int n);//constructor with a parameter
	Vector(int n, DT& val);//constructor with 2 parameters
	Vector(const Vector<DT>& v);//copy constructor
	Vector(const ArrayClass<DT>& ac);//copy constructor
	void operator= (const Vector<DT>& v);//overloaded = operator
	void operator= (const ArrayClass<DT>& ac);//overloaded = operator
	virtual void insert(const DT& item, int index);//inserts an element into the vector
	virtual void remove(int index);//removes element from vector
	virtual void add(const DT& item);//adds an element to vector
	virtual int sizeReturn() const;//returns size
	virtual int capacity() const;//returns capacity
	virtual int incrementReturn() const;//returns the increment factor of the vector
	virtual void setIncFactor(int f);//sets the increment factor of the vector
	void setCapacity(int c);//sets the capacity of the vector
	void display();//displays content of the vector
	void operator<< (const Vector<DT>& v);
	virtual ~Vector();
};
template<class DT>
Vector<DT>::Vector() :ArrayClass<DT>() {//default constructor
	currentSize = 0;
	incFactor = 1;
}
template <class DT>
Vector<DT>::Vector(int n) : ArrayClass<DT>(n) {//constructor with a parameter
	currentSize = 0;
	incFactor = n;
}
template <class DT>
Vector<DT>::Vector(int n, DT& val) : ArrayClass<DT>(n, val) {//constructor with 2 parameters
	currentSize = 0;
	incFactor = n;
}
template <class DT>
Vector<DT>::Vector(const Vector<DT>& v) : ArrayClass<DT>(v) {//copy contructor
	currentSize = v.currentSize;
	incFactor = v.incFactor;
}
template<class DT>
Vector<DT>::Vector(const ArrayClass<DT>& ac) : ArrayClass<DT>(ac) {//copy constructor
	currentSize = ac.sizeReturn();
	incFactor = (currentSize + 1);
}
template<class DT>
void Vector<DT>::operator= (const Vector<DT>& v) {//overloaded equals operator
	ArrayClass<DT>::copy(v);
	currentSize = v.currentSize;
	incFactor = v.incrementReturn();
}
template<class DT>
void Vector<DT>::operator= (const ArrayClass<DT>& ac) {//overloaded equals operator function
	ArrayClass<DT>::copy(ac);
	currentSize = ac.sizeReturn();
	incFactor = (currentSize + 1);
}
template<class DT>
int Vector<DT>::sizeReturn() const {//returns current size of the vector
	return currentSize;
}
template<class DT>
int Vector<DT>::capacity() const {//returns the size of the vector
	return _size;
}
template<class DT>
int Vector<DT>::incrementReturn() const {//returns increment factor
	return incFactor;
}
template <class DT>
void Vector<DT>::setIncFactor(int f) {//sets increment factor
	if (f >= 0)
		incFactor = f;
}
template <class DT>
void Vector<DT>::setCapacity(int c) {//needs exception handling
	int len = currentSize;
	if (len > c)
		len = c;
	DT* paNew = new DT[c];
	if (paNew == NULL) {
		throw ArrayMemoryException();
	}
	for (int i = 0; i < len; i++) {
		paNew[i] = paObject[i];
	}
	if (paObject != NULL) {
		delete[] paObject;
	}
	paObject = paNew;
	_size = c;
	if (currentSize > len) {
		currentSize = len;
	}
}
template <class DT>
void Vector<DT>::insert(const DT& item, int index) {//this one needs exception handling too (pg 210)
	if ((index < 0) || (index > currentSize)) {
		throw ArrayBoundsException();
	}
	if ((currentSize + 1) == _size) {
		setCapacity(_size + incFactor);
	}
	currentSize++;
	for (int i = currentSize - 1; i > index; i--) {
		(*this)[i] = (*this)[i - 1];
	}
	(*this)[index] = item;
}
template <class DT>
void Vector<DT>::add(const DT& item) {
	insert(item, currentSize);
}
template <class DT>
void Vector<DT>::remove(int index) {//needs exception handling
	if ((index < 0) || (index >= currentSize)) {
		throw ArrayBoundsException();
	}
	if (currentSize <= _size - incFactor) {
		setCapacity(_size - incFactor);
	}
	for (int i = index; i < currentSize - 1; i++) {
		(*this)[i] = (*this)[i + 1];
	}
	currentSize--;
}
template <class DT>
void Vector<DT>::display() {//displays vector contents
	for (int i = 0; i < currentSize; i++) {
		cout << (*this)[i];
	}

}
//template <class DT>
//void Vector<DT>::operator<< (const DT& v) {
//	display();
//}
template <class DT>
Vector<DT>::~Vector() {
}
#endif


//Cell class. Functions as a linked list with other cells.
template <class DT>
class Cell{
	//friend ostream& operator <<(ostream& s, DT& cell);
protected:
	DT _value;//Value contained inside the cell
	Cell<DT>* _right;//Pointer to the next Cell
public:
	Cell();//Default constructor
	Cell(DT value);//Initializer constructor with a value
	Cell(DT value, Cell<DT>* right);//Initializer constructor with a value and a pointer to the next cell
	Cell(Cell<DT>& copyCell);//Copy constructor
	DT getValue();//Returns _value
	Cell<DT>* getNextCell();//Returns pointer to next cell
	void add(Cell<DT>* object);//Adds a pointer to _right
	//void cellDisplay(ostream& s);
	~Cell();//Destructor
};
template <class DT>
Cell<DT>::Cell() {//Default constructor
	_value = NULL;
	_right = NULL;
}
template <class DT>
Cell<DT>::Cell(DT value) {//Initializer constructor with a value
	_value = value;
	_right = NULL;
}
template <class DT>
Cell<DT>::Cell(DT value, Cell<DT>* right) {//Initializer constructor with a value and a pointer to the next cell
	_value = value;
	_right = right;
}
template<class DT>
Cell<DT>::Cell(Cell<DT>& copyCell) {//Copy constructor
	_value = copyCell.getValue();
	_right = copyCell.getNextCell();
}
template <class DT>
DT Cell<DT>::getValue() {//Returns _value
	return _value;
}
template <class DT>
Cell<DT>* Cell<DT>::getNextCell() {//Returns pointer to next cell
	return _right;
}
template <class DT>
void Cell<DT>::add(Cell<DT>* object) {//Adds a pointer to _right
	if (_right == NULL) {
		_right = object;
	}
	else {
		_right->add(object);
	}
}
template<class DT>
Cell<DT>::~Cell() {//Destructor
	if (_right != NULL) {
		delete _right;//recursive delete of pointers
		_right = NULL;
	}
}

//CellNode class. Functions as a linked list with Cell objects. 
template <class DT1, class DT2>
class CellNode {
	//friend ostream& operator<<(ostream& s, CellNode<DT1,DT2>& cellNode);
protected:
	DT1 _info;//The info of the CellNode (either char type or int
	DT2* _myCell;//Pointer to a cell
	int listSize;//Size of list read in from file
public:
	
	CellNode();//Default constructor
	CellNode(DT1 info);//Initializer constructor with info (main program uses a vector here)
	CellNode(DT2* myCell);//Initializer constructor with a pointer to a cell
	CellNode(DT1 info, DT2* myCell, int newSize);//Initializer constructor with info, a pointer to a cell, and its size
	CellNode(CellNode<DT1, DT1>& copyCellNode);//Copy constructor
	int size();//Returns listSize value
	void addCell(DT2* object);//Adds a pointer to _myCell
	DT1 getInfo();//Returns _info
	DT2* getCell();//Returns a pointer to the next cell(which is _myCell)
	void setSize(int newSize);//Sets the listSize value
	int getSize();//returns listSize
	~CellNode();//Destructor
	//void display(ostream& s);
	
};
template <class DT1, class DT2>
CellNode<DT1,DT2>::CellNode() {//Default constructor
	//_info = NULL;
	_myCell = NULL;
	listSize = NULL;
}
template <class DT1, class DT2>
CellNode<DT1, DT2>::CellNode(DT1 info) {//Initializer constructor with info (main program uses a vector here)
	_info = info;
}
template <class DT1, class DT2>
CellNode<DT1, DT2>::CellNode(DT2* myCell) {//Initializer constructor with a pointer to a cell
	_myCell = myCell;
}
template <class DT1, class DT2>
CellNode<DT1,DT2>::CellNode(DT1 info, DT2* myCell, int newSize) {//Initializer constructor with info, a pointer to a cell, and its size
	_info = info;
	_myCell = myCell;
	listSize = newSize;
}
template <class DT1,class DT2>
CellNode<DT1, DT2>::CellNode(CellNode<DT1, DT1>& copyCellNode) {//Copy constructor
	_info = copyCellNode.getInfo();
	_myCell = copyCellNode.getCell();
	listSize = copyCellNode.getSize();
}
template <class DT1,class DT2>
int CellNode<DT1, DT2>::size() {//Returns listSize value
	if (next == NULL) {
		if (_info == NULL) {
			return 0
		}
		else {
			return 1;
		}
	}
	else {
		return 1 + _next->size();
	}
}
template <class DT1,class DT2>
void CellNode<DT1, DT2>::addCell(DT2* object) {//Adds a pointer to _myCell
	if (_myCell == NULL) {
		_myCell = object;
	}
	else {
		_myCell->add(object);
	}
}
template <class DT1,class DT2>
DT1 CellNode<DT1, DT2>::getInfo() {//Returns _info
	return _info;
}
template <class DT1,class DT2>
DT2* CellNode<DT1, DT2>::getCell() {//Returns a pointer to the next cell(which is _myCell)
	return _myCell;
}
template <class DT1,class DT2>
void CellNode<DT1, DT2>::setSize(int newSize) {//Sets the listSize value
	listSize = newSize;
}
template <class DT1, class DT2>
int CellNode<DT1, DT2>::getSize() {//returns listSize
	return listSize;
}

template <class DT1,class DT2>
CellNode<DT1, DT2>::~CellNode() {//Destructor
	if (_myCell != NULL) {
		delete _myCell;
		_myCell = NULL;
	}
}
//MasterCell class. Holds the vector of pointers of CellNodes.
template <class DT1, class DT2>
class MasterCell {
protected:
	Vector<DT1*> _cellNodeVector;//Vector of pointers of CellNodes
public:
	MasterCell();//Default constructor
	MasterCell(CellNode<DT1,DT2> cellNodeVector);//Initializer constructor
	void addCellNode(DT1* cell);//Adds a CellNode pointer to the Vector
	void display();//Displays each linked list of CellNodes and Cells within the vector
	~MasterCell();//Destructor for the Vector
};
template <class DT1,class DT2>
MasterCell<DT1,DT2>::MasterCell() {//Default constructor
	_cellNodeVector.setCapacity(1);
}
template <class DT1,class DT2>
MasterCell<DT1,DT2>::MasterCell(CellNode<DT1,DT2> cellNodeVector) {//Initializer constructor
	_cellNodeVector = cellNodeVector;
}
template <class DT1,class DT2>
void MasterCell<DT1, DT2>::addCellNode(DT1* cell) {//Adds a CellNode pointer to the Vector
	_cellNodeVector.add(cell);
}
template <class DT1,class DT2>
void MasterCell<DT1, DT2>::display() {//Displays each linked list of CellNodes and Cells within the vector
	
	for (int i = 0; i < _cellNodeVector.capacity()-1; i++) {
		_cellNodeVector[i]->getInfo().display();
		cout << " " << _cellNodeVector[i]->getSize();
		Cell<DT2>* dt = _cellNodeVector[i]->getCell();
		while ((dt->getNextCell() != NULL)) {//Goes through and prints the values of each cell until the last one is reached. Then it stops.
			cout << " " << dt->getValue();
			//cout << dt;
			cout << " ";
			dt = dt->getNextCell();
		}
		cout << " " << dt->getValue();//Since the while loop stops at the last one, it does not print its value. This line of code does.
		cout  << endl;
		delete dt;
	}
}

template <class DT1,class DT2>
MasterCell<DT1, DT2>::~MasterCell() {//Destructor for MasterCell
	cout << "Destructor of MasterCell Called";
}
int main() {
	char aChar;
	char blank;
	char comma;
	int values;
	int numberOfCells;
	MasterCell<CellNode<Vector<char>,Cell<int>>,int> masterCell;
	while (!cin.eof()) {//Gets info for the CellNode by adding it to the vector
		Vector<char> v;
		do {
			cin.get(aChar);
			if (aChar != '\n') {
				if (aChar == ',') {
					v.add(aChar);
					break;
				}
				else {
					v.add(aChar);
				}
			}
			
		} while ((aChar != '\n') && !cin.eof());
		CellNode<Vector<char>, Cell<int>>* cellNode;
		cellNode = new CellNode<Vector<char>, Cell<int>>(v);
		cin.get(blank);
		cin >> numberOfCells;//Gets size for cellNode
		cellNode->setSize(numberOfCells);//Sets size
		while (!cin.eof()) {//Gets info for the cell, makes a cell, then adds it to the list
			cin.get(blank);
				if (blank == '\n') {
					break;
				}
				else {
					cin >> values;
					Cell<int>* cell = new Cell<int>(values);
					cellNode->addCell(cell);
					if (blank == '\n') {
						break;
					}
				}
		}
		masterCell.addCellNode(cellNode);//adds a cellNode to the masterCell.
	}
	masterCell.display();
}