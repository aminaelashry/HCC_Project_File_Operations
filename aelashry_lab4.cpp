//Amina El-Ashry
// March 2, 2020
//program that keeps track of records using file operations

//preprocessor directives
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//struct to hold inventory members
struct Inventory
{
	char desc[30];
	int qty;
	double wholeSaleCost;
};

// Function prototypes
void addRecord(fstream&);
void viewRecord(fstream&);
void changeRecord(fstream&);

int main()
{
	using namespace std;

	fstream inventoryFile;
	int choice;
	cout << setprecision(2) << fixed;

	do
	{
		// Display the menu.
		cout << "\n1. Add a new record\n";
		cout << "2. View an existing record by record number\n";
		cout << "3. Change an existing record\n";
		cout << "4. Exit\n\n";

		do
		{
			cout << "Enter your choice (1-4): ";
			cin >> choice;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "invalid entry, please enter again:";
				cin >> choice;
				cin.ignore();
			}

			cin.ignore();
		} while (choice < 1 || choice > 4);

		// Process the selection.
		switch (choice)
		{
			// Choice 1 is to add a record.
		case 1:
			addRecord(inventoryFile);
			break;

			// Choice 2 is to view a record.
		case 2:
			viewRecord(inventoryFile);
			break;

			// Choice 3 is to change a record.
		case 3:
			changeRecord(inventoryFile);
		}

	} while (choice != 4);

	cout << "Thank you for visiting the El-Ashry store" << endl;

	system("pause");
	return 0;
}

//function to add record to file
void addRecord(fstream& file) {
	Inventory p;

	cout << "Enter the following information about your inventory:" << endl;
	//opening file in append and binary mode
	file.open("elashryInventory.dat", ios::app | ios::binary);

	//confirming file was opened / created successfully 
	if (!file) {
		cout << "Erorr opening file. Program is quitting...";
	}

	//prompting user for each member of struct and validating input
	cout << "Description:";
	cin.getline(p.desc, 30);
	do {

		cout << "Quantity:";
		cin >> p.qty;
		//validating number was entered
		while (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "invalid entry, please enter again:";
			cin >> p.qty;
		}

	} while (p.qty < 0);


	do {
		cout << "Whole sale cost:";
		cin >> p.wholeSaleCost;
		//validating number was entered
		while (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "invalid entry, please enter again:";
			cin >> p.wholeSaleCost;
		}
	} while (p.wholeSaleCost < 0);

	//writing data to the file
	file.write(reinterpret_cast<char*>(&p), sizeof(p));
	cout << "Record written to file." << endl;

	//confirming data was written successfully 
	if (!file) {
		cout << "Error writing to file..." << endl;
	}

	//closing file 
	file.close();
}

//function that displays records that are stored in file 
void viewRecord(fstream& file) {
	Inventory p;
	//opening file for reading
	file.open("elashryInventory.dat", ios::in | ios::binary);

	//confirming file was successfully opened
	if (!file) {
		cout << "Erorr opening file..." << endl;
	}

	int index;

	cout << "Enter the record number you will like to view(-1 if you want to view all records):";
	cin >> index;
	//input validation
	while (cin.fail()) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "invalid entry, please enter again:";
		cin >> index;
	}

	if (index == -1) {
		//reading first record
		file.read(reinterpret_cast<char*>(&p), sizeof(p));

		//confirming record was read correctly
		if (!file) {
			cout << "Erorr reading from file. Record not found..." << endl;
		}

		//reading all the records in the file
		while (!file.eof()) {
			cout << "Description:" << p.desc << endl;
			cout << "Quantity: " << p.qty << endl;
			cout << "Whole Sale Cost: " << p.wholeSaleCost << endl << endl;

			file.read(reinterpret_cast<char*>(&p), sizeof(p));
		}
	}
	else {
		file.clear(); //use when eof has been reached previously 
		//finding the record that was requested, reading it, and displaying it 
		file.seekg((index * sizeof(p)), ios::beg);
		file.read(reinterpret_cast<char*>(&p), sizeof(p));
		//confirming record was read correctly
		if (!file) {
			cout << "Error reading from file. Record not found..." << endl;
		}
		cout << "Description:" << p.desc << endl;
		cout << "Quantity: " << p.qty << endl;
		cout << "Whole Sale Cost: " << p.wholeSaleCost << endl << endl;
	}

	//closing file
	file.close();
}

//function to change specified record
void changeRecord(fstream& file) {
	Inventory p;

	int index;

	do {
		cout << "Enter the record number you will like to change:";
		cin >> index;
		cin.ignore();
		//input validation
		while (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "invalid entry, please enter again:";
			cin >> index;
			cin.ignore();
		}
	} while (index < 0);

	//opening file for reading and writing in binary mode
	file.open("elashryInventory.dat", ios::in | ios::out | ios::binary);
	//confirming file was opened correctly
	if (!file) {
		cout << "Erorr opening file..." << endl;
	}

	
	cout << "Current data for this record: " << endl;
	file.clear();
	//retrieves current data for record and displays it 
	file.seekg((index * sizeof(p)), ios::beg);
	//reads data from file
	file.read(reinterpret_cast<char*>(&p), sizeof(p));
	//confirms data was read correctly
	if (!file) {
		cout << "Erorr reading from file. Record not found..." << endl;
	}

	cout << "Description:" << p.desc << endl;
	cout << "Quantity:" << p.qty << endl;
	cout << "Whole Sale Cost:" << p.wholeSaleCost << endl << endl;

	//resets position at the record specified and prompts user to enter new data 
	file.seekp((index * sizeof(p)), ios::beg);
	cout << "Enter new data for this record." << endl;
	cout << "Description:";
	cin.getline(p.desc, 30);
	do {

		cout << "Quantity:";
		cin >> p.qty;
		//input validation
		while (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "invalid entry, please enter again:";
			cin >> p.qty;
		}

	} while (p.qty < 0);

	do {
		cout << "Whole sale cost:";
		cin >> p.wholeSaleCost;
		//input validation
		while (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "invalid entry, please enter again:";
			cin >> p.wholeSaleCost;
		}
	} while (p.wholeSaleCost < 0);

	//writing all members of structure back into the record that needed to be changed
	file.write(reinterpret_cast<char*>(&p), sizeof(p));
	//confirming writing was done correctly
	if (!file) {
		cout << "Erorr writing file..." << endl; 
	}

	//closing file
	file.close();

}