#include"Track.h"

#include"common.h"

void Spotify::Track::set(const JSON& _json) {
	if (!_json.isObject()) {
		throw Util::makeError(U"Spotify::Track::[[private]]set", U"json is not object");
	}
	TrackSimple::set(_json);
	album.set(_json[Type::album]);
	popularity = _json[Type::popularity].getOr<uint8>(unknown::asUint);
}
