#pragma once
#ifndef _SPOTIFY_CONSTS_H_
#define _SPOTIFY_CONSTS_H_

namespace Spotify {
	namespace Type {
		constexpr const char32_t* id{ U"id" };
		constexpr const char32_t* name{ U"name" };
		constexpr const char32_t* artists{ U"artists" };
		constexpr const char32_t* artist{ U"artist" };
		constexpr const char32_t* total_tracks{ U"total_tracks" };
		constexpr const char32_t* album{ U"album" };
		constexpr const char32_t* genres{ U"genres" };
		constexpr const char32_t* total{ U"total" };
		constexpr const char32_t* followers{ U"followers" };
		constexpr const char32_t* url{ U"url" };
		constexpr const char32_t* images{ U"images" };
		constexpr const char32_t* popularity{ U"popularity" };
		constexpr const char32_t* type{ U"type" };
		constexpr const char32_t* href{ U"href" };
		constexpr const char32_t* release_date{ U"release_date" };
		constexpr const char32_t* album_type{ U"album_type" };
		constexpr const char32_t* tracks{ U"tracks" };
		constexpr const char32_t* items{ U"items" };
		constexpr const char32_t* albums{ U"albums" };
		constexpr const char32_t* access_token{ U"access_token" };

		constexpr const char32_t* acousticness{ U"acousticness" };
		constexpr const char32_t* danceability{ U"danceability" };
		constexpr const char32_t* duration_ms{ U"duration_ms" };
		constexpr const char32_t* energy{ U"energy" };
		constexpr const char32_t* instrumentalness{ U"instrumentalness" };
		constexpr const char32_t* key{ U"key" };
		constexpr const char32_t* liveness{ U"liveness" };
		constexpr const char32_t* loudness{ U"loudness" };
		constexpr const char32_t* mode{ U"mode" };
		constexpr const char32_t* speechiness{ U"speechiness" };
		constexpr const char32_t* tempo{ U"tempo" };
		constexpr const char32_t* time_signature{ U"time_signature" };
		constexpr const char32_t* valence{ U"valence" };


	}

	namespace unknown {
		constexpr const char32_t* asString{ U"unknown" };
		constexpr const char32_t* asURL{ U"unknown" };
		constexpr unsigned char asUint{ 0u };
		constexpr signed char asInt{ 0u };
	}
}

#endif
