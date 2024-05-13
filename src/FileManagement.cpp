/**
 * @file FileManagement.cpp
 * @brief implements functions for saving and loading decks.
 * @author Bruce Scott
 */

#include "../include/FileManagement.h"

/**
 * @brief takes in a vector of decks, and saves them into the file system
 * @param decks list of decks to save
*/
void saveDecks(const std::vector<std::shared_ptr<FlashCardDeck>> decks)
{

    // Loops over each deck in the given vector
    for (std::shared_ptr<FlashCardDeck> deck : decks) {

        // Creates a new file with the name of the current deck
        std::string name = deck->getName();
        std::ostringstream deckFileName;
        deckFileName << "decks" << "/" << name;
        std::ofstream deckFile(deckFileName.str());

        // Catches errors
        if (!deckFile) {
            std::cerr << "Error creating deck file: " << deckFileName.str() << std::endl;
            return;
        }

        // Loops over each question and answer, and writes it to the file
        for (std::shared_ptr<FlashCard> card : deck->getCards())
        {
            deckFile << card->getQuestion() << ":" << card->getAnswer() << std::endl;
        }

        // Closes the file
        deckFile.close();
    }
}

/**
 * @brief Loads all the decks from the file system into a vector
 * @returns A vector of all card decks found
*/
std::vector<std::shared_ptr<FlashCardDeck>> loadDecks()
{

    // Creates vector to return
    std::vector<std::shared_ptr<FlashCardDeck>> decks;

    // Loops over every file in the directory called decks
    for (const auto& directoryItem : std::__fs::filesystem::directory_iterator("decks")) 
    {

        // Ensures that this is a file
        if (directoryItem.is_regular_file()) 
        {

            // Opens a fileStream to read
            std::ifstream inputFile(directoryItem.path());
            if (inputFile.is_open()) 
            {

                // Creates a deck object to edit from file
                std::string deckName = directoryItem.path().filename().string();
                std::shared_ptr<FlashCardDeck> deck = std::make_shared<FlashCardDeck>(deckName);

                // Loops until no more lines are available
                std::string line;
                while (std::getline(inputFile, line)) 
                {
                    std::istringstream iss(line);
                    std::string question;
                    std::string answer;

                    // Splits line into question and answer
                    if (std::getline(iss, question, ':') && std::getline(iss, answer)) 
                    {

                        // Creates a FlashCard with question and answer, adds it to the deck
                        std::shared_ptr<FlashCard> card = std::make_shared<FlashCard>(question, answer);
                        deck->addCard(card);
                    }
                }

                // Closes current file, and adds deck to the vector
                inputFile.close();
                decks.push_back(deck);
            } 
            else 
            {

                // Prints error if files cannot be opened
                std::cerr << "Error opening file: " << directoryItem.path() << std::endl;
            }
        }
    }

    return decks;
}