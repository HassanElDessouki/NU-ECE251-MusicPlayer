#include "include/song.h"
#include "include/playlist.h"
#include "include/playlistutils.h"
#include "include/utils.h"
using namespace std;

int main() {
    initalRunChecks();

    clearScreen();
    cout << "==============================" << endl;
    cout << "      WELCOME TO MPLayer      " << endl;
    cout << "==============================" << endl;
    waitScreen();

    bool appStatus = 1;

    while (appStatus) {
        clearScreen();

        // Refresh playlist list
        vector<string> playlists = listAllPlaylists();

        // Show main menu
        int choice = showMainMenuScreen(playlists);

        // Handle no playlists case
        if (playlists.empty() && choice != 9 && choice != 0) {
            cout << "\nNo playlists available. Please create one first!" << endl;
            continue;
        }

        // Handle choice
        if (choice > 0 && choice <= playlists.size()) {
            // User selected a playlist
            string chosenPlaylist = playlists[choice - 1];
            Playlist playlist(chosenPlaylist, chosenPlaylist + ".playlist");
            managePlaylist(playlist);

        } else if (choice == 9) {
            // CREATE NEW PLAYLIST SCREEN
            createPlaylistScreen();

        } else if (choice == 0) {
            // QUIT APPLICATION
            cout << "\nGoodbye!" << endl;
            waitScreen();
            appStatus = false;

        } else {
            // INVALID OPTION
            cout << "\nInvalid option! Please try again." << endl;
            waitScreen();

        }
    }
    return 0;
}