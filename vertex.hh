#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stdio.h>
#include <string.h>
using namespace std;

class Vertex{
public:
	//constructor
	Vertex(){
		name = "";
		index = -1;
		distance = -1;
		checked = false;
		//initilizing vector
		neighborVector.clear();
	}
	Vertex(string input){
		name = input;
		index = -1;
		distance = -1;
		checked = false;
		//initilizing vector
		neighborVector.clear();
	}
	Vertex(string input, int index){
		name = input;
		this->index = index;
		distance = -1;
		checked = false;
		//initilizing vector
		neighborVector.clear();
	}

	//accessor and mutator methods
	string getName() {return name;}
	void setName(string name) {this->name = name;}

	int getIndex() {return index;}
	void setIndex(int value) {this->index = value;}

	bool isCheck() {return checked;}
	void setCheck(bool var) {this->checked = var;}

	int getDistance() {return distance;}
	void setDistance(int d) {this->distance = d;}

	vector<Vertex*> getNeighborVector() {return neighborVector;}
	void pushToNeighbor(Vertex *v) {this->neighborVector.push_back(v);}


	bool isNeighbor(string name);
	void print();
	void printNeighbor();
private:
	int distance;
	bool checked;
	int index;
	string name;
	vector<Vertex*> neighborVector;
};

//implementation of methods--------------------------
void Vertex::print(){
	cout << name;
}

void Vertex::printNeighbor(){
	for (int i = 0; i < neighborVector.size(); i ++){
		cout << neighborVector[i]->getName() << ", ";
	}
	cout << endl;
}

bool Vertex::isNeighbor(string name){
	for(int i = 0; i < neighborVector.size(); i++){
		if(neighborVector[i]->getName() == name){
			return true;
		}
	}
	return false;
}