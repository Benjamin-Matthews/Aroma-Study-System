#include "FlashCard.h"
#include "FlashCardDeck.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

void saveDecks(const std::vector<std::shared_ptr<FlashCardDeck>> decks);
std::vector<std::shared_ptr<FlashCardDeck>> loadDecks();