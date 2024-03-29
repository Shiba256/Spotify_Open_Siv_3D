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

		HashTable<String, double> AsHashTable()const noexcept;

		HashTable<String, double> AsHashTableNormalized(double tempo_max = 250.0)const noexcept;

		inline Duration length() {
			return Duration{ duration_ms };
		}

		String id{};
		double acousticness{ 0.0 };
		double danceability{ 0.0 };
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
	private:
		MillisecondsF duration_ms{ 0.0ms };
	};
}

#endif
