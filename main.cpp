#include "include/song.h"
using namespace std;

int main() {
    Song s("C:/Users/Hassan/Music/Ace of Base - Cruel Summer.mp3");
    s.loadMetadata();
    s.displayInfo();
    s.playSong();
    return 0;
}