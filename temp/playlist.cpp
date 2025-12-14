#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "song.h"
#include "playlist.h"
using namespace std;
class playlist {
private:
		string name;
		vector<Song> songs;
public:
	//constructor
	playlist(const string& n) : name(n) {}
		//getter and setter
		string getName() const { return name; }	
		void setName(const string& n) { return name = n; }
		int getSize() const { return songs.size(); }
		//function declaration
		// basic functions
		void addSong(const Song& s) {    //add to playlist
		
		
		};
		bool removeSong(int songID);
		void clear();

		// getting Information
		bool isEmpty() const { return size == 0; }
		int getTotalDuration() const;


		// displaying playlist
		void displayPlaylist() const;
		void saveToFile(const string& filename) const;
		void loadFromFile(const string& filename);

		// to find a specific song in the playlist by title/ID momken neshof anhy ashl w ne3mlha
		int findSongByID(int songID) const;
		int findSongByTitle(const string& title) const;

};