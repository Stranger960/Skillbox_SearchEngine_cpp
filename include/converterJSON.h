#pragma once
#include "searchEngine.h"


class ConverterJSON {
public:
	ifstream configFile, requestsFile;
	const string requestsPath = "requests.json";
	const string configPath = "config.json";
	const string answersPath = "answers.json";
	string appVersion = "";
	
	nlohmann::json 	confData, config, reqData;
	vector <string> fileList;
	vector <string> requestsList;
	int responsesLimit = 0;
	int filesNumber = 0;

	ConverterJSON() = default;
	~ConverterJSON() = default;

	vector<string> GetTextDocuments();

	int GetResponsesLimit();

	vector<string> GetRequests();

	void PutAnswers(const vector<vector<pair<int, float>>>& _searchResults);
};