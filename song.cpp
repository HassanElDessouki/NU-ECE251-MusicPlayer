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
	: filePath(path), song_Id(id), title(t), artist(a), album(al), genre(g), duration(dur),playCount(pc) {
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
	ma_result result;
	ma_engine engine;

	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) {
		return 0;
	}

	incrementPlayCount();
	ma_engine_play_sound(&engine, filePath.c_str(), NULL);
	printf("Press Enter to quit...");
	ma_sleep(3000); // 3 seconds

	ma_engine_uninit(&engine);
    return 1;
}