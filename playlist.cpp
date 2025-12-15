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

void Playlist::deleteSong(Song *song) {
	// if head is null, print message to user that the list is empty
	if (head == nullptr) {
		cout << "List is empty!" << endl;
		return;
	}
	// check if it's the only node
	if (head->next == head && head->song == song) {
		delete head;
		head = nullptr;
		return;
	}
	// check if head is the node to delete
	if (head->song == song) {                // if so, then the next node after the head becomes the new head
		PlaylistNode *newHead = head->next;         // first store the memory address of the next node
		newHead->prev = head->prev;         // set the previous of the newHead to be the last node
		head->prev->next = newHead;         // set the next of the last node in the list to the newHead
		delete head;                        // then delete the current head
		head = newHead;                     // then set the head as the memory address of the next node
		return;
	}
	// otherwise, serarch for the node by traversing it
	PlaylistNode *currentNode = head;
	PlaylistNode *toDeleteNode = nullptr;
	do {
		if (currentNode->song == song) {
			toDeleteNode = currentNode;
		}
		currentNode = currentNode->next;
	} while (currentNode != head);
	if (toDeleteNode == nullptr) {
		cout << "Song node " << song->getTitle() << " does not exist" << endl;
	} else {
		toDeleteNode->prev->next = toDeleteNode->next;
		toDeleteNode->next->prev = toDeleteNode->prev;
		delete toDeleteNode;
	}
}

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