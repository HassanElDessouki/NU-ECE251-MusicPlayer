#include "include/song.h"
#include "include/playlist.h"
#include "include/playlistutils.h"
using namespace std;

int main() {
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
    Playlist* playlist = createPlaylist("MAX Mix");
    if (playlist != nullptr) {
        playlist->importFolder("C:/Users/Hassan/Music");
        playlist->displayPlaylist();
        playlist->play();
    }

    return 0;
}