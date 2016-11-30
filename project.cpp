//members of group are Chris Pool, Thomas Yeomans, Michael Henning, and Alexander Cockrum 
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <ctime>
#include <iterator>

using namespace std;

/*
 *Creates a default constructor for file
*/
class file{
public:
	string title; //string title which is used to store name of file
	time_t created; //time_t is used to store time of file creation

	file(string a){ //constructor for file
		title = a;
	}


};
/* Two maps are created with one containing directory class and the other containing file class.
 * Time is created as well as pointer named parent.
 * Two constructors are created for directory, one with just string and the other with string and a pointer.
*/

class directory{
public:
	string title; //string used to store directory name
	time_t created; // time_t stores time directory was created
	map <string, directory> children; //map children with declaration of string and directory 
	map<string, file> files; //map files with declaration of string and file
	directory *parent; //pointer for directory named parent
	
	directory(string a){ //constructor for directory when only a string is needed
	    title = a;
	}

	directory(string a, directory *b){ //constructor for directory when a string and pointer is needed
		title = a;
		parent = b;
	} 
	


};

// Changes the pointer to the root directory
directory* cd(directory*curr){
	//makes sure not to try to go to roots parent	
	if(curr->title == "root"){// checks if pointer curr is already set to root
	cout<<"Already in root directory"<<endl;
	return curr;
	}else{
	//goes to parent
	curr = curr->parent; //curr is reassigned to pointer parent
	cout<<"Now in directory "<<curr->title<<endl;
	return curr;
	}
}

//Allows the user to change to a directory in the map if it exists
directory* cd (string name, directory *curr){
   bool found = false; //decleration of boolean found 
	
  	//making sure not in root before trying parent
	if(curr->title != "root"){ //if curr is not currently set to root
		//trying to go to parent	
		if(curr->parent->title == name){ //reassigns curr to parent directory
			curr = curr->parent;
			cout<<"Now in directory "<<curr->title<<endl;
			found = true;
			return curr;
		}
	}
	//trying to go to child
	map<string, directory>::iterator i; //declears an iterator i 
	for (i = curr->children.begin();i != curr->children.end(); ++i){ //locates directory with supplied name 
		if(i->first == name){
	 	curr = &(i->second); //sets pointer curr to desired directory
	 	 cout<<"Now in directory "<<curr->title<<endl;
		found = true; //changes boolean found
		return curr; //retruns pointer curr
		}

	}
	//no directory of that name
	if(found == false){ 
	cout<<"Error: no directory with that name found"<<endl;
        }
    	//no changes made, returns original curr
   	 return curr;
}

//Moves the pointer to root and clears all of its children
directory* mkfs(directory root, directory *curr){ 
  	
	//incase already in root directory, clears root
	if(curr->title == "root"){
	curr->children.clear(); //clears children of root
	curr->files.clear(); // clears the files of root
	cout<<"System Formatted"<<endl;
	return curr;
	}
	
	//moves pointer to root then clears
	while(curr->title !="root"){
	curr=curr->parent; //reasigns curr to root
	}
	curr->children.clear(); //clears children of root
	curr->files.clear(); //clears files of root
	cout<<"System Formatted"<<endl;
	return curr;
}
	
//pirnts out all of the children of a directory and differentiates between directories and files
void ls(directory *curr){
	map<string, directory >::iterator i; //creates iterator i 
	for (i = curr->children.begin();i != curr->children.end(); ++i){//iterates through children map of directories, printing names	
	cout<<"["<<i->first<<"]"<<"  ";
	}
		
	map<string, file >::iterator t; //creates iterator t 
	for (t = curr->files.begin();t != curr->files.end(); ++t){//iterates through file map of strings, printing names
		
	cout<<t->first<<"  ";
	}
		
	//formatting
	cout<<endl; 
}

//checks if the directory exists and removes it if it does
void rmdir(string name, directory *curr){
	bool found = false; //decleration of boolean variable found
	
	//checks if name is file not directory
	map<string, file >::iterator t;//decleration of iterator t 
	for (t = curr->files.begin();t != curr->files.end(); ++t){//iterates through files in the map
		if(t->first == name){ //if the name exist and is a file
		cout<<"Error: "<<name<<" is a file, not a directory"<<endl;
		return;
		}		
	}
	
	
	//iterates through map children and deletes if name matches
	map<string, directory >::iterator i;//decleration of iterator t
	for (i = curr->children.begin();i != curr->children.end(); ++i){ //iterates through map children
		if(i->first == name){ //if name exist in map children	
			directory temp = i->second;
			if(temp.children.size()!=0||temp.files.size()!=0){//to check if directory is empty
			cout<<"Error: Cannot remove non-empty directory"<<endl;
			return;
			}
		curr->children.erase(i);//erases children
		found =true;//updates boolean variable found
		break;
		}
	}

	//no directory of that name
	if(found ==false){
	cout<<"Error: "<<name<<" not found"<<endl;	
	}
}

//checks if the file exists and removes it if it does
void rmfl(string name, directory *curr){
	bool found = false;//decleration of boolean variable found
	
	//checks if name directory not a file
	map<string, directory >::iterator t; //decleration of iterator t
	for (t = curr->children.begin();t != curr->children.end(); ++t){//iterates through map children
		if(t->first == name){//if name is found in map children
		cout<<"Error: "<<name<<" is a directory, not a file"<<endl;
		return;
		}		
	}

	
	
	//iterates through map files and deletes if name matches
	map<string, file >::iterator i;//decleration of iterator i
	for (i = curr->files.begin();i != curr->files.end(); ++i){//iterates through map files
		if(i->first == name){	//if name is found in map files
			curr->files.erase(i);//erases from map files
	
			found =true;
			break;
		}
	}
	
		//no file of that name
	if(found ==false){
		cout<<"Error: "<<name<<" not found"<<endl;
	}

}

//creates a file in the file map and stores time created
void mkfl(string name, directory *curr){
	time_t now=time(0);//curent time is set to zero
	char* dt=ctime(&now);//time now is assigned to char pointer dt
	//checking if name is used for directory
	map<string, directory >::iterator i; //decleration of iterator i
	for (i = curr->children.begin();i != curr->children.end(); ++i){//iterates through map children
		if(i->first ==name){//if name is found in map children
		cout<<"Error: name already used for a Directory"<<endl;
		return;
		}
	}
	
	//checking if name used for a file
	map<string, file >::iterator t; //decleration of iterator t
	for (t = curr->files.begin();t != curr->files.end(); ++t){//iterates through map files
		if(t->first ==name){//if name is found in map files
		cout<<"Error: name already used for a File"<<endl;
		return;
		}
	
	}
	
	//inserts name as key and temp as actual file
	file temp(name);//file temp is created with name
	temp.created=now;//time created is stored
	curr->files.insert(pair<string,file>(name, temp));
	
	cout<< "File " << name << " created in " << curr->title <<" at "<<dt<<endl;
}

//creates a directory in the directory map and stores time created
void mkdir(string name, directory *curr){
	time_t now=time(0);//time is set to zero
	char* dt=ctime(&now);//time now is assigned to pointer char dt
	//checking if name is used for directory
	map<string, directory >::iterator i; //decleration of iterator i
	for (i = curr->children.begin();i != curr->children.end(); ++i){//iterates through map children
		if(i->first ==name){//if name is found in map childrn 
		cout<<"Error: name already used for a Directory"<<endl;
		return;
		}
	}
	
	//checking if name used for a file
	map<string, file >::iterator t; //decleration of iterator t
	for (t = curr->files.begin();t != curr->files.end(); ++t){//iterates through map files
		if(t->first ==name){//if name is found in map files
		cout<<"Error: name already used for a File"<<endl;
		return;
		}
	
	}

	//constructor taking name and pointer to parent directory
	directory b(name, curr);//directory b is declared
	b.created=now;//time is stroed
	//adding directory with key as passed name
	curr->children.insert(pair<string,directory>(name,b));

	cout<< "Directory " << name << " created in " << curr->title <<" at "<<dt<<endl;
}

//assigns time created to the directory or file created so the information can be accesssed
void stat(string name, directory *curr){
	bool found = false;//decleration of boolean variable found
	//find the file or... 
	map<string, file >::iterator i;//decleration of iterator i
	for (i = curr->files.begin();i != curr->files.end(); ++i){//iterates through map files
		if(i->first == name){	//if name is found in map files
			file temp=i->second; // temp is assigned to file
			char* dt=ctime(&temp.created); //dt is assigned to temp.created
			cout<<"File "<<temp.title<<" created at "<<dt<<endl;
			found =true;//boolean is updated
			break;//stat is exited
			return;
		}
	}
	//find the directory or...
	map<string, directory >::iterator t;//iterator t is decleared 
	for (t = curr->children.begin();t != curr->children.end(); ++t){//iterates through map children
		if(t->first == name){//if name is found in map children
			directory temps =t->second;//temp is assigned to pointer second
			char* td=ctime(&temps.created);//dt is assigned to temps.created
			cout<<"Directory ["<<temps.title<<"] created at "<<td<<endl;
		found =true;//updates boolean variable
		break;//exits stat
		return;
		}
	}//the file/directory does not exist
	if(found ==false){
		cout<<"Directory or file \""<<name<<"\" not found"<<endl;	
	}
}

//breaks the shell loop
bool exit(){
	return false;
}

//uses a boolean status to keep itself running until exit is entered
//if statements are used to assign parameters to the commands 
//a for loop is used to break up user input into commands and parameters
void shell_loop(directory rootdir, directory *curr){
bool status = 1;//decleration of boolean variable status
bool format = 0;//decleration of boolean variable format
string input;//decleration of string input
string command;//decleration of string command
string parameter = "";//decleration and assignment of string parameter

	do{
	parameter = "";
	cout<< "My_shell_3232: ";
	getline(cin, input);//gets user input
	for(int i = 0; i<input.length();i++){//looks for space in command line, assigns command and parameter	
	if(input[i] ==' '){//looks for empty space
	command = input.substr(0,i);//command is assigned to first user input
	parameter = input.substr(i+1,input.length()-1);//parameter is assigned to second user input if it exist
	break;
	}else{
	//no space, no parameter entered
	command = input;
	}
}
	if (command=="exit"){//exits loop
	status = exit();
	}
	else if (command=="mkfs"){//runs mkfs method
		curr = mkfs(rootdir, curr);
		format = 1;
	}
	else if(command =="mkfile" && format == 1){//incase no parameter is entered with method mkfile
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		mkfl(parameter, curr);
		}
	}
	else if(command =="mkdir" && format == 1){//incase no parameter is entered with method mkdir
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		mkdir(parameter, curr);
		}
	}
	else if(command =="ls" && format == 1){//checks that ls is entered with no parameter
		ls(curr);
	}
	else if(command == "rmdir" && format == 1){//incase no parameter is entered with method rmdir
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		rmdir(parameter, curr);
		}
	}
	else if(command == "rmfile" && format == 1){//incase no parameter is entered with method rmfile
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		rmfl(parameter, curr);
		}
	}
	else if(command =="cd" && format == 1){//incase no parameter is entered with method cd
		if(parameter==""){
		  curr = cd(curr);
		}else{
		curr = cd(parameter, curr);
		}
    	}
	else if(command == "stat" && parameter == 1){//incase no parameter is entered with method stat
		//if(parameter == ""){
			cout<<"command requires parameter"<<endl;
		}
		else{
			stat(parameter, curr);
		}
	}
	else if(format == 0){//incase mkfs is not the first method used
	cout<<"Must format File System: Enter mkfs"<<endl;
	}
	else{
	cout<<"command "<< command<< " not recognized"<<endl;
	}
	}while(status ==  1);
}




//creates pointer curr and root directory and starts the pointer at root
//begins shell loop
int main(){
directory  *curr;
directory rootdir("root");
curr = &rootdir;

//initializes the shell loop 
cout<<"Welcome to CSCI 3232 shell file system!\n";

shell_loop(rootdir, curr);



cout<<"System Exit"<<endl;

return EXIT_SUCCESS;
}
