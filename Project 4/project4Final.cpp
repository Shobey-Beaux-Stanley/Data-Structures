#include <iostream>
using namespace std;
//CS 2413
//Shobey Stanley
//OU ID: 112808884
//project 4
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
class Cell {
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
CellNode<DT1, DT2>::CellNode() {//Default constructor
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
CellNode<DT1, DT2>::CellNode(DT1 info, DT2* myCell, int newSize) {//Initializer constructor with info, a pointer to a cell, and its size
	_info = info;
	_myCell = myCell;
	listSize = newSize;
}
template <class DT1, class DT2>
CellNode<DT1, DT2>::CellNode(CellNode<DT1, DT1>& copyCellNode) {//Copy constructor
	_info = copyCellNode.getInfo();
	_myCell = copyCellNode.getCell();
	listSize = copyCellNode.getSize();
}
template <class DT1, class DT2>
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
template <class DT1, class DT2>
void CellNode<DT1, DT2>::addCell(DT2* object) {//Adds a pointer to _myCell
	if (_myCell == NULL) {
		_myCell = object;
	}
	else {
		_myCell->add(object);
	}
}
template <class DT1, class DT2>
DT1 CellNode<DT1, DT2>::getInfo() {//Returns _info
	return _info;
}
template <class DT1, class DT2>
DT2* CellNode<DT1, DT2>::getCell() {//Returns a pointer to the next cell(which is _myCell)
	return _myCell;
}
template <class DT1, class DT2>
void CellNode<DT1, DT2>::setSize(int newSize) {//Sets the listSize value
	listSize = newSize;
}
template <class DT1, class DT2>
int CellNode<DT1, DT2>::getSize() {//returns listSize
	return listSize;
}

template <class DT1, class DT2>
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
	MasterCell(CellNode<DT1, DT2> cellNodeVector);//Initializer constructor
	void addCellNode(DT1* cell);//Adds a CellNode pointer to the Vector
	void display();//Displays each linked list of CellNodes and Cells within the vector
	void findKeyWords(int searchValue);//Searchs cells for a matching value and prints the cellNode info
	int stringMatch(Vector<char> stringToMatch);//Matches a string from input to a cellNodes info
	Vector<int> andFunction(int search1,int search2);//And function that uses two ints for searching through the _cellNodeVector
	Vector<int> andFunction(Vector<int>& v, int search2);//And function compares a vector with another element in the _cellNodeVector
	Vector<int> orFunction(int search1, int search2);//Or function that uses two ints for searching through the _cellNodeVector
	Vector<int> orFunction(Vector<int> search1, int search2);//Or function compares a vector with another element in the _cellNodeVector
	Vector<int> xorFunction(int search1, int search2);//xor function that uses two ints for searching through the _cellNodeVector
	Vector<int> xorFunction(Vector<int> search1, int search2);//xor function compares a vector with another element in the _cellNodeVector
	~MasterCell();//Destructor for the Vector
};
template <class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell() {//Default constructor
	_cellNodeVector.setCapacity(1);
}
template <class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell(CellNode<DT1, DT2> cellNodeVector) {//Initializer constructor
	_cellNodeVector = cellNodeVector;
}
template <class DT1, class DT2>
void MasterCell<DT1, DT2>::addCellNode(DT1* cell) {//Adds a CellNode pointer to the Vector
	_cellNodeVector.add(cell);
}
template <class DT1, class DT2>
void MasterCell<DT1, DT2>::display() {//Displays each linked list of CellNodes and Cells within the vector

	for (int i = 0; i < _cellNodeVector.capacity() - 1; i++) {
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
		cout << endl;
		delete dt;
	}
}
template <class DT1, class DT2>
void MasterCell<DT1, DT2>::findKeyWords(int searchValues) {//Searches for a value in the cells and returns the info of the corresponding CellNode
	int count = 0;
	for (int i = 0; i < _cellNodeVector.sizeReturn(); i++) {//Loops through each CellNode
		Cell<DT2>* dt = _cellNodeVector[i]->getCell();//Temporary Cell
		while ((dt->getNextCell() != NULL) && (dt->getValue() != NULL)) {//Used to go through each cell and check values
			if (dt->getValue() == searchValues) {
				_cellNodeVector[i]->getInfo().display();
				cout << endl;
				count++;
				break;
			}
			else {
				dt = dt->getNextCell();
			}
		}
		if (dt->getNextCell() == NULL) {//Used to check the last cell since the while loop breaks out at the last one
			if (dt->getValue() == searchValues) {
				count++;
				_cellNodeVector[i]->getInfo().display();
				cout << endl;
			}
		}
		if (i == _cellNodeVector.sizeReturn() - 1) {//Used to determine if there are no matches
			if (dt->getValue() != searchValues) {
				if (count == 0) {
					cout << "No Matches";
					break;
				}
			}
		}
	}
}
template <class DT1, class DT2>
int MasterCell<DT1, DT2>::stringMatch(Vector<char> stringToMatch) {//Used to check that an input matches a cellNodes info.
	int returnValue = -1;//Default
	cout << '"';
	stringToMatch.display();//Displays the string
	cout << '"';
	cout << " ";
	for (int i = 0; i <  _cellNodeVector.sizeReturn(); i++) {//Loops through all the cell nodes and checks for a match
		for (int j = 0; j < _cellNodeVector[i]->getInfo().sizeReturn() -2  && j < stringToMatch.sizeReturn() -2 ; j++) {
		 if (_cellNodeVector[i]->getInfo()[j] == stringToMatch[j]) {
				if (j == _cellNodeVector[i]->getInfo().sizeReturn() - 4) {
						returnValue = i;
						return returnValue;
						break;
				}
			}
			else if(_cellNodeVector[i]->getInfo()[j] != stringToMatch[j]){
				break;
			}
		}
	}
	return returnValue;
}
template <class DT1, class DT2>
Vector<int> MasterCell<DT1, DT2>::andFunction(int search1, int search2) {//Displays content that are in both linked lists
	Vector<int> vector1;
	Vector<int> vector2;
	Vector<int> vector3;
	Cell<DT2>* dt = _cellNodeVector[search1]->getCell();
	for (int i = 0; i < _cellNodeVector[search1]->getSize(); i++) {//Goes through and adds the values of each cell to the vector until the last one is reached. Then it stops.
		vector1.add(dt->getValue());
		dt = dt->getNextCell();
	}
	dt = _cellNodeVector[search2]->getCell();
	for (int i = 0; i < _cellNodeVector[search2]->getSize(); i++) {//Goes through and adds the values of each cell to the vector until the last one is reached. Then it stops.
		vector2.add(dt->getValue());
		dt = dt->getNextCell();
	}
	delete dt;
	for (int i = 0; i < vector1.sizeReturn(); i++) {//Checks to see what values are common in the two vectors
		for (int j = 0; j < vector2.sizeReturn(); j++) {
			if (vector1[i] == vector2[j]) {
				vector3.add(vector1[i]);
			}
		}
	}
	vector3.remove(vector3.sizeReturn() - 1);
	return vector3;
}
template <class DT1,class DT2>
Vector<int> MasterCell<DT1, DT2>::andFunction(Vector<int>& v, int search2) {//Used for multiple operations. Checks values with the vector parameter
	Vector<int> vector2;
	Vector<int> vector3;
	Vector<int> temp;
	Cell<DT2>* dt = _cellNodeVector[search2]->getCell();
	for (int i = 0; i < _cellNodeVector[search2]->getSize(); i++) {//Goes through and adds the values of each cell to the vector until the last one is reached. Then it stops.
		vector2.add(dt->getValue());
		dt = dt->getNextCell();
	}
	delete dt;
	for (int i = 0; i < v.sizeReturn(); i++) {//Checks for values in both vectors that equal one another
		for (int j = 0; j < vector2.sizeReturn(); j++) {
			if (v[i] == vector2[j]) {
				temp.add(v[i]);
			}
		}
	}
	for (int i = 0; i <= temp.sizeReturn(); i++) {//Adds the values to vector3 that are in both vectors so that vector3 can be returned
		vector3.add(temp[i]);
	}
	return vector3;
}
template <class DT1, class DT2>
Vector<int> MasterCell<DT1, DT2>::orFunction(int search1, int search2) {//Displays content that are in either linked list
	Vector<int> vector3;
	Cell<DT2>* dt = _cellNodeVector[search1]->getCell();
	for (int i = 0; i < _cellNodeVector[search1]->getSize(); i++) {//Goes through and adds the values of each cell to the vector until the last one is reached. Then it stops.
		vector3.add(dt->getValue());
		dt = dt->getNextCell();
	}
	 dt = _cellNodeVector[search2]->getCell(); // pointer used to traverse linked list
	 for (int i = 0; i < _cellNodeVector[search2]->getSize(); i++) {//Used to add the second set of values to vector3 without duplicates
		 for (int j = 0; j < vector3.sizeReturn(); j++) {
			 if (vector3[j] == dt->getValue()) {
				 break;
			 }
			 else {
				 if (j == vector3.sizeReturn()-1) {
					 vector3.add(dt->getValue());
					 break;
				 }
				 continue;
			 }
		 }
		 dt = dt->getNextCell();
	 }
	delete dt;
	vector3.remove(vector3.sizeReturn() - 1);
	return vector3;
}
template <class DT1,class DT2>
Vector<int> MasterCell<DT1, DT2>::orFunction(Vector<int> search1, int search2) {//Used for input with multiple operations
	Vector<int> vector3;
	Cell<DT2>* dt = _cellNodeVector[search2]->getCell();
	for (int i = 0; i < _cellNodeVector[search2]->getSize(); i++) {//Adds values from second input without producing duplicates.
		for (int j = 0; j < search1.sizeReturn(); j++) {
			if (search1[i] == dt->getValue()) {
				break;
			}
			else {
				if (j == search1.sizeReturn()-1) {
					vector3.add(dt->getValue());
					break;
				}
				continue;
			}
		}
		dt = dt->getNextCell();
	}
	for (int i = 0; i <= vector3.sizeReturn(); i++) {//Adds the values so the vector can be returned
		search1.add(vector3[i]);
	}
	delete dt;
	return search1;
}
template <class DT1, class DT2>
Vector<int> MasterCell<DT1, DT2>::xorFunction(int search1, int search2) {//Displays content that are not common in either linked list
	Vector<int> vector1;
	Vector<int> vector2;
	Vector<int> vector3;
	Vector<int> elementsToDelete;
	Cell<DT2>* dt = _cellNodeVector[search1]->getCell();//Pointer used to traverse linked list
	while ((dt->getNextCell() != NULL)) {//Goes through and adds the values of each cell to the vector until the last one is reached. Then it stops.
		vector1.add(dt->getValue());
		dt = dt->getNextCell();
	}
	vector1.add(dt->getValue());//Since the while loop stops at the last one, it does not add its value. This line of code does.
	dt = _cellNodeVector[search2]->getCell();
	while ((dt->getNextCell() != NULL)) {//Goes through and adds the values of each cell to the vector until the last one is reached. Then it stops.
		vector2.add(dt->getValue());
		dt = dt->getNextCell();
	}
	vector2.add(dt->getValue());//Since the while loop stops at the last one, it does not add its value. This line of code does.
	cout << endl;
	delete dt;
	for (int i = 0; i < vector1.sizeReturn(); i++) {//Checks for values exclusive to each vector
		for (int j = 0; j < vector2.sizeReturn(); j++) {
			if (vector1[i] == vector2[j]) {
				break;
			}
			else if(j == vector2.sizeReturn()-1){
				if (vector1[i] != vector2[j]) {
					vector3.add(vector1[i]);
					break;
				}
				continue;
			}
		}
	}
	for (int i = 0; i < vector2.sizeReturn(); i++) {//Checks for values exclusive to each vector
		for (int j = 0; j < vector1.sizeReturn(); j++) {
			if (vector2[i] == vector1[j]) {
				break;
			}
			else if (j == vector1.sizeReturn() - 1) {
				if (vector2[i] != vector1[j]) {
					vector3.add(vector2[i]);
					break;
				}
				continue;
			}
		}
	}
	vector3.remove(vector3.sizeReturn() - 1);
	return vector3;
}

template <class DT1, class DT2>
Vector<int> MasterCell<DT1, DT2>::xorFunction(Vector<int> search1, int search2) {//Displays content that are not common in either linked list. Used for input with multiple operations										
	Vector<int> vector2;														 
	Vector<int> vector3;
	Cell<DT2>* dt = _cellNodeVector[search2]->getCell();//Pointer used to traverse linked list
	while ((dt->getNextCell() != NULL)) {//Goes through and adds the values of each cell to the vector until the last one is reached. Then it stops.
		vector2.add(dt->getValue());
		dt = dt->getNextCell();
	}
	vector2.add(dt->getValue());//Since the while loop stops at the last one, it does not add its value. This line of code does.
	cout << endl;
	delete dt;
	for (int i = 0; i < search1.sizeReturn(); i++) {//Checks for exclusive values
		for (int j = 0; j < vector2.sizeReturn(); j++) {
			if (search1[i] == vector2[j]) {
				break;
			}
			else if (j == vector2.sizeReturn() - 1) {
				if (search1[i] != vector2[j]) {
					vector3.add(search1[i]);
					break;
				}
				continue;
			}
		}
	}
	for (int i = 0; i <= vector2.sizeReturn(); i++) {//Checks for exclusive values
		for (int j = 0; j <= search1.sizeReturn(); j++) {
			if (vector2[i] == search1[j]) {
				break;
			}
			else if (j == search1.sizeReturn()-1 ) {
				if (vector2[i] != search1[j]) {
					vector3.add(vector2[i]);
					break;
				}
				continue;
			}
		}
	}
	return vector3;
}

template <class DT1, class DT2>
MasterCell<DT1, DT2>::~MasterCell() {//Destructor for MasterCell
	cout << "Destructor of MasterCell Called";
}
int main() {
	char aChar;
	char blank;
	char comma;
	int values;
	int numberOfCells;
	int numLines;//For the first line. Indicates how many times to read each line
	int numCount = 0;//Used to keep track of the loop and make sure it does not input any command lines into a cell
	cin >> numLines;
	cin.get(blank);
	MasterCell<CellNode<Vector<char>, Cell<int>>, int> masterCell;
	while (numCount < numLines && !cin.eof()) {//Gets info for the CellNode by adding it to the vector
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
		numCount++;//increments numCount so that it won't read in commands
	}
	//Testing the findKeyWords function with different inputs
	cout << "Testing the findKeyWords function using 5000";
	masterCell.findKeyWords(5000);
	cout << "Testing the findKeywords function using 20: ";
	masterCell.findKeyWords(20);
	cout << endl;
	cout << "Testing the findKeywords function using 89: ";
	masterCell.findKeyWords(89);
	cout << endl;
	cout << "Testing the findKeywords function using -1: ";
	masterCell.findKeyWords(-1);
	cout << endl;
	cout << "Testing the findKeyWords function using 434: ";
	masterCell.findKeyWords(434);
	cout << endl;
	char ac;
	Vector<char> commandList;//Holds the commands from the file (&,|,%)
	Vector<int> numberOfCommands;//Holds how many commands there are in each line
	Vector<int> arrayPlaceHolder;//Used to hold the array index of each of the inputs from the file
	int commandNumber = 0;
	while (!cin.eof()) {//Loops through the file, and based on the inputs, performs operations and prints data
		Vector<char> temp;//Used to hold the input from the file so it can be sent to string match to get its array index
		do {
			
			cin.get(ac);
			if (ac != '\n') {
				if (ac == '&') {
					commandNumber++;
					commandList.add(ac);
					arrayPlaceHolder.add(masterCell.stringMatch(temp));//Gets the array index according to input
					cin.get(ac);
					break;
				}
				else if (ac == '|') {
					commandNumber++;
					commandList.add(ac);
					arrayPlaceHolder.add(masterCell.stringMatch(temp));//Gets the array index according to input
					cin.get(ac);
					break;
				}
				else if (ac == '%') {
					commandNumber++;
					commandList.add(ac);
					arrayPlaceHolder.add(masterCell.stringMatch(temp));//Gets the array index according to input
					cin.get(ac);
					break;
				}
				else {
					temp.add(ac);//adds a character to temp so it can be used for stringMatch function
				}
			}
			
			if (ac == '\n' || cin.eof()) {//At the end of the line or file
				numberOfCommands.add(commandNumber);
				arrayPlaceHolder.add(masterCell.stringMatch(temp));//Gets index of the last input in the line/file
				cout << " ";
				commandList.display();
				Vector<int> values;
				for (int i = 0; i < commandNumber; i++) {
					if (commandList[i] == '&') {
						if (i == 0) {//For the first input, uses the array index of each input to perform operation
							
							 Vector<int> tempVector = masterCell.andFunction(arrayPlaceHolder[i], arrayPlaceHolder[i + 1]);
							 for (int i = 0; i <= tempVector.sizeReturn(); i++) {
								 int h = (tempVector[i]);
								 values.add(h);
							 }
							continue;
						}
						else {//For the second input, uses the vector of values from previous operations and the array index of the next input
							Vector<int> tempVector = masterCell.andFunction(values, arrayPlaceHolder[i + 1]);
							values = tempVector;
							continue;
						}
					}
					else if (commandList[i] == '|') {//For the first input, uses the array index of each input to perform operation
						if (i == 0) {
							Vector<int> tempVector = masterCell.orFunction(arrayPlaceHolder[i], arrayPlaceHolder[i + 1]);
							for (int i = 0; i <= tempVector.sizeReturn(); i++) {
								int h = (tempVector[i]);
								values.add(h);
							}
							continue;
						}
						else {//For the second input, uses the vector of values from previous operations and the array index of the next input
							Vector<int> tempVector = masterCell.orFunction(values, arrayPlaceHolder[i + 1]);
							values = tempVector;
							continue;
						}
					}
					else if (commandList[i] == '%') {//For the first input, uses the array index of each input to perform operation
						if (i == 0) {
							Vector<int> tempVector = masterCell.xorFunction(arrayPlaceHolder[i], arrayPlaceHolder[i + 1]);
							for (int i = 0; i <= tempVector.sizeReturn(); i++) {
								int h = (tempVector[i]);
								values.add(h);
							}
							continue;
						}
						else {//For the second input, uses the vector of values from previous operations and the array index of the next input
							Vector<int> tempVector = masterCell.xorFunction(values, arrayPlaceHolder[i + 1]);
							values = tempVector;
							continue;
						}
					}
				}
				if (values[0] < 0) { //If there are no values after operations
					cout << " No values to display using these operands" << endl;
					cout << endl;
					//break;
					while (commandList.sizeReturn() != 0) {//clears commandList of commands
						commandList.remove(0);
					}
					while (arrayPlaceHolder.sizeReturn() != 0) {//clears arrayPlaceHolder of array indexes 
						arrayPlaceHolder.remove(0);
					}
					commandNumber = 0;//sets number of commands back to zero for the next line of inputs
					break;
				}
				else {//If there are values after operations
					cout << " Values after all operations: " << endl;
					for (int i = 0; i < values.sizeReturn()-1; i++) {//Prints values
						cout << values[i] << " ";
					}
					cout << endl << endl;
					while (commandList.sizeReturn() != 0) {//clears commandList of commands
						commandList.remove(0);
					}
					while (arrayPlaceHolder.sizeReturn() != 0) {//clears arrayPlaceHolder of array indexes 
						arrayPlaceHolder.remove(0);
					}
					commandNumber = 0;//sets number of commands back to zero for the next line of inputs
					break;
				}
			}
		} while ((ac != '\n') && !cin.eof());
	}
	
}