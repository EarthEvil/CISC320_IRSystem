#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>
#include <string.h>
#include "vertex.hh"
using namespace std;
class Graph {
public:
	//constructor
	Graph() {
		//initilizing vector
		adj_List.clear();
		adj_List.reserve(20000);//reserve space for adj_List.
	}

	//accessor methods
	int getSize();
	vector <Vertex*> getAdjList();
	Vertex *getVertex(int index);//return vertex at given index;
	Vertex *getRoot();//return first vertex in adj_List
	std::vector<string> getpathToRoot() {return pathToRoot;}
	std::vector<string> getpathToRoot2() {return pathToRoot2;}
	//push string name into path_to_root vector
	void pushtopathToRoot(string name) {pathToRoot.push_back(name);}
	void pushtopathToRoot2(string name) {pathToRoot2.push_back(name);}
	void readtext();
	//print method
	void print();//print out graph
	void insert(string &);//insert vertex with input name
	void insert(vector<string> v);//insert a list of word in to adj_List, the first token in v is parent, rest are children or neighbors as we called.
	int search(string name);//find if item exist in list, if yes, return index, other wise return null

	void initializeAdjList();// initialize every vertex in adj_List. set distance to -1, set check to false
	//Q1
	int numberOfSubtypeAt(Vertex *, int order); // return number of subtype at given order

	//Q2
	string mostDiversed(Vertex *); //return name of vertex that is most diversed
	int mostDiversedHelper(Vertex *v); // helper function

	//Q3
	string findLowestCommomAncestor(Vertex *, Vertex *); //find LCA of two vertices
	void findLowestCommomAncestorHelper(Vertex *, Vertex *, vector<string> path, int pathnumber);//helper function, find path between 2 vertex;


	std::vector<string> getDirectSubtype(string);

private:
	vector <Vertex*> adj_List;
	//pathToRoot and pathToRoot2 store path of certain vertex to root
	//used for findLowestCommomAncestor
	std::vector<string> pathToRoot;
	std::vector<string> pathToRoot2;

};
//implementation of methods--------------------------
std::vector<string> Graph::getDirectSubtype(string s){
	Vertex *u;
	std::vector<string> v;

	for(auto c: adj_List){
		if(c->getName() == s){
			for(auto neighbors: c->getNeighborVector()){
				v.push_back(neighbors->getName());
			}

		}

	}
	return v;
}

void Graph::readtext() {
	//parsing stdin
	string str;
	string delimiter1 = ": ";
	string delimiter2 = ", ";

	int pos = 0;
	std::vector<string> sentence;
	std::vector<std::vector<string> > total;
	string token;
	std::vector<string> wordList;


	ifstream inStream;
	string filePath = "/home/tongming/320_Project_2/CISC320_IRSystem/graph_hyponymy.txt";
	//try to open file
	inStream.open(filePath);
	if (inStream.fail()) {
		cout << "Fail to open graph_hyponymy.txt" << endl;
		exit(1);
	}

	while (getline(inStream, str)) {
		//convert to lower case
		for (int i = 0; i < str.length(); i ++) {
			str[i] = tolower(str[i]);
		}

		sentence.push_back(str);

		//get first word in the sentence
		pos = str.find(delimiter1);
		token = str.substr(0, pos);
		wordList.push_back(token);
		str.erase(0, pos + delimiter1.length()); //erase first word from list

		//get rest of words
		pos = str.find(delimiter2); //get position of ','
		while (pos != std::string::npos) {
			token = str.substr(0, pos); //get word
			wordList.push_back(token);
			str.erase(0, pos + delimiter2.length()); //erase word from list
			pos = str.find(delimiter2);
		}
		token = str;
		wordList.push_back(token); //now wordList contains all words in one sentence
		// cout << "here" << endl;
		total.push_back(wordList);
		wordList.clear(); //clear wordList, prepare for next sentence
	}//end of parsing stdin

	// Graph *g = new Graph(); //constructor new graph
	//insert everything in total vector into graph g;
	for ( int i = 0; i < total.size(); i ++) {
		insert(total[i]);
		// cout << "here" << endl;

	}
}

int Graph::getSize() {
	return adj_List.size();
}
Vertex * Graph::getVertex(int index) {
	return adj_List[index];
}
vector <Vertex*> Graph::getAdjList() {
	return adj_List;
}
Vertex *Graph::getRoot() {
	return adj_List[0];
}

void Graph::initializeAdjList() {
	for (int i = 0; i < adj_List.size(); i++) {
		adj_List[i]->setDistance(-1);
		adj_List[i]->setCheck(false);
	}
}
//print out vertex name and it's neighbors'
void Graph::print() {
	for (int i = 0; i < adj_List.size(); i++) {
		adj_List[i]->print();
		cout << ":";
		adj_List[i]->printNeighbor();
	}
}
//search if vertex with given name exist in adj_List
int Graph::search(string name) {
	//search for index of vertex, if not found, return -1
	for (int i = 0; i < adj_List.size(); i++) {
		if (adj_List[i]->getName() == name) {
			return i;
		}
	}
	return -1;
}

void Graph::insert(string & s) {
	if (search(s) == -1) { // if s is no in list, push it in.
		adj_List.push_back(new Vertex(s, adj_List.size()));
	}
}

void Graph::insert(vector<string> v) {
	int pIndex;
	for (int i = 0; i < v.size(); i ++) {
		insert(v[i]);
	}
	pIndex = search(v[0]);//index of first item in v which is parent
	Vertex* &temp = adj_List[pIndex];//WORK
	Vertex * insertVertex;
	for ( int i = 1; i < v.size(); i ++) { //add rest items in to parent's neighbor list\
		cout
		temp->pushToNeighbor(adj_List[search(v[i])]);
	}
}


//-------------------Q1-----------------------------------------------------
/*
this function uses BFS to traverse though graph and denoting distance(order)
of each vertext to given staring vertex root, when distance equal order, increment result by 1
and not push current vertext in to queue anymore.
function stop when reach vertext with distance equal to order+1.
*/
int Graph::numberOfSubtypeAt(Vertex *root, int order) {
	//result stores number of subtypes of vertex root at given order
	int result = 0;
	//initialize vertices
	this->initializeAdjList();

	queue<Vertex*> myqueue;
	root->setDistance(0);
	myqueue.push(root);
	Vertex * u;
	while (!myqueue.empty()) {
		u = myqueue.front();
		myqueue.pop();
		for (Vertex* v : u->getNeighborVector()) {
			if (!v->isCheck()) {
				v->setDistance(u->getDistance() + 1);
				if (v->getDistance() == order) {
					result ++;
				}
				else {
					myqueue.push(v);
				}
			}
		}
		u->setCheck(true);
	}

	return result;
}

//---------------------------Q2---------------------------------------
/*
We have a helper function that calculate total number of sub-categories of SP,
we run this helper function for each sub-species of SP,
and return sub-species that with max number of sub-categories
*/

//find all subtype of Vertex v, using bsf
int Graph::mostDiversedHelper(Vertex *root) {
	//result stores total number of subtypes of vertex root
	int result = 0;

	//initialize vertices
	this->initializeAdjList();
	queue<Vertex*> myqueue;
	root->setDistance(0);
	myqueue.push(root);
	Vertex * u;
	while (!myqueue.empty()) {
		u = myqueue.front();
		myqueue.pop();
		for (Vertex *v : u->getNeighborVector()) {
			if (!v->isCheck()) {
				result ++;
				myqueue.push(v);
			}
		}
		u->setCheck(true);
	}

	return result;
}

string Graph::mostDiversed(Vertex *v) {
	int max = 0;
	int tempmax = 0;
	int index = 0;
	//compare number of sub-species of each neighbor of vertex v, and return the max one.
	for (int i = 0; i < v->getNeighborVector().size(); i++) {
		tempmax = this->mostDiversedHelper(v->getNeighborVector()[i]);
		if (tempmax > max) {
			max = tempmax;
			index = i;
		}
	}
	return v->getNeighborVector()[index]->getName();
}


//find lowest commom ancestor for vertex v1 and v2
/*
find path from v1 to root, store in vector pathToRoot;
find path from v2 to root, store in vector pathToRoot2;
compare pathToRoot and pathToRoot2 to find lowest comom ancestor
*/
string Graph::findLowestCommomAncestor(Vertex *v1, Vertex *v2) {
	Vertex * root = this->getRoot();
	int minimunSize = 0;
	//creat vector to store path
	std::vector<string> path1;
	std::vector<string> path2;
	//initialize pathToRoot vector
	pathToRoot.clear();
	pathToRoot2.clear();

	//initialize all vertices
	this->initializeAdjList();
	//find path from v1 to root, store in vector pathToRoot;
	findLowestCommomAncestorHelper(root, v1, path1, 1);

	//after run findLowestCommomAncestorHelper, need to initialize all vertices again
	this->initializeAdjList();
	//find path from v2 to root, store in vector pathToRoot2;
	findLowestCommomAncestorHelper(root, v2, path2, 2);

	//compare pathToRoot and pathToRoot2 to find LCA and return the name of LCA
	minimunSize = min(pathToRoot.size(), pathToRoot2.size());
	for (int i = 0; i < minimunSize; i ++) {
		if (pathToRoot[i] != pathToRoot2[i]) {
			return pathToRoot[i - 1];
		}
	}
}

/*
recursive function (DFS) that find path from vertex v1 to v2
*/
void Graph::findLowestCommomAncestorHelper(Vertex *v1, Vertex *v2, vector<string> path, int pathnumber) {
	//mark root as discovered;
	v1->setCheck(true);

	//add current vertex to path
	path.push_back(v1->getName());

	//add to pathToRoot according to pathnumber

	//if v1 and v2 are the same
	if ( v1->getName() == v2->getName()) {
		//transfer to path to pathToRoot or pathToRoot2 according to pathnumber;
		for (int i = 0; i < path.size(); i++) {
			if (pathnumber == 1) {
				this->pushtopathToRoot(path[i]);
			}
			else {
				this->pushtopathToRoot2(path[i]);
			}
		}
	}
	else { //if current vertex is not destination
		//Recur for all the vertices adjacent to current vertex
		for (int i = 0; i < v1->getNeighborVector().size(); i++) {
			if (!v1->getNeighborVector()[i]->isCheck()) {
				findLowestCommomAncestorHelper(v1->getNeighborVector()[i], v2, path, pathnumber);
			}
		}
	}
}
