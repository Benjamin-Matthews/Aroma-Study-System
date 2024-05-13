/**
 * @file FlashCardDialog.cpp
 * @brief Implementation of the FlashCardDialog class.
 * @author Mattias Jentschw
 */

#include "../include/FlashCardDialog.h"

/**
 * @brief Constructor for the FlashCardDialog class.
 * @param parent The parent window.
 * @param title The title of the dialog.
 * @param flashcards The vector of flashcards to display.
 */
FlashCardDialog::FlashCardDialog(wxWindow* parent, const wxString& title, const std::vector<std::shared_ptr<FlashCard>>& flashcards)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)), flashcards(flashcards), currentCardIndex(0), flipped(false) {

    // Create UI elements
    flashcardText = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);

    // Set up sizers for layout
    wxBoxSizer* vBox = new wxBoxSizer(wxVERTICAL);
    vBox->Add(flashcardText, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer* hBox = new wxBoxSizer(wxHORIZONTAL);
    wxButton* prevButton = new wxButton(this, wxID_ANY, "Previous");
    wxButton* flipButton = new wxButton(this, wxID_ANY, "Flip");
    wxButton* nextButton = new wxButton(this, wxID_ANY, "Next");

    // Bind events to event handlers
    prevButton->Bind(wxEVT_BUTTON, &FlashCardDialog::OnPrevious, this);
    flipButton->Bind(wxEVT_BUTTON, &FlashCardDialog::OnFlip, this);
    nextButton->Bind(wxEVT_BUTTON, &FlashCardDialog::OnNext, this);

    hBox->Add(prevButton, 0, wxALL, 10);
    hBox->Add(flipButton, 0, wxALL, 10);
    hBox->Add(nextButton, 0, wxALL, 10);

    vBox->Add(hBox, 0, wxEXPAND);
    SetSizerAndFit(vBox);

    // Display the first flashcard
    ShowQuestion();
}

/**
 * @brief Event handler for displaying the next flashcard.
 * Advances to the next flashcard in the vector and shows its question.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardDialog::OnNext(wxCommandEvent& event) {
    if (currentCardIndex < flashcards.size() - 1) {
        currentCardIndex++;
        flipped = false;  
        ShowQuestion();
    }
}

/**
 * @brief Event handler for displaying the previous flashcard.
 * Goes back to the previous flashcard in the vector and shows its question.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardDialog::OnPrevious(wxCommandEvent& event) {
    if (currentCardIndex > 0) {
        currentCardIndex--;
        flipped = false;  
        ShowQuestion();
    }
}

/**
 * @brief Event handler for flipping the current flashcard.
 * Toggles between displaying the question and the answer.
 * @param event The wxCommandEvent associated with the event.
 */
void FlashCardDialog::OnFlip(wxCommandEvent& event) {
    flipped = !flipped;
    if (flipped) {
        ShowAnswer();
    } else {
        ShowQuestion();
    }
}

/**
 * @brief Displays the question of the current flashcard.
 */
void FlashCardDialog::ShowQuestion() {
    flashcardText->SetLabel(wxString::Format("Question: %s", flashcards[currentCardIndex]->getQuestion()));
}

/**
 * @brief Displays the answer of the current flashcard.
 */
void FlashCardDialog::ShowAnswer() {
    flashcardText->SetLabel(wxString::Format("Answer: %s", flashcards[currentCardIndex]->getAnswer()));
}
