#pragma once
#ifndef _SPOTIFY_UTIL_H_
#define _SPOTIFY_UTIL_H_

namespace Spotify {
	namespace Util {
		namespace Encode {
			inline String urlEncode(const String& str) {
				std::ostringstream oss;
				for (const auto s : str.toUTF8()) {
					if (IsASCII(s)) {
						oss << s;
					}
					else {
						char buf[3] = { 0 };
						sprintf_s(buf, "%02x", uint8_t(s));
						oss << '%' << std::string(buf);
					}
				}
				return Unicode::Widen(oss.str());
			}
		}

		inline String randomString(size_t _size = 20) {
			constexpr const char32_t* element{
				U"1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
			};
			constexpr size_t element_size{ std::char_traits<char32_t>::length(element) };
			String rtn;
			for (size_t i = 0; i < _size; ++i) {
				rtn += element[Random(0ull, element_size - 1ull)];
			}
			return rtn;
		}

		namespace TempFiles {
			constexpr const char32_t* directory_path{ U"./_sys_/" };

			inline void removeAll() {
				for (const auto& path : FileSystem::DirectoryContents(directory_path)) {
					if (path.ends_with(U".temp_")) {
						FileSystem::Remove(path);
					}
				}
			}

			inline FilePath makeUniquePath(size_t _size = 20) {
				return { directory_path + randomString(_size) + U".temp_" };
			}
		}

		inline Error makeError(const String& _where, const String& _message) {
			return Error{ U"{} [{}]"_fmt(_where, _message) };
		}
	}

}

#endif
