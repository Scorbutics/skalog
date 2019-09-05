#pragma once
#include <ostream>

namespace ska {
	enum EnumColorStream {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		GREY,
		DARKGREY,
		LIGHTBLUE,
		LIGHTGREEN,
		LIGHTCYAN,
		LIGHTRED,
		LIGHTMAGENTA,
		YELLOW,
		WHITE,
		BACKGROUND_BLACK,
		BACKGROUND_BLUE,
		BACKGROUND_GREEN,
		BACKGROUND_CYAN,
		BACKGROUND_RED,
		BACKGROUND_MAGENTA,
		BACKGROUND_YELLOW,
		BACKGROUND_WHITE
	};

	std::ostream& operator<<(std::ostream& stream, const EnumColorStream &);
}
