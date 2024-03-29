#pragma once
#ifndef _SPOTIFY_ARTISTSSIMPLE_H_
#define _SPOTIFY_ARTISTSSIMPLE_H_

#include"stdafx.h"

namespace Spotify {
	struct ArtistSimple {
	public:
		ArtistSimple();

		ArtistSimple(const ArtistSimple&) = default;
		ArtistSimple(ArtistSimple&&)noexcept = default;

		ArtistSimple(const JSON& _json) {
			this->set(_json);
		}

		virtual ~ArtistSimple() {}

		void set(const JSON& _json);

		String id;
		String name;
		URL href;
		String type;
	};
}

#endif
