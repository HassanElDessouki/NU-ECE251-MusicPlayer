#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "include/song.h"

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
		string dateCreated;
		string dateModified;
		int songCount;
		int totalDuration;

	public:
		//constructor
		Playlist(const string& n, const string& f) {playlistName = n; playlistFile = f; head = nullptr;};

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

		// basic functions
		void clear();

		// getting Information
		int getSize() const; //how many songs in playlist
		bool isEmpty() const;
		int getTotalDuration() const;

		// displaying playlist
		void loadPlaylist();
		void savePlaylist();

		void importFolder(string folder);

		// to find a specific song in the playlist by title/ID momken neshof anhy ashl w ne3mlha
		int findSongByID(int songID) const;
		int findSongByTitle(const string& title) const;

		bool containsSong(const string& filePath) const;
		void deletePlaylist();

};