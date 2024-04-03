# Spotify APIs using Open Siv 3D

### 1.Information
This project is for the Spotify API using [Open Siv 3D](https://github.com/Siv3D/OpenSiv3D)(C++ framework).

This project is currently **under development**. As such,**The API is expect to change frequently**.

### 2.Features
    ○ Search tracks
    ○ Search albums
    ○ Search artists
    ○ Get track features
    ○ Get artist top tracks
    ○ Get artist albums
    ○ Get related tracks(simple)
    ○ Get related artists


### 3.Examples
```C++
#include"Spotify.h"

void Main(){
    //Set id and secret
    Spotify::API api{U"your_id",U"your_secret"};
    
    //Search Artists
    for (const auto& artist : api.searchArtists(U"name", 1)) {

        //Print Artist
		Print << U"[{}]"_fmt(artist.name);
		
        //Get Artist Top Tracks
        for (const auto& track : api.getArtistTopTracks(artist.id)) {
			
            //Print Track and BPM
            Print << U"Track[{}] , BPM={}"_fmt(track.name, api.getTracksFeatures(track.id).tempo);
		}
	}

    while(System::Update()){}
}

```

### 4.API
List of [struct class enum]

    ○ struct Album
    ○ class API
    ○ struct Artist
    ○ struct ArtistSimple
    ○ enum Key
    ○ enum Mode
    ○ struct Track
    ○ struct TrackFeature
    ○ struct TrackSimple