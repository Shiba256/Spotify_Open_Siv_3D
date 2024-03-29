#include"TrackSimple.h"

#include"common.h"


void Spotify::TrackSimple::set(const JSON& _json) {
	if (!_json.isObject()) {
		throw Util::makeError(U"Spotify::TrackSimple::set", U"json is not object");
	}
	for (const auto& artist : _json[Type::artists]) {
		artists << ArtistSimple{ artist.value };
	}
	id = _json[Type::id].getOr<String>(unknown::asString);
	name = _json[Type::name].getOr<String>(unknown::asString);
	href = _json[Type::href].getOr<URL>(unknown::asURL);
}

