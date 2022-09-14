#include "snake.h" // We want to use our snake functions so we include them too

int main()
{
    // Setup the terminal
    if ( initscr() == NULL ) // Try to enable advanced control of the terminal and return 1 if it fails
        return 1;

    cbreak(); // Tell the terminal to process input without waiting for the user to press enter
    timeout( 300 ); // Set the time to wait before inputs are processed to control execution speed
    CLEAR_SCREEN();

    int result = play(); // Start the game and store the result code (by convention, 0 means success and anything else means an error has occured)

    // Undo changes made by the program to the terminal
    nocbreak(); // Tell the terminal to wait for user to press enter before processing input
    endwin(); // Disable advanced terminal control and clear custom settings

    return result;
}