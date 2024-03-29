# Spotify APIs using Open Siv 3D

### 1.Information
This project is for the Spotify API using [Open Siv 3D](https://github.com/Siv3D/OpenSiv3D)(C++ framework).

This project is currently **under development**. As such,**The API is expect to change frequently**.

### 2.Features
    ○ Search tracks
    ○ Search albums
    ○ Search artists
    ○ Get track features
    ○ Get artist top songs

### 3.Examples
```C++
#include"Spotify.h"

void Main(){
    //Set id and secret
    Spotify::API api{U"id",U"secret"};

    //Get tracks
    const auto tracks{api.searchTracks(U"name")};

    //Print track name
    for(const auto& track : tracks){
        Print << track.name;
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