#include<Siv3D.hpp>

#include"Spotify.h"
#include"API.h"

void Main() {
	const INI ini{ U"./_sys_/.config" };
	Spotify::API api{
		ini.get<String>(U"Spotify", U"id"),
		ini.get<String>(U"Spotify", U"secret")
	};

	auto&& tracks = api.searchTrack(U"ずとまよ 残機", 5);
	for (const auto& track : tracks) {
		Print << api.getTracksFeatures(track.id).energy;
	}

	while(System::Update()){
	}
}
