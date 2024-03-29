#pragma once
#ifndef _SPOTIFY_API_H_
#define _SPOTIFY_API_H_

#include"Album.h"
#include"Artist.h"
#include"ArtistSimple.h"
#include"Track.h"
#include"TrackFeature.h"

namespace Spotify {
	enum class SearchType {
		track,
		artist,
		album
	};

	inline String parseSearchType(SearchType _type) {
		switch (_type) {
		case Spotify::SearchType::track:
			return U"track";
			break;
		case Spotify::SearchType::artist:
			return U"artist";
			break;
		case Spotify::SearchType::album:
			return U"album";
		default:
			return U"unknown";
			break;
		}
	}

	class API {
	public:
		API(const String& _client_id, const String& _client_secret);
		API(const API&) = default;
		API(API&&)noexcept = default;

		virtual ~API();

		Array<Track> searchTracks(const String& query, uint16 max = 10, uint16 offset = 0, const String& market = U"JP");
		Array<Artist> searchArtists(const String& query, uint16 max = 10, uint16 offset = 0, const String& market = U"JP");
		Array<Album> searchAlbums(const String& query, uint16 max = 10, uint16 offset = 0, const String& market = U"JP");

		TrackFeature getTracksFeatures(const String& id);

		Array<Track> getArtistTop(const String& id);

		void refreshToken();

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};
}

#include"API.ipp"

#endif
