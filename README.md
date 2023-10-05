# Music_Library_System
This C++ code defines a simple music library system with the ability to perform various operations related to music tracks and playlists.

Here's a information of the main components and functionality of the code:

1. `MusicTrack` Class:
   - Represents a music track with attributes such as ID, title, artist, album, genre, and a pointer to the next track (for collision handling in the hash table).
   - Provides methods for getting, displaying, and updating track information.

2. `MusicLibrary` Class:
   - Manages a collection of music tracks using a hash table.
   - Supports functions for adding, retrieving, updating, and deleting tracks.
   - Implements collision handling using chaining.
   - Also includes a method for searching if a song exists in the library.

3. `PlaylistTrack` Class:
   - Represents a track within a playlist with an ID and a pointer to the next track in the playlist.

4. `PlayList` Class:
   - Represents a playlist and provides functionality to add and remove tracks from the playlist.
   - It uses the `MusicLibrary` to verify if a track exists before adding it to the playlist.
   - Offers a method to display the contents of the playlist.

5. `main` Function:
   - The main program flow is managed here.
   - It initializes a `MusicLibrary` and a `PlayList`.
   - The user is presented with a menu to perform various actions on the music library and playlist, such as adding, retrieving, updating, and deleting tracks, as well as managing playlists.

6. Hashing:
   - The code uses a simple hash function to distribute tracks into the hash table based on their IDs.
   - The size of the hash table is determined by user input.
