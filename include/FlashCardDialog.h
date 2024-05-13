
#ifndef FlashCardDialog_H
#define FlashCardDialog_H
#include <wx/wx.h>
#include <vector>
#include <string>
#include "../include/FlashCard.h"
class FlashCardDialog : public wxDialog {
public:
    FlashCardDialog(wxWindow* parent, const wxString& title, const std::vector<std::shared_ptr<FlashCard>>& flashcards);

private:
    void OnNext(wxCommandEvent& event);
    void OnPrevious(wxCommandEvent& event);
    void OnFlip(wxCommandEvent& event);
    void ShowQuestion();
    void ShowAnswer();

    wxStaticText* flashcardText;
    std::vector<std::shared_ptr<FlashCard>> flashcards;
    size_t currentCardIndex;
    bool flipped;
};
#endif