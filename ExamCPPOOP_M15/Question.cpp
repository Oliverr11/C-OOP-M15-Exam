#include "Question.h"

Question::Question(string questionText, vector<string> opts, int answer)
{
	this->questionText = questionText;
	this->options = opts;
	this->correctAnswer = answer;
}

json Question::toJson()
{
	return json{
		{"questionText",questionText},
		{"options",options},
		{"correctAnswer",correctAnswer}
	};
}

Question Question::fromJson(json j)
{
	return Question{
		   j.at("questionText").get<std::string>(),
		   j.at("options").get<std::vector<std::string>>(),
		   j.at("correctAnswer").get<int>()
	};
}
