// Grach Muradyan, Skillbox diploma work, September 2025
#pragma once
#include "searchEngine.h"
#include "invertedIndex.h"
#include "converterJSON.h"


struct RelativeIndex {
	size_t doc_id;
	float rank;
	bool operator ==(const RelativeIndex& other) const {
		return (doc_id == other.doc_id && rank == other.rank);
	}
};


struct RequestCounter {
	string word;
	size_t cou;
};


class SearchServer {
public:
	SearchServer(InvertedIndex& idx) : _index(idx) { };
	~SearchServer() = default;

	vector<vector<RelativeIndex>> search(const	vector<string>& queries_input);

	vector<pair<string, int>> queriesVec;

	int _maxResp = 5;
	void getLimits(int conv);

private:
	InvertedIndex& _index;
};