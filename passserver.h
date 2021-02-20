/*
*PASSSERVER.H 
*COLIN MACRAE
*11/18/20
*/
#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <crypt.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include<stdio.h>
#include <initializer_list>


using namespace cop4530;

class PassServer{
public:
	explicit PassServer(size_t serverSize = 101); // constructor
	~PassServer(); // deconstructor
	bool load(const char * filename); // load a password file into password server
	bool addUser(std::pair<std::string,std::string>& kv); // add a new username and password
	bool addUser(std::pair<std::string,std::string>&&kv); // move version of addUser
	bool removeUser(const std::string& k); // remove user from server
	bool changePassword(const std::pair<std::string,std::string> &p, const  std::string & newpassword); // change and existing users's password
	bool find(const std::string &user); // check if a user exists
	void dump(); // show the structure and contents of hashtable on the screen
	size_t size(); //return size of hashtable 
	bool write_to_file(const char* filename); //save user and password combination to server
private:
	HashTable<std::string,std::string> server;
	std::string encrypt(const std::string &str); //encrypt parameter string and return encrypted string 
};