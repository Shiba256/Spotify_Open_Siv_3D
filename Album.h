#pragma once
#ifndef _SPOTIFY_ALBUM_H_
#define _SPOTIFY_ALBUM_H_

#include"ArtistSimple.h"

#include"stdafx.h"

namespace Spotify {
	enum class AlbumType {
		none,
		album,
		single,
		compilation
	};

	struct Album {
		Album() = default;
		Album(const Album&) = default;
		Album(Album&&)noexcept = default;

		Album(const JSON& _json) {
			this->set(_json);
		}

		virtual ~Album() {}

		void set(const JSON& _json);

		Array<Texture> getImage();

		AlbumType album_type{ AlbumType::none };
		URL href;
		Array<URL> img_url;
		Date release_date{ 0,0,0 };
		String type;
		Array<ArtistSimple> artists;
		String id;
		String name;
		uint32 total_tracks{ 0u };
	};
}

#endif
