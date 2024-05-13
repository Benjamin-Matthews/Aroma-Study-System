#pragma once

#include "FlashCard.h"
#include <string>
#include <vector>
#include <memory>

class FlashCardDeck
{
private:
    std::vector<std::shared_ptr<FlashCard>> cards;
    std::string name;
public:
    FlashCardDeck(const std::string& name);
    std::vector<std::shared_ptr<FlashCard>> getCards();
    std::string getName();
    std::string toString();
    std::shared_ptr<FlashCard> getCard(int index);
    int getSize();
    void addCard(const std::shared_ptr<FlashCard> card);
    void removeCard(const std::shared_ptr<FlashCard> card);
};