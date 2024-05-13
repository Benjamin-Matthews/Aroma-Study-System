
#ifndef AromaLibraryDialog_H
#define AromaLibraryDialog_H

#include <wx/wx.h>


class AromaLibraryDialog : public wxDialog
{
public:
    AromaLibraryDialog(const wxString& title, const wxArrayString& aromas);
    

    wxArrayString getAromas();
    wxString getSelectedAroma();
    

private:
    // Event handlers
    void selectAroma(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);
    void setAromas(wxArrayString aromas);

    // UI elements
    wxListBox* aromaListBox;
    wxButton* selectButton;
    wxButton* closeButton;
  

    // Aroma data
    wxArrayString aromas;
    wxString selectedAroma;

};

#endif