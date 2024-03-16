#pragma once

#include <ostream>

namespace ConsoleColor {
	enum class Code {
		BOLD = 1,
		RESET = 0,
		BG_BLUE = 44,
		BG_DEFAULT = 49,
		BG_GREEN = 42,
		BG_RED = 41,
		FG_BLACK = 30,
		FG_BLUE = 34,
		FG_CYAN = 36,
		FG_DARK_GRAY = 90,
		FG_DEFAULT = 39,
		FG_GREEN = 32,
		FG_LIGHT_BLUE = 94,
		FG_LIGHT_CYAN = 96,
		FG_LIGHT_GRAY = 37,
		FG_LIGHT_GREEN = 92,
		FG_LIGHT_MAGENTA = 95,
		FG_LIGHT_RED = 91,
		FG_LIGHT_YELLOW = 93,
		FG_MAGENTA = 35,
		FG_RED = 31,
		FG_WHITE = 97,
		FG_YELLOW = 33,
	};
	class Modifier {
		Code code;
	public:
		Modifier(Code pCode) : code(pCode) {}
		friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
			return os << "\033[" << static_cast<int>(mod.code) << "m";
		}
	};
}

static ConsoleColor::Modifier bold_off(ConsoleColor::Code::RESET);
static ConsoleColor::Modifier bold_on(ConsoleColor::Code::BOLD);
static ConsoleColor::Modifier def(ConsoleColor::Code::FG_DEFAULT);
static ConsoleColor::Modifier red(ConsoleColor::Code::FG_RED);
static ConsoleColor::Modifier green(ConsoleColor::Code::FG_GREEN);
static ConsoleColor::Modifier yellow(ConsoleColor::Code::FG_YELLOW);
static ConsoleColor::Modifier blue(ConsoleColor::Code::FG_BLUE);
static ConsoleColor::Modifier magenta(ConsoleColor::Code::FG_MAGENTA);
static ConsoleColor::Modifier cyan(ConsoleColor::Code::FG_CYAN);
static ConsoleColor::Modifier lightGray(ConsoleColor::Code::FG_LIGHT_GRAY);
static ConsoleColor::Modifier darkGray(ConsoleColor::Code::FG_DARK_GRAY);
static ConsoleColor::Modifier lightRed(ConsoleColor::Code::FG_LIGHT_RED);
static ConsoleColor::Modifier lightGreen(ConsoleColor::Code::FG_LIGHT_GREEN);
static ConsoleColor::Modifier lightYellow(ConsoleColor::Code::FG_LIGHT_YELLOW);
static ConsoleColor::Modifier lightBlue(ConsoleColor::Code::FG_LIGHT_BLUE);
static ConsoleColor::Modifier lightMagenta(ConsoleColor::Code::FG_LIGHT_MAGENTA);
static ConsoleColor::Modifier lightCyan(ConsoleColor::Code::FG_LIGHT_CYAN);