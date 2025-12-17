#include "include/song.h"
#include "include/playlist.h"
#include "include/playlistutils.h"
#include <filesystem>
#include <fstream>
string settingsFile = "playlists.csv";
using namespace std;

void initalRunChecks() {
    // CHECK IF PLAYLIST SETTINGS FILE EXISTS!
    if (filesystem::exists(settingsFile)) {
        cout << "[INFO] Playlist Settings file exists" << endl;
    } else if (!filesystem::exists(settingsFile)) {
        cout << "[WARNING] Playlist Settings file does not exist" << endl;
        cout << "[INFO] Creating new Playlist Settings file" << endl;
        ofstream file(settingsFile);
        file.close();
        cout << "[INFO] Playlist Settings file created" << endl;
    }
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";  // Clear screen + move cursor to top
}

// Display main menu and get choice
int showMainMenu(vector<string>& playlists) {
    cout << "\n========================================" << endl;
    cout << "          MUSIC PLAYER MENU" << endl;
    cout << "========================================" << endl;

    if (!playlists.empty()) {
        cout << "\nPlaylists:" << endl;
        for (int i = 0; i < playlists.size(); i++) {
            cout << (i + 1) << ". " << playlists[i] << endl;
        }
        cout << endl;
    } else {
        cout << "\nNo playlists found." << endl;
        cout << endl;
    }

    cout << "9. Create New Playlist" << endl;
    cout << "0. Quit" << endl;
    cout << "\nChoose an option: ";

    int choice;
    cin >> choice;
    clearInput();
    return choice;
}

// Display playlist menu
int showPlaylistMenu(const string& playlistName) {
    cout << "\n========================================" << endl;
    cout << "  Playlist: " << playlistName << endl;
    cout << "========================================" << endl;
    cout << "1. List Playlist Items" << endl;
    cout << "2. Add a New Song" << endl;
    cout << "3. Delete Song" << endl;
    cout << "4. Play Playlist" << endl;
    cout << "5. Enable/Disable Shuffle" << endl;
    cout << "6. Enable/Disable Repeat" << endl;
    cout << "7. Import Folder" << endl;
    cout << "8. Save Playlist" << endl;
    cout << "0. Return to Main Menu" << endl;
    cout << "\nChoose an option: ";

    int choice;
    cin >> choice;
    clearInput();
    return choice;
}

// Handle playlist management
void managePlaylist(Playlist& playlist) {
    bool inPlaylistMenu = true;

    while (inPlaylistMenu) {
        int choice = showPlaylistMenu(playlist.getName());

        switch (choice) {
            case 1: // List playlist items
                cout << "\n--- Playlist Songs ---" << endl;
                playlist.displayPlaylist();
                break;

            case 2: // Add a new song
                cout << "\n[TODO] Add new song functionality" << endl;
                // TODO: Implement add song
                break;

            case 3: // Delete song
                cout << "\n[TODO] Delete song functionality" << endl;
                // TODO: Implement delete song
                break;

            case 4: // Play playlist
                cout << "\n--- Playing Playlist ---" << endl;
                playlist.play();
                break;

            case 5: // Enable/Disable Shuffle
                cout << "\n[TODO] Shuffle functionality" << endl;
                // TODO: Implement shuffle toggle
                break;

            case 6: // Enable/Disable Repeat
                cout << "\n[TODO] Repeat functionality" << endl;
                // TODO: Implement repeat toggle
                break;

            case 7: // Import folder
                {
                    string folderPath;
                    cout << "\nEnter folder path: ";
                    getline(cin, folderPath);
                    playlist.importFolder(folderPath);
                    cout << "Folder imported successfully!" << endl;
                }
                break;

            case 8: // Save playlist
                playlist.savePlaylist();
                cout << "Playlist saved successfully!" << endl;
                break;

            case 0: // Return to main menu
                inPlaylistMenu = false;
                break;

            default:
                cout << "\nInvalid option! Please try again." << endl;
        }
    }
}

// Create new playlist with user input
void handleCreatePlaylist() {
    string playlistName;
    cout << "\nEnter playlist name: ";
    getline(cin, playlistName);

    if (playlistName.empty()) {
        cout << "[ERROR] Playlist name cannot be empty!" << endl;
        return;
    }

    Playlist* newPlaylist = createPlaylist(playlistName);
    if (newPlaylist != nullptr) {
        cout << "[SUCCESS] Playlist created!" << endl;
        delete newPlaylist;  // Clean up
    }
}

int main() {
    initalRunChecks();

    cout << "==============================" << endl;
    cout << "      WELCOME TO MPLayer      " << endl;
    cout << "==============================" << endl;

    bool appStatus = 1;

    while (appStatus) {
        // Refresh playlist list
        vector<string> playlists = listAllPlaylists();

        // Show main menu
        int choice = showMainMenu(playlists);

        // Handle no playlists case
        if (playlists.empty() && choice != 9 && choice != 0) {
            cout << "\n[ERROR] No playlists available. Please create one first!" << endl;
            continue;
        }

        // Handle choice
        if (choice > 0 && choice <= playlists.size()) {
            // User selected a playlist
            string chosenPlaylist = playlists[choice - 1];
            Playlist playlist(chosenPlaylist, chosenPlaylist + ".playlist");
            managePlaylist(playlist);

        } else if (choice == 9) {
            // Create new playlist
            handleCreatePlaylist();

        } else if (choice == 0) {
            // Quit
            cout << "\nThank you for using Music Player. Goodbye!" << endl;
            appStatus = false;

        } else {
            cout << "\n[ERROR] Invalid option! Please try again." << endl;
        }
    }

    return 0;
}
    // Song s("C:/Users/Hassan/Music/Britney Spears - ...Baby One More Time.mp3");
    // s.loadMetadata();
    // s.displayInfo();
    // s.playSong();
    // Playlist general("General", "G:/Projects/Academic/music-player/general.csv");
    // general.loadPlaylist();
    // general.displayPlaylist();
    // general.importFolder("C:/Users/Hassan/Music");
    // // general.play();
    // // general.savePlaylist();
    // createPlaylist("MAX Mix1");
    // listAllPlaylists();
    // createPlaylist("MAX Mix2");
    // listAllPlaylists();
    // playlistExists("MAX Mix1");
    // Playlist* playlist = createPlaylist("MAX Mix");
    // Playlist playlist2("MAX Mix", "MAX Mix.playlist");
    // playlist2.loadPlaylist();
    // playlist2.displayPlaylist();
    // playlist2.play();
    // if (playlist != nullptr) {
    //     playlist->importFolder("C:/Users/Hassan/Music");
    //     playlist->displayPlaylist();
    //     playlist->play();
    // }

    // cout << "Welcome back" << endl;
    // cout << endl;
    // vector<string> playlists = listAllPlaylists();
    // if (!playlists.empty()) {
    //     cout << "Playlists:" << endl;
    //     for (int i = 0; i < playlists.size(); i++) {
    //         cout << i+1 << ". " << playlists[i] << endl;
    //     }
    //     int playlistNum;
    //     string chosenPlaylist;
    //     cout << endl;
    //     cout << "Please choose a playlist: ";
    //     cin >> playlistNum;
    //     chosenPlaylist = playlists[playlistNum-1];
    //     Playlist playlist(chosenPlaylist, chosenPlaylist+".playlist");
    //     playlist.loadPlaylist();
    //     playlist.play();
    //
    // } else {
    //     string playlistName;
    //     cout << "Create a new playlist:" << endl;
    //     cout << "Playlist Name: ";
    //     cin >> playlistName;
    //     createPlaylist(playlistName);
    // }
    // return 0;
// }