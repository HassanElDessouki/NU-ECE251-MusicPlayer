#ifndef PLAYLISTUTILS_H
#define PLAYLISTUTILS_H

#include "playlist.h"
#include <string>
#include <vector>

// Create Playlist and store it in Settings CSV File
bool createPlaylist(const string& name);           // Creates empty CSV file
void deletePlaylist();                              // Deletes the CSV file
vector<string> listAllPlaylists();                 // Returns list of available playlists
bool playlistExists(const string& name);           // Check if playlist CSV exists

void toggleShuffle(const string& name);
void toggleRepeat(const string& name);
void savePlaylistSettings(const string& name, const int& songCount, const int& totalDuration, const int& playlistShuffle, const int& playlistRepeat);
#endif //PLAYLISTUTILS_H
