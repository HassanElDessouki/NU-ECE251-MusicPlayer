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
			playlistName = n; playlistFile = f; head = nullptr;
		};
		Playlist(const string& n, const string& f, const int& d) {
			playlistName = n;
			playlistFile = f;
			dateCreated = d;
			songCount = 0;
			totalDuration = 0;
			playlistShuffle = false;
			playlistRepeat = false;
			head = nullptr;
			loadPlaylist();
		}

        void insertSong(Song *song);
		void deleteSong(Song *song);
		void displayPlaylist();

		void play();
		void pause();
		void stop();
		void next();
		void previous();

		//getter and setter
		string getName() const { return playlistName; }
		void setName(const string& n) { playlistName = n; }

		// getting Information
		int getSize() const { return songCount; };			//how many songs in playlist
		bool isEmpty() const {return songCount == 0; };
		int getTotalDuration() const { return totalDuration; };

		// displaying playlist
		void loadPlaylist();
		void savePlaylist();

		void importFolder(string folder);

		// to find a specific song in the playlist by title/ID momken neshof anhy ashl w ne3mlha
		int findSongByID(int songID) const;
		int findSongByTitle(const string& title) const;

		bool containsSong(const string& filePath) const;
		void deletePlaylist();

		bool toggleShuffle();
		bool toggleRepeat();
};