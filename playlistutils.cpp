// ======================================================== //
#include "include/utils.h"
#include "include/playlistutils.h"
#include "include/playlist.h"
#include "include/song.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <ctime>
// #DEFINE
// ======================================================== //
using namespace std;

bool createPlaylist(const string& name) {
    string fileName = name + ".playlist";
    bool existsInCSV = playlistExists(name);

    // ifstream playlistSettings("playlists.csv");
    // if (playlistSettings.is_open()) {
    //     string csvRow;
    //     while(getline(playlistSettings, csvRow)) {
    //         if (csvRow.empty()) continue;  // Skip empty lines
    //
    //         stringstream csvRowSS(csvRow); // Move Row to a String Stream
    //         string cell;
    //
    //         getline(csvRowSS, cell, ';');
    //
    //         if (csvName == name) {
    //             existsInCSV = 1;
    //             break;
    //         }
    //     }
    //     playlistSettings.close();
    // } else {
    //     cout << "[ERROR] Could not open settings file!" << endl;  // ← Add this
    //     return 0;
    // }

    bool fileExists = filesystem::exists(fileName);

    if (!existsInCSV && !fileExists) {
        ofstream file(fileName);
        file.close();

        ofstream playlistSettings("playlists.csv", ios::app);
        playlistSettings << name << ";" << fileName << ";" << epochTime() << ";0;0;0;0" <<  endl;
        playlistSettings.close();

        // cout << "[SUCCESS] Successfully created playlist" << endl;
        return 1;
    }

    if (existsInCSV && !fileExists) {
        cout << "[ERROR] Playlist exists in settings file, but the file for the playlist could not be found!" << endl;
        ofstream file(fileName);
        file.close();

        cout << "[INFO] Recreated playlist file" << endl;
        return 1;
    }

    if (!existsInCSV && fileExists) {
        cout << "[ERROR] Playlist file exists, but does not exist in the settings file!" << endl;
        cout << "[INFO] Adding playlist to the settings file" << endl;

        ofstream playlistSettings("playlists.csv", ios::app);
        playlistSettings << name << ";" << fileName << ";" << epochTime() << ";0;0;0;0" <<  endl;
        playlistSettings.close();

        cout << "[INFO] Added playlist back to the settings file" << endl;
        return 1;
    }

    if (existsInCSV && fileExists) {
        cout << "[INFO] Playlist already exists: " << name << endl;
        return 0;
    }
    return 0;
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
        string csvName;

        getline(csvRowSS, csvName, ';');
        playlists.push_back(csvName);
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

        /* Seperate each value to its designated playlist struct variable */
        getline(csvRowSS, cell, ';');
        if (cell == name) {
            playlistSettings.close();
            // cout << "Playlist was found" << endl;
            return 1;
        }
    }
    // cout << "[ERROR] Could not find playlist!" << endl;
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