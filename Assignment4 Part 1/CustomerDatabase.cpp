/*This is an implement of the a Customer database application
The underlining data structure used is a binary tree
*/
#include "CustomerDatabase.h"

/*This function gets the data from the file. It
1) Reads it line and stores in a char array*/
extern void getDataFromFile(BinaryTree * tree, char * file_name, 
	bool * file_not_found) {
	char recordAttribute[RECORD_ATTRIBUTE_LIMIT];

	//Opening file for reading 
	ifstream infile;
	ofstream outfile;
	infile.open(file_name);
	outfile.open("outfile.txt", ios::app); 
	if (infile.fail()) {
		cout << file_name<<" not found" << endl;
		cout << "Please ensure it's in the same folder as the source files" <<
			endl;
		//exit(1);
		*file_not_found = true;
		return;
	}
	if (outfile.fail()) {
		cout << "outfile" << " not found" << endl;
		cout << "Please ensure it's in the same folder as the source files" <<
			endl;
		exit(1);
		return;
	}

	while (!infile.eof()) {
		/*Getting a customer record which is sepereated by a ')'
		charater*/
		//infile.getline(recordLine, LINE_LIMIT,')');
		//Make a treeNode point from line
		//TreeNodePtr treeNode = new TreeNode;
		CustomerData * customerData = new CustomerData;
		//getting the lastname
		infile.getline(recordAttribute, RECORD_ATTRIBUTE_LIMIT, '(');
		copy_attribute_into_Node(&(customerData->lastName),
			recordAttribute);

		//getting first name
		infile.getline(recordAttribute, RECORD_ATTRIBUTE_LIMIT, ',');
		copy_attribute_into_Node(&(customerData->firstname),
			recordAttribute);

		//getting phone
		infile.getline(recordAttribute, RECORD_ATTRIBUTE_LIMIT, ',');
		copy_attribute_into_Node(&(customerData->phone),
			recordAttribute);

		//getting address
		infile.getline(recordAttribute, RECORD_ATTRIBUTE_LIMIT, ',');
		copy_attribute_into_Node(&(customerData->address),
			recordAttribute);


		//getting job title
		infile.getline(recordAttribute, RECORD_ATTRIBUTE_LIMIT, ',');
		copy_attribute_into_Node(&(customerData->job_title),
			recordAttribute);

		//getting company
		infile.getline(recordAttribute, RECORD_ATTRIBUTE_LIMIT, ',');
		copy_attribute_into_Node(&(customerData->company),
			recordAttribute);

		//getting annual_income
		infile.getline(recordAttribute, RECORD_ATTRIBUTE_LIMIT, ')');
		copy_attribute_into_Node(&(customerData->annual_income),
			recordAttribute);

		//writing to out file
		outfile << customerData->lastName << '(' << customerData->firstname
			<< ", " << customerData->phone << ", " << customerData->address
			<< ", " << customerData->job_title << ", " << customerData->company
			<< ", " << customerData->annual_income << ')' << endl;
		//inserting into tree
		if (tree->root == NULL) {
			tree->root = newTreeNode(customerData);
			//return;
		}
		else{
			insert_record(tree, customerData);
		}
		//Gets the ')' character at the end of each record in the 
		//data file
		infile.get(); 
		


	}
	cout << "Customer Data has been loaded from data file." << endl;
	infile.close();
	outfile.close();
}
/*This function parses through a record line for customer data*/
extern TreeNodePtr insert_record(BinaryTree * tree, CustomerData * customerData) {
	int cmpValue = 0;
	if (tree->root == NULL) return newTreeNode(customerData);
	TreeNodePtr curr = tree->root;
	while ((cmpValue = strcmp(customerData->lastName,
		curr->customerData->lastName)) != 0) {
		if (cmpValue < 1) {
			if (curr->left == NULL) return curr->left =
				newTreeNode(customerData);
			curr = curr->left;
		}
		else { // try right
			if (curr->right == NULL) return curr->right = 
				newTreeNode(customerData);
			curr = curr->right;
		}
		
	}return curr;
}

/*This function dynamically allocates memory for the node attriute
which for the node in on the tree.
It then copys the record attribute from the data file */
extern void copy_attribute_into_Node(char ** nodeAttribute, char * record_Attriubte) {
	*nodeAttribute = new char[strlen(record_Attriubte)];
	if (!nodeAttribute) {
		cout << "Memory allocation for an attritube failed!"
			<< endl;
		exit(1);
	}
	strcpy(*nodeAttribute, record_Attriubte);
}
/*This function creates a new dynamically allocated treeNode
and set's customer data to data*/
extern TreeNodePtr newTreeNode(CustomerData * data) {
	TreeNodePtr p = new TreeNode;
	p->customerData = data;
	p->left = p->right = NULL;
	return p;
}
/*This function prints out reads customer data*/
extern void read_customer_data(CustomerData customerData) {
	cout << "Name: " << customerData.firstname << " " <<
		customerData.lastName << endl << "   " << "Address: "
		<< customerData.address << ", " << "Phone: " <<
		customerData.phone << endl << "   " << "Job title: " <<
		customerData.job_title << ", " << "Company: " <<
		customerData.company << ",   Annual Salary: " <<
		customerData.annual_income << endl;
}
/*This function sorts the record in ascending order (alphabethical)*/
extern void sort_records(TreeNodePtr node) {
	if (node != NULL) {
		sort_records(node->left);
		read_customer_data(*(node->customerData));
		sort_records(node->right);
	}
}
/*This function handles the adding of a records functionality*/
extern void add_record(BinaryTree tree) {
	char user_input[RECORD_ATTRIBUTE_LIMIT];
	//allocating memory for the data record from the users input
	CustomerData * customerData = new CustomerData; 
	cout << "First Name: ";
	cin >> user_input;
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); //clearing cin buffer
	copy_attribute_into_Node(&customerData->firstname, user_input);
	cout << "Last Name: ";
	cin >> user_input;
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); //clearing cin buffer
	copy_attribute_into_Node(&customerData->lastName, user_input);
	cout << "Phone: ";
	cin >> user_input;
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); //clearing cin buffer
	copy_attribute_into_Node(&customerData->phone, user_input);
	cout << "Full address: ";
	cin >> user_input;
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); //clearing cin buffer
	copy_attribute_into_Node(&customerData->address, user_input);
	cout << "Job title: ";
	cin >> user_input;
	copy_attribute_into_Node(&customerData->job_title, user_input);
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n');
	cout << "Company: ";
	cin >> user_input;
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); //clearing cin buffer
	copy_attribute_into_Node(&customerData->company, user_input);
	cout << "Annual Income: ";
	cin >> user_input;
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); //clearing cin buffer
	copy_attribute_into_Node(&customerData->annual_income, user_input);
	cout << "The record for " << customerData->firstname << " " <<
		customerData->lastName << " will now be insert into the " <<
		"database." << endl;
	cout << "Please enter to go back to the main options"<< endl<<endl;
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n');
	insert_record(&tree, customerData);
	ofstream outfile;
	outfile.open("outfile.txt", ios::app);
	//writing to out file
	outfile << customerData->lastName << '(' << customerData->firstname
		<< ", " << customerData->phone << ", " << customerData->address
		<< ", " << customerData->job_title << ", " << customerData->company
		<< ", " << customerData->annual_income << ')' << endl;
	outfile.close();

}
/*This function handles the finding and displaying of a record
using last name*/
extern void retrieve_record(char  * lastName, BinaryTree * tree) {
	cout << "Please enter the last name of the customer you which to" <<
		" retrieve:";
	cin >> lastName; // retrieve last name from user
	cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); // clearing th
	int found = 0;
	TreeNodePtr curr = tree->root;
	while (curr != NULL) {
		if (strcmp(lastName, curr->customerData->lastName) < 0) {
			if (curr->left == NULL) return;
			curr = curr->left;
		}
		else { // try right
			if (strcmp(lastName, curr->customerData->lastName) == 0) {
				found++;
				cout << found << " ";
				read_customer_data(*curr->customerData);
				curr = curr->right; //continue searching
				// all nodes with a last name that matchs
				// the one beine cin bufferg searched for will always be 
				// on the right
			}
			else {
				if (curr->right == NULL) return;
				curr = curr->right;
			}
		}

	}
	if (found == 0) {
		cout << "No record with customer last name: " << lastName <<
			" found." << endl;
	}

}
/*This function handles the loading data from a file functionality*/
extern void load_from_user_data_file(BinaryTree * tree, char * file_name) {
		bool file_not_found = false;
		while (!false) {
			cout << "Important!!! " << endl
				<< "For the records to be loaded properly" <<
				" they have to be written in the file in this"
				<< " way: " << endl << 
				"lastname(firstname,phone,adress,job title,company,annual income)."
				<< endl << endl;
			cout << "Please enter the file name:";
			cin >>file_name;
			cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); // clearing cin
			getDataFromFile(tree,file_name,&file_not_found);
			//
			cout << "Press q to go back to controls." <<
				" Press any other key to enter a filename again";
			cin >> file_name;
			cin.ignore(RECORD_ATTRIBUTE_LIMIT, '\n'); // clearing cin
			if ((strlen(file_name) < 2) && file_name[0] == 'q') {
				file_name[0] = ' ';
				return;
			}
		}
		
	}