
#ifndef FlashCardFrame_H
#define FlashCardFrame_H

#include <wx/wx.h>
#include <wx/listbox.h>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "FlashCardDeck.h"
#include "FlashCardDialog.h"
#include "AromaLibraryDialog.h"

class FlashCardFrame : public wxFrame {
public:
    FlashCardFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    
private:
    void OnClose(wxCloseEvent& event);
    void OnDeckSelected(wxCommandEvent& event);
    void OnShowFlashcard(wxCommandEvent& event);
    void LoadFlashcards(wxString deck);
    void createDeck(wxCommandEvent& event);
    void LoadDecks();
    void ShowErrorDialog(const wxString& errorMessage);
    void addCard(wxCommandEvent& event);
    void toggleAromaLibrary(wxCommandEvent& event);
    void toggleAromaSync(wxCommandEvent& event);

    bool aromaSync;
    wxListBox* deckListBox;
    wxButton* selectButton;
    wxButton* createButton;
    wxButton* addCardButton;
    wxButton* aromaLibraryButton;
    wxCheckBox* aromaToggle;
    wxArrayString aromas;
    wxString currentAroma;
    std::shared_ptr<FlashCardDeck> currentDeck;
    std::vector<std::shared_ptr<FlashCardDeck>> decks;
    
};
#endif