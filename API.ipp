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
			if (SimpleHTTP::Get(url, headers, path).isOK()) {
				auto json{ JSON::Load(path) };
				json.save(path);
				json = JSON::Load(path);
				return json;
			}
			else {
				throw Error{ U"Spotify::getJSON [Get request failed]" };
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
				if (json_file.contains(Type::access_token)) {
					return json_file[Type::access_token].getString();
				}
				else {
					throw Error{ U"Spotify::getToken [Unable to obtain access_token]" };
				}
			}
			else {
				throw Error{ U"Spotify::getToken [Post request failed]" };
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
		Array<Track>rtn;
		const auto&& json = m_impl->search(query, SearchType::track, max, offset,market);
		for (const auto& track : json[Type::tracks][Type::items]) {
			rtn << Track{ track.value };
		}
		return rtn;
	}

	Array<Artist> API::searchArtists(const String& query, uint16 max, uint16 offset, const String& market) {
		Array<Artist>rtn;
		const auto&& json = m_impl->search(query, SearchType::artist, max, offset, market);
		for (const auto& track : json[Type::artists][Type::items]) {
			rtn << Artist{ track.value };
		}
		return rtn;
	}

	Array<Album> API::searchAlbums(const String& query, uint16 max, uint16 offset, const String& market) {
		Array<Album>rtn;
		const auto&& json = m_impl->search(query, SearchType::album, max, offset, market);
		for (const auto& track : json[Type::albums][Type::items]) {
			rtn << Album{ track.value };
		}
		return rtn;
	}

	TrackFeature API::getTracksFeatures(const String& id) {
		const URL url = U"https://api.spotify.com/v1/audio-features/" + id;
		return TrackFeature{ m_impl->getJSON(url) };
	}

	Array<Track> API::getArtistTop(const String& id) {
		const URL url = U"https://api.spotify.com/v1/artists/" + id + U"/top-tracks?market=JP";
		const auto&& json = m_impl->getJSON(url);
		Array<Track>rtn;
		for (const auto& track : json[Type::tracks]) {
			rtn << Track{ track.value };
		}
		return rtn;
	}

	void API::refreshToken() {
		this->m_impl->refreshToken();
	}

}
