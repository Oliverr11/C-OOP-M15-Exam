#include "FileManager.h"

void FileManager::SaveUserInformationDataJson(json json)
{
	ofstream file;
	file.open(path);
	if (file.is_open()) {
		file << json.dump();
		file.close();
	}
}

json FileManager::LoadUserInformationDataJson()
{
	json contentJson;
	ifstream file;
	file.open(path);
	if (file.is_open()) {
		file >> contentJson;
		file.close();
	}
	return contentJson;
}

void FileManager::SaveExamRecord(vector<ExamRecord> records)
{
	ofstream file("exam_results.json");
	if (file.is_open()) {
		json j;
		for (auto record : records) {
			j.push_back(record.toJson());
		}
		file << j.dump(4); 
		file.close();
	}
	else {
		cout << "Error opening file for writing exam results." << endl;
	}
}

void FileManager::LoadExamRecord(vector<ExamRecord> records)
{
	ifstream file("exam_results.json");
	if (file.is_open()) {
		json j;
		file >> j;
		for (const auto& record : j) {
			records.push_back(ExamRecord(record["id"], record["category"], record["name"], record["score"]));
		}
		file.close();
	}
	else {
		cout << "Error opening exam results file." << endl;
	}
}

void FileManager::saveTests(const vector<Test>& tests, const string& filename)
{
	json j;
	for (auto test : tests) {
		j.push_back(test.toJson());
	}
	std::ofstream file(filename);
	if (file.is_open()) {
		file << j.dump(4); 
		file.close();
	}
	else {
		throw std::runtime_error("Unable to open file for writing.");
	}

}

void FileManager::loadTests(vector<Test>& tests, const string& filename)
{
	Test t;
	std::ifstream file(filename);
	if (file.is_open()) {
		json j;
		file >> j;
		for (const auto& testJson : j) {
			tests.push_back(t.fromJson(testJson));
		}
		file.close();
	}
	else {
		throw std::runtime_error("Unable to open file for reading.");
	}
}





