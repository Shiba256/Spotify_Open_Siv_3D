#pragma once
#ifndef _SPOTIFY_TRACKFEATURE_H_
#define _SPOTIFY_TRACKFEATURE_H_

#include"stdafx.h"
#include"Key.h"
#include"Mode.h"

namespace Spotify {
	struct TrackFeature {
		TrackFeature(const JSON& _json) {
			this->set(_json);
		}

		TrackFeature() = default;

		void set(const JSON& _json);

		String id{};
		double acousticness{ 0.0 };
		double danceability{ 0.0 };
		MicrosecondsF duration_ms{ 0.0ms };
		double energy{ 0.0 };
		double instrumentalness{ 0.0 };
		Key key{ Key::none };
		double liveness{ 0.0 };
		double loudness{ 0.0 };
		Mode mode{ Mode::major };
		double speechiness{ 0.0 };
		double tempo{ 0.0 };
		double time_signature{ 0.0 };
		double valence{ 0.0 };
	};
}

#endif
