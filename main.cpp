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

// void readStopWord(IRSystem *irs) {
// 	string s;
// 	ifstream inStream;
// 	string filePath = "/home/tongming/320_Project_2/CISC320_IRSystem/stop_words.txt";
// 	//try to open file
// 	inStream.open(filePath);
// 	if (inStream.fail()) {
// 		cout << "Fail to open stop_words.txt" << endl;
// 		exit(1);
// 	}

// 	while (!inStream.eof()) {
// 		inStream >> s;
// 		irs->addStopWord(s);
// 	}
// 	inStream.close();
// }

int main() {
	IRSystem *irs = new IRSystem();

	// need to read files from folder here
	static string path = "/home/tongming/320_Project_2/CISC320_IRSystem/Documents";
	string filePath;
	DIR* dir;
	dirent* pdir;
	std::vector<string> files;
	ifstream inStream;
	string line;
	string fileString;
	string query;
	dir = opendir(path.c_str());

	while (pdir = readdir(dir)) {
		if ( !strcmp(pdir->d_name, ".") || !strcmp(pdir->d_name, "..") )
		{
			// do nothing
		} else {
			files.push_back(pdir->d_name); // use it
		}
	}

	for (int i = 0; i < files.size(); i++) {
		filePath = path + "/" + files[i];	// get full path of file
		// cout <<filePath<< endl;
		// try to open file
		inStream.open(filePath);
		if (inStream.fail()) {
			cout << "Fail to open file" << endl;
			exit(1);
		}

		// read input line one by one
		while (getline(inStream, line)) {
			fileString += line;
		}

		inStream.close();	// close inStream

		// now fileString = content of document
		// add document name
		irs->addDocumentName(files[i]);
		// add document content
		irs->addDocument(fileString);

		fileString.clear();
	} // end of for

	cout << "Welcome to SHA (Super Human Animal) Information Retrieval System" << endl;
	cout << "Type in your query: \n";
	getline(cin, query);
	irs->addDocumentName("query");
	irs->addDocument(query);
	irs->initialize();

	irs->makeFrequencyMatrix();
	irs->printQueryResult();
	if (irs->getshouldexpand()) {
		irs->newfun();
	}
	
}

