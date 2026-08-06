# Music Player 

A CLI music player written in C++ as a team project for the course **ECE251: Data Structures and Algorithms** at *Nile University*.

The project explores the use of custom data structures in a practical application. Songs within each playlist are stored using a circular doubly linked list, while playlist and song information is persisted locally between sessions.

## Features

- Create and delete playlists
- Add individual MP3 files to a playlist
- Import all MP3 files from a folder
- Extract song metadata automatically
- Play, pause, resume, skip, and return to previous tracks
- Automatically advance when a song finishes
- Enable or disable playlist repeat
- Display song and playlist information
- Track the number of times a song has been played
- Save playlists and settings between sessions
- Prevent duplicate file paths within the same playlist

> [!NOTE]
> The interface includes a shuffle setting, but shuffle playback has not yet been implemented.

## Data Structure

Each playlist is represented using a **circular doubly linked list**.

Every node contains:

- A pointer to a `Song` object
- A pointer to the next song
- A pointer to the previous song

This structure allows playback to move forwards and backwards through a playlist and makes it possible to return from the last song to the first when repeat is enabled.

## Technologies

- **C++20**
- **CMake**
- **TagLib** for reading MP3 metadata
- **miniaudio** for audio playback
- C++ Standard Library:
  - Filesystem
  - Threads
  - File streams
  - Vectors
  - String streams

## Project Structure

```text
.
├── include/
│   ├── playlist.h
│   ├── playlistutils.h
│   ├── song.h
│   └── utils.h
├── miniaudio/
├── main.cpp
├── playlist.cpp
├── playlistutils.cpp
├── song.cpp
├── utils.cpp
└── CMakeLists.txt
