#include <iostream>
using namespace std;

//CS 2413
//Shobey Stanley
//OU ID: 112808884

//This class will hold the url from the file. Will be inserted into tab class.
class webAddressInfo
{
private:
	int length = 0;//Used to tell the display method when to stop printing the url array
	char url[201]; //allow a maximum of 200 characters
public:
	webAddressInfo(); //Default constructor
	webAddressInfo(char newUrl[201]); //Constructor with parameters
	void setAddressLength(int newLength); //Sets new length
	void setWebAddressInfo(char newUrl[201]);//Saves the url from the parameter so that it can be displayed when needed
	void display();//Displays character by character the url
};

//Methods for webAddressInfo class
webAddressInfo::webAddressInfo() {//Empty constructor
}
webAddressInfo::webAddressInfo(char newUrl[201]) {//Constructor with char array to save url
	for (int i = 0; i < 201; i++) {
		url[i] = newUrl[i];
	}
}
void webAddressInfo::setAddressLength(int newLength) {//Sets the length for the individual url
	length = newLength;
}
void webAddressInfo::setWebAddressInfo(char newUrl[201]) {//Sets the url array values
	for (int i = 0; i < 201; i++) {
		url[i] = newUrl[i];
	}
}

void webAddressInfo::display(void) {//Prints out character by character from the url array
	cout << "The url is: ";
	for (int i = 0; i < length; i++) {
		if (url[i] != '\0') {
			cout << url[i];
		}
	}
	cout << endl;
}


//This class will contain the url. Will keep index of urls with numAddress and currentAddress variables.
class tab {
private:
	int numAddress = 0;
	int numOfAddresses = 0;//Used to keep track of the total number of addresses within the tab object
	int currentAddress = 0;//Used to keep track of the address position within the array of type webAddressInfo
	int tabIdentifier = 0;//Used within main function to identify tabs and save webAddressInfo objects to them accordingly
	webAddressInfo webAddresses[30];//Array which holds webAddressInfo objects for each specific tab
public:
	tab();//Default Constructor
	tab(webAddressInfo webAddress,int tabID);//Constructor with parameters
	int getTabID();//Returns the tabIdentifier
	void setTabID(int newID);//Sets the tabIdentifier of the tab object
	void addWebAddress(webAddressInfo url);//Adds a new webAddressInfo object to the tab's array of webAddressInfo objects
	int getNumOfAddresses();//Displays the total number of addresses
	int getCurrentAddress();//Displays the current address
	void forward();//Used by the main function's switch statement. Increments currentAddress.
	void backward();//Used by the main function's switch statement. Decrements currentAddress.
	webAddressInfo getWebAddress();//Returns the current webAddressInfo object
	
};
tab::tab() {//Defualt Constructor
	numAddress = 0;
	currentAddress = 0;
}
tab::tab(webAddressInfo url, int tabID) {//Constructor with parameters
	tabIdentifier = tabID;
	webAddresses[currentAddress] = url;
	
}
int tab::getTabID() {//Returns the tabIdentifier
	return tabIdentifier;
}
void tab::setTabID(int newID) {//Sets the tabIdentifier of the tab object
	tabIdentifier = newID;
}
void tab::addWebAddress(webAddressInfo url) {//Adds a new webAddressInfo object to the tab's array of webAddressInfo objects
	currentAddress++;
	webAddresses[currentAddress] = url;
	numOfAddresses++;
}
int tab::getNumOfAddresses() {//Displays the total number of addresses
	return numOfAddresses;
}
int tab::getCurrentAddress() {//Displays the current address
	return currentAddress;
}
void tab::forward() {//Used by the main function's switch statement. Increments currentAddress.
	currentAddress++;
}
void tab::backward() {//Used by the main function's switch statement. Decrements currentAddress.
	currentAddress--;
}

webAddressInfo tab::getWebAddress() {//Returns the current webAddressInfo object
	return webAddresses[currentAddress];
}

//This class will hold the tab. The tabs will be identified by a tab number, which can then be used to access the tab, and that tab's webAddresses.
class browserTab {
protected:
	int numberOfTabs = 0;//Total number of tabs within the browser
	tab tabList[20];//Holds the tab objects
	
	
public:
	browserTab();//Default constructor
	browserTab(int tabNum);//Constructor with parameters
	int getNumberOfTabs();//Used to retrieve the numberOfTabs
	tab& getTab(int abNum);//Used to retrieve a tab object within the array of tab objects
	void addNewTab(tab newTab);//Adds a new tab to the array of tab objects
	int getTabID(int tabNum);//Returns the tabID of a tab
	void setTab(tab newTab, int tabNum);
};
browserTab::browserTab() {//Default constructor
	
}
browserTab::browserTab(int newTabNum) {//Constructor with parameters
	numberOfTabs = newTabNum;
}

int browserTab::getNumberOfTabs() {//Used to retrieve the numberOfTabs
	return numberOfTabs;
}
tab& browserTab::getTab(int tabNum) {//Used to retrieve a tab object within the array of tab objects
	
	for (int i = 0; i < 20; i++) {
		if (tabList[i].getTabID() == tabNum) {
			tab& temp= tabList[i];
			return temp;
			break;
		}
	}
}
void browserTab::addNewTab(tab newTab) {//Adds a new tab to the array of tab objects
	tabList[numberOfTabs] = newTab;
	numberOfTabs++;
	
}
int browserTab::getTabID(int tabNum) {//make a parameter using an int that will specific which tab to return
	int idReturn;
	for (int i = 0; i < 20; i++) {
		if (tabList[i].getTabID() == tabNum) {
			idReturn = tabNum;
			return idReturn;
		}
	}
}
void browserTab::setTab(tab newTab, int tabNum) {
	tabList[0] = newTab;
}



int main() {
	browserTab browserList;
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
		switch (command) {
			case 'N': {//Command is N. Creates to url
				i = 0;
				cin.get(blank);
				do {
					cin.get(aChar);
					if (aChar != '\n') {
						webAddress[i++] = aChar;
					}
				} while ((aChar != '\n') && (i < 201) && !cin.eof());
			webAddressInfo address(webAddress);//Creates a webAddressInfo object to be stored in the proceeding if-statements
			length = i;
			address.setAddressLength(length);
			if (browserList.getNumberOfTabs() == 0) {//If there are no tabs, this if-statement is used
				tab newTab(address, tabNumber);
				browserList.addNewTab(newTab);
				browserList.getTab(tabNumber).getWebAddress().setAddressLength(length);
				cout << "A new tab is created. Its tab is: " << tabNumber << endl;
				cout << "Its address is: ";
				browserList.getTab(tabNumber).getWebAddress().display();
				cout << endl << endl;
			}
			else if (browserList.getTabID(tabNumber) == (tabNumber)) {//Checks to see if the tab exists. If it does, it will add the webAddressInfo object to that tab
				browserList.getTab(tabNumber).addWebAddress(address);
				browserList.getTab(tabNumber).getWebAddress().setAddressLength(length);
				cout << "Tab exists " << tabNumber << ". Adding new web address to this tab";
				cout << "The web address is : ";
				browserList.getTab(tabNumber).getWebAddress().display();
				cout << endl << endl;
			}
			else {//If tab does not exist, this will create a new one and add the webAddressInfo object to it.
				tab newTab(address,tabNumber);
				browserList.addNewTab(newTab);
				browserList.getTab(tabNumber).getWebAddress().setAddressLength(length);
				cout << "A new tab is created. Its tab is: " << tabNumber << endl;
				cout << "Its address is: ";
				browserList.getTab(tabNumber).getWebAddress().display();
				cout << endl << endl;
			}
			break;
		}
		case 'F': { //Forward
			
			if (browserList.getTab(tabNumber).getNumOfAddresses() > browserList.getTab(tabNumber).getCurrentAddress()) {
				cout << "Forward" << endl;
				cout << "Before forward is press: " << endl;
				browserList.getTab(tabNumber).getWebAddress().display();
				cout << "After forward is pressed: " << endl;
				browserList.getTab(tabNumber).forward();
				browserList.getTab(tabNumber).getWebAddress().display();
				cout << endl << endl;
			}
			else {
				cout << "Cannot go forward any further" << endl;
			}
			break;
		}
			case 'B': { //Backward
				if (browserList.getTab(tabNumber).getCurrentAddress() == 0) {
					cout << "Cannot go backward any further" << endl;
				}
				else {
					cout << "backward" << endl;
					cout << "Before back is pressed: " << endl;
					browserList.getTab(tabNumber).getWebAddress().display();
					browserList.getTab(tabNumber).backward();
					cout << "After back is pressed: " << endl;
					browserList.getTab(tabNumber).getWebAddress().display();
					cout << endl << endl;
				}
				break;
			}
			case 'P': { //Print current
				cout << "Printing current address...  " << endl;
				browserList.getTab(tabNumber).getWebAddress().display();
				cout << endl << endl;
				break;
			}
			default: { //illeagal action}
				cout << "Incorrect input. Input must be N,F,B, or P" << endl;
			}
		}
	}
	return 0;
}//End of Program
