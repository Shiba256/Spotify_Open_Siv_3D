#include"Album.h"

#include"common.h"

void Spotify::Album::set(const JSON& _json) {
	if (!_json.isObject()) {
		throw Util::makeError(U"Spotify::Album::[[private]]set", U"json is not object");
	}
	for (const auto& artist : _json[Type::artists]) {
		artists << ArtistSimple{ artist.value };
	}
	id = _json[Type::id].getOr<String>(unknown::asString);
	name = _json[Type::name].getOr<String>(unknown::asString);
	total_tracks = _json[Type::total_tracks].getOr<uint32>(unknown::asUint);
	for (const auto& url : _json[Type::images]) {
		img_url << url.value[Type::url].getOr<String>(unknown::asString);
	}

	const auto&& temp = _json[Type::album_type].getOr<String>(unknown::asString);
	if (temp == U"album") {
		album_type = AlbumType::album;
	}
	else if (temp == U"single") {
		album_type = AlbumType::single;
	}
	else if (temp == U"compilation") {
		album_type = AlbumType::compilation;
	}
	else {
		album_type = AlbumType::none;
	}

	const auto&& date = _json[Type::release_date].getOr<String>(unknown::asString);
	const auto&& param = date.split(U'-');

	auto pop_front_0 = [&param](size_t index)->String {
		auto str = param.fetch(index, U"-1");
		while (str.front() == U'0') {
			str.pop_front();
		}
		return str;
		};

	release_date.year = Parse<int32>(pop_front_0(0));
	release_date.month = Parse<int32>(pop_front_0(1));
	release_date.day = Parse<int32>(pop_front_0(2));

	type = _json[Type::type].getOr<String>(unknown::asString);
	href = _json[Type::href].getOr<String>(unknown::asString);
}

Array<Texture> Spotify::Album::getImage() {
	Array<Texture> rtn;
	for (const auto& url : img_url) {
		const FilePath path{ Util::TempFiles::makeUniquePath()};
		if (!SimpleHTTP::Save(url, path)) {
			throw Util::makeError(U"Spotify::Artist::getImage", U"[HTTP Save failed]");
		}
		rtn << Texture{ path };
	}
	return rtn;

}

