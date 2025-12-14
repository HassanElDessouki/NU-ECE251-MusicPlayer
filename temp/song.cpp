#include <Song.h>

Song::Song(
	const string& path,
	const string& t,
	const string& a,
	const string& al,
	const string& g,
	int id,
	int pc,
	int dur)
	: filepath(path), title(t), artist(a), album(al), genre(g), song_Id(id), playCount(pc), duration(dur) {
}

bool Song:: loadMetadataFromFile() { return false;}
void Song::displayInfo() const {
	cout << "Title: " << title << endl;
	cout << "Artist: " << artist << endl;
	cout << "Album: " << album << endl;
	cout << "Genre: " << genre << endl;
	cout << "Duration: " << duration << " sec" << endl;
	cout << "Filepath: " << filepath << endl;
	cout << "Play Count: " << playCount << endl;
}