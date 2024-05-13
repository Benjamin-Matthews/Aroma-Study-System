/**
* @file FlashCardDeck.cpp
* @brief This Class deals with all of the movement and retrieval of the flashcards in the application
* @author Bruce Scott
* @author Mattias Jentsch
*/

#include "../include/FlashCardDeck.h"
#include <iostream>

/**
 * @brief Constructor for the Flash Card Deck, simply sets the deck name
 * @param name The name of the deck
*/
FlashCardDeck::FlashCardDeck(const std::string& name)
{
    this->name = name;
}

/**
 * @brief Gets the vector of all cards in the deck
 * @returns vector of card pointers
*/
std::vector<std::shared_ptr<FlashCard>> FlashCardDeck::getCards() 
{
    return cards;
}

/**
 * @brief Gets the name of the deck
 * @returns string name of the deck
*/
std::string FlashCardDeck::getName() 
{
    return name;
}

/**
 * @brief Gets the card at the given index
 * @param index index of the card to retrieve
 * @returns the card at the given index, or a null pointer if not found
*/
std::shared_ptr<FlashCard> FlashCardDeck::getCard(int index)
{
    int i = 0;
    // Loops through all cards incrementing the index, if index matches, return card
    for (auto card : cards)
    {
        if (i == index)
            return card;
        i++;
    }
    return nullptr;
}

/**
 * @brief Adds the given card to the deck
 * @param card the card to add
*/
void FlashCardDeck::addCard(const std::shared_ptr<FlashCard> card) 
{
    cards.push_back(std::move(card));
}

/**
 * @brief Removes the given card from the deck
 * @param card the card to remove
*/
void FlashCardDeck::removeCard(const std::shared_ptr<FlashCard> card) 
{

    // Iterates over all cards, if currect card == given card, remove it
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        auto value = *it;
        if (card == value) 
        {
            cards.erase(it);
            return;
        }
    }
}

/**
 * @brief Gets the string representation of the deck
 * @returns string representation of the deck
*/
std::string FlashCardDeck::toString() 
{
    std::string result = name + "\n";

    // Loops over each card, appending the result of it's toString to the resultant string
    for (std::shared_ptr<FlashCard>& card : cards) {
        result += card->toString() + "\n\n";
    }
    return result;
}
