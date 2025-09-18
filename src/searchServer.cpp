#include "searchEngine.h"
#include "invertedIndex.h"
#include "converterJSON.h"
#include "searchServer.h"
#include <algorithm>
using namespace std;

void SearchServer::getLimits(int conv) { _maxResp = conv; }

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& reqList)
{
	//RelativeIndex: { size_t doc_id;	float rank; }
	vector<vector<RelativeIndex>> reply;


	vector<RequestCounter> reqLine;
	vector<RelativeIndex>  docAnswers, docFinal;
	vector<Entry> wordCount, wordSumm = {};
	map <size_t, size_t> wordMap = { {0,0} };

	if (PRINT) cout << "\n*** SearchServer: requests  / max Limits = " << _maxResp << endl;

	for (const auto& line : reqList)
	{
		docAnswers.clear();
		docFinal.clear();
		reqLine.clear();
		wordMap.clear();
		string oneWord = "";
		size_t maxCount = 0;
		bool notFound = false;

		istringstream _stream(line);
		while (_stream >> oneWord)
		{
			auto it = find_if(reqLine.begin(), reqLine.end(),
				[&oneWord](const RequestCounter& entry) { return entry.word == oneWord; });

			if (it == reqLine.end())            reqLine.push_back({ oneWord, 1 });
			else  it->cou += 1;
		}

		sort(reqLine.begin(), reqLine.end(), [](const RequestCounter& n, const RequestCounter& m) {
			return n.cou < m.cou; });

		if (PRINT) cout << "\n*** Request: <" << line << ">  ";

		for (const auto& _cou : reqLine)
		{
			wordCount = _index.GetWordCount(_cou.word);
			for (const auto& _count : wordCount)
			{
				if (PRINT) cout << "\n## Word_count for <" << _cou.word << ">  docId: " << _count.docId << "  Count: " << _count.count;
				wordMap[_count.docId] += _count.count;
			}
		}

		for (const auto& _map : wordMap) {
			if (PRINT) cout << "\nwordMap Doc: " << _map.first << "    Total search request words found (cou): " << _map.second;
			if (maxCount < _map.second) maxCount = _map.second;
		}
		if (PRINT) cout << "\nmaxCount per request line: " << maxCount;

		if (maxCount != 0) {
			for (auto& _map : wordMap) {
				float rank = (float)_map.second / (float)maxCount;
				docAnswers.push_back(RelativeIndex{ _map.first, rank });
			}
			maxCount = 0;

			sort(docAnswers.begin(), docAnswers.end(), [](const RelativeIndex& x, const RelativeIndex& y) {
				return x.rank > y.rank;	});
		}
		else {
			notFound = true;
		};

		if (PRINT) {
			cout << "\n\n*** Sorted docAnswers: \n{\n";
			for (const auto& _doc : docAnswers)		cout << "{" << _doc.doc_id << ", " << _doc.rank << "}  \n";
			cout << "}\n";
		};

		if (notFound) {
			reply.push_back({});
			bool notFound = false;
			continue;
		}

		int numItemsCopy = (docAnswers.size() < _maxResp) ? docAnswers.size() : _maxResp;
		copy_n(docAnswers.begin(), numItemsCopy, back_inserter(docFinal));

		reply.push_back(docFinal);
	}

	return reply;
}