#ifndef UTILS_H
#define UTILS_H
#include "playlist.h"
#include <string>
#include <vector>
using namespace std;

// ========= SCREEN OPTIONS ==========
void clearScreen();
void waitScreen();

// ============ RUN CHECK ============
void initalRunChecks();

// ========== TIME OPTIONS ===========
long int epochTime();
string epochTimeStr(long int epochTime);
string durationStr(int durationSeconds);

// ========== MISCELLANOUS ===========
void clearInput();

// ======== SCREEN DISPLAYS ==========
void createPlaylistScreen();
void createPlaylistScreen();
int showMainMenuScreen(vector<string>& playlists);
int showPlaylistMenuScreen(const string& playlistName);
void managePlaylist(Playlist& playlist);

#endif //UTILS_H