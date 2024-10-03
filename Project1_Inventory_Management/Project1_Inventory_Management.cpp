#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

class item {
private:
	string name;
	string unit;
	int quantity;
	double price;
	short minInStock;
	bool toBeOrdered;

public:

	//constructors
	item() {
		toBeOrdered = false;
	}

	item(string n, string u, int q, double p, short m) {
		name = n;
		unit = u;
		quantity = q;
		price = p;
		minInStock = m;
		toBeOrdered = false;
	}
	//getters
	string getName() {
		return name;
	}
	string getUnit() {
		return unit;
	}
	int getQuantity() {
		return quantity;
	}
	double getPrice() {
		return price;
	}
	short getMinInStock() {
		return minInStock;
	}
	bool getToBeOrdered() {
		if (quantity < minInStock) {
			toBeOrdered = true;
		}
		else {
			toBeOrdered = false;
		}
		return toBeOrdered;
	}
	string printTBO() {
		if (toBeOrdered == true) {
			return "Yes";

		}
		else {
			return "No";
		}
	}

	//setters
	void setName(string n) {
		name = n;
	}
	void setUnit(string u) {
		unit = u;
	}
	void setQuantity(int q) {
		quantity = q;
	}
	void setPrice(double p) {
		price = p;
	}
	void setMinInStock(short m) {
		minInStock = m;
	}
	void checkTBO() {
		if (quantity < minInStock) {
			toBeOrdered = true;
		}
		else {
			toBeOrdered = false;
		}
	}


};
//function prototypes

void printList(item[], int);
void printListByIndex(item[], int, int[]);

void editItem(item[], int);

void searchList(item[], int);

int searchByNumber(item[], int);
int searchByName(item [], int);
int searchByUnit(item[], int);
int searchByQuantity(item[], int);
int searchByPrice(item[], int);
int searchByMIS(item [], int );
int searchByTBO(item[], int);

void sortList(item[], int);

void alphabeticSort(item[], int);
void unitSort(item[], int);
void quantitySort(item[], int);
void priceSort(item[], int);
void tboSort(item[], int);

void swap(int, int, item[], int);

//main
int main()
{

	srand(time(nullptr));

	int listSize = 0;
	string inputs;
	cout << "WELCOME TO GLENN'S INVENTORY MANAGEMENT SYSTEM V.0.1.0" << endl;
	cout << "!!!PLEASE INPUT THE NUMBER OF ITEMS YOU WISH TO CREATE!!!" << endl;

	cin >> listSize; //edge case, leaves \n in the input buffer
	//cout << sizeof(n) << endl;
	//cout << "n:" << n << endl;
	while (listSize <= 0) {
		cout << "!!![ERROR, VALUE MUST BE GREATER THAN 0]!!!\n";
		cin >> listSize;
	}

	getline(cin, inputs); //eats extra \n char in the input buffer or else getline() runs twice w/o it

	cout << "YOU HAVE CREATED " << listSize << " ITEMS" << endl;

	item* list = new item[listSize];

	cout << "PLEASE INPUT DATA IN THIS ORDER, SEPERATED BY COMMAS" << endl;
	cout << "---------\n";
	cout << "NAME, UNIT, QUANTITY, PRICE, MINIMUM AMOUNT IN STOCK\n";
	cout << "---------\n";


	string name;
	string unit;


	//increments whole string and sections each bit out
	for (int i = 0; i < listSize; i++){
		cout << "PLEASE INPUT DATA FOR ITEM " << i + 1 << endl;
		getline(cin, inputs);

		int cursor;

		//sets name
		for (int x = 0; x < inputs.length(); x++) {
			if (inputs[x] != ',') { //stops at the first comma
				name += inputs[x]; //adds every charachter before that to 'name'
			}
			else {
				cursor = x;
				break;
			}
		}
		list[i].setName(name);
		name = "";

		//sets unit
		for (int x = cursor+1; x < inputs.length(); x++) { //starts at comma+1
			if (inputs[x] != ' ') { //as long as its not a space
				if (inputs[x] != ',') { //and if it's not a comma
					unit += inputs[x]; //add the charachter to unit
				}
				else {
					cursor = x;
					break;
				}
			}
		}
		list[i].setUnit(unit);
		unit = "";

		string tempString; //temporary string to hold the value of the current section of input
		
		//sets quantity
		for (int x = cursor + 1; x < inputs.length(); x++) { 
			if (inputs[x] != ' ') { 
				if (inputs[x] != ',') {
					tempString += inputs[x]; //turn into its own string and then make quantity = substring
				}
				else {
					cursor = x;
					break;
				}
			}
		}

		list[i].setQuantity(stoi(tempString));
		tempString = "";

		//sets price
		for (int x = cursor + 1; x < inputs.length(); x++) {
			if (inputs[x] != ' ') {
				if (inputs[x] != ',') {
					tempString += inputs[x]; 
				}
				else {
					cursor = x;
					break;
				}
			}
		}
		list[i].setPrice(stod(tempString));
		tempString = "";

		//sets minInStock
		for (int x = cursor + 1; x < inputs.length(); x++) {
			if (inputs[x] != ' ') {
				if (inputs[x] != ',') {
					tempString += inputs[x]; 
				}
				else {
					//cursor = x;  //redundant, maybe save for future if more values are added
					break;
				}
			}
		}
		list[i].setMinInStock(stoi(tempString));
		tempString = "";

		list[i].checkTBO();

	}
	cout << "PRINTING LIST....\n";

	printList(list, listSize);

	bool quit = false;
	while (quit == false) {

		int input;
		cout << "\nMAIN MENU:\n" << "------\n";
		cout << "-1 = [QUIT]\n";
		cout << "1  = [SORT LIST]\n";
		cout << "2  = [SEARCH LIST]\n";
		cout << "3  = [PRINT LIST]\n\n";


		cout << "PLEASE INPUT YOUR MENU OPTION\n";
		cin >> input;
		switch(input){
			case -1:
				cout << "YOU HAVE SELECTED [QUIT]\n";
				cout << "QUITTING PROGRAM...\n";
				quit = true;
				break;
			case 1:
				cout << "YOU HAVE SELECTED [SORT LIST]\n";
				sortList(list, listSize);
				break;
			case 2:
				cout << "YOU HAVE SELECTED [SEARCH ITEM]\n";
				searchList(list, listSize);
				break;
			case 3: 
				cout << "YOU HAVE SELECTED [PRINT LIST]\n";
				printList(list, listSize);
				break;
			default:
				cout << "THAT IS NOT A VAID INPUT. PLEASE TRY AGAIN.\n";
				break;
		}
	}
	cout << "random number :)\n";
	cout << rand() << endl;
}


//printing functions
//pass by reference (since array names are pointers to the values)
//pass by value (passes the value of listSize)
void printList(item list[], int listSize) {
	cout << setw(10) << "ITEM #" << left << setw(10) << "NAME" << left << setw(10) << "UNIT" << setw(10) << "QUANTITY" << setw(10) << left << "PRICE";
	cout << setw(15) << "MIN IN STOCK" << setw(10) << "NEEDS RESTOCKING" << endl;
	cout << "--------------------------------------------------------------------- \n";
	for (int i = 0; i < listSize; i++) {
		cout << setw(10) << i << setw(10) << left << list[i].getName() << left << setw(10) << list[i].getUnit();
		cout << setw(10) << list[i].getQuantity() << setw(10) << list[i].getPrice() << setw(15);
		cout << list[i].getMinInStock() << setw(10) << list[i].printTBO() << endl;
	}
	cout << endl;
}

void printListByIndex(item list[], int listSize, int indexList[], int lastElement) {
	cout << setw(10) << "ITEM #" << left << setw(10) << "NAME" << left << setw(10) << "UNIT" << setw(10) << "QUANTITY" << setw(10) << left << "PRICE";
	cout << setw(15) << "MIN IN STOCK" << setw(10) << "NEEDS RESTOCKING" << endl;
	cout << "--------------------------------------------------------------------- \n";
	for (int i = 0; i < lastElement; i++) {

	cout << setw(10) << indexList[i] << setw(10) << left << list[indexList[i]].getName() << left << setw(10) << list[indexList[i]].getUnit();
	cout << setw(10) << list[indexList[i]].getQuantity() << setw(10) << list[indexList[i]].getPrice() << setw(15);
	cout << list[indexList[i]].getMinInStock() << setw(10) << list[indexList[i]].printTBO() << endl;
	}
	cout << endl;
}

void printItem(item list[], int listSize, int i) {
	cout << "YOUR ITEM:\n";
	cout << setw(10) << "ITEM #" << left << setw(10) << "NAME" << left << setw(10) << "UNIT" << setw(10) << "QUANTITY" << setw(10) << left << "PRICE";
	cout << setw(15) << "MIN IN STOCK" << setw(10) << "NEEDS RESTOCKING" << endl;
	cout << "--------------------------------------------------------------------- \n";
	cout << setw(10) << i << setw(10) << left << list[i].getName() << left << setw(10) << list[i].getUnit();
	cout << setw(10) << list[i].getQuantity() << setw(10) << list[i].getPrice() << setw(15);
	cout << list[i].getMinInStock() << setw(10) << list[i].printTBO() << endl;
}

//edit functions, yet to be added
void editItem(item list[], int listSize) {
	cout << "in editItem()\n";
}

//searching functions
void searchList(item list[], int listSize) {
	bool goBack = false;
	while (goBack == false) {

		int input;
		cout << "\nSEARCHING MENU:\n";
		cout << "-1 = [GO BACK]\n";
		cout << "1  = [SEARCH BY ITEM #]\n";
		cout << "2  = [SEARCH BY NAME]\n";
		cout << "3  = [SEARCH BY UNIT]\n";
		cout << "4  = [SEARCH BY QUANTITY]\n";
		cout << "5  = [SEARCH BY PRICE]\n";
		cout << "6  = [SEARCH BY MIN IN STOCK]\n";
		cout << "7  = [SEARCH BY TO BE ORDERED]\n\n";


		cout << "PLEASE INPUT YOUR MENU OPTION\n";
		cin >> input;
		int itemIndex;
		switch (input) {
		case -1:
			cout << "YOU HAVE SELECTED [GO BACK]\n";
			goBack = true;
			break;
		case 1:
			cout << "YOU HAVE SELECTED [SEARCH BY ITEM #]\n";
			itemIndex = searchByNumber(list, listSize);
			printItem(list, listSize, itemIndex);
			break;
		case 2:
			cout << "YOU HAVE SELECTED [SEARCH BY NAME]\n";
			itemIndex = searchByName(list, listSize);
			printItem(list, listSize, itemIndex);
			break;
		case 3:
			cout << "YOU HAVE SELECTED [SEARCH BY UNIT]\n";
			itemIndex = searchByUnit(list, listSize);
			printItem(list, listSize, itemIndex);
			break;
		case 4:
			cout << "YOU HAVE SELECTED [SEARCH BY QUANTITY]\n";
			itemIndex = searchByQuantity(list, listSize);
			printItem(list, listSize, itemIndex);
			break;		
		case 5:
			cout << "YOU HAVE SELECTED [SEARCH BY PRICE]\n";
			itemIndex = searchByPrice(list, listSize);
			printItem(list, listSize, itemIndex);
			break;
		case 6:
			cout << "YOU HAVE SELECTED [SEARCH BY MIN IN STOCK]\n";
			itemIndex = searchByMIS(list, listSize);
			printItem(list, listSize, itemIndex);
			break;
		case 7:
			cout << "YOU HAVE SELECTED [SEARCH BY TO BE ORDERED]\n";
			itemIndex = searchByTBO(list, listSize);
			printItem(list, listSize, itemIndex);
			break;

		default:
			cout << "THAT IS NOT A VAID INPUT. PLEASE TRY AGAIN.\n";
			break;
		}


	}

}

int searchByNumber(item list[], int listSize) {
	cout << "SEARCHING FOR ITEM VIA [ITEM #]\n";
	cout << "PLEASE INPUT ITEM #\n";
	int querey;
	cin >> querey;

	int min = 0;
	int max = listSize - 1;
	int mid = listSize / 2;

	if (mid == querey) {
		return mid;
	}
	else {
		while (mid != querey) {
			if (querey < mid) {
				max = mid;
				mid = (max + mid) / 2;
			}
			if (querey > mid) {
				min = mid;
				mid = (max + mid) / 2;
			}
		}
		return mid;
	}
}
int searchByName(item list[], int listSize) {
	cout << "SEARCHING FOR ITEM VIA [NAME]\n";
	cout << "PLEASE INPUT ITEM NAME\n";
	string querey;
	int* results = new int[listSize];
	int resultsIndex = 0;
	getline(cin, querey);
	getline(cin, querey);
	for (int i = 0; i < listSize; i++) {
		if (querey == list[i].getName()) {
			results[resultsIndex] = i;
			resultsIndex++;
		}
	}
	printListByIndex(list, listSize, results, resultsIndex);
	cout << "PLEASE SELECT THE ITEM YOU ARE LOOKING FOR\n";
	int result;
	cin >> result;
	return result;

}
int searchByUnit(item list[], int listSize) {
	cout << "SEARCHING FOR ITEM VIA [UNIT]\n";
	int* results = new int[listSize];
	int resultsIndex = 0;
	cout << "PLEASE INPUT ITEM UNIT\n";
	string querey;
	cin >> querey;

	for (int i = 0; i < listSize; i++) {
		if (querey == list[i].getUnit()) {
			results[resultsIndex] = i;
			resultsIndex++;
		}
	}
	printListByIndex(list, listSize, results, resultsIndex);
	cout << "PLEASE SELECT THE ITEM YOU ARE LOOKING FOR\n";
	int result;
	cin >> result;
	return result;

	
}
int searchByQuantity(item list[], int listSize ) {
	cout << "SEARCHING FOR ITEM VIA [QUANTITY]\n";
	int *results = new int[listSize];
	int resultsIndex = 0;
	cout << "PLEASE INPUT ITEM QUANTITY\n";
	int querey;
	cin >> querey;

	for (int i = 0; i < listSize; i++) {
		if (querey == list[i].getQuantity()) {
			results[resultsIndex] = i;
			resultsIndex++;
		}
	}
	printListByIndex(list, listSize, results,resultsIndex);
	cout << "PLEASE SELECT THE ITEM YOU ARE LOOKING FOR\n";
	int result;
	cin >> result;
	return result;
}
int searchByPrice(item list[], int listSize) {
	cout << "SEARCHING FOR ITEM VIA [PRICE]\n";
	int* results = new int[listSize];
	int resultsIndex = 0;
	cout << "PLEASE INPUT ITEM PRICE\n";
	double querey;
	cin >> querey;

	for (int i = 0; i < listSize; i++) {
		cout << "i:" << i << endl;
		if (querey == list[i].getPrice()) {

			results[resultsIndex] = i;
			cout << "results[index]: " << results[resultsIndex] << endl;

			resultsIndex++;
		}
	}
	printListByIndex(list, listSize, results, resultsIndex);
	cout << "PLEASE SELECT THE ITEM YOU ARE LOOKING FOR\n";
	int result;
	cin >> result;
	return result;
}
int searchByMIS(item list[], int listSize) {
	cout << "SEARCHING FOR ITEM VIA [MIN IN STOCK]\n";
	int* results = new int[listSize];
	int resultsIndex = 0;
	cout << "PLEASE INPUT ITEM MIN IN STOCK\n";
	int querey;
	cin >> querey;

	for (int i = 0; i < listSize; i++) {
		if (querey == list[i].getMinInStock()) {
			results[resultsIndex] = i;
		}
	}
	printListByIndex(list, listSize, results, resultsIndex);
	cout << "PLEASE SELECT THE ITEM YOU ARE LOOKING FOR\n";
	int result;
	cin >> result;
	return result;
}
int searchByTBO(item list[], int listSize) {
	cout << "SEARCHING FOR ITEM VIA [TO BE ORDERED]\n";
	int* results = new int[listSize];
	int resultsIndex = 0;
	int querey;
	cout << "PLEASE IF INPUT ITEM IS TO BE ORDERED\n 1 FOR YES, 0 FOR NO.\n";
	cin >> querey;

	while ((querey != 0 ) && (querey != 1)) {
		cout << "THAT IS NOT A VALID INPUT. PLEASE TRY AGAIN.\n";
		cin >> querey;
	}

	for (int i = 0; i < listSize; i++) {
		if (querey == list[i].getToBeOrdered()) {
			results[resultsIndex] = i;
			resultsIndex++;

		}
	}

	printListByIndex(list, listSize, results, resultsIndex);
	cout << "PLEASE SELECT THE ITEM YOU ARE LOOKING FOR\n";
	int result;
	cin >> result;
	return result;
}

//sorting functions
void sortList(item list[], int listSize) {
	bool goBack = false;
	while (goBack == false) {

		int input;
			cout << "SORTING MENU:\n";
			cout << "-1 = [GO BACK]\n";
			cout << "1  = [SORT BY NAME]\n";
			cout << "2  = [SORT BY UNIT]\n";
			cout << "3  = [SORT BY QUANTITY]\n";
			cout << "4  = [SORT BY PRICE]\n";
			cout << "5  = [SORT BY T.B.O.]\n\n";

			cout << "PLEASE INPUT YOUR MENU OPTION\n";
			cin >> input;
			switch (input) {
			case -1:
				cout << "YOU HAVE SELECTED [GO BACK]\n";
				goBack = true;
				break;
			case 1:
				cout << "YOU HAVE SELECTED [SORT BY NAME]\n";
				alphabeticSort(list, listSize);

				break;
			case 2:
				cout << "YOU HAVE SELECTED [SORT BY UNIT]\n";
				unitSort(list, listSize);

				break;
			case 3:
				cout << "YOU HAVE SELECTED [SORT BY QUANTITY]\n";
				quantitySort(list, listSize);
				break;
			case 4:
				cout << "YOU HAVE SELECTED [SORT BY PRICE]\n";
				priceSort(list, listSize);
				break;
			case 5:
				cout << "YOU HAVE SELECTED [SORT BY T.B.O.]\n";
				tboSort(list, listSize);
				break;
			default:
				cout << "THAT IS NOT A VAID INPUT. PLEASE TRY AGAIN.\n";
				break;
		}


	}

}

void alphabeticSort(item list[], int listSize) {
	int minIndex;
	string minName;
	for (int i = 0; i < listSize - 1; i++) {
		minIndex = i;
		minName = list[i].getName();

		for (int x = i + 1; x < listSize; x++) {
			if (list[x].getName() < minName) {
				minName = list[x].getName();
				minIndex = x;
			}
		}
		swap(minIndex, i, list, listSize);
	}
	cout << "LIST HAS BEEN SORTED BY [NAME]\n";
}
void unitSort(item list[], int listSize) {
	int minIndex;
	string minUnit;
	for (int i = 0; i < listSize - 1; i++) {
		minIndex = i;
		minUnit = list[i].getUnit();

		for (int x = i + 1; x < listSize; x++) {
			if (list[x].getUnit() < minUnit) {
				minUnit = list[x].getUnit();
				minIndex = x;
			}
		}
		swap(minIndex, i, list, listSize);
	}
	cout << "LIST HAS BEEN SORTED BY [UNIT]\n";
}
void quantitySort(item list[], int listSize) {
	int minIndex;
	int minQuantity;
	for (int i = 0; i < listSize - 1; i++) {
		minIndex = i;
		minQuantity = list[i].getQuantity();

		for (int x = i + 1; x < listSize; x++) {
			if (list[x].getQuantity() < minQuantity) {
				minQuantity = list[x].getQuantity();
				minIndex = x;
			}
		}
		swap(minIndex, i, list, listSize);
	}
	cout << "LIST HAS BEEN SORTED BY [QUANTITY]\n";

}
void priceSort(item list[], int listSize) {
	int minIndex;
	double minPrice;
	for (int i = 0; i < listSize - 1; i++) {
		minIndex = i;
		minPrice = list[i].getPrice();

		for (int x = i + 1; x < listSize; x++) {
			if (list[x].getPrice() < minPrice) {
				minPrice = list[x].getPrice();
				minIndex = x;
			}
		}
		swap(minIndex, i, list, listSize);
	}
	cout << "LIST HAS BEEN SORTED BY [PRICE]\n";
}
void tboSort(item list[], int listSize) {
	int minIndex;
	for (int i = 0; i < listSize - 1; i++) {
		minIndex = i;

		for (int x = i + 1; x < listSize; x++) {
			if (list[x].getToBeOrdered() == true) {
				minIndex = x;
			}
		}
		swap(minIndex, i, list, listSize);
	}
	cout << "LIST HAS BEEN SORTED BY [T.B.O.]\n";
}

void swap(int newValue, int currentValue, item list[], int listSize) {
	item tempIndex = list[currentValue];
	list[currentValue] = list[newValue];
	list[newValue] = tempIndex;
};
