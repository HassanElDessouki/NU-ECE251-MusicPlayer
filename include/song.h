#pragma once
#include <string>
#include <iostream>

class Song {
	private:
		std::string title;
		std::string artist;
		std::string filepath;
		std::string album;
		std::string genre;
		int duration; // in sec
		int song_Id;
		int playCount;

	public:
		//constructor
		Song(
			const std::string& path,
			const std::string& t = "",
			const std::string& a = "",
			const std::string& al = "",
			const std::string& g = "",
			int id = 0,
			int pc = 0,
			int dur = 0
        );

	//getter
		std::string getTitle() const { return title; }
		std::string getArtist() const { return artist; }
		std::string getAlbum() const { return album; }
		std::string getGenre() const { return genre; }
		std::string getFilepath() const { return filepath; }
		int getDuration() const { return duration; }
		int getSongId() const { return song_Id; }
		int getPlayCount() const { return playCount; }

	//setter
		void setTitle(const std::string& t) { title = t; }
		void setArtist(const std::string& a) { artist = a; }
		void setAlbum(const std::string& al) { album = al; }
		void setGenre(const std::string& g) { genre = g; }
	//function declaration
		void incrementPlayCount(){playCount++;}
		bool loadMetadata();
		void displayInfo() const;
};