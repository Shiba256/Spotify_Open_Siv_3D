#pragma once
#ifndef _SPOTIFY_TRACK_H_
#define _SPOTIFY_TRACK_H_

#include"stdafx.h"

#include"Album.h"

namespace Spotify {
	struct Track {
		Track(const JSON& _json) {
			this->set(_json);
		}

		void set(const JSON& _json);

		Array<ArtistSimple> artists;
		Album album;
		String id;
		String name;
		uint8 popularity;
		URL href;
	};
}
#endif
