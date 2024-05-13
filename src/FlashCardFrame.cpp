/**
 * @file FlashCardFrame.cpp
 * @brief Implementation of the FlashCardFrame class.
 * @author Mattias Jentsch
 * @author Bruce Scott
 */

#include "../include/FlashCardFrame.h"
#include "../include/FileManagement.h"
#include "../include/AromaControl.h"

/**
 * @brief Constructor for the FlashCardFrame class.
 * @param title The title of the frame.
 * @param pos The position of the frame.
 * @param size The size of the frame.
 */
FlashCardFrame::FlashCardFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), decks() {

    // Create the main panel
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create UI elements
    deckListBox = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 400), 0, nullptr, wxLB_SINGLE);
    selectButton = new wxButton(panel, wxID_ANY, "Study Deck");
    createButton = new wxButton(panel, wxID_ANY, "Create Deck");
    addCardButton = new wxButton(panel, wxID_ANY, "Add Card");
    aromaLibraryButton = new wxButton(panel, wxID_ANY, "Aroma Library"); 
    aromaToggle= new wxCheckBox(panel, wxID_ANY, "Toggle Aroma", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator);
    
    // Create sizers for layout
    wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hBox = new wxBoxSizer(wxHORIZONTAL);

    // Add UI elements to sizers
    hBox->Add(aromaToggle, 0, wxALIGN_CENTER | wxALL, 10);
    hBox->Add(aromaLibraryButton, 0, wxALIGN_CENTER | wxALL, 10); 
    hBox->Add(selectButton, 0, wxALIGN_CENTER | wxALL, 10);
    hBox->Add(createButton, 0, wxALIGN_CENTER | wxALL, 10);
    hBox->Add(addCardButton, 0, wxALIGN_CENTER | wxALL, 10); 
    vBox->Add(deckListBox, 1, wxEXPAND | wxALL, 10);
    vBox->Add(hBox, 0, wxALIGN_CENTER | wxALL, 10);
    
    // Set sizer for the panel
    panel->SetSizer(vBox);

    // Initialize variables
    aromaSync = false;

    // Bind events to functions
    deckListBox->Bind(wxEVT_LISTBOX, &FlashCardFrame::OnDeckSelected, this);
    selectButton->Bind(wxEVT_BUTTON, &FlashCardFrame::OnShowFlashcard, this);
    createButton->Bind(wxEVT_BUTTON, &FlashCardFrame::createDeck, this);
    addCardButton->Bind(wxEVT_BUTTON, &FlashCardFrame::addCard, this); 
    aromaLibraryButton->Bind(wxEVT_BUTTON, &FlashCardFrame::toggleAromaLibrary, this); 
    aromaToggle->Bind(wxEVT_CHECKBOX, &FlashCardFrame::toggleAromaSync, this);
    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(FlashCardFrame::OnClose));

    // Load existing decks
    decks = loadDecks();
    LoadDecks();

    aromas.Add("1");
    aromas.Add("2");
    aromas.Add("3");

    // Initialize pins
    initPin(PIN_ONE);
    initPin(PIN_TWO);
    initPin(PIN_THREE);
}

/**
 * @brief Event handler for the selection of a deck in the deckListBox.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardFrame::OnDeckSelected(wxCommandEvent& event) {
    wxString selectedDeck = deckListBox->GetStringSelection();
    LoadFlashcards(selectedDeck);
    addCardButton->Enable();
}

/**
 * @brief Event handler for when the window is closed
 * @param event the wxCloseEvent associated with the event
*/
void FlashCardFrame::OnClose(wxCloseEvent& event) {

    // Saves the current decks
    saveDecks(decks);
    event.Skip();
}

/**
 * @brief Loads existing decks into the deckListBox.
 */
void FlashCardFrame::LoadDecks() {
    for(size_t i = 0; i < decks.size(); i++){
        if (deckListBox->FindString(decks[i]->getName()) == wxNOT_FOUND) {
            wxString deckSize = std::to_string(decks[i]->getCards().size());
            wxString displayString = decks[i]->getName();
            deckListBox->Append(displayString);
        }
    }
}

/**
 * @brief Loads flashcards for the selected deck.
 * @param deckName The name of the selected deck.
 */
void FlashCardFrame::LoadFlashcards(wxString deckName){
     for(size_t i = 0; i < decks.size(); i++ ){
        if(decks[i]->getName() == deckName){
            currentDeck = decks[i];
            break;
        }
    }
}

/**
 * @brief Event handler for the "Study Deck" button click.
 * Displays the flashcards of the selected deck in a dialog.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardFrame::OnShowFlashcard(wxCommandEvent& event) {
    wxString selectedDeck = deckListBox->GetStringSelection();
    if (selectedDeck.IsEmpty()) {
        wxMessageBox("Please select a deck first.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    if (currentDeck->getCards().size() <= 0) {
        wxMessageBox("No FlashCards In Deck", "Error", wxOK | wxICON_ERROR);
        return;
    }
    
    std::unique_ptr<FlashCardDialog> flashcardDialog = std::make_unique<FlashCardDialog>(this, "Flashcards", currentDeck->getCards());
    flashcardDialog->ShowModal();
}

/**
 * @brief Event handler for creating a new deck.
 * Prompts the user to enter a name for the new deck and creates it.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardFrame::createDeck(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Enter the name for the new deck:", "Create Deck", "New Deck");

    if (dialog.ShowModal() == wxID_OK) {
        wxString newDeckName = dialog.GetValue();
        if (!newDeckName.IsEmpty()) {
            if (deckListBox->FindString(newDeckName) == wxNOT_FOUND) {
                std::shared_ptr<FlashCardDeck> deck = std::make_shared<FlashCardDeck>(newDeckName.utf8_string());
                decks.push_back(deck);
                LoadDecks();
            }
            else{
                ShowErrorDialog("Deck Already Exists");
                return;
            }
        }
    }
}

/**
 * @brief Displays an error dialog with the given error message.
 * @param errorMessage The error message to be displayed.
 */
void FlashCardFrame::ShowErrorDialog(const wxString& errorMessage) {
    wxMessageBox(errorMessage, "Error", wxOK | wxICON_ERROR);
}

/**
 * @brief Event handler for adding a new flashcard to the current deck.
 * Prompts the user to enter the question and answer for the new flashcard.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardFrame::addCard(wxCommandEvent& event) {
    wxString selectedDeck = deckListBox->GetStringSelection();

    if (selectedDeck.IsEmpty()) {
        wxMessageBox("Please select a deck first.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxTextEntryDialog dialog(this,"Enter the question and answer, separated by a colon :", "Add Card");

    if (dialog.ShowModal() == wxID_OK) {
        wxString userInput = dialog.GetValue();

        // Find the position of the colon
        size_t colonPos = userInput.Find(':');

        // Check if both question and answer are provided
        if (colonPos != wxString::npos) {
            // Split the string into question and answer
            wxString question = userInput.BeforeFirst(':');
            wxString answer = userInput.AfterFirst(':');

            // Remove leading and trailing whitespaces
            question = question.Strip(wxString::both);
            answer = answer.Strip(wxString::both);

            // Check if both question and answer are not empty
            if (!question.IsEmpty() && !answer.IsEmpty()) {
                std::shared_ptr<FlashCard> newCard = std::make_shared<FlashCard>(question.ToStdString(), answer.ToStdString());
                currentDeck->addCard(newCard);
            } else {
                wxMessageBox("Please enter both question and answer.", "Error", wxOK | wxICON_ERROR);
            }
        } else {
            wxMessageBox("Please enter a valid input with a colon.", "Error", wxOK | wxICON_ERROR);
        }
    }
}

/**
 * @brief Event handler for toggling the aroma library dialog.
 * Displays the aroma library dialog for selecting aromas.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardFrame::toggleAromaLibrary(wxCommandEvent& event){
    std::unique_ptr<AromaLibraryDialog> dialog = std::make_unique<AromaLibraryDialog>("Aroma Library", aromas);
    dialog->ShowModal();
    aromas = dialog->getAromas();
    currentAroma = dialog->getSelectedAroma();
}

/**
 * @brief Event handler for toggling aroma synchronization.
 * Displays a message box indicating the current aroma sync status.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardFrame::toggleAromaSync(wxCommandEvent& event) {
    if(aromaSync){
        aromaSync = false;
        wxMessageBox("Aroma Sync Now Off", "Aroma Sync");
        int num;
        currentAroma.ToInt(&num);
        turnOffPin(num);
    }else {
        aromaSync = true;
        if(currentAroma.IsEmpty()){
            wxMessageBox("Aroma Sync Now On, Please use the Library to select", "Aroma Sync");
        }else {
            wxMessageBox("Aroma Sync Now On, Current Selection: " + currentAroma, "Aroma Sync");
            int num;
            currentAroma.ToInt(&num);
            turnOnPin(num);
        }
    }
}
