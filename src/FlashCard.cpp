/**
* @file FlashCard.cpp
* @brief This class represents a flash card, holding a question and answer
* @author Bruce Scott
* @author Mattias Jentsch
*/

#include "../include/FlashCard.h"
#include <iostream>

/**
 * @brief Constructor for the flash card
 * @param q question for card
 * @param a answer for the card
*/
FlashCard::FlashCard(const std::string& q, const std::string& a) {

    this->question = q;
    this->answer = a;
}

/**
 * @brief Setter for the flash card's question
 * @param q question to set for the card
*/
void FlashCard::setQuestion(const std::string& q)
{
    question = q;
}

/**
 * @brief Setter for the flash card's answer
 * @param a answer for the card
*/
void FlashCard::setAnswer(const std::string& a)
{
    answer = a;
}

/**
 * @brief Getter for the question
 * @returns the flash card's question
*/
std::string FlashCard::getQuestion()
{
    return question;
}

/**
 * @brief Getter for the answer
 * @returns the flash card's answer
*/
std::string FlashCard::getAnswer()
{
    return answer;
}

/**
 * @brief toString method for flash card
 * @returns the string representation of the card
*/
std::string FlashCard::toString()
{
    std::string res = "";
    res += "Question: " + getQuestion() + "\nAnswer: " + getAnswer();
    return res;
}
