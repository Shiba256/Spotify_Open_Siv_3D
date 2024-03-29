#pragma once
#ifndef _SPOTIFY_API_H_
#define _SPOTIFY_API_H_

#include"Util.h"
#include"consts.h"
#include"Spotify.h"

namespace Spotify {
	enum class SearchType {
		track,
		artist,
		album
	};

	class API {
	public:
		static String parseType(SearchType _type) {
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
				return U"";
				break;
			}
		}

		API(const String& _client_id, const String& _client_secret) :
			client_id(_client_id),
			client_secret(_client_secret),
			token(getToken())
		{}

		~API() {
			Util::TempFiles::removeAll();
		}

		Array<Track> searchTrack(const String& query, uint16 max = 10, uint16 offset = 0) {
			Array<Track>rtn;
			const auto&& json = search(query, SearchType::track, max, offset);
			for (const auto& track : json[U"tracks"][U"items"]) {
				rtn << Track{ track.value };
			}
			return rtn;
		}
		Array<Artist> searchArtist(const String& query, uint16 max = 10, uint16 offset = 0) {
			Array<Artist>rtn;
			const auto&& json = search(query, SearchType::artist, max, offset);
			for (const auto& track : json[U"artists"][U"items"]) {
				rtn << Artist{ track.value };
			}
			return rtn;
		}
		Array<Album> searchAlbum(const String& query, uint16 max = 10, uint16 offset = 0) {
			Array<Album>rtn;
			const auto&& json = search(query, SearchType::album, max, offset);
			for (const auto& track : json[U"albums"][U"items"]) {
				rtn << Album{ track.value };
			}
			return rtn;
		}

		TrackFeature getTracksFeatures(const String& id) {
			const URL url = U"https://api.spotify.com/v1/audio-features/" + id;
			return TrackFeature{ getJSON(url) };
		}

		Array<Track> getArtistsTop(const String& id) {
			const URL url = U"https://api.spotify.com/v1/artists/" + id + U"/top-tracks?market=JP";
			const auto&& json = getJSON(url);
			Array<Track>rtn;
			for (const auto& track : json[U"tracks"]) {
				rtn << Track{ track.value };
			}
			return rtn;
		}

		String refreshToken() {
			this->getToken();
		}

		String market = U"JP";

	private:
		String client_id;
		String client_secret;
		String token;

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

		JSON search(const String& query, SearchType type, uint16 max = 10, uint16 offset = 0) {
			URL url = U"https://api.spotify.com/v1/search?q=";
			url += Util::Encode::urlEncode(query.removed(U' ').removed(U'　').removed(U'	'));
			url += U"&type=" + parseType(type);
			url += U"&market=" + market;
			url += U"&offset=" + Format(offset);
			url += U"&limit=" + Format(max);
			return getJSON(url);
		}

		String getToken() {
			const URL url = U"https://accounts.spotify.com/api/token";
			const HashTable<String, String> headers = { { U"Content-Type",U"application/x-www-form-urlencoded"} };
			std::string data = U"grant_type=client_credentials&client_id={}&client_secret={}"_fmt(client_id, client_secret).narrow();
			const FilePath path = Util::TempFiles::makeUniquePath();
			if (SimpleHTTP::Post(url, headers, data.data(), data.size(), path).isOK()) {
				const auto json_file{ JSON::Load(path) };
				if (json_file.contains(U"access_token")) {
					return json_file[U"access_token"].getString();
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
}



#endif
