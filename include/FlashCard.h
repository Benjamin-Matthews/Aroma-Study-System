#pragma once

#include <string>
#include <memory>

class FlashCard
{
private:
    std::string question;
    std::string answer;
public:
    FlashCard(const std::string& q, const std::string& a);
    void setQuestion(const std::string& question);
    void setAnswer(const std::string& answer);
    std::string getQuestion();
    std::string getAnswer();
    std::string toString();
};