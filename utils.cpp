#include "include/utils.h"
#include "include/playlistutils.h"
#include "include/playlist.h"
#include <iostream>
#include <thread>
#include <filesystem>
#include <fstream>

using namespace std;
string settingsFile = "playlists.csv";

// ========= SCREEN OPTIONS ==========
void clearScreen() {
    cout << "\033[2J\033[1;1H";  // Clear screen + move cursor to top
}
void waitScreen() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// ============ RUN CHECK ============
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

// ========== TIME OPTIONS ===========
long int epochTime() {
    time_t now = time(nullptr);
    return now;
}
string epochTimeStr();

// ========== MISCELLANOUS ===========
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ======== SCREEN DISPLAYS ==========
void createPlaylistScreen() {
    clearScreen();

    string playlistName;
    cout << "\nEnter new playlist name: ";
    getline(cin, playlistName);

    if (playlistName.empty()) {
        cout << "[ERROR] Playlist name cannot be empty!" << endl;
        return;
    }

    bool newPlaylist = createPlaylist(playlistName);
    if (newPlaylist == 1) {
        cout << "[SUCCESS] Playlist created!" << endl;
        return;
    }
    waitScreen();
}
int showMainMenuScreen(vector<string>& playlists) {
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
int showPlaylistMenuScreen(const string& playlistName) {
    clearScreen();
    cout << "==============================" << endl;
    cout << "  Playlist: " << playlistName << endl;
    cout << "==============================" << endl;
    cout << "1. Play Playlist" << endl;
    cout << endl;
    cout << "2. Add a New Song" << endl;
    cout << "3. Delete Song" << endl;
    cout << "4. List Songs" << endl;
    cout << endl;
    cout << "5. Enable/Disable Shuffle" << endl;
    cout << "6. Enable/Disable Repeat" << endl;
    cout << "7. Import Folder" << endl;
    cout << endl;
    cout << "8. Playlist Info" << endl;
    cout << "9. Delete Playlist" << endl;
    cout << endl;
    cout << "0. Return to Main Menu" << endl;
    cout << endl;
    cout << "Choose an option: ";

    int choice;
    cin >> choice;
    clearInput();
    return choice;
}
void managePlaylist(Playlist& playlist) {
    bool status = 1;
    while (status) {
        clearScreen();
        int choice = showPlaylistMenuScreen(playlist.getName());

        switch (choice) {
            case 1: // Play playlist
                cout << "\n--- Playing Playlist ---" << endl;
            playlist.play();
            break;

            case 2: // Add a new song
            {
                clearScreen();
                string filePath;
                cout << "\nEnter MP3 File path: ";
                getline(cin, filePath);

                if (filesystem::exists(filePath)) {
                    Song *s = new Song(filePath);
                    s->loadMetadata();
                    playlist.insertSong(s);
                    playlist.savePlaylist();
                    savePlaylistSettings(playlist.getName(), playlist.getSize(), playlist.getTotalDuration(), playlist.getShuffleStatus(), playlist.getRepeatStatus());
                    cout << "Song " << s->getTitle() << " by " << s->getArtist() << " has been imported successfully!" << endl;
                } else {
                    cout << "MP3 file not found!" << endl;
                }
                waitScreen();
                break;
            }

            case 3: // Delete song
            {
                clearScreen();
                string filePath;
                cout << "\nEnter MP3 File path: ";
                getline(cin, filePath);

                if (filesystem::exists(filePath)) {
                    Song *s = new Song(filePath);
                    s->loadMetadata();
                    playlist.deleteSong(s);
                    playlist.savePlaylist();
                    savePlaylistSettings(playlist.getName(), playlist.getSize(), playlist.getTotalDuration(), playlist.getShuffleStatus(), playlist.getRepeatStatus());
                    cout << "Song " << s->getTitle() << " by " << s->getArtist() << " has been imported successfully!" << endl;
                    delete s;
                } else {
                    cout << "MP3 file not found!" << endl;
                }
                break;
            }

            case 4: // List playlist items
                clearScreen();
                cout << endl;
                cout << "======== Playlist Songs ========" << endl;
            playlist.displayPlaylist();
            break;

            case 5: // Enable/Disable Shuffle
                {
                    clearScreen();
                    bool shuffleStatus = playlist.toggleShuffle();

                    cout << endl;
                    cout << "Shuffle: ";
                    if (shuffleStatus == 0) {
                        cout << "Disabled";
                    } else {
                        cout << "Enabled";
                    }
                    waitScreen();
                    break;
                }

            case 6: // Enable/Disable Repeat
                {
                    clearScreen();
                    bool repeatStatus = playlist.toggleRepeat();

                    cout << endl;
                    cout << "Repeat: ";
                    if (repeatStatus == 0) {
                        cout << "Disabled";
                    } else {
                        cout << "Enabled";
                    }
                    waitScreen();

                    break;
                }

            case 7: // Import folder
                {
                    clearScreen();
                    string folderPath;
                    cout << "\nEnter folder path: ";
                    getline(cin, folderPath);
                    playlist.importFolder(folderPath);
                    cout << "Folder imported successfully!" << endl;
                    waitScreen();
                    break;
                }

            case 8: // PLAYLIST INFO
                clearScreen();
                cout << "Playlist Name: " << playlist.getName() << endl;
                cout << "Playlist Created on: " << playlist.getCreationDate() << endl;
                cout << "Playlist Songs Count: " << playlist.getSize() << endl;
                cout << "Playlist Duration: " << playlist.getTotalDuration() << endl;
                cout << endl;
                int shuffleStatus, repeatStatus;
                shuffleStatus = playlist.getShuffleStatus();
                repeatStatus = playlist.getRepeatStatus();
                if (shuffleStatus == 0) {
                    cout << "Shuffle Status: Disabled" << endl;
                } else {
                    cout << "Shuffle Status: Enabled" << endl;
                }
                if (repeatStatus == 0) {
                    cout << "Repeat Status: Disabled" << endl;
                } else {
                    cout << "Repeat Status: Enabled" << endl;
                }
                cout << endl;
                cout << "Return back..." << endl;
                getchar();
            break;

            case 9: // DELETE PLAYLIST
            {
                clearScreen();
                int doubleCheck;
                cout << "Are you sure you want to delete the playlist? (this action is irreversable!)" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "Choose an option: ";
                cin >> doubleCheck;
                if (doubleCheck == 1) {
                    int deleteStatus;
                    deleteStatus = playlist.deletePlaylist();
                    if (deleteStatus == 1) {
                        cout << "Playlist deleted successfully!" << endl;
                        waitScreen();
                        status = 0;
                    } else {
                        cout << "Playlist deleted failed!" << endl;
                        waitScreen();
                    }
                } else {
                    cout << "Returning back" << endl;
                    waitScreen();
                }
            }

            case 0: // Return to main menu
                status = 0;
            break;

            default:
                cout << endl;
                cout << "Invalid option! Please try again." << endl;
        }
    }
}