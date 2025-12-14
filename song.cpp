#include "include/song.h"
#include <filesystem>
#include <string>
#include <taglib/fileref.h>
#include <taglib/tag.h>
namespace fs = std::filesystem;

Song::Song(
	const std::string& path,										// filePath
	const std::string& t,										// MP3 Title
	const std::string& a,										// Artist
	const std::string& al,										// Album
	const std::string& g,										// Genre
	int id,													// Genre
	int pc,
	int dur)
	: filepath(path), title(t), artist(a), album(al), genre(g), song_Id(id), playCount(pc), duration(dur) {
}

bool Song::loadMetadata() {
	TagLib::FileRef f((filepath.data()));
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
	    std::cout << "Could not open file or no tags found: " << std::endl;
        return false;
	}
}

void Song::displayInfo() const {
	std::cout << "Title: " << title << std::endl;
	std::cout << "Artist: " << artist << std::endl;
	std::cout << "Album: " << album << std::endl;
	std::cout << "Genre: " << genre << std::endl;
	std::cout << "Duration: " << duration << " sec" << std::endl;
	std::cout << "Filepath: " << filepath << std::endl;
	std::cout << "Play Count: " << playCount << std::endl;
}

// void mp3METADATA(string filename) {

// }