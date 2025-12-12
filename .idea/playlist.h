#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "song.h"
using namespace std;

class Playlist {
private:
	string name;
	vector<Song> songs;

public:
	//constructor
	Playlist(const string& n);
	//getter and setter
	string getName() const { return name; }	
	void setName(const string& n) { name = n; }

	// basic functions
	void addSong(const Song& s);
	bool removeSong(int songID);        
	void clear();                       

	// getting Information
	int getSize() const; //how many songs in playlist   
	bool isEmpty() const;               
	int getTotalDuration() const;                  
	

	// displaying playlist
	void displayPlaylist() const;
	void saveToFile(const string& filename) const;
	void loadFromFile(const string& filename);

	// to find a specific song in the playlist by title/ID momken neshof anhy ashl w ne3mlha
	int findSongByID(int songID) const;
	int findSongByTitle(const string& title) const;
};

