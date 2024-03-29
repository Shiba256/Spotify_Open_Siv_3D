#pragma once
#ifndef _SPOTIFY_TRACK_H_
#define _SPOTIFY_TRACK_H_

#include"stdafx.h"

#include"Album.h"

#include"TrackSimple.h"

namespace Spotify {
	struct Track : public TrackSimple {
		Track(const JSON& _json) {
			this->set(_json);
		}

		void set(const JSON& _json);

		Album album;
		uint8 popularity;
	};
}
#endif
