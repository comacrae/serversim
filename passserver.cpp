/*
*PASSSERVER.H IMPLEMENTATION
*COLIN MACRAE
*11/18/20
*/
#include "passserver.h"
PassServer::PassServer(size_t serverSize) :server(serverSize){}//default is 101

PassServer::~PassServer() // destructor. Clears the server 
{
	server.clear();
}
bool PassServer::load(const char * filename) // load the file into the server (assumes proper format)
{
	return server.load(filename);
}
bool PassServer::addUser(std::pair<std::string,std::string>& kv) // add user specified by pair parameter
{
	
	std::string username = std::get<0>(kv); // extract username from pair
	std::string encryptedPassword = encrypt(std::get<1>(kv)); //extract password from pair and encrypt
	std::pair<std::string,std::string> encryptedPair(username, encryptedPassword); // load username w/ encrypted password into server
	return server.insert(encryptedPair); // return success or failure 
}
bool PassServer::addUser(std::pair<std::string,std::string>&&kv) // move version of above method
{
	std::pair<std::string,std::string> encryptedPair(std::get<0>(kv), encrypt(std::get<1>(kv)));
	return server.insert(encryptedPair);
}
bool PassServer::removeUser(const std::string& k) // attempt to remove user with specified username from server and report success/failure
{
	return server.remove(k);
}
bool PassServer::changePassword(const std::pair<std::string,std::string> &p, const  std::string & newpassword) // update password of user
{	
	if(server.contains(std::get<0>(p))) // if username is in the server
	{
		std::pair<std::string,std::string> encryptedPair(std::get<0>(p), encrypt(std::get<1>(p)));
		if(server.match(encryptedPair)) // if correct password for username entered 
		{
			std::pair<std::string,std::string> updatedUser(std::get<0>(p), encrypt(newpassword));
			return server.insert(updatedUser); // if the new password is the same as current password, then false will be returned  
		}
	}
		return false; // if this point was reached, then the username wasnt in the server 
}
bool PassServer::find(const std::string &user) // returns if specified username is in server 
{
	return server.contains(user);
}
void PassServer::dump() // print server's usernames and encrypted passwords 
{
	server.dump();
}
size_t PassServer::size() // returns number of users in the server 
{
	return server.size();
}
bool PassServer::write_to_file(const char* filename) // print out the server's usernames and encrypted passwords 
{
	return server.write_to_file(filename);
}
//PRIVATE FUNCTION
std::string PassServer::encrypt(const std::string &str) // encrypt password using GNU crypt() function 
{
	char salt[12]  = "$1$########";
	return std::string(crypt(str.c_str(), salt)).substr(12,34);
}
