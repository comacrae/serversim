/*
*DRIVER
*COLIN MACRAE
*11/18/20
*/
#include <iostream>
#include <string>
#include "passserver.h"
using namespace std;
void Menu() // prints out preformatted menu 
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}


void load(PassServer & s) // prompt user for a file to load into the server and make attempt
{
	string filename = "";
	cout << "Enter password file name to load from: ";
	cin >> filename;
	if(!s.load(filename.c_str()))
	{
		cout << "\nError: Cannot open file " << filename << endl;
	}
}

void addUser(PassServer & s)// prompt user for a username and password to add to server and attempt 
{
	string username = "";
	string password ="";
	cout << "Enter username: ";
	cin >> username;
		cout << "Enter password: ";
	cin >> password;
	pair<string,string> p(username, password);
	if(s.addUser(p))
	{
		cout << "\nUser '" << username << "' added." << endl;
	}else
	{
		cout << "\n*****Error: User already exists. Could not add user.\n";
	}
}

void removeUser(PassServer & s) // prompt user for a username to remove from server and attempt to do so
{
	string username = "";
	cout << "Enter the username of user to remove: ";
	cin >> username;
	if(s.removeUser(username))
	{
		cout << "\nUser '" << username << "' deleted." << endl;
	}else
	{
		cout << "\n*****Error: User not found.  Could not delete user\n";
	}
}

void changeUserPassword(PassServer & s) // prompt user for a username to update with new password and make attempt
{
	string username = "";
	string oldPassword = "";
	string newPassword ="";
	cout << "Enter username	: ";
	cin >> username;
	
		cout << "Enter password	: ";
		cin >> oldPassword;
		cout << "\nEnter new password: ";
		cin >> newPassword;
		pair<string,string> p(username, oldPassword);
		if(s.changePassword(p, newPassword))
		{
			cout << "\nPassword changed for user '" << username <<"'\n";
		}else
		{
			cout << "\n*****Error: Could not change user password\n";
		}
	
}

void findUser(PassServer &s) // prompt user for a username to find in the server and report attempt 
{
	string username = "";
	cout << "Enter username		: ";
	cin >> username;
	if(s.find(username))
	{
		cout << "\nUser '"<< username << "' found.\n";
	}else
	{
		cout << "\nUser '" << username << "' not found.\n";
	}
}

void dump(PassServer & s) // print out contents of server 
{
	s.dump();
}

void size(PassServer & s) // print out size of server in current users 
{
	 cout << "\nSize of hashtable: " << s.size() << endl;
}

void write(PassServer & s) // prompt user for the name of a file to write the server contents to 
{
	string filename = "";
	cout << "Enter password file name to write to: ";
	cin >> filename;
	if(!s.write_to_file(filename.c_str()))
	{
		cout << "\nUnable to write to file name '" << filename << "'";
	}
}

void invalidEntry() //report invalid menu entry 
{
	cout << "\n *****Error: Invalid entry. Try again.";
}
bool Selection(char c, PassServer & s) // determine appropriate function to be called according to user input 
{
	bool quit = false;
	switch(c)
	{
		case 'l' : load(s); 				break;
		case 'a' : addUser(s); 				break;
		case 'r' : removeUser(s);		 	break;
		case 'c' : changeUserPassword(s); 	break;
		case 'f' : findUser(s);				break;
		case 'd' : dump(s);					break;
		case 's' : size(s);					break;
		case 'w' : write(s);				break;
		case 'x' : quit = true;				break;
		default  : invalidEntry();			break;
	}
	
	return quit; 
}


int main() // main function; loops menu and performs user selection until user quits 
{
	
	char input;
	bool quit = false;
	unsigned int size; 
	cout << "Enter preferred hash table capacity: ";
	cin >> size;
	PassServer s(size); // default size of 101 
	cout << endl;
	do{
		Menu();
		cin >> input; 
		
	}while(!Selection(input,s));
	
	return 0;
}
