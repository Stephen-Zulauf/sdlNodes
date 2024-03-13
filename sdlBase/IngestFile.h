#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>

#include "BSTree.h"

using std::ifstream;
using std::string;
using std::queue;

class Ingest {
private:
	string fileName;
	ifstream file;

	queue<char> keys;
	queue<string> data;

	vector<char> rKeys;
	vector<string> rData;
	
public:

	Ingest(string nFile) {
		this->fileName = nFile;
	}

	//open file
	bool openFile();

	//ingest file into vectors (closes file)
	bool ingestFile();

	//needs sorted data file ingested with ingest file to vectors
	void medianCut(int nStart, int nEnd);

	//load to tree
	bool loadToTree(BST* nTree);

	//print ingested key queue (emptys queue)
	void printQueue();

	//get length of keys queue
	int getKeyLength();

};