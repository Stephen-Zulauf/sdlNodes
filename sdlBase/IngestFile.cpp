#include "IngestFile.h"

//open file
bool Ingest::openFile() {

	this->file.open(this->fileName);

	if (this->file) {

		cout << "Opened file: " << this->fileName << endl;
		return true;
	}
	else {
		cout << "ERR INGEST: failed to open " << this->fileName << endl;
		return false;
	}

}

//ingest file (median cut)
bool Ingest::ingestFile() {

	this->openFile();

	string buff;

	if (this->file) {
		while (std::getline(this->file, buff)) {
			this->rKeys.push_back(buff[0]);
			this->rData.push_back(buff.substr(2));
		}

		for (int i = 0; i < this->rKeys.size(); i++) {
			cout << this->rKeys[i] << endl;
		}

		this->file.close();
		return true;
	}
	else {
		cout << "ERR INGEST: no file found" << endl;

		return false;
	}
	
}

//needs sorted data file ingested with ingest file to vectors
void Ingest::medianCut(int nStart, int nEnd) {
	if (nEnd > nStart) {

		int mid = 0;
		//put start at 0 of char vector
		//put end at end of char vector

		//get middle address of vector (length-from-start-to-end)/2
		mid = (nEnd - nStart + 1) / 2;

		//add key to key queue(middle address)
		this->keys.push(this->rKeys[nStart + mid]);
		//add string to string queue(middle address)
		this->data.push(this->rData[nStart + mid]);

		//recursive call left start-midpoint
		medianCut(nStart, nStart+mid-1);
		//recursive call right midpoint-end
		medianCut(nStart + mid+1, nEnd);
	}
	else if (nEnd == nStart && nEnd < this->rKeys.size()) {
		//add key to key queue(middle address)
		this->keys.push(this->rKeys[nStart]);
		//add string to string queue(middle address)
		this->data.push(this->rData[nStart]);
	}
	
	
}

//load to tree (closes file)
bool Ingest::loadToTree(BST nTree) {
	return true;
}

//print ingested key queue (emptys queue)
void Ingest::printQueue() {

	while (this->keys.size() != 0) {
		char temp = this->keys.front();
		cout << temp << endl;
		this->keys.pop();
	}
}

//get length of keys queue
int Ingest::getKeyLength() {
	return this->rKeys.size();
}