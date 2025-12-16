#ifndef PLAYLISTUTILS_H
#define PLAYLISTUTILS_H

#include "playlist.h"
#include <string>
#include <vector>

// Standalone functions (not a class)
Playlist* createPlaylist(const string& name);           // Creates empty CSV file
void deletePlaylist(const string& name);           // Deletes the CSV file
vector<string> listAllPlaylists();                 // Returns list of available playlists
bool playlistExists(const string& name);           // Check if playlist CSV exists

#endif //PLAYLISTUTILS_H
