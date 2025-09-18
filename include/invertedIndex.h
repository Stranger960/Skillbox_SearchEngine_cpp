#pragma once
#include "searchEngine.h"


struct Entry {
	size_t docId, count;

	bool operator == (const Entry& other) const {
		return (docId == other.docId && count == other.count);
	}
};


class InvertedIndex {
public:
	ifstream docFile;
	string docPath;
	string oneLine = "";
	string docData = "";
	vector <string> docs;

	InvertedIndex() = default;
	~InvertedIndex() = default;

	map<string, vector<Entry>>GetFreqDictionary();

	void DocFilesRead(const vector<string>& fileList);

	void UpdateDocumentBase(vector<string>);

	vector<Entry> GetWordCount(const string&);

private:
	map<string, vector<Entry>> freqDictionary;
};




