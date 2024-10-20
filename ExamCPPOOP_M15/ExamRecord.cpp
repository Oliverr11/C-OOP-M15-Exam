#include "ExamRecord.h"

ExamRecord::ExamRecord(string id, string category, string studentName,  int score)
{
	this->studentID = id;
    this->studentName = studentName;
	this->category = category;
	this->score = score;
}

json ExamRecord::toJson()
{
    return {
             {"id", studentID},
             {"name", studentName}, // Include name in the JSON representation
             {"category", category},
             {"score", score}
    };
}

ExamRecord ExamRecord::fromJson(json j)
{
    ExamRecord record;
    record.studentID = j["id"];
    record.studentName = j["name"];
    record.category = j["category"];
    record.score = j["score"];
    return record;
}
