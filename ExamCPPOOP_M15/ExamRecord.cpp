#include "ExamRecord.h"

ExamRecord::ExamRecord(string id, string category,  int score)
{
	this->studentID = id;
	this->category = category;
	this->score = score;
}

json ExamRecord::toJson()
{
    json toJson(); {
        json j;
        j["id"] = studentID;
        j["category"] = category;
        j["score"] = score;
        return j;
    }
}

ExamRecord ExamRecord::fromJson(json j)
{
    ExamRecord record;
    record.studentID = j["id"];
    record.category = j["category"];
    record.score = j["score"];
    return record;
}
