/**
 * @file FlashCardApp.cpp
 * @brief Implementation of the FlashCardApp class.
 * @author Mattias Jentsch
 */

#include "../include/FlashCardApp.h"
#include "../include/FlashCardFrame.h"

/**
 * @brief Entry point for the FlashCard application.
 * @return True if the application initializes successfully, false otherwise.
 */
wxIMPLEMENT_APP(FlashCardApp);

/**
 * @brief Initialization function for the FlashCard application.
 * Creates and shows the main frame of the application.
 * @return True if initialization is successful, false otherwise.
 */
bool FlashCardApp::OnInit() {
    FlashCardFrame* frame = new FlashCardFrame("Aroma Cards", wxDefaultPosition, wxSize(800, 600));
    frame->Show(true);
    return true;
}
