// ======================================================== //
#pragma once
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

    if (filesystem::exists(fileName)) {
        ifstream playlistSettings("playlists.csv");

        if (!playlistSettings.is_open()) {
            cout << "[ERROR] Could not open settings file!" << endl;  // ← Add this
            return nullptr;
        }

        string csvRow;
        while(getline(playlistSettings, csvRow)) {
            if (csvRow.empty()) continue;  // Skip empty lines

            stringstream csvRowSS(csvRow); // Move Row to a String Stream
            string cell;

            // DEBUG
            if ((name + ";" + fileName) == csvRow) {
                cout << "[WARNING] Playlist already exists!" << endl;
                return nullptr;
            }
        }
        playlistSettings.close();
        cout << "[ERROR] Playlist file exists, but does not exist in the settings file!" << endl;
        cout << "[INFO] Adding playlist to the settings file" << endl;

        ofstream playlistSettingsWrite("playlists.csv", ios::app);
        playlistSettingsWrite << name << ";" << fileName << endl;
        playlistSettingsWrite.close();
        cout << "[SUCCESS] Successfully added playlist back to the settings file" << endl;

        return nullptr;
    }
    try {
        // Create Empty Playlist CSV
        ofstream file(fileName);
        file.close();
        ofstream playlistSettings("playlists.csv", ios::app);
        playlistSettings << name << ";" << fileName << endl;
        playlistSettings.close();
        cout << "[SUCCESS] Successfully created playlist" << endl;
        return new Playlist(name, fileName);
    }
    catch (int errorCode) {
        cout << "[ERROR] Unmapped error: " << errorCode << endl;
    }
    // error handling : if file does not exist but its already added to the settings file
    // if settings file could not be opened
    // if playlist file wasn't created
    return nullptr;
};

void deletePlaylist(const string& name) {

};

vector<string> listAllPlaylists()       {
    vector<string> playlists;
    ifstream playlistSettings("playlists.csv");
    playlistSettings.open("playlists.csv");

    if (!playlistSettings.is_open()) {
        cout << "[ERROR] Could not open playlist file!" << endl;  // ← Add this
        // ERROR HANDLING MISSING!!!!!!!!!!!!!
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
        cout << playlistName << endl;
        playlists.push_back(playlistName);
    }
    playlistSettings.close();
    return playlists;
};

bool playlistExists(const string& name) {
    ifstream playlistSettings("playlists.csv");

    if (!playlistSettings.is_open()) {
        cout << "[ERROR] Could not open playlist file!" << endl;  // ← Add this
        // ERROR HANDLING MISSING!!!!!!!!!!!!!
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
    return 0;
    playlistSettings.close();
};