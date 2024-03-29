#include"Artist.h"

#include"common.h"

void Spotify::Artist::set(const JSON& _json) {
	//base
	ArtistSimple::set(_json);

	if (!_json.isObject()) {
		throw Util::makeError(U"Spotify::Artist::[[private]] set_plus", U"[json file is not object]");
	}

	followers = _json[Type::followers][Type::total].getOr<uint64>(unknown::asUint);
	popularity = _json[Type::popularity].getOr<uint8>(unknown::asUint);

	//genre
	for (const auto& genre : _json[Type::genres]) {
		genres << genre.value.getOr<String>(unknown::asString);
	}

	//url of image
	for (const auto& url : _json[Type::images]) {
		img_url << url.value[Type::url].getOr<URL>(unknown::asURL);
	}
}

Array<Texture> Spotify::Artist::getImage() {
	Array<Texture> rtn;
	for (const auto& url : img_url) {
		const FilePath path{ Util::TempFiles::makeUniquePath() };
		if (!SimpleHTTP::Save(url, path)) {
			throw Util::makeError(U"Spotify::Artists::getImage", U"HTTP::Save failed");
		}
		rtn << Texture{ path };
	}
	return rtn;
}
