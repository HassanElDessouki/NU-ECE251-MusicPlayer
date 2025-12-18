// ======================================================== //
#include "include/playlist.h"
#include "include/playlistutils.h"
#include "include/song.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "include/utils.h"
// ======================================================== //

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
	totalDuration += song->getDuration();
	songCount++;
}

int Playlist::deleteSong(const string& songTitle) {
	// if head is null, print message to user that the list is empty
	if (head == nullptr) {
		cout << "List is empty!" << endl;
		return 0;
	}
	// check if it's the only node
	if (head->next == head && head->song->getTitle() == songTitle) {
		delete head;
		head = nullptr;

		songCount--;
		totalDuration = 0;
		savePlaylist();
		savePlaylistSettings(playlistName, songCount, totalDuration, playlistShuffle, playlistRepeat);

		return 1;
	}
	// check if head is the node to delete
	if (head->song->getTitle() == songTitle) {                // if so, then the next node after the head becomes the new head
		int oldDuration = head->song->getDuration();
		PlaylistNode *newHead = head->next;         // first store the memory address of the next node
		newHead->prev = head->prev;         // set the previous of the newHead to be the last node
		head->prev->next = newHead;         // set the next of the last node in the list to the newHead
		delete head;                        // then delete the current head
		head = newHead;                     // then set the head as the memory address of the next node

		songCount--;
		totalDuration -= oldDuration;
		savePlaylist();
		savePlaylistSettings(playlistName, songCount, totalDuration, playlistShuffle, playlistRepeat);

		return 1;
	}
	// otherwise, serarch for the node by traversing it
	PlaylistNode *currentNode = head;
	PlaylistNode *toDeleteNode = nullptr;
	do {
		if (currentNode->song->getTitle() == songTitle) {
			toDeleteNode = currentNode;
		}
		currentNode = currentNode->next;
	} while (currentNode != head);
	if (toDeleteNode == nullptr) {
		cout << "Song with title " << songTitle << " does not exist" << endl;
		return 0;
	} else {
		int oldDuration = toDeleteNode->song->getDuration();
		toDeleteNode->prev->next = toDeleteNode->next;
		toDeleteNode->next->prev = toDeleteNode->prev;
		delete toDeleteNode;
		songCount--;
		totalDuration -= oldDuration;
		savePlaylist();
		savePlaylistSettings(playlistName, songCount, totalDuration, playlistShuffle, playlistRepeat);
		return 1;
	}
}

void Playlist::displayPlaylist() {
	// if head is null, print message to user that the list is empty
	if (head == nullptr) {
		cout << "List is empty!" << endl;
		return;
	}
	// otherwise, traverse through the list and print the values until the end of the list
	PlaylistNode *currentNode = head;
	do {
		cout << currentNode->song->getTitle() << " by " << currentNode->song->getArtist() << endl;
		currentNode = currentNode->next;
	} while (currentNode != head);
	cout << endl;
}

int Playlist::findSongByTitle(const string& title) {
	// if head is null, print message to user that the list is empty
	if (head == nullptr) {
		cout << "Playlist is empty!" << endl;
		return 0;
	}
	// otherwise, traverse through the list and print the values until the end of the list
	PlaylistNode *currentNode = head;
	do {
		if (currentNode->song->getTitle() == title) {
			cout << "==============" << currentNode->song->getTitle() << "==============" << endl;
			cout << "Artist: "		<< currentNode->song->getArtist() << endl;
			cout << "Album: "		<< currentNode->song->getAlbum() << endl;
			cout << "Genre: "		<< currentNode->song->getGenre() << endl;
			cout << "Duration: "	<< currentNode->song->getDuration() << endl;
			return 1;
		}
		currentNode = currentNode->next;
	} while (currentNode != head);

	cout << "[ERROR] Song not found!" << endl;
	return 0;
}

void Playlist::loadPlaylistSettings() {
	ifstream playlistSettings("playlists.csv");

	if (!playlistSettings.is_open()) {
		cout << "[ERROR] Could not open playlist file!" << endl;
		return;
	}

	string csvRow;
	while(getline(playlistSettings, csvRow)) {
		if (csvRow.empty()) continue;  // Skip empty lines

		stringstream csvRowSS(csvRow); // Move Row to a String Stream
		string cell, csvName, csvFile;
		int csvDate, csvSongCount, csvTotalDuration, csvShuffle, csvRepeat;

		getline(csvRowSS, csvName, ';');
		if (csvName != playlistName) continue;

		getline(csvRowSS, csvFile, ';');
		getline(csvRowSS, cell, ';');       csvDate             = stoi(cell);
		getline(csvRowSS, cell, ';');       csvSongCount        = stoi(cell);
		getline(csvRowSS, cell, ';');       csvTotalDuration    = stoi(cell);
		getline(csvRowSS, cell, ';');       csvShuffle          = stoi(cell);
		getline(csvRowSS, cell, ';');       csvRepeat           = stoi(cell);

		dateCreated = csvDate;
		// songCount = csvSongCount;
		// totalDuration = csvTotalDuration;
		playlistShuffle = csvShuffle;
		playlistRepeat = csvRepeat;
		break;
	}
	playlistSettings.close();
}

void Playlist::loadPlaylist() {
	ifstream playlistData;       		// file stream "playlistData"
	playlistData.open(playlistFile); 	// Load File

	if (!playlistData.is_open()) {
		cout << "[ERROR] Could not open playlist file!" << endl;  // ← Add this
		return;
	}

	string csvRow;
	while(getline(playlistData, csvRow)) {
		if (csvRow.empty()) continue;  // Skip empty lines

		stringstream csvRowSS(csvRow); // Move Row to a String Stream
		string cell;


		// DEBUG
		// cout << csvRow << endl;
		string filePath, title, artist, album, genre;
		int songID, songDuration, songPlayCount;
		/* Seperate each value to its designated song struct variable */
		getline(csvRowSS, cell, ';'); filePath 			= cell;
		getline(csvRowSS, cell, ';'); songID 			= stoi(cell);
		getline(csvRowSS, cell, ';'); title 			= cell;
		getline(csvRowSS, cell, ';'); artist 			= cell;
		getline(csvRowSS, cell, ';'); album 			= cell;
		getline(csvRowSS, cell, ';'); genre 			= cell;
		getline(csvRowSS, cell, ';'); songDuration 		= stoi(cell);
		getline(csvRowSS, cell, ';'); songPlayCount 	= stoi(cell);
		Song* n = new Song(filePath, songID, title, artist, album, genre, songDuration, songPlayCount);
		insertSong(n);
	}
	cout << "[INFO] Playlist loaded successfully" << endl;
	playlistData.close();
}

//
void Playlist::play() {
	// TODO: AUTO ADVANCE TO NEXT SONG
	if (head == nullptr) {
		cout << "Playlist is empty!" << endl;
		waitScreen();
		return;
	}

	// otherwise, traverse through the list and print the values until the end of the list
	PlaylistNode *currentNode = head;
	bool pauseStatus = 0;
	bool playStatus = 1;
	bool playbackStatus = 1;

	currentNode->song->playSong();
	while (playbackStatus) {
		clearScreen();
		// Display current song info
		cout << "========================================" << endl;
		cout << "  NOW PLAYING IN " << playlistName << endl;
		cout << "========================================" << endl;
		cout << "Title:  " << currentNode->song->getTitle() << endl;
		cout << "Artist: " << currentNode->song->getArtist() << endl;
		cout << "Album:  " << currentNode->song->getAlbum() << endl;
		cout << endl;
		cout << "Status: " << (pauseStatus ? "PAUSED" : "PLAYING") << endl;
		cout << "========================================" << endl;
		cout << endl;

		cout << "CONTROLS:" << endl;
		cout << "n - Next Song" << endl;
		cout << "b - Previous Song" << endl;
		cout << "p - " << (pauseStatus ? "Resume" : "Pause") << endl;
		cout << "s - Stop and Return to Menu" << endl;
		cout << endl;
		cout << "Choose an option: ";

		char choice;
		cin >> choice;
		clearInput();

		switch (choice) {
			case 'n':
				currentNode->song->stopSong();
				currentNode = currentNode->next;

				if (currentNode == head && (playlistRepeat == 0)) {
					cout << "Playlist Finished" << endl;
					waitScreen();
					playbackStatus = 0;
				} else {
					currentNode->song->playSong();
					pauseStatus = 0;
				}
				break;

			case 'b':
				currentNode->song->stopSong();
				currentNode = currentNode->prev;

				currentNode->song->playSong();
				pauseStatus = 0;
				break;

			case 'p':
				if (pauseStatus == 0) {
					currentNode->song->pauseSong();
					pauseStatus = 1;
				} else {
					currentNode->song->resumeSong();
					pauseStatus = 0;
				}
				break;

			case 's':
				clearScreen();
				currentNode->song->stopSong();
				currentNode->song->stopAudioEngine();

				cout << "Returning to Playlist Menu..." << endl;
				waitScreen();
				playbackStatus = 0;
				break;

			default:
				cout << "Invalid option!" << endl;
				waitScreen();
				clearScreen();
		}
	}
};

// void Playlist::pause() {
//     if (soundLoaded && !paused) {
//         ma_sound_set_paused(&currentSound, MA_TRUE);
//         paused = true;
//         std::cout << "Paused\n";
//     }
// }
//
// void Playlist::resume() {
//     if (soundLoaded && paused) {
//         ma_sound_set_paused(&currentSound, MA_FALSE);
//         paused = false;
//         std::cout << "Resumed\n";
//     }
// }

void Playlist::importFolder(string folder) {
    for (const auto & entry : filesystem::directory_iterator(folder)) {
    	string songFilePath = entry.path().string();
        if (entry.path().extension() == ".mp3") {
        	if (!containsSong(songFilePath)) {
        		Song* s = new Song(songFilePath);
        		s->loadMetadata();
        		insertSong(s);
        	} else {
        		cout << "[WARNING] MP3 file already exists in the playlist!" << endl;
        	}
        }
    }
	savePlaylist();
	savePlaylistSettings(playlistName, songCount, totalDuration, playlistShuffle, playlistRepeat);
}

bool Playlist::containsSong(const string& filePath) const {
	if (head == nullptr) return 0;

	PlaylistNode* currentNode = head;
	do {
		if (currentNode->song->getFile() == filePath) {
			return 1;  // Found it!
		}
		currentNode = currentNode->next;
	} while (currentNode != head);

	return 0;  // Not found
}

void Playlist::savePlaylist() {
	ofstream playlistData;
	playlistData.open(playlistFile); // Load File

	PlaylistNode *currentNode = head;

	if (currentNode == nullptr) {
		playlistData.close();
		return;
	}

	do {
		stringstream playlistSongDataStream;

		string filePath, title, artist, album, genre;
		int songID, songDuration, songPlayCount;
		filePath = currentNode->song->getFile();
        title = currentNode->song->getTitle();
        artist = currentNode->song->getArtist();
		album = currentNode->song->getAlbum();
        genre = currentNode->song->getGenre();
        songID = currentNode->song->getSongID();
        songDuration = currentNode->song->getDuration();
        songPlayCount = currentNode->song->getPlayCount();

		playlistSongDataStream << filePath << ";" << songID << ";" << title << ";" << artist << ";" << album << ";" << genre << ";" << songDuration << ";" << songPlayCount;
        playlistData << playlistSongDataStream.str() << endl;
		currentNode = currentNode->next;
	} while (currentNode != head);

	playlistData.close();
}

int Playlist::deletePlaylist() {
    bool doesPlaylistExist = playlistExists(playlistName);
	bool deleteStatus = 0;
    if (doesPlaylistExist) {
        ifstream playlistSettings("playlists.csv");

        if (!playlistSettings.is_open()) {
            cout << "[ERROR] Could not open playlist file!" << endl;
            return 0;
        }

        vector<string> playlistSettingsLINES;
        string csvRow;

        while(getline(playlistSettings, csvRow)) {
            if (csvRow.empty()) continue;  // Skip empty lines

            stringstream csvRowSS(csvRow); // Move Row to a String Stream
            string cell;

            // DEBUG
            // cout << csvRow << endl;
            string csvName, csvFile;
            int csvDate, csvSongCount, csvTotalDuration, csvShuffle, csvRepeat;

            getline(csvRowSS, csvName, ';');

        	if (csvName == playlistName) {
        		remove(playlistFile.c_str());
        		deleteStatus = 1;
        		continue;
        	}
            getline(csvRowSS, csvFile, ';');
            getline(csvRowSS, cell, ';');       csvDate             = stoi(cell);
            getline(csvRowSS, cell, ';');       csvSongCount        = stoi(cell);
            getline(csvRowSS, cell, ';');       csvTotalDuration    = stoi(cell);
            getline(csvRowSS, cell, ';');       csvShuffle          = stoi(cell);
            getline(csvRowSS, cell, ';');       csvRepeat           = stoi(cell);

            stringstream playlistSettingsData;
            playlistSettingsData << csvName << ";" << csvFile << ";" << csvDate << ";" << csvSongCount << ";" << csvTotalDuration << ";" << csvShuffle << ";" << csvRepeat;
            playlistSettingsLINES.push_back(playlistSettingsData.str());

        }
        playlistSettings.close();
        ofstream playlistSettingsWR("playlists.csv");
        for (const string& line : playlistSettingsLINES) {
            playlistSettingsWR << line << endl;
        }
        playlistSettingsWR.close();
    	return deleteStatus;
    }
}

bool Playlist::toggleShuffle() {
	if (playlistShuffle == 0) {
		playlistShuffle = 1;
	} else if (playlistShuffle == 1) {
		playlistShuffle = 0;
	}

	savePlaylistSettings(playlistName, songCount, totalDuration, playlistShuffle, playlistRepeat);
	return playlistShuffle;
}

bool Playlist::toggleRepeat() {
	if (playlistRepeat == 0) {
		playlistRepeat = 1;
	} else if (playlistRepeat == 1) {
		playlistRepeat = 0;
	}

	savePlaylistSettings(playlistName, songCount, totalDuration, playlistShuffle, playlistRepeat);

	return playlistRepeat;
}