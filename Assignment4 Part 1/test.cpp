#include "CustomerDatabase.h"

int main() {
	//Data Binary Tree that can hold 30 records
	BinaryTree dataTree;
	dataTree.root = NULL;
	char user_input[RECORD_ATTRIBUTE_LIMIT];
	char file_name[RECORD_ATTRIBUTE_LIMIT] = "CustomerDatabaseFile.txt";
	user_input[0] = 'e';
	bool file_not_found = false;
	getDataFromFile(&dataTree,file_name, &file_not_found);
	if (file_not_found) {
		cout << "The program is supposed to load records from " <<
			"CustomerDatabaseFile.txt on start up but it can still" <<
			" function without thr data from in file." << endl <<
			"if you wish to load the data from the file again choose" <<
			" the 'l' option once you get to the control options " << 
			endl << "Type any character and press enter to continue";
		cin >> user_input;
		cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); // clearing cin

	}
	cout << endl<<"Hello this is an implementation of a customer database" << endl;
	cout << "Here are the controls:" << endl <<
		"  Add a record: 'a' "<< endl << "  Delete a record by given last name: 'd'" << endl<<
		"  Load records from a file: 'l'" << endl <<
		"  Save current records into a file: 's'" << endl <<
		"  Display all records in alphabetical order: 'd'" << endl <<
		"  Return a list of records with a certain last name: 'r'" << endl<<
		"  Quit the program: 'q'" << endl << 
		"  Unfortunately because of time deleting was not implemented." << endl<< endl;
	
	while (user_input[0] != 'q') {
		cout << "Please enter a command:";
		cin >> user_input;
		switch (user_input[0])
		{
		case 'd':
		sort_records(dataTree.root);
		cout << "No more records left" << endl;
		case 'q':
			break;
		case 'a':
			add_record(dataTree);
			break;
		case 'r':
			retrieve_record(user_input,&dataTree);
			break;
		case 'l':
			load_from_user_data_file(&dataTree,user_input);
			break;
		case 's':
			cout << "Data  saved to outfile.txt . you can find this " <<
				"file where the source files are "<<
				"(Assignment4 Part 1\\Assignment4 Part 1)." << endl;
			break;
		default:
			cout << "Sorry that wasn't a recongized input." << endl;
				cout << "Remember the controls are:" << endl <<
				"  Add a record: 'a' " << endl << "  Delete a record by given last name: 'd'" << endl <<
				"  Load records from a file: 'l'" << endl <<
				"  Save current records into a file: 's'" << endl <<
				"  Display all records in alphabetical order: 'd'" << endl <<
				"  Return list of records with a certain last name: 'r'" << endl <<
				"  Quit: 'q'" << endl << endl;
			break;
		}

	}
	cout << "GoodBye!" << endl;
	system("pause");
	return 0;
}