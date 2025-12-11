#include <iostream>
#include <windows.h>
#include <mmsystem.h>

// Works for Visual Studio. For VS Code/G++, use "-lwinmm" in terminal.
#pragma comment(lib, "winmm.lib")

using namespace std;

void play() {
    // 1. Use mciSendStringA (The 'A' is important!)
    // This ensures it accepts standard text strings.
    MCIERROR err = mciSendStringA("open \"C:/Users/karee/Downloads/kklld.mp3\" type mpegvideo alias mp3file", NULL, 0, NULL);
    
    if (err != 0) {
        // If the file path is wrong or the file is corrupted, this will print.
        cout << "Error: Could not open file! Check the path." << endl;
        return;
    }

    std::cout << "Playing music..." << std::endl;
    
    // 2. Play with 'wait'
    // Warning: Your program will FREEZE here until the song finishes because of 'wait'.
    // Remove 'wait' if you want the program to keep running while music plays.
    mciSendStringA("play mp3file wait", NULL, 0, NULL);

    // 3. Close
    mciSendStringA("close mp3file", NULL, 0, NULL);
}

int main() {
    cout << "Hazem is here" << endl;
    cout << "I DID IT"; // Note: This won't print a new line immediately
    cout << "changes" << endl;
    
    play();
    
    return 0;
}