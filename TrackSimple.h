#pragma once
#ifndef _SPOTIFY_TRACKSIMPLE_H_
#define _SPOTIFY_TRACKSIMPLE_H_

#include"ArtistSimple.h"
#include"common.h"

namespace Spotify {
	struct TrackSimple {
		TrackSimple() = default;
		TrackSimple(const JSON& _json) {
			this->set(_json);
		}

		virtual void set(const JSON& _json);

		Array<ArtistSimple> artists;
		String id;
		String name;
		URL href;
	};
}
#endif
