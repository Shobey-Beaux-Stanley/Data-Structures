#include <iostream>

using namespace std;
class ArrayException : public exception {};
class ArrayMemoryException : public ArrayException {};
class ArrayBoundsException : public ArrayException {};
class wrongInputException : public exception {};//used in main program for wrong inputs
class wrongTabException : public exception {};//used in program for tabs that don't exist
#ifndef _ABSTRACTARRAY_H
#define _ABSTRACTARRAY_H

//CS 2413
//Shobey Stanley
//OU ID: 112808884
//project 2



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
};
template<class DT>
Vector<DT>::Vector() :ArrayClass<DT>() {//default constructor
	currentSize = 0;
	incFactor = 5;
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
#endif


//This class will contain the url. Will keep index of urls with numAddress and currentAddress variables.
template <class DT>
class tab {
private:
	int numAddress = 0;
	int numOfAddresses = 0;//Used to keep track of the total number of addresses within the tab object
	int currentAddress = 0;//Used to keep track of the address position within the array of type webAddressInfo
	int tabIdentifier = 0;//Used within main function to identify tabs and save webAddressInfo objects to them accordingly
	Vector<DT> webAddresses;//Used to hold the addresses from the text file

public:
	tab();//Default Constructor
	tab(DT& address, int tabID);//Constructor with parameters
	int getTabID();//Returns the tabIdentifier
	void setTabID(int newID);//Sets the tabIdentifier of the tab object
	void addWebAddress(DT& url);//Adds a new webAddressInfo object to the tab's array of webAddressInfo objects ////was Vector<DT>&
	int getNumOfAddresses();//Displays the total number of addresses
	int getCurrentAddress();//Displays the current address
	void forward();//Used by the main function's switch statement. Increments currentAddress.
	void backward();//Used by the main function's switch statement. Decrements currentAddress.
	DT& getWebAddress();//returns webAddress of vector
	void decrementTabID();
	~tab();//Destructor for tab
};
template <class DT>
tab<DT>::tab() {//Defualt Constructor
	numAddress = 0;
	currentAddress = 0;
}
template <class DT>
tab<DT>::tab(DT& address, int tabID) {//Constructor with parameters
	tabIdentifier = tabID;
	webAddresses.add(address);

}
template <class DT>
int tab<DT>::getTabID() {//Returns the tabIdentifier
	return tabIdentifier;
}
template <class DT>
void tab<DT>::setTabID(int newID) {//Sets the tabIdentifier of the tab object
	tabIdentifier = newID;
}
template <class DT>
void tab<DT>::addWebAddress(DT& url) {//Adds a new webAddressInfo object to the tab's array of webAddressInfo objects
	currentAddress++;
	webAddresses[currentAddress] = url;
	numOfAddresses++;
}
template <class DT>
int tab<DT>::getNumOfAddresses() {//Displays the total number of addresses
	return numOfAddresses;
}
template <class DT>
int tab<DT>::getCurrentAddress() {//Displays the current address
	return currentAddress;
}
template <class DT>
void tab<DT>::forward() {//Used by the main function's switch statement. Increments currentAddress.
	currentAddress++;
}
template <class DT>
void tab<DT>::backward() {//Used by the main function's switch statement. Decrements currentAddress.
	currentAddress--;
}
template <class DT>
DT& tab<DT>::getWebAddress() {//Returns the current webAddressInfo object
	return webAddresses[currentAddress];
}
template <class DT>
void tab<DT>::decrementTabID() {//Decements the tab Identifiers for the tab
	tabIdentifier--;
}

template <class DT>
tab<DT>::~tab() {//destructor for tab class
}

//This class will hold the tabs. The tabs will be identified by a tab number, which can then be used to access the tab, and that tab's webAddresses.
template <class DT>
class browserTab {
protected:
	int numberOfTabs = 0;//Total number of tabs within the browser
	Vector<DT> tabList;//Holds the tab objects


public:
	browserTab();//Default constructor
	browserTab(int tabNum);//Constructor with parameters
	int getNumberOfTabs();//Used to retrieve the numberOfTabs
	DT& getTab(int abNum);//Used to retrieve a tab object within the array of tab objects
	void addNewTab(DT& newTab);//Adds a new tab to the array of tab objects ///Was tab<DT>&
	void setTab(tab<DT> newTab, int tabNum);
	void removeTab(int tabNumber);
	void moveTab(int tabNumber, int mTab);
	int checkExist(int tabNumber);
	int getIndex(int tabNumber);
	ostream& operator<< (double x);// changed this to return type
	~browserTab();//Destructor for browserTab

};
template <class DT>
browserTab<DT>::browserTab() {//Default constructor
	numberOfTabs = 0;
}
template <class DT>
browserTab<DT>::browserTab(int newTabNum) {//Constructor with parameters
	numberOfTabs = newTabNum;
}
template <class DT>
int browserTab<DT>::getNumberOfTabs() {//Used to retrieve the numberOfTabs
	return numberOfTabs;
}

template <class DT>//Adding Check Exist
DT& browserTab<DT>::getTab(int tabNum) {//Used to retrieve a tab object within the array of tab objects //was tab<DT>&:
	for (int i = 0; i < numberOfTabs; i++) {
		if (tabList[i].getTabID() == tabNum) {
			DT& temp = tabList[i];
			return temp;
			break;
		}
	}
}

template <class DT>
void browserTab<DT>::addNewTab(DT& newTab) {//Adds a new tab to the array of tab objects
	tabList.add(newTab);
	numberOfTabs++;
}

template <class DT>
void browserTab<DT>::setTab(tab<DT> newTab, int tabNum) {
	tabList[0] = newTab;
}
template <class DT>
browserTab<DT>::~browserTab() {//Destructor for browserTab class
	cout << "deleting browserTab";
}
template <class DT>
void browserTab<DT>::removeTab(int tabNumber) {//Removes selected tab and sets the other tabs' IDs accordingly
	int j = getIndex(tabNumber);
	tabList.remove(j);
	for (int i = tabNumber; i <= numberOfTabs; i++) {
		tabList[i].decrementTabID();
	}
	
}
template <class DT>
int browserTab<DT>::getIndex(int tabNumber) {//Returns the index of the tab specified tab number
	for (int i = 0; i <= tabList.sizeReturn(); i++) {
		if (tabList[i].getTabID() == tabNumber) {
			return i;
		}
	}
}
template <class DT>
void browserTab<DT>::moveTab(int tabNumber, int mTab) {//Moves tab and changes tab IDs accordingly
	if (tabNumber < mTab) {
		getTab(tabNumber).setTabID(0);//temporarily moves the tab so there is not a duplicate while setting tabs numbers
		for (int i = tabNumber + 1; i <= mTab; i++) {
			getTab(i).setTabID(i - 1);
		}
		getTab(0).setTabID(mTab);
	}
	if (tabNumber > mTab) {
		getTab(tabNumber).setTabID(0);
		int j = tabNumber;
		for (int i = (tabNumber - 1); i > mTab; i--) {
			if (checkExist(i) != 0) {
				getTab(i).setTabID(j);
			}
			else if (checkExist(i) == 0) {
				if ((i - 1) > mTab) {
					getTab(i - 1).setTabID(j);
				}
				else {
					break;
				}
			}
			j--;
		}
		getTab(0).setTabID(mTab);
	}
}
template <class DT>
int browserTab<DT>::checkExist(int tabNumber) {//checks to make sure a tab exists
	int idReturn;
	for (int i = 0; i <= tabList.sizeReturn(); i++) {
		if (tabList[i].getTabID() == tabNumber) {
			idReturn = tabNumber;
			return idReturn;
		}
		else if (i == tabList.sizeReturn()) {
			return 0;
		}
	}
}
template <class DT>
ostream &browserTab<DT>::operator<< (double x) {
	return v.getWebAddress().display();
}
int main() {
	browserTab<tab<Vector<char>>> browserList;

	char command;
	char aCString[201];
	char blank;
	char action;
	char aChar;

	char webAddress[201];
	int tabNumber = 0;
	int i;
	int length;

	while (!cin.eof()) // while end of line is not reached
	{

		cin >> tabNumber;
		cin.get(blank);
		cin.get(command);
		try {
			switch (command) {
			case 'N': {//Command is N. Creates to url
				Vector<char> v;
				i = 0;
				cin.get(blank);
				do {
					cin.get(aChar);
					if (aChar != '\n') {
						v.add(aChar);
					}
				} while ((aChar != '\n') && !cin.eof());
				if (browserList.getNumberOfTabs() == 0) {//If there are no tabs, this if-statement is used
					tab<Vector<char>> newTab(v, tabNumber);
					browserList.addNewTab(newTab);
					cout << "A new tab is created. Its tab is: " << tabNumber << endl;
					cout << "Its address is: ";
					browserList.getTab(tabNumber).getWebAddress().display();
					cout << endl << endl;
				}
				else if (browserList.checkExist(tabNumber) != 0) {//Checks to see if the tab exists. If it does, it will add the webAddressInfo object to that tab
					cout << "Tab exists " << tabNumber << ". Adding new web address to this tab";
					cout << "The web address is : ";
					browserList.getTab(tabNumber).addWebAddress(v);
					browserList.getTab(tabNumber).getWebAddress().display();
					cout << endl << endl;
				}
				else {//If tab does not exist, this will create a new one and add the webAddressInfo object to it.
					tab<Vector<char>> newTab(v, tabNumber);
					browserList.addNewTab(newTab);
					cout << "A new tab is created. Its tab is: " << tabNumber << endl;
					cout << "Its address is: ";
					browserList.getTab(tabNumber).getWebAddress().display();
					cout << endl << endl;
				}
				break;

			}

			case 'F': { //Forward
				try {
					if (browserList.checkExist(tabNumber) != 0) {
						if (browserList.getTab(tabNumber).getNumOfAddresses() > browserList.getTab(tabNumber).getCurrentAddress()) {
							cout << "Forward" << endl;
							cout << "Before forward is press: " << endl;
							browserList.getTab(tabNumber).getWebAddress().display();
							cout << " After forward is pressed: " << endl;
							browserList.getTab(tabNumber).forward();
							browserList.getTab(tabNumber).getWebAddress().display();
							cout << endl << endl;
						}
						else {
							cout << "Cannot go forward any further" << endl;
						}
					}
					else {
						throw wrongTabException();
					}
				}
				catch (wrongTabException& e) {
					cout << "Tab does not exist. Cannot go forward";
					cout << endl << endl;
				}
				break;
			}
			case 'B': { //Backward
				try {
					if (browserList.checkExist(tabNumber) != 0) {
						if (browserList.getTab(tabNumber).getCurrentAddress() == 0) {
							cout << "Cannot go backward any further" << endl;
						}
						else {
							cout << "backward" << endl;
							cout << "Before back is pressed: " << endl;
							browserList.getTab(tabNumber).getWebAddress().display();
							browserList.getTab(tabNumber).backward();
							cout << " After back is pressed: " << endl;
							browserList.getTab(tabNumber).getWebAddress().display();
							cout << endl << endl;
						}
					}
					else {
						throw wrongTabException();
					}
				}
				catch (wrongTabException& e) {
					cout << "Tab does not exist. Cannot go backwards.";
					cout << endl << endl;
				}
				break;
			}
			case 'P': { //Print current
				try {
					if (browserList.checkExist(tabNumber) != 0) {
						cout << "Printing current address...  " << endl;
						browserList.getTab(tabNumber).getWebAddress().display();
						cout << endl << endl;
						break;
					}
					else {
						throw wrongTabException();
					}
				}
				catch (wrongTabException& e) {//If the tab does not exist
					cout << "Tab does not exist. Cannot Print.";
					cout << endl << endl;
				}

			}
			case 'C': {//Changes the current address based on input
				try {
					if (browserList.checkExist(tabNumber) != 0) {
						cout << "Change Selected " << endl;
						Vector<char> v;
						i = 0;
						cin.get(blank);
						do {
							cin.get(aChar);
							if (aChar != '\n') {
								webAddress[i++] = aChar;
								v.add(aChar);
							}
						} while ((aChar != '\n') && (i < 201) && !cin.eof());
						cout << "Before Change: " << endl;
						browserList.getTab(tabNumber).getWebAddress().display();
						cout << endl;
						cout << "After Change: " << endl;
						browserList.getTab(tabNumber).getWebAddress() = v;
						browserList.getTab(tabNumber).getWebAddress().display();
						cout << endl << endl;
					}
				}
				catch (wrongTabException& e) {//If the tab does not exist
					cout << "Tab does not exist. Cannot change  current address";
					cout << endl << endl;
				}
				break;
			}
			case 'R': {//Removes a tab and all of its addresses
				try {
					if (browserList.checkExist(tabNumber) != 0) {
						if (browserList.getTab(tabNumber).getTabID() == tabNumber) {
							cout << "Remove Selected for tab: " << tabNumber << endl;
							cout << "Before removing the tab, tab number " << tabNumber << " current address is ";
							browserList.getTab(tabNumber).getWebAddress().display();
							cout << endl;
							browserList.removeTab(tabNumber);
						}
					}
					else {
						throw wrongTabException();
					}
				}
				catch (wrongTabException& e) {//If the tab does not exist
					cout << "Cannot remove tab. Tab not found/does not exist" << endl;
				}
				cout << endl << endl;
				break;
			}
			case 'M': {//Moves a tab to the specified tab
				try {

					if (browserList.checkExist(tabNumber) != 0) {
						int mTab = 0;
						cin >> mTab;
						cout << "Move Selected for tab: " << tabNumber << endl;
						cout << "Moving tab " << tabNumber << " before tab " << mTab << endl;
						browserList.moveTab(tabNumber, mTab);
						cout << endl;

					}
					else {//Used if tab input is not correct
						throw wrongTabException();
					}
				}
				catch (wrongTabException& e) {//If tab does not exist
					cout << " Tab does not exist. Cannot Move";

				}
				cout << endl;
				break;
			}
			default: {//If none of the inputs are correct, this will throw an error and handle it
				throw wrongInputException();
			}
			}
		}
		catch (wrongInputException& e) {//Reuses code from above in case there is input after incorrect command
			Vector<char> v;
			i = 0;
			do {
				cin.get(aChar);
				if (aChar != '\n') {
					webAddress[i++] = aChar;
					v.add(aChar);
				}
			} while ((aChar != '\n') && !cin.eof());
			if (v.sizeReturn() != 0) {
				if (browserList.getNumberOfTabs() == 0) {//If there are no tabs, this if-statement is used
					tab<Vector<char>> newTab(v, tabNumber);
					browserList.addNewTab(newTab);
					cout << "A new tab is created. Its tab is: " << tabNumber << endl;
					cout << "Its address is: ";
					browserList.getTab(tabNumber).getWebAddress().display();
					cout << endl << endl;
				}
				else if (browserList.getTab(tabNumber).getTabID() == (tabNumber)) {//Checks to see if the tab exists. If it does, it will add the webAddressInfo object to that tab
					browserList.getTab(tabNumber).addWebAddress(v);
					cout << "Tab exists " << tabNumber << ". Adding new web address to this tab";
					cout << "The web address is : ";
					browserList.getTab(tabNumber).getWebAddress().display();
					cout << endl << endl;
				}
				else {//If tab does not exist, this will create a new one and add the webAddressInfo object to it.
					tab<Vector<char>> newTab(v, tabNumber);
					browserList.addNewTab(newTab);
					cout << "A new tab is created. Its tab is: " << tabNumber << endl;
					cout << "Its address is: ";
					browserList.getTab(tabNumber).getWebAddress().display();
					cout << endl << endl;
				}
			}
		}

	}
	return 0;
}//End of Program