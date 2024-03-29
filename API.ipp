#pragma once

#include"common.h"

#include"stdafx.h"

namespace Spotify {
	struct API::Impl {
		Impl(const String& _id, const String& _secret) :
			client_id(_id),
			client_secret(_secret)
		{
			token = this->postToken();
		}

		const String& getToken() const noexcept {
			return token;
		}

		void refreshToken() {
			token = this->postToken();
		}

		JSON getJSON(const URL& url) {
			const HashTable<String, String> headers = { { U"Authorization", U"Bearer " + token } };
			const FilePath path{ Util::TempFiles::makeUniquePath() };
			const auto status{ SimpleHTTP::Get(url, headers, path) };
			if (status.isOK()) {
				auto json{ JSON::Load(path) };
				json.save(path);
				json = JSON::Load(path);
				return json;
			}
			else {
				throw Error{ U"Get request failed!\nstatus code({})::{}"_fmt(status.getStatusCodeInt(),status.getStatusLine()) };
			}
		}

		JSON search(const String& query, SearchType type, uint16 max = 10, uint16 offset = 0, const String& market = U"JP") {
			URL url = U"https://api.spotify.com/v1/search?q=";
			url += Util::Encode::urlEncode(query.removed(U' ').removed(U'　').removed(U'	'));
			url += U"&type=" + parseSearchType(type);
			url += U"&market=" + market;
			url += U"&offset=" + Format(offset);
			url += U"&limit=" + Format(max);
			return getJSON(url);
		}

	private:
		String client_id;
		String client_secret;
		String token;

		String postToken() {
			const URL url = U"https://accounts.spotify.com/api/token";
			const HashTable<String, String> headers = { { U"Content-Type",U"application/x-www-form-urlencoded"} };
			std::string data = U"grant_type=client_credentials&client_id={}&client_secret={}"_fmt(client_id, client_secret).narrow();
			const FilePath path = Util::TempFiles::makeUniquePath();
			if (SimpleHTTP::Post(url, headers, data.data(), data.size(), path).isOK()) {
				const auto json_file{ JSON::Load(path) };
				return json_file[Type::access_token].getString();
			}
			else {
				throw Error{ U"Post request failed! check [client_id] and [client_secret]" };
			}
		}
	};

	API::API(const String& id, const String& secret) :
		m_impl(std::make_unique<Impl>(id, secret))
	{}

	API::~API() {
		Util::TempFiles::removeAll();
	}

	Array<Track> API::searchTracks(const String& query, uint16 max, uint16 offset, const String& market ) {
		try {
			Array<Track>rtn;
			const JSON json = m_impl->search(query, SearchType::track, max, offset, market);
			for (const auto& track : json[Type::tracks][Type::items]) {
				rtn << Track{ track.value };
			}
			return rtn;
		}
		catch (Error& er) {
			throw Util::makeError(U"Spotify::API::searchTrack()", er.what());
		}
	}

	Array<Artist> API::searchArtists(const String& query, uint16 max, uint16 offset, const String& market) {
		try {
			Array<Artist>rtn;
			const auto&& json = m_impl->search(query, SearchType::artist, max, offset, market);
			for (const auto& track : json[Type::artists][Type::items]) {
				rtn << Artist{ track.value };
			}
			return rtn;
		}
		catch (Error& er) {
			throw Util::makeError(U"Spotify::API::searchArtists()", er.what());
		}
	}

	Array<Album> API::searchAlbums(const String& query, uint16 max, uint16 offset, const String& market) {
		try {
			Array<Album>rtn;
			const auto&& json = m_impl->search(query, SearchType::album, max, offset, market);
			for (const auto& track : json[Type::albums][Type::items]) {
				rtn << Album{ track.value };
			}
			return rtn;
		}
		catch(Error& er){
			throw Util::makeError(U"Spotify::API::searchAlbums()", er.what());
		}
	}

	TrackFeature API::getTracksFeatures(const String& id) {
		try {
			const URL url = U"https://api.spotify.com/v1/audio-features/" + id;
			return TrackFeature{ m_impl->getJSON(url) };
		}
		catch (Error& er) {
			throw Util::makeError(U"Spotify::API::getTracksFeatures()", er.what());
		}
	}

	Array<Album> API::getArtistAlbums(const String& id,uint16 limit,uint16 offset, const String& market) {
		try {
			Array<Album> rtn;
			URL url = U"https://api.spotify.com/v1/artists/{}/albums?"_fmt(id);
			url += U"market={}"_fmt(market);
			url += U"&limit={}"_fmt(limit);
			url += U"&offset={}"_fmt(offset);
			const auto json = m_impl->getJSON(url);
			for (const auto& album : json[Type::items]) {
				rtn << Album{ album.value };
			}
			return rtn;
		}
		catch (Error& er) {
			throw Util::makeError(U"Spotify::API::getArtistAlbums()", er.what());
		}
	}

	Array<Artist> API::getRelatedArtists(const String& id) {
		try {
			Array<Artist> rtn;
			const URL url{ U"https://api.spotify.com/v1/artists/{}/related-artists"_fmt(id) };
			const auto json = m_impl->getJSON(url);
			for (const auto& artist : json[Type::artists]) {
				rtn << Artist{ artist.value };
			}
			return rtn;
		}
		catch (Error& er) {
			throw Util::makeError(U"Spotify::API::getRelatedArtists", er.what());
		}
		
	}

	Array<TrackSimple> API::getAlbumTracks(const String& id, uint16 max, uint16 offset, const String& market) {
		try {
			Array<TrackSimple> rtn;
			URL url = U"https://api.spotify.com/v1/albums/{}/tracks?"_fmt(id);
			url += U"market={}"_fmt(market);
			url += U"&limit={}"_fmt(max);
			url += U"&offset={}"_fmt(offset);
			const auto json = m_impl->getJSON(url);
			for (const auto& track : json[Type::items]) {
				rtn << TrackSimple{ track.value };
			}
			return rtn;
		}
		catch (Error& er) {
			throw Util::makeError(U"Spotify::API::getAlbumTracks()", er.what());
		}
	}

	Array<Track> API::getArtistTopTracks(const String& id) {
		try {
			const URL url = U"https://api.spotify.com/v1/artists/" + id + U"/top-tracks?market=JP";
			const auto&& json = m_impl->getJSON(url);
			Array<Track>rtn;
			for (const auto& track : json[Type::tracks]) {
				rtn << Track{ track.value };
			}
			return rtn;
		}
		catch (Error& er) {
			throw Util::makeError(U"Spotify::API::getArtistTop()", er.what());
		}
	}

	Array<Track> API::getRelatedTracksSimple(const String& track_id,uint16 max,const String& market) {
		try {
			URL url = U"https://api.spotify.com/v1/recommendations?";
			url += U"limit={}"_fmt(max);
			url += U"&market={}"_fmt(market);
			url += U"&seed_tracks={}"_fmt(track_id);
			const auto&& json = m_impl->getJSON(url);
			Array<Track>rtn;
			for (const auto& track : json[Type::tracks]) {
				rtn << Track{ track.value };
			}
			return rtn;
		}
		catch (Error& er) {
			throw Util::makeError(U"Spotify::API::getRelatedTracksSimple()", er.what());
		}
	}

	void API::refreshToken() {
		this->m_impl->refreshToken();
	}

}
