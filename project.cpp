#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <ctime>

using namespace std;

bool status = 1;

class directory{
public:
	string title;
	time_t created;
	map <string, directory> children;
	string files[50];
	time_t fcreated[50];
	int numfiles = 0;
	
	directory(string a){
	    title = a;
	}
};

directory *curr;

void mkfs(void){
    map<string,directory>root;
	root.clear();
	directory root("root");
	root.insert(pair<string,directory>("root",root));
	curr = &root;
	cout<<"System has been formatted"<<endl;
}

void mkdir(string name){
directory name("name");
}

void mkfl(string a){
    curr->files[curr->numfiles] = a;
    cout<<a<<" "<<curr->fcreated[curr->numfiles]<<endl;
    curr->numfiles++;
}

bool exit(){
return false;
}


void shell_loop(void){
string input;
string command;
string parameter;
	do{
	cout<< "My_shell_WANG: ";
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
	//break;
	status = exit();
	}
	if (command=="mkfs"){
		mkfs();
	}
	
	}while(status ==  1);
}

int main(){//initializes the shell loop 
cout<<"Welcome to CSCI 3232 shell file system!\n";

shell_loop();

cout<<"bye"<<endl;

return EXIT_SUCCESS;
}
