

//Adding Liabraries
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <occi.h>


//Establishing Connections
using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

//Making struct to make variables 
struct Employee
{
	char lastName[50], firstName[50], email[100], phone[50], atwadi[10], reportsTo[100], jobTitle[50], city[50];

	int bndhuNumber;
};

//Made function to reset the app
void thamjaBhaijan(void)
{

	printf("<< ENTER key to Continue... >>");

	do
	{
		;
	} while (getchar() != '\n');

	putchar(0);
}

//Made a functon to get an input in Number 
int getInt(const char* prompt = nullptr) {

	bool wrongInput = 1;

	int kimat;

	switch (prompt != nullptr)
	{

	case 1:

		std::cout << prompt;

	}

	while (wrongInput) {

		std::cin >> kimat;

		if (std::cin.fail())
		{
			std::cin.ignore(10000, '\n');
			std::cin.clear();


			std::cout << "Please enter a valid number: ";
		}


		else if (getchar() != '\n')
		{
			cout << "Enter only an integer, please try again: ";

			cin.ignore(1000, '\n');
			cin.clear();


		}

		else
		{
			wrongInput = 0;
		}

	}

	return kimat;

}

//Made a function to so that C++ can read the data from SQL file.
int findEmployee(Connection* conn, int bndhuNumber, struct Employee* emp) {

	int lbgea;

	try
	{
		Statement* stmt = conn->createStatement();

		stmt->setSQL("SELECT e.employeeNumber, e.lastName, e.firstName, e.email, o.phone, e.extension, m.firstName || ' ' || m.lastName, e.jobTitle, o.city FROM dbs211_employees e LEFT JOIN dbs211_employees m ON m.employeeNumber = e.reportsto LEFT JOIN dbs211_offices o ON e.officecode = o.officecode WHERE e.employeeNumber = :1");

		stmt->setInt(1, bndhuNumber);

		ResultSet* parmanu = stmt->executeQuery();

		switch (parmanu->next())

		{

		case 1:

			lbgea = 1;

			emp->bndhuNumber = parmanu->getInt(1);

			strcpy(emp->atwadi, parmanu->getString(6).c_str());

			strcpy(emp->lastName, parmanu->getString(2).c_str());

			strcpy(emp->phone, parmanu->getString(5).c_str());

			strcpy(emp->firstName, parmanu->getString(3).c_str());

			strcpy(emp->email, parmanu->getString(4).c_str());

			strcpy(emp->city, parmanu->getString(9).c_str());

			strcpy(emp->jobTitle, parmanu->getString(8).c_str());


			strcpy(emp->reportsTo, parmanu->getString(7).c_str());

		}

		conn->terminateStatement(stmt);

	}

	catch (SQLException& exception)

	{
		cout << exception.getErrorCode() << ": " << exception.getMessage() << endl;
	}

	return lbgea;

}


//Function to display Employee data according to the input Number
void displayEmployee(Connection* conn, struct Employee emp)
{

	int bndhuNumber = getInt("Enter an employee number: ");

	if (findEmployee(conn, bndhuNumber, &emp))
	{

		cout << endl;

		cout << "employeeNumber = " << emp.bndhuNumber << endl;

		cout << "lastName = " << emp.lastName << endl;

		cout << "firstName = " << emp.firstName << endl;

		cout << "email = " << emp.email << endl;

		cout << "phone = " << emp.phone << endl;

		cout << "extension = " << emp.atwadi << endl;

		cout << "reportsTo = " << emp.reportsTo << endl;

		cout << "jobTitle = " << emp.jobTitle << endl;

		cout << "city = " << emp.city << endl << endl;


	}

	//If the required Employee not exist then give the error

	else { cout << "Employee " << bndhuNumber << " does not exist." << endl << endl; }

}
//Function to display all the employees from the SQL file
void displayAllEmployees(Connection* conn) {

	try
	{
		cout.setf(ios::left);

		Statement* stmt = conn->createStatement();
		ResultSet* parmanu = stmt->executeQuery("SELECT e.employeenumber, e.firstname || ' ' || e.lastname, e.email, o.phone, e.extension, m.firstname || ' ' || m.lastname FROM dbs211_employees e LEFT JOIN dbs211_employees m ON m.employeeNumber = e.reportsto LEFT JOIN dbs211_offices o ON e.officecode = o.officecode ORDER BY e.employeeNumber");

		if (!(parmanu->next()))
		{
			cout << "There are no employee information to be displayed." << endl;
		}

		else
		{

			cout.width(7);

			cout << "E";

			cout.width(20);

			cout << "Employee Name";

			cout.width(34);

			cout << "Email";


			cout.width(18);

			cout << "Phone Number";

			cout.width(8);

			cout << "Ext";

			cout.width(8);

			cout << "Manager" << endl;

			cout.width(95);

			cout.fill('-');

			cout << "-" << endl;

			cout.fill(' ');

			while (parmanu->next())
			{

				cout.width(7);

				cout << parmanu->getInt(1);

				cout.width(20);

				cout << parmanu->getString(2);

				cout.width(34);

				cout << parmanu->getString(3);

				cout.width(18);

				cout << parmanu->getString(4);

				cout.width(8);

				cout << parmanu->getString(5);

				cout << parmanu->getString(6) << endl;

			}

		}

		cout << endl;

		conn->terminateStatement(stmt);

	}

	catch (SQLException& exception)
	{
		cout << exception.getErrorCode() << ": " << exception.getMessage() << endl;
	}

}

//Function to add the employee in data
void insertEmployee(Connection* conn, struct Employee emp) {

	try
	{
		//Check if the employee already exist

		int bndhuNumber = getInt("Employee Number: ");

		if (findEmployee(conn, bndhuNumber, &emp))
		{
			cout << "An employee with the same employee number exists." << endl << endl;
		}

		//Creating a form to add the information of the person to get added in the data

		else
		{
			cout << "Last Name: ";

			cin.getline(emp.lastName, 50);

			cout << "First Name: ";

			cin.getline(emp.firstName, 50);

			cout << "Email: ";

			cin.getline(emp.email, 100);

			cout << "extension: ";

			cin.getline(emp.atwadi, 10);

			cout << "Job Title: ";

			cin.getline(emp.jobTitle, 50);

			cout << "City: ";

			cin.getline(emp.city, 50);

			Statement* stmt = conn->createStatement();

			//Add the value in the dbs211_employees's table in the SQL

			stmt->setSQL("INSERT INTO dbs211_employees VALUES (:1, :2, :3, :4, :5, :6, :7, :8)");

			stmt->setInt(1, bndhuNumber);

			stmt->setString(2, emp.lastName);

			stmt->setString(3, emp.firstName);

			stmt->setString(4, emp.atwadi);

			stmt->setString(5, emp.email);

			stmt->setString(6, "1");

			stmt->setInt(7, 1002);

			stmt->setString(8, emp.jobTitle);

			//If the employee added successfully then a message will get displayed

			if (stmt->executeUpdate())
			{
				cout << "The new employee is added successfully." << endl << endl;
			}

			//If any error occurs then a error message will get displayed.

			else
			{
				cout << "Failed to add new employee" << endl;
			}

			conn->terminateStatement(stmt);

		}

	}
	//Select data from SQL
	catch (SQLException& exception)
	{
		cout << exception.getErrorCode() << ": " << exception.getMessage() << endl;
	}
}

//To update the employee's data
void updateEmployee(Connection* conn, int bndhuNumber) {

	try
	{

		Employee emp = {};

		char atwadi[10];

		if (findEmployee(conn, bndhuNumber, &emp))
		{
			Statement* stmt = conn->createStatement();

			cout << "New phone extension: ";

			cin.getline(atwadi, 10);

			stmt->setSQL("UPDATE dbs211_employees SET extension = :1 WHERE employeeNumber = :2");

			stmt->setString(1, atwadi);

			stmt->setInt(2, bndhuNumber);

			switch (stmt->executeUpdate())
			{
			case 1:
				cout << "Phone extension updated." << endl << endl;
			}


			conn->terminateStatement(stmt);


		}

		//If the wrong employee number entered then a error will got displayed

		else
		{
			cout << "Employee " << bndhuNumber << " does not exist." << endl << endl;

		}
	}


	catch (SQLException& exception)

	{
		cout << exception.getErrorCode() << ": " << exception.getMessage() << endl;

		cout << "Employee " << bndhuNumber << " was NOT updated." << endl;
	}
}
// To delete a employee's data
void deleteEmployee(Connection* conn, int bndhuNumber) {

	Employee emp = {};

	try

	{

		//Check the data from the SQL data

		if (findEmployee(conn, bndhuNumber, &emp)) {

			Statement* stmt = conn->createStatement();

			//Checks the data from particular table

			stmt->setSQL("DELETE FROM dbs211_employees WHERE employeeNumber = :1");	stmt->setInt(1, bndhuNumber);

			stmt->setInt(1, bndhuNumber);

			// get remove if the data matches with data file


			if (stmt->executeUpdate()) {
				cout << "The employee is deleted." << endl << endl;
			}

			conn->terminateStatement(stmt);

		}


		else
		{
			cout << "Employee " << bndhuNumber << " does not exist." << endl << endl;
		}
	}

	catch (SQLException& exception)
	{

		cout << exception.getErrorCode() << ": " << exception.getMessage();

		cout << "Employee " << bndhuNumber << " was NOT deleted." << endl << endl;

	}
}

//Main function which is used to combine every function.
int main() {

	Environment* env = nullptr;
	Connection* conn = nullptr;
	//To establish connection between sql and c++ with the help of sql username and sql password and sql server 
	string usr = "dbs211_223zdd36";
	string pass = "30642168";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";


	Employee emp = {};
	bool invalidOption = true;
	int menuOption = -1;
	int empNumber = 0;
	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		do {
			//Statements to be displayed on the starting of the application
			do {
				std::cout << "******* HR Menu *******" << endl;
				std::cout << "1) Find Employee" << endl;
				std::cout << "2) Employees Report" << endl;
				std::cout << "3) Add Employee" << endl;
				std::cout << "4) Update Employee" << endl;
				std::cout << "5) Remove Employee" << endl;
				std::cout << "0) Exit" << endl;
				//to get an input
				menuOption = getInt("Enter an option (0 - 5): ");
				if (menuOption < 0 || menuOption > 5) {
					std::cout << "Please enter a valid option." << endl << endl;
				}
				else {
					invalidOption = false;
				}
			} while (invalidOption);
			//switch according to the cases which are present in this application

			switch (menuOption) {
			case 1:
				cout << endl;
				displayEmployee(conn, emp);
				thamjaBhaijan();
				break;
			case 2:
				cout << endl;
				displayAllEmployees(conn);
				thamjaBhaijan();
				break;
			case 3:
				cout << endl;
				insertEmployee(conn, emp);
				thamjaBhaijan();
				break;
			case 4:
				cout << endl;
				empNumber = getInt("Enter an employee number: ");
				updateEmployee(conn, empNumber);
				thamjaBhaijan();
				break;
			case 5:
				cout << endl;
				empNumber = getInt("Enter an employee number: ");
				deleteEmployee(conn, empNumber);
				thamjaBhaijan();
				break;
			case 0:
				cout << "Exiting" << endl;
				break;
			default:
				break;
			}
		} while (menuOption != 0);

		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& exception)
	{
		cout << exception.getErrorCode() << ": " << exception.getMessage();
		cout << "Cound not connect to database, exiting" << endl;
	}
	return 0;
}