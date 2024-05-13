/**
 * @file AromaLibraryDialog.cpp
 * @brief Implementation of the AromaLibraryDialog class.
 * @author Mattias Jentsch
 */

#include "../include/AromaLibraryDialog.h"

/**
 * @brief Constructor for the AromaLibraryDialog class.
 * @param title The title of the dialog.
 * @param initialAromas The list of aromas to display.
 */
AromaLibraryDialog::AromaLibraryDialog(const wxString& title, const wxArrayString& aromas)
    : wxDialog(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)), aromas(aromas) {

    // Create UI elements
    aromaListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    selectButton = new wxButton(this, wxID_ANY, "Select Aroma");
    closeButton = new wxButton(this, wxID_ANY, "Close");

    // Connect events to event handlers
    selectButton->Bind(wxEVT_BUTTON, &AromaLibraryDialog::selectAroma, this);
    closeButton->Bind(wxEVT_BUTTON, &AromaLibraryDialog::OnClose, this);
    
    // Set initial aromas
    setAromas(aromas);

    // Set up the layout
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    hbox->Add(selectButton, 0, wxALIGN_CENTER | wxALL, 10);
    hbox->Add(closeButton, 0, wxALIGN_CENTER | wxALL, 10);
    vbox->Add(aromaListBox, 1, wxEXPAND | wxALL, 10);
    vbox->Add(hbox, 1, wxEXPAND | wxALL, 10);
    
    SetSizerAndFit(vbox);
    Centre();
}

/**
 * @brief Event handler for selecting an aroma.
 * Sets the selected aroma and displays a message box with the selection.
 * @param event The wxCommandEvent associated with the event.
 */
void AromaLibraryDialog::selectAroma(wxCommandEvent& event) {
    wxString selection = aromaListBox->GetStringSelection();
    if (!selection.IsEmpty()) {
        selectedAroma = selection;
        wxMessageBox("Selected Aroma: " + selection, "Aroma Information", wxOK | wxICON_INFORMATION, this);
    }
}

/**
 * @brief Getter for the list of aromas.
 * @return The array of aromas.
 */
wxArrayString AromaLibraryDialog::getAromas() {
    return aromas;
}

/**
 * @brief Setter for the list of aromas. Adds the given aromas to the list.
 * @param aromas The array of aromas to set.
 */
void AromaLibraryDialog::setAromas(wxArrayString aromas) {
    if (aromaListBox) {
        for (const wxString& aroma : aromas) {
            aromaListBox->Append(aroma);
        }
    } else {
        // Handle the case where aromaListBox is null
        wxMessageBox("Error: aromaListBox is null", "Error", wxOK | wxICON_ERROR, this);
    }
}

/**
 * @brief Getter for the selected aroma.
 * @return The selected aroma.
 */
wxString AromaLibraryDialog::getSelectedAroma() {
    return selectedAroma;
}

/**
 * @brief Event handler for closing the dialog.
 * Ends the modal state with OK status.
 * @param event The wxCommandEvent associated with the event.
 */
void AromaLibraryDialog::OnClose(wxCommandEvent& event) {
    EndModal(wxID_OK);
}
