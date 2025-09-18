#include "searchEngine.h"
#include "converterJSON.h"
#include <filesystem>
#include <string>
#include <utility>
using namespace std;
using json = nlohmann::json;


int ConverterJSON::GetResponsesLimit() { return config["max_responses"]; }


vector<string> ConverterJSON::GetTextDocuments() {
	vector<string> _fileList;

	filesystem::path currentPath = filesystem::current_path();

	configFile.open(configPath);
	if (configFile.is_open()) {
		configFile >> confData;
		configFile.close();
	}
	else {
		cerr << "*** ConverterJSON: file is missing -> " << configPath << "\n\n";
		exit(70);
	}

	auto it = confData.begin();
	if (it.key() != "config") {
		cerr << "*** ConverterJSON: file is empty -> " << configPath << "\n\n";
		exit(71);
	}

	//parsing config
	config = it.value();
	cout << "\n*** Starting " << to_string(config["name"]);
	appVersion = config["version"];

	cout << "\n*** Version: " << config["version"];

	//parsing files list
	it++;
	nlohmann::json  files = it.value();

	for (auto file : files) 	_fileList.push_back(file);

	filesNumber = _fileList.size();

	if (filesNumber <= 0 || filesNumber > 1000) {
		cerr << "\n\n*** ConverterJSON: incorrect files number -> " << filesNumber << "\n\n";
		exit(72);
	}
	return _fileList;
}

vector <string> ConverterJSON::GetRequests() {
	vector <string> _requestsList;
	requestsFile.open(requestsPath);
	if (requestsFile.is_open()) {
		requestsFile >> reqData;
		requestsFile.close();
	}
	else { cerr << "\n\n*** ConverterJSON: file is missing -> " << requestsPath << "\n\n";	exit(73); }

	auto it = reqData.begin();
	nlohmann::json requests = it.value();
	for (auto r : requests)	_requestsList.push_back(r);
	return _requestsList;
}


void ConverterJSON::PutAnswers(const vector<vector<pair<int, float>>>& _searchResults) {
	if (PRINT) {
		cout << "\n*** _searchResults: \n ";
		for (const auto& l0 : _searchResults) {
			for (const auto& l1 : l0) cout << "\n{" << l1.first << ", " << l1.second << "}";
		}
	}

	namespace fs = filesystem;
	fs::path currentPath = fs::current_path();
	const string outputFile = "answers.json";

	json final;
	json finalFile;

	int cou = 1;
	int totalResults = 0;
	if (!PRINT) cout << "\n*** Search results by request:";
	for (const auto& _results : _searchResults) {
		json finalRec;
		const string recNum =
			(cou < 10 ? "request00" : (cou < 100 ? "request0" : "request")) + to_string(cou);

		if (!PRINT) {
			cout << endl << recNum;
			if (_results.empty()) {
				cout << "  Empty record ";
			}
			else {
				totalResults++;
				cout << "  Record: ";
				for (const auto& p : _results)
					cout << "(" << p.first << ", " << (to_string(p.second)).substr(0, 5) << ") ";
			}
		}

		finalRec["Result"] = !_results.empty();

		if (_results.size() > 1) {
			json relevance = json::array();
			for (const auto& p : _results) {
				//relevance.push_back({ {"docid", p.first}, {"rank", to_string(p.second)} });
				relevance.push_back({ {"docid", p.first}, {"rank", floor(p.second*1000.0) / 1000.0} });
			}
			finalRec["relevance"] = relevance;
		}
		else if (_results.size() == 1) {
			finalRec["docid"] = floor(_results[0].first *  1000.0) / 1000.0;
			finalRec["rank"] =  floor(_results[0].second * 1000.0) / 1000.0;
		}

		final[recNum] = finalRec;
		++cou;
	}
	if (!PRINT) cout << "\n\n*** Total results: " << totalResults;

	finalFile["answers"] = final;

	cout << "\n\n*** finalFile: \n ";
	cout << finalFile.dump(4);

	ofstream file(outputFile);
	if (file) {
		file << finalFile.dump(4);
		cout << "\n\n*** PutAnswers: \"finalFile\" data sent to file " << outputFile << std::endl;
	}
	else {
		cerr << "\n\n*** PutAnswers: file is missing ->  " << outputFile << std::endl;
	}
}
