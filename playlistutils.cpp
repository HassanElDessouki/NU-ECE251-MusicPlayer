// ======================================================== //
#include "include/playlistutils.h"
#include "include/playlist.h"
#include "include/song.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
// ======================================================== //
using namespace std;

Playlist* createPlaylist(const string& name) {
    string fileName = name + ".playlist";
    bool existsInCSV = 0;

    ifstream playlistSettings("playlists.csv");
    if (playlistSettings.is_open()) {
        string csvRow;
        while(getline(playlistSettings, csvRow)) {
            if (csvRow.empty()) continue;  // Skip empty lines

            stringstream csvRowSS(csvRow); // Move Row to a String Stream
            string csvName, csvFile;
            getline(csvRowSS, csvName, ';');
            getline(csvRowSS, csvFile, ';');

            if (csvName == name) {
                existsInCSV = 1;
                break;
            }
        }
        playlistSettings.close();
    } else {
        cout << "[ERROR] Could not open settings file!" << endl;  // ← Add this
        return nullptr;
    }

    bool fileExists = filesystem::exists(fileName);

    if (!existsInCSV && !fileExists) {
        ofstream file(fileName);
        file.close();

        ofstream playlistSettings("playlists.csv", ios::app);
        playlistSettings << name << ";" << fileName << endl;
        playlistSettings.close();

        cout << "[SUCCESS] Successfully created playlist" << endl;
        return new Playlist(name, fileName);
    }

    if (existsInCSV && !fileExists) {
        cout << "[ERROR] Playlist exists in settings file, but the file for the playlist could not be found!" << endl;
        ofstream file(fileName);
        file.close();

        cout << "[SUCCESS] Successfully created playlist file" << endl;
        return new Playlist(name, fileName);
    }

    if (!existsInCSV && fileExists) {
        cout << "[ERROR] Playlist file exists, but does not exist in the settings file!" << endl;
        cout << "[INFO] Adding playlist to the settings file" << endl;

        ofstream playlistSettingsWrite("playlists.csv", ios::app);
        playlistSettingsWrite << name << ";" << fileName << endl;
        playlistSettingsWrite.close();

        cout << "[SUCCESS] Successfully added playlist back to the settings file" << endl;
        return new Playlist(name, fileName);
    }

    if (existsInCSV && fileExists) {
        cout << "[INFO] Playlist already exists: " << name << endl;
        return new Playlist(name, fileName);
    }
//        playlistSettingsWrite << name << ";" << fileName << ";" << dateCreated << ";" << dateModified << ";" << songCount << ";" << totalDuration << ";" << description << ";" << endl;
};



vector<string> listAllPlaylists()       {
    vector<string> playlists;
    ifstream playlistSettings("playlists.csv");

    if (!playlistSettings.is_open()) {
        cout << "[ERROR] Could not open playlist file!" << endl;
        return playlists;
    }

    string csvRow;
    while(getline(playlistSettings, csvRow)) {
        if (csvRow.empty()) continue;  // Skip empty lines

        stringstream csvRowSS(csvRow); // Move Row to a String Stream
        string cell;

        // DEBUG
        // cout << csvRow << endl;
        string playlistName, playlistFile;

        /* Seperate each value to its designated playlist struct variable */
        getline(csvRowSS, cell, ';'); playlistName 			= cell;
        getline(csvRowSS, cell, ';'); playlistFile 			= cell;
        playlists.push_back(playlistName);
    }
    playlistSettings.close();
    return playlists;
};

bool playlistExists(const string& name) {
    ifstream playlistSettings("playlists.csv");

    if (!playlistSettings.is_open()) {
        cout << "[ERROR] Could not open playlist file!" << endl;  // ← Add this
        return 0;
    }

    string csvRow;
    while(getline(playlistSettings, csvRow)) {
        if (csvRow.empty()) continue;  // Skip empty lines

        stringstream csvRowSS(csvRow); // Move Row to a String Stream
        string cell;

        // DEBUG
        // cout << csvRow << endl;
        string playlistName, playlistFile;

        /* Seperate each value to its designated playlist struct variable */
        getline(csvRowSS, cell, ';'); playlistName 			= cell;
        getline(csvRowSS, cell, ';'); playlistFile 			= cell;
        if (playlistName == name) {
            cout << "Playlist was found" << endl;
            return 1;
        }
    }
    cout << "[ERROR] Could not find playlist!" << endl;
    playlistSettings.close();
    return 0;
};

void savePlaylistSettings(const string& name, const int& songCount, const int& totalDuration, const int& playlistShuffle, const int& playlistRepeat) {
    bool doesPlaylistExist = playlistExists(name);
    if (doesPlaylistExist) {
        ifstream playlistSettings("playlists.csv");

        if (!playlistSettings.is_open()) {
            cout << "[ERROR] Could not open playlist file!" << endl;
            return;
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
            getline(csvRowSS, csvFile, ';');
            getline(csvRowSS, cell, ';');       csvDate             = stoi(cell);
            getline(csvRowSS, cell, ';');       csvSongCount        = stoi(cell);
            getline(csvRowSS, cell, ';');       csvTotalDuration    = stoi(cell);
            getline(csvRowSS, cell, ';');       csvShuffle          = stoi(cell);
            getline(csvRowSS, cell, ';');       csvRepeat           = stoi(cell);
            if (csvName == name) {
                csvSongCount = songCount;
                csvTotalDuration = totalDuration;
                csvShuffle = playlistShuffle;
                csvRepeat = playlistRepeat;
            }

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
    }
}