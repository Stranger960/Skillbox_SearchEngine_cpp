#include "searchEngine.h"
#include "converterJSON.h"
#include "invertedIndex.h"
#include "searchServer.h"
using namespace std;


int main()
{
	map<string, vector<Entry>>	_freqDict;
	vector< vector<Entry> >		_resultIndex;
	vector <vector<RelativeIndex> > _resultServer;
	vector <vector<pair<int, float>> > _resultConverted;
	vector<pair<int, float>> _pairConverted;

	ConverterJSON converterJSON;
	converterJSON.fileList = converterJSON.GetTextDocuments();
	cout << "\n\n*** Files list (converterJSON.fileList): ";
	for (auto& file : converterJSON.fileList) cout << "\n" << file;

	converterJSON.responsesLimit = converterJSON.GetResponsesLimit();
	cout << "\n\n*** Responses limit: " << converterJSON.responsesLimit;

	converterJSON.requestsList = converterJSON.GetRequests();
	if (!PRINT) {
		cout << "\n\n*** Requests list (converterJSON.requestsList): ";
		for (auto& request : converterJSON.requestsList) cout << "\n" << request;
		cout << "\n\n";
	};

	InvertedIndex idx;
	idx.DocFilesRead(converterJSON.fileList);
	idx.UpdateDocumentBase(idx.docs);

	_freqDict = idx.GetFreqDictionary();
	if (PRINT) {
		for (auto& _entry : _freqDict) {
			cout << "\n" << _entry.first << ": ";
			for (auto& _entry2 : _entry.second) 	cout << _entry2.docId << ", " << _entry2.count << "    ";
		}
	};

	for (auto& request : converterJSON.requestsList) {
		stringstream __stream(request);
		string singleWord;
		while (__stream >> singleWord) {
			vector<Entry> word_count = idx.GetWordCount(singleWord);
			_resultIndex.push_back(word_count);
		}
	}

	SearchServer srv(idx);
	srv.getLimits(converterJSON.responsesLimit);
	_resultServer = srv.search(converterJSON.requestsList);

	if (_resultServer.empty()) {
		cout << "\n\n *** Search completed: no results ***\n\n";
		return 0;
	}

	// Converting _resultServer to vector <vector<pair<int, float>> > _resultConverted;
	for (const auto& innerVec : _resultServer) {
		for (const auto& _index : innerVec) _pairConverted.emplace_back(_index.doc_id, _index.rank);
		_resultConverted.push_back(move(_pairConverted));
	}

	converterJSON.PutAnswers(_resultConverted);
	cout << "\n*** Search completed OK, window will be closed in " << WAIT_SECONDS << " seconds\n\n";
	PAUSE

	return 0;
}
