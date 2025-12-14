#pragma once
#include <string>
#include <iostream>
using namespace std;

class Song {
private:
	string title;
	string artist;
	string filepath;
	string album;
	string genre;
	int duration; // in sec 
	int song_Id;
	int playCount;

public:
	//constructor
	Song(
		const string& path,
		const string& t = "",
		const string& a = "",
		const string& al = "",
		const string& g = "",
		int id = 0,
		int pc = 0,
		int dur = 0);

//getter
	string getTitle() const { return title; }
	string getArtist() const { return artist; }
	string getAlbum() const { return album; }
	string getGenre() const { return genre; }
	string getFilepath() const { return filepath; }
	int getDuration() const { return duration; }
	int getSongId() const { return song_Id; }
	int getPlayCount() const { return playCount; }


//setter	
	void setTitle(const string& t) { title = t; }
	void setArtist(const string& a) { artist = a; }
	void setAlbum(const string& al) { album = al; }
	void setGenre(const string& g) { genre = g; }
//function declaration
	void incrementPlayCount(){playCount++;}
	bool loadMetadataFromFile();
	void displayInfo() const;

};