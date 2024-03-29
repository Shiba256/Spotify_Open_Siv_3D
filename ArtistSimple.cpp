#include"ArtistSimple.h"

#include"common.h"

Spotify::ArtistSimple::ArtistSimple() :
	id{},
	name{},
	href{},
	type{}
{}

void Spotify::ArtistSimple::set(const JSON& _json) {
	if (!_json.isObject()) {
		throw Spotify::Util::makeError(U"Spotify::ArtistSimple", U"json is not object");
	}

	id = _json[Type::id].getOr<String>(unknown::asString);
	name = _json[Type::name].getOr<String>(unknown::asString);
	href = _json[Type::href].getOr<URL>(unknown::asURL);
	type = _json[Type::type].getOr<String>(unknown::asString);
}
