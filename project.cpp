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
	
  	//making sure not in root before trying parent
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
	cout<<"Error: no directory with that name found"<<endl;
        }
    	//no changes made, returns original curr
   	 return curr;
}



directory* mkfs(directory root, directory *curr){
  	
	//incase already in root directory, clears root
	if(curr->title == "root"){
	curr->children.clear();
	curr->files.clear();
	cout<<"System Formatted"<<endl;
	return curr;
	}
	
	//moves pointer to root then clears
	while(curr->title !="root"){
	curr=curr->parent;
	}
	curr->children.clear();
	curr->files.clear();
	cout<<"System Formatted"<<endl;
	return curr;
}
	

void ls(directory *curr){
	
	//iterates through children map of directories, printing names
	map<string, directory >::iterator i; 
	for (i = curr->children.begin();i != curr->children.end(); ++i){
		
	cout<<"["<<i->first<<"]"<<"  ";
	}
	
	//iterates through file map of strings, printing names
	map<string, file >::iterator t; 
	for (t = curr->files.begin();t != curr->files.end(); ++t){
		
	cout<<t->first<<"  ";
	}
		
	//formatting
	cout<<endl; 
}

void rmdir(string name, directory *curr){
	bool found = false;
	
	//checks if name is file not directory
	map<string, file >::iterator t; 
	for (t = curr->files.begin();t != curr->files.end(); ++t){
		if(t->first == name){
		cout<<"Error: "<<name<<" is a file, not a directory"<<endl;
		return;
		}		
	}
	
	
	//iterates through map children and deletes if name matches
	map<string, directory >::iterator i;
	for (i = curr->children.begin();i != curr->children.end(); ++i){
		if(i->first == name){
			//to check if directory is empty	
			directory temp = i->second;
			if(temp.children.size()!=0||temp.files.size()!=0){
			cout<<"Error: Cannot remove non-empty directory"<<endl;
			return;
			}
		curr->children.erase(i);
		found =true;
		break;
		}
	}

	//no directory of that name
	if(found ==false){
	cout<<"Error: "<<name<<" not found"<<endl;	
	}
}

void rmfl(string name, directory *curr){
	bool found = false;
	
	//checks if name directory not a file
	map<string, directory >::iterator t; 
	for (t = curr->children.begin();t != curr->children.end(); ++t){
		if(t->first == name){
		cout<<"Error: "<<name<<" is a directory, not a file"<<endl;
		return;
		}		
	}

	
	
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
		cout<<"Error: "<<name<<" not found"<<endl;
	}

}


void mkfl(string name, directory *curr){
	time_t now=time(0);
	char* dt=ctime(&now);
	//checking if name is used for directory
	map<string, directory >::iterator i; 
	for (i = curr->children.begin();i != curr->children.end(); ++i){
		if(i->first ==name){
		cout<<"Error: name already used for a Directory"<<endl;
		return;
		}
	}
	
	//checking if name used for a file
	map<string, file >::iterator t; 
	for (t = curr->files.begin();t != curr->files.end(); ++t){
		if(t->first ==name){
		cout<<"Error: name already used for a File"<<endl;
		return;
		}
	
	}
	
	//inserts name as key and temp as actual file
	file temp(name);
	temp.created=now;
	curr->files.insert(pair<string,file>(name, temp));
	
	cout<< "File " << name << " created in " << curr->title <<" at "<<dt<<endl;
}

void mkdir(string name, directory *curr){
	time_t now=time(0);
	char* dt=ctime(&now);
	//checking if name is used for directory
	map<string, directory >::iterator i; 
	for (i = curr->children.begin();i != curr->children.end(); ++i){
		if(i->first ==name){
		cout<<"Error: name already used for a Directory"<<endl;
		return;
		}
	}
	
	//checking if name used for a file
	map<string, file >::iterator t; 
	for (t = curr->files.begin();t != curr->files.end(); ++t){
		if(t->first ==name){
		cout<<"Error: name already used for a File"<<endl;
		return;
		}
	
	}

	//constructor taking name and pointer to parent directory
	directory b(name, curr);
	b.created=now;
	//adding directory with key as passed name
	curr->children.insert(pair<string,directory>(name,b));

	cout<< "Directory " << name << " created in " << curr->title <<" at "<<dt<<endl;
}

void stat(string name, directory *curr){
	bool found = false;
	//find the file or... 
	map<string, file >::iterator i;
	for (i = curr->files.begin();i != curr->files.end(); ++i){
		if(i->first == name){	
			file temp=i->second;
			char* dt=ctime(&temp.created);
			cout<<"File "<<temp.title<<" created at "<<dt<<endl;
	
			found =true;
			break;
		}
	}
	//find the directory or...
	map<string, directory >::iterator t;
	for (t = curr->children.begin();t != curr->children.end(); ++t){
		if(t->first == name){
			directory temps =t->second;
			char* td=ctime(&temps.created);
			cout<<"Directory ["<<temps.title<<"] created at "<<td<<endl;
		found =true;
		break;
		}
	}//the file/directory does not exist
	if(found ==false){
		cout<<"Directory or file \""<<name<<"\" not found"<<endl;	
	}
}

bool exit(){
	//break shell_loop
	return false;
}

void shell_loop(directory rootdir, directory *curr){
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
		curr = mkfs(rootdir, curr);
		format = 1;
	}
	else if(command =="mkfile" && format == 1){
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
	else if(command == "rmfile" && format == 1){
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
	else if(command == "stat"){
		if(parameter == ""){
			cout<<"command requires parameter"<<endl;
		}
		else{
			stat(parameter, curr);
		}
	}
	else if(format == 0){
	cout<<"Must format File System: Enter mkfs"<<endl;
	}
	else{
	cout<<"command "<< command<< " not recognized"<<endl;
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



cout<<"System Exit"<<endl;

return EXIT_SUCCESS;
}
