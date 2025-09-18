#include "searchEngine.h"
#include "invertedIndex.h"
#include "converterJSON.h"
using namespace std;


map<string, vector<Entry>>  InvertedIndex::GetFreqDictionary() { return freqDictionary; };


void InvertedIndex::DocFilesRead(const vector<string>& fileList) {
	for (const auto& file : fileList) {
		ifstream docFile(file);
		if (!docFile.is_open()) {
			throw runtime_error("*** DocFilesRead: missing file -> " + file);
		}
		string oneLine, docData;
		while (getline(docFile, oneLine)) docData += (oneLine + " ");
		docs.push_back(docData);
	}
}


void InvertedIndex::UpdateDocumentBase(vector<string>  _docs)
{
	vector<thread> threads;
	mutex docMute;

	auto wordProcess = [&](size_t docCou, const string _doc)
		{
			istringstream _stream(_doc);
			string oneWord;

			while (_stream >> oneWord)
			{
				lock_guard<mutex> guard(docMute);

				auto it = freqDictionary.find(oneWord);

				if (it == freqDictionary.end())
				{
					freqDictionary[oneWord].push_back({ docCou, 1 });
				}
				else
				{
					bool updated = false;
					for (auto& entry : it->second)
					{
						if (entry.docId == docCou)
						{
							entry.count += 1;
							updated = true;
							break;
						}
					}
					if (!updated)
					{
						freqDictionary[oneWord].push_back({ docCou, 1 });
					}
				}
			}
		};
	for (int k = 0; k < _docs.size(); k++)	threads.emplace_back(wordProcess, k, _docs[k]);
	for (auto& thread : threads) 	thread.join();
}


vector<Entry> InvertedIndex::GetWordCount(const string& _word)
{
	vector<Entry> _result = {};

	for (const auto& _entry : freqDictionary) {
		if (_entry.first == _word) {
			for (const auto& _entry2 : _entry.second) _result.push_back({ _entry2.docId, _entry2.count });
			break;
		}
	}

	return _result;
}