#include"Track.h"

#include"common.h"

void Spotify::Track::set(const JSON& _json) {
	if (!_json.isObject()) {
		throw Util::makeError(U"Spotify::Track::[[private]]set", U"json is not object");
	}
	album.set(_json[Type::album]);
	for (const auto& artist : _json[Type::artists]) {
		artists << ArtistSimple{ artist.value };
	}
	id = _json[Type::id].getOr<String>(unknown::asString);
	name = _json[Type::name].getOr<String>(unknown::asString);
	popularity = _json[Type::popularity].getOr<uint8>(unknown::asUint);
	href = _json[Type::href].getOr<URL>(unknown::asURL);
}
