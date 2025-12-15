#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "include/song.h"
#include "playlist.h"
using namespace std;

void Playlist::insertSong(Song *song) {
	PlaylistNode *newNode = new PlaylistNode;           //
	newNode->song = song;                // create new node with the value to be inserted

	if (head == nullptr) {              // in the case that head is a null, initialize list by storing memory address of the node as the head
		head = newNode;
		head->next = head;
		head->prev = head;
	} else {
		newNode->prev = head->prev;         //
		newNode->next = head;               //
		head->prev->next = newNode;         //
		head->prev = newNode;               //
	}
}

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


// void importFolder(string folder) {
//     for (const auto & entry : fs::directory_iterator(folder)) {
//         if (entry.path().extension() == ".mp3") {
//             mp3METADATA(entry.path().string());
//         }
//     }
// }
//
// int main() {
//     importFolder("C:/Users/Hassan/Music/");
//     return 0;
// }