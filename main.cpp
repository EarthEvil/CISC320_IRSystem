#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <ctype.h>
#include <math.h>
#include <dirent.h>
#include <fstream>
#include "IRSystem.hh"
using namespace std;

#define TRUE 1
#define FALSE 0
#define VNAME(x) #x //macro that convert variable name to string
/*
how to compile: g++ -std=c++11 main.cpp -o main
or make
     ./main
*/


/*----------------------------Class Definition----------------------------------------*/
/*
wordset ------ remove duplicate


*/

void readStopWord(IRSystem *irs){
	string s;
	ifstream inStream;
	string filePath = "/home/tongming/320_Project_2/stop_words.txt";
	int count = 0;
	//try to open file
	inStream.open(filePath);
	if (inStream.fail()) {
		cout << "Fail to open stop_words.txt" << endl;
		exit(1);
	}

	while (!inStream.eof()) {
		inStream >> s;
		cout << s << endl;
		irs->addStopWord(s);
		count ++;
	}
	cout << count<< endl;
	inStream.close();

}




int main() {
	string searchstring = "place";
	IRSystem *irs = new IRSystem();
	irs->initialize();
	irs->makeFrequencyMatrix();

	// need to read files from folder here
	string path = "/home/tongming/320_Project_2/texts_project";
	string filePath;
	DIR* dir;
	dirent* pdir;
	std::vector<string> files;
	ifstream inStream;
	string line;
	dir = opendir(path.c_str());

	while (pdir = readdir(dir)) {
		if ( !strcmp(pdir->d_name, ".") || !strcmp(pdir->d_name, "..") )
		{
			// do nothing
		} else {
			files.push_back(pdir->d_name); // use it
			cout << pdir->d_name << endl;
		}
	}

	for (auto c : files) {
		// cout << c << " ";
	}
	for (int i = 0; i < files.size(); i++) {
		// cout << " file name: " << files[i] << endl;
		filePath = path + "/" + files[i];	// get full path of file

		// try to open file
		inStream.open(filePath);
		if (inStream.fail()) {
			cout << "Fail to open file" << endl;
			exit(1);
		}

		// read input line one by one
		while (getline(inStream, line)) {
			// cout << line <<"||||||"<< endl;
		}

		inStream.close();	// close inStream
	}

	readStopWord(irs);
	// test addStopWord
	for( auto c : irs->getStopWordsList()){
		cout << c << " ";
	}
}

