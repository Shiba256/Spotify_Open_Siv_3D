#pragma once
#ifndef  _SPOTIFY_ARTIST_H_
#define  _SPOTIFY_ARTIST_H_

#include"ArtistSimple.h"

#include"stdafx.h"

namespace Spotify {
	struct Artist : public ArtistSimple {
		Artist() = default;
		Artist(const Artist&) = default;
		Artist(Artist&&)noexcept = default;

		Artist(const JSON& _json){
			this->set(_json);
		}

		virtual ~Artist() {}

		Array<Texture> getImage();

		void set(const JSON& _json);

		uint64 followers;
		uint8 popularity;
		Array<String> genres;
		Array<URL> img_url;
	};


}

#endif
