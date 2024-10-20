#include "ExamResult.h"

ExamResult::ExamResult(string name, string category, double score, int correct, int total)
{
	this->studentName = name;
	this->category = category;
	this->score = score;
	this->correctAnswers = correct;
	this->totalQuestions = total;
}

void ExamResult::SaveExamRecord()
{
    // Load existing exam results
    ifstream file("exam_results.json");
    json examResults = json::array();

    if (file.is_open()) {
        file >> examResults; // Load existing records
    }

    // Add the new exam result
    examResults.push_back(toJson());

    // Save updated results back to file
    ofstream outFile("exam_results.json");
    outFile << examResults.dump(4); // Pretty print with an indent of 4 spaces
}

json ExamResult::toJson()
{
    return json{
           {"studentName", studentName},
           {"category", category},
           {"correctAnswers", correctAnswers},
           {"totalQuestions", totalQuestions},
           {"score", score}
    };
}
void ExamResult::fromJson(json j)
{
    studentName = j.at("studentName").get<std::string>();
    category = j.at("category").get<std::string>();
    correctAnswers = j.at("correctAnswers").get<int>();
    totalQuestions = j.at("totalQuestions").get<int>();
    score = j.at("score").get<double>();
}
