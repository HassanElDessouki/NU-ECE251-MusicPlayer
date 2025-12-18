// ======================================================== //
#include "include/song.h"
#include <iostream>
#include <filesystem>
#include <string>
// ====================MP3 Audio Player==================== //
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"
// =====================MP3 Audio Tags===================== //
#include <taglib/fileref.h>
#include <taglib/tag.h>
// ======================================================== //

namespace fs = std::filesystem;

Song::Song(
	const std::string& path,										// filePath
	int id,
	const std::string& t,											// MP3 Title
	const std::string& a,											// Artist
	const std::string& al,											// Album
	const std::string& g,											// Genre
	int dur,
    int pc
)
	: filePath(path), songID(id), title(t), artist(a), album(al), genre(g), duration(dur),playCount(pc) {
}

bool Song::loadMetadata() {
	TagLib::FileRef f((filePath.data()));
    if (f.isNull()) { std::cout << "[ERROR] Could not open file or no tags found: " << std::endl; return false; }
	if (!f.isNull() && f.tag()) {
	  	TagLib::Tag *tag = f.tag();
	    title 	= tag->title().toCString(true);
	    artist 	= tag->artist().toCString(true);
	    album 	= tag->album().toCString(true);
		genre 	= tag->genre().toCString(true);
        duration = f.audioProperties()->lengthInSeconds();
//	    Year: tag->year();
//	    Track: tag->track();
        return true;
	} else {
        return false;
	}
}

void Song::displayInfo() const {
	std::cout << "Title: " << title << std::endl;
	std::cout << "Artist: " << artist << std::endl;
	std::cout << "Album: " << album << std::endl;
	std::cout << "Genre: " << genre << std::endl;
	std::cout << "Duration: " << duration << " sec" << std::endl;
	std::cout << "File Path: " << filePath << std::endl;
	std::cout << "Play Count: " << playCount << std::endl;
}

bool Song::playSong() {
	// A LOT OF IMPROVEMENTS CAN BE MADE HERE TO MAKE SONG PLAYING EFFICENT, BUT FOR A SMALL PROJECT, THIS GETS THE JOB DONE :-)
	// THIS IS A NOTE TO BE TAKEN IF IMPROVEMENTS WERE TO BE MADE LATER
	// MINIAUDIO Audio Engine is uninitalized and then initalized again every single time an audio is played, hence the inefficiency
	ma_result result;
	stopAudioEngine();

	// Initialize the miniaudio engine. This creates an internal thread for audio playback.
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) {
		std::cerr << "Failed to initialize audio engine." << std::endl;
		return 0;
	}

	engineStatus = 1;

	// Play the sound asynchronously. This function returns immediately.
	result = ma_sound_init_from_file(&engine, filePath.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &sound);
	if (result != MA_SUCCESS) {
		std::cerr << "Failed to play sound: " << result << std::endl;
		ma_engine_uninit(&engine);
		return 0;
	}

	soundStatus = 1;

	ma_sound_start(&sound);
	return 1;
}

void Song::pauseSong() {
	ma_sound_stop(&sound);
}

void Song::resumeSong() {
	ma_sound_start(&sound);
}

void Song::stopSong() {
	ma_sound_stop(&sound);
	ma_sound_seek_to_pcm_frame(&sound, 0);  // rewind to start
}

void Song::stopAudioEngine() {
	if (soundStatus) {
		ma_sound_uninit(&sound);
		soundStatus = 0;
	}
	if (engineStatus) {
		ma_engine_uninit(&engine);
		engineStatus = 0;
	}
}

// bool Song::playSong() {
// 	ma_result result;
// 	ma_engine engine;
//
// 	result = ma_engine_init(NULL, &engine);
// 	if (result != MA_SUCCESS) {
// 		return 0;
// 	}
//
// 	incrementPlayCount();
// 	ma_engine_play_sound(&engine, filePath.c_str(), NULL);
// 	printf("Press Enter to quit...");
// 	ma_sleep(3000); // 3 seconds
//
// 	ma_engine_uninit(&engine);
//     return 1;
// }