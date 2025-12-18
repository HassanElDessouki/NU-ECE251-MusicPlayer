#pragma once
#include <string>
#include <iostream>

class Song {
	private:
		std::string title;
		std::string artist;
		std::string filePath;
		std::string album;
		std::string genre;
		int duration; // in sec
		int songID;
		int playCount;

	public:
		//constructor
		Song(
			const std::string& path,
			int id = 0,
			const std::string& t = "",
			const std::string& a = "",
			const std::string& al = "",
			const std::string& g = "",
			int dur = 0,
			int pc = 0
        );

	//getter
		std::string getTitle() const { return title; }
		std::string getArtist() const { return artist; }
		std::string getAlbum() const { return album; }
		std::string getGenre() const { return genre; }
		std::string getFile() const { return filePath; }
		int getDuration() const { return duration; }
		int getSongID() const { return songID; }
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

	// Playback Options
		bool playSong();
		void pauseSong();
		void resumeSong();
		void stopSong();
		void stopAudioEngine();
};