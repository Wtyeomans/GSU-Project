#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <ctime>
#include <iterator>

using namespace std;

class file{
public:
	string title;
	time_t created;

	file(string a){
	title = a;
	}


};


class directory{
public:
	string title;
	time_t created;
	map <string, directory> children; 
	//string files[50];
	//int numfiles = 0;
	
	
	map<string, file> files;

	directory *parent;
	
	directory(string a){
	    title = a;
	}

	directory(string a, directory *b){
		title = a;
		parent = b;
	} 
	
	void clear(){
	this->children.clear();
	}

};


directory* cd(directory*curr){
	//makes sure not to try to go to roots parent	
	if(curr->title == "root"){
	cout<<"Already in root directory"<<endl;
	return curr;
	}else{
	//goes to parent
	curr = curr->parent;
	cout<<"Now in directory "<<curr->title<<endl;
	return curr;
	}
}


directory* cd (string name, directory *curr){
   bool found = false;
	
  //making sure not to try to go to root parents
	if(curr->title != "root"){
		//trying to go to parent	
		if(curr->parent->title == name){
			curr = curr->parent;
			cout<<"Now in directory "<<curr->title<<endl;
			found = true;
			return curr;
		}
	}
	//trying to go to child
	map<string, directory>::iterator i;
	for (i = curr->children.begin();i != curr->children.end(); ++i){
		if(i->first == name){
	 	curr = &(i->second);
	 	 cout<<"Now in directory "<<curr->title<<endl;
		found = true;
		return curr;
		}

	}
	//no directory of that name
	if(found == false){
	cout<<"Error, no directory with that name found"<<endl;
        }
    	//no changes made, returns original curr
   	 return curr;
}



void mkfs(directory dir){
  	//making sure root contains nothing
	dir.clear();
	
	
	cout<<"System has been formatted"<<endl;
}
void ls(directory *curr){
	
	//iterates through children map of directories, printing names
	map<string, directory >::iterator i; 
	for (i = curr->children.begin();i != curr->children.end(); ++i){
		
	cout<<"["<<i->first<<"]"<<"  ";
	}
	
	//iterates through file map of strings, printing names
	map<string, file >::iterator t; //part of the map class
	for (t = curr->files.begin();t != curr->files.end(); ++t){
		
	cout<<t->first<<"  ";
	}
		
	//formatting
	cout<<endl; 
}

void rmdir(string name, directory *curr){
	bool found = false;
	
	map<string, directory >::iterator i;
	
	for (i = curr->children.begin();i != curr->children.end(); ++i){
		if(i->first == name){
			//to check if directory is empty	
			directory temp = i->second;
			if(temp.children.size()!=0||temp.files.size()!=0){
			cout<<"Cannot remove non-empty directory"<<endl;
			return;
			}
	//deleting child
		curr->children.erase(i);
		found =true;
		break;
		}
	}

	//no directory of that name
	if(found ==false){
	cout<<"directory: "<<name<<" not found"<<endl;	
	}
}

void rmfl(string name, directory *curr){
	bool found = false;
	
	//iterates through map files and deletes if name matches
	map<string, file >::iterator i;
	for (i = curr->files.begin();i != curr->files.end(); ++i){
	if(i->first == name){	
	curr->files.erase(i);
	
	found =true;
	break;
	}
	}
	
	//no file of that name
	if(found ==false){
	cout<<"file: "<<name<<" not found"<<endl;
	}

}


void mkfl(string name, directory *curr){
	
	//inserts name as key and temp as actual file
	file temp(name);
	curr->files.insert(pair<string,file>(name, temp));
}

void mkdir(string name, directory *curr){
	string temp = name;

	//constructor taking name and pointer to parent directory
	directory b(temp, curr);
	//adding directory with key as passed name
	curr->children.insert(pair<string,directory>(name,b));

	cout<< "directory " << temp << " created in " << curr->title << endl;
}

bool exit(){
	//break shell_loop
	return false;
}

void shell_loop(directory root, directory *curr){
bool status =1;
bool format = 0;
string input;
string command;
string parameter = "";

	do{
	parameter = "";
	cout<< "My_shell_3232: ";
	getline(cin, input);
	for(int i = 0; i<input.length();i++){
	//looks for space in command line, assigns command and parameter
	if(input[i] ==' '){
	command = input.substr(0,i);
	parameter = input.substr(i+1,input.length()-1);
	break;
	}else{
	//no space, no parameter entered
	command = input;
	}
}
	if (command=="exit"){
	
	status = exit();
	}
	else if (command=="mkfs"){
		mkfs(root);
		format = 1;
	}
	else if(command =="mkfl" && format == 1){
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		mkfl(parameter, curr);
		}
	}
	else if(command =="mkdir" && format == 1){
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		mkdir(parameter, curr);
		}
	}
	else if(command =="ls" && format == 1){
		ls(curr);
	}
	else if(command == "rmdir" && format == 1){
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		rmdir(parameter, curr);
		}
	}
	else if(command == "rmfl" && format == 1){
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		rmfl(parameter, curr);
		}
	}
	else if(command =="cd" && format == 1){
		if(parameter==""){
		  curr = cd(curr);
		}else{
		curr = cd(parameter, curr);
		}
    	}
	else if(format == 0){
	cout<<"Must format File System: Enter mkfs"<<endl;
	}
	else{
	cout<<"command not recognized"<<endl;
	}
	}while(status ==  1);
}





int main(){



directory  *curr;
directory rootdir("root");
curr = &rootdir;

//initializes the shell loop 
cout<<"Welcome to CSCI 3232 shell file system!\n";

shell_loop(rootdir, curr);



cout<<"System Ended"<<endl;

return EXIT_SUCCESS;
}
