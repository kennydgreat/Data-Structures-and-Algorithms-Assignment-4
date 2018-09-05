/*This is an implement of the a Customer database application
	The underlining data structure used is a binary tree
*/
#include<iostream>
#include<fstream>
#define LINE_LIMIT 101
#define RECORD_ATTRIBUTE_LIMIT 70
using namespace std;
/*This is the data struct of a record in the database*/
typedef struct {
	char * lastName, * firstname,
		* phone, * address, * job_title, * company,
		*annual_income;
	
}CustomerData;

/*This is the struct of a Binary tree node */
typedef struct treenode{
	CustomerData * customerData;
	struct treenode *left, *right;
}TreeNode, *TreeNodePtr;

/*This is the struct for binary tree*/
typedef struct {
	TreeNodePtr root;
}BinaryTree;
//	Function protypes 
void getDataFromFile(BinaryTree * tree, char * file_name,
	bool * file_not_found);
TreeNodePtr insert_record(BinaryTree * tree, CustomerData * customerData);
void copy_attribute_into_Node(char ** nodeAttribute, char * record_Attriubte);
TreeNodePtr newTreeNode(CustomerData * data);
void read_customer_data(CustomerData customerData);
void sort_records(TreeNodePtr node);
void add_record(BinaryTree tree);
void retrieve_record(char  * lastName, BinaryTree * tree);
void load_from_user_data_file(BinaryTree * tree, char * file_name);