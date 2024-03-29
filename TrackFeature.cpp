#include"TrackFeature.h"

#include"common.h"
#include"Key.h"
#include"Mode.h"

void Spotify::TrackFeature::set(const JSON& _json) {
	if (!_json.isObject()) {
		throw Util::makeError(U"Spotify::TrackFeature::[[private]]set", U"json file is not object");
	}
	constexpr double default_value{ 0.0 };
	id = _json[Type::id].getString();
	acousticness = _json[Type::acousticness].getOr<double>(default_value);
	danceability = _json[Type::danceability].getOr<double>(default_value);
	energy = _json[Type::energy].getOr<double>(default_value);
	instrumentalness = _json[Type::energy].getOr<double>(default_value);
	liveness = _json[Type::liveness].getOr<double>(default_value);
	loudness = _json[Type::loudness].getOr<double>(default_value);
	speechiness = _json[Type::speechiness].getOr<double>(default_value);
	tempo = _json[Type::tempo].getOr<double>(default_value);
	time_signature = _json[Type::time_signature].getOr<double>(default_value);
	valence = _json[Type::valence].getOr<double>(default_value);
	duration_ms = static_cast<MicrosecondsF>(_json[Type::duration_ms].getOr<long double>(0.0));
	key = static_cast<Key>(_json[Type::key].getOr<int>(-1));
	mode = static_cast<Mode>(_json[Type::mode].getOr<int>(1));
}
