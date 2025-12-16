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

int main() {
    initalRunChecks();
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

    cout << "Welcome back" << endl;
    cout << endl;
    vector<string> playlists = listAllPlaylists();
    cout << "Playlists:" << endl;
    for (int i = 0; i < playlists.size(); i++) {
        cout << i+1 << ". " << playlists[i] << endl;
    }
    int playlistNum;
    string chosenPlaylist;
    cout << endl;
    cout << "Please choose a playlist: ";
    cin >> playlistNum;
    chosenPlaylist = playlists[playlistNum-1];
    Playlist playlist(chosenPlaylist, chosenPlaylist+".playlist");
    playlist.loadPlaylist();
    playlist.play();

    return 0;
}