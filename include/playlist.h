#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "song.h"

using namespace std;

class Playlist {
	private:
		string playlistName;
		string playlistFile;
		struct PlaylistNode {
			Song *song;
			PlaylistNode *next;
			PlaylistNode *prev;
		};
		PlaylistNode *head;
		int dateCreated;
		int songCount;
		int totalDuration;
		bool playlistShuffle;
		bool playlistRepeat;

	public:
		//constructor
		Playlist(const string& n, const string& f) {
			playlistName = n;
			playlistFile = f;
			head = nullptr;
			dateCreated = 0;
			songCount = 0;
			totalDuration = 0;
			playlistShuffle = 0;
			playlistRepeat = 0;

			loadPlaylist();
			loadPlaylistSettings();
		};

        void insertSong(Song *song);
		int deleteSong(const string& songTitle);
		void displayPlaylist();

		void play();
		void pause();
		void stop();
		void next();
		void previous();

		//getter and setter
		string getName() const { return playlistName; }
		int getCreationDate() const { return dateCreated; };
		int getSize() const { return songCount; };			//how many songs in playlist
		bool isEmpty() const { return songCount == 0; };
		int getTotalDuration() const { return totalDuration; };
		int getShuffleStatus() const { return playlistShuffle; };
		int getRepeatStatus() const { return playlistRepeat; };

		// displaying playlist
		void loadPlaylist();
		void loadPlaylistSettings();
		void savePlaylist();
		int deletePlaylist();

		void importFolder(string folder);

		// to find a specific song in the playlist by title
		int findSongByTitle(const string& title);

		bool containsSong(const string& filePath) const;

		bool toggleShuffle();
		bool toggleRepeat();
		~Playlist() {
			if (head == nullptr) return;

			PlaylistNode *currentNode = head;
			PlaylistNode *oldHead = head;
			do {
				PlaylistNode *tempNode = currentNode;
				currentNode = currentNode->next;
				delete tempNode->song;
				delete tempNode;
			} while (currentNode != oldHead);
		}
};