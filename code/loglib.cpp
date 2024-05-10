module;

// -- internal compiler error --
//#include <spdlog/sinks/stdout_color_sinks.h>

//#include <fmt/core.h>
#include <sstream>

export module loglib;

export import <iostream>;
export import <string_view>;
export import <string>;
export import <source_location>;

// Use integer 1-3 for different tests!
#define TEST_NUM 3

#ifdef DISABLE_LOGGING
constexpr bool should_log = false;
#else
constexpr bool should_log = true;
#endif

// Colors found in a comment here:
// https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/

// --- FOREGROUND COLORS ---
constexpr std::string_view fgBlack{ "\u001b[30m" };
constexpr std::string_view fgRed{ "\u001b[31m" };
constexpr std::string_view fgGreen{ "\u001b[32m" };
constexpr std::string_view fgYellow{ "\u001b[33m" };
constexpr std::string_view fgBlue{ "\u001b[34m" };
constexpr std::string_view fgMagenta{ "\u001b[35m" };
constexpr std::string_view fgCyan{ "\u001b[36m" };
export inline const std::string_view fgWhite{ "\u001b[37m" };


// --- BACKGROUND COLORS ---
constexpr std::string_view bgBlack{ "\u001b[40m" };
constexpr std::string_view bgRed{ "\u001b[41m" };
constexpr std::string_view bgGreen{ "\u001b[42m" };
constexpr std::string_view bgYello{ "\u001b[43m" };
constexpr std::string_view bgBlue{ "\u001b[44m" };
constexpr std::string_view bgMagenta{ "\u001b[45m" };
constexpr std::string_view bgCyan{ "\u001b[46m" };
constexpr std::string_view bgWhite{ "\u001b[47m" };

// --- CONTROL ---
inline constexpr std::string_view reset{ "\u001b[0m" };

struct ColoredOutput
{
	std::string_view text;
	std::string_view fgColor;
	std::string_view bgColor;
};

std::ostream& operator<<(std::ostream& stream, const ColoredOutput&& out)
{
	return stream << out.fgColor << out.bgColor << out.text << reset;
}

enum class LogLevel { trace, info, debug, warn, error, fatal };

void loglevel_color_apply(LogLevel level)
{
	switch (level)
	{
	case LogLevel::trace:
		std::cout << fgWhite; return;
	case LogLevel::info:
		std::cout << fgGreen; return;
	case LogLevel::debug:
		std::cout << fgCyan; return;
	case LogLevel::warn:
		std::cout << fgYellow; return;
	case LogLevel::error:
		std::cout << fgRed; return;
	case LogLevel::fatal:
		std::cout << fgWhite << bgRed; return;
	default:
		return;
	}
}

void loglevel_color_reset()
{
	std::cout << reset;
}

// ====================== //
// === TEST 1: Simple === //
// ====================== //

#if TEST_NUM == 1
export void log_trace(std::string_view msg)
{
	std::cout << fgWhite << msg << reset << '\n';
}

export void log_info(std::string_view msg)
{
	std::cout << fgGreen << msg << reset << '\n';
}

export void log_debug(std::string_view msg)
{
	std::cout << fgCyan << msg << reset << '\n';
}

export void log_warn(std::string_view msg)
{
	std::cout << fgYellow << msg << reset << '\n';
}

export void log_error(std::string_view msg)
{
	std::cout << fgRed << msg << reset << '\n';
}

export void log_fatal(std::string_view msg)
{
	std::cout << fgWhite << bgRed << msg << reset << '\n';
}
#endif

// ============================ //
// === TEST 2: Disable test === //
// ============================ //

#if TEST_NUM == 2
export void log_trace(std::string_view msg)
{
	if constexpr (!should_log) return;
	std::cout << fgWhite << msg << reset << '\n';
}

export void log_info(std::string_view msg)
{
	if constexpr (!should_log) return;
	std::cout << fgGreen << msg << reset << '\n';
}

export void log_debug(std::string_view msg)
{
	if constexpr (!should_log) return;
	std::cout << fgCyan << msg << reset << '\n';
}

export void log_warn(std::string_view msg)
{
	if constexpr (!should_log) return;
	std::cout << fgYellow << msg << reset << '\n';
}

export void log_error(std::string_view msg)
{
	if constexpr (!should_log) return;
	std::cout << fgRed << msg << reset << '\n';
}

export void log_fatal(std::string_view msg)
{
	if constexpr (!should_log) return;
	std::cout << fgWhite << bgRed << msg << reset << '\n';
}
#endif

// ==================================== //
// === TEST 3: Templated formatting === //
// ==================================== //

#if TEST_NUM == 3
// export template<typename Arg, typenam>
// void simple_format(std::string_view msg, Arg&& arg)
// {
// 	while (msg.length > 0)
// 	{

// 	}
// }

class str_view
{
public:
	str_view(const std::string& str) {
		ref = &str;
		begin = 0;
		end = str.size();
	}

	bool starts_with(const std::string& str)
	{
		unsigned int len = str.size();
		for (unsigned int i = 0; i < len; i++)
		{
			unsigned int addi = begin + i;
			if (addi >= end || str[i] != (*ref)[addi]) return false;
		}
		return true;
	}

	void remove_prefix(unsigned int amount)
	{
		begin += amount; // overflow not important here!
		if (begin > end) { begin = end; }
	}

	bool empty()
	{
		return begin >= end || (*ref).empty();
	}

	char front()
	{
		return (begin >= end) ? '\0' : (*ref)[begin];
	}

private:
	friend std::ostream& operator<<(std::ostream& s, str_view& view);
	std::string const* ref = nullptr;
	unsigned int begin = 0;
	unsigned int end = 0;
};

std::ostream& operator<<(std::ostream& s, str_view& view)
{
	for (unsigned int i = view.begin; i < view.end; i++)
	{
		s << (*(view.ref))[i];
	}
	return s;
}


#define FMT_FORWARD(args) std::forward<decltype(args)>(args)

template <typename T>
class is_streamable
{
    template <typename U> // must be template to get SFINAE fall-through...
    static auto test(const U* u) -> decltype(std::cout << *u);

    static auto test(...)        -> std::false_type;

 public:
    static constexpr bool value = !std::is_same_v<decltype(test((T*)0)), std::false_type>;
};

template<typename A>
concept IsStreamable = is_streamable<A>::value;

template<typename Arg>
void fmt_log_only_arg(Arg arg) // &&
{
	std::cout << arg;
}

template<typename A>
requires IsStreamable<A>
void fmt_log_arg(str_view& view, A a) // &&
{
	while (!view.empty())
	{
		if (view.starts_with("{}"))
		{
			fmt_log_only_arg(a);
			view.remove_prefix(2);
			return;
		}
		else
		{
			std::cout << view.front();
			view.remove_prefix(1);
		}
	}
}

template<class A, class B, class ...C>
void fmt_log_arg(str_view view, A a, B b, C... c)
{
	while (!view.empty())
	{
		if (view.starts_with("{}"))
		{
			fmt_log_arg<A>(view, a);
			return fmt_log_arg<B, C...>(view, b, c...);
		}
		else
		{
			std::cout << view.front();
			view.remove_prefix(1);
		}
	}
}

// No parameters -> no auto templates
void log(const std::string& msg, LogLevel logLevel)
{
	loglevel_color_apply(logLevel);
	std::cout << msg;
	loglevel_color_reset();
	std::cout << '\n';
}

export void log_trace(const std::string& msg) { log(msg, LogLevel::trace); }
export void log_info (const std::string& msg) { log(msg, LogLevel::info);  }
export void log_debug(const std::string& msg) { log(msg, LogLevel::debug); }
export void log_warn (const std::string& msg) { log(msg, LogLevel::warn);  }
export void log_error(const std::string& msg) { log(msg, LogLevel::error); }
export void log_fatal(const std::string& msg) { log(msg, LogLevel::fatal); }

// Single template parameter, or final recursed variadic template parameter
template<typename A>
void log(const std::string& msg, LogLevel logLevel, A a)
{
	str_view view(msg);
	if (view.empty())
	{
		return;
	}

	loglevel_color_apply(logLevel);
	fmt_log_arg<A>(view, a);
	if (!view.empty())
	{
		std::cout << view;
	}
	loglevel_color_reset();
	std::cout << '\n';
}

export template<class A>
void log_trace(const std::string& msg, A a)
{
	log(msg, LogLevel::trace, a);
}
export template<class A>
void log_info(const std::string& msg, A a)
{
	log(msg, LogLevel::info, a);
}
export template<class A>
void log_debug(const std::string& msg, A a)
{
	log(msg, LogLevel::debug, a);
}
export template<class A>
void log_warn(const std::string& msg, A a)
{
	log(msg, LogLevel::warn, a);
}
export template<class A>
void log_error(const std::string& msg, A a)
{
	log(msg, LogLevel::error, a);
}
export template<class A>
void log_fatal(const std::string& msg, A a)
{
	log(msg, LogLevel::fatal, a);
}

// Full variadic template expansion for multiple template parameters
template<typename A, typename B, typename ...C>
void log(const std::string& msg, LogLevel logLevel, A a, B b, C... c)
{
	str_view view(msg);
	if (view.empty())
	{
		return;
	}

	loglevel_color_apply(logLevel);
	fmt_log_arg<A, B, C...>(view, a, b, c...);
	loglevel_color_reset();
	std::cout << '\n';
}

export template<typename A, typename B, typename ...C>
void log_trace(const std::string& msg, A a, B b, C... c)
{
	log(msg, LogLevel::trace, a, b, c...);
}
export template<typename A, typename B, typename ...C>
void log_info(const std::string& msg, A a, B b, C... c)
{
	log(msg, LogLevel::info, a, b, c...);
}
export template<typename A, typename B, typename ...C>
void log_debug(const std::string& msg, A a, B b, C... c)
{
	log(msg, LogLevel::debug, a, b, c...);
}
export template<typename A, typename B, typename ...C>
void log_warn(const std::string& msg, A a, B b, C... c)
{
	log(msg, LogLevel::warn, a, b, c...);
}
export template<typename A, typename B, typename ...C>
void log_error(const std::string& msg, A a, B b, C... c)
{
	log(msg, LogLevel::error, a, b, c...);
}
export template<typename A, typename B, typename ...C>
void log_fatal(const std::string& msg, A a, B b, C... c)
{
	log(msg, LogLevel::fatal, a, b, c...);
}

#endif


//
// Experiment with deduction guides for inserting std::source_location
// into logging functions.
//

using SL = std::source_location;

void print_source_location(const SL& sl)
{
	std::cout << '[' << sl.function_name() << "] ";
}

// Adapted function from above, to also print std::source_location.
template<typename A>
void log(const SL& sl, const std::string& msg, LogLevel logLevel, A a)
{
	str_view view(msg);
	if (view.empty())
	{
		return;
	}

	loglevel_color_apply(logLevel);
	print_source_location(sl);
	fmt_log_arg<A>(view, a);
	if (!view.empty())
	{
		std::cout << view;
	}
	loglevel_color_reset();
	std::cout << '\n';
}

template<typename A, typename B, typename ...C>
void log(const SL& sl, const std::string& msg, LogLevel logLevel, A a, B b, C... c)
{
	str_view view(msg);
	if (view.empty())
	{
		return;
	}

	loglevel_color_apply(logLevel);
	print_source_location(sl);
	fmt_log_arg<A, B, C...>(view, a, b, c...);
	loglevel_color_reset();
	std::cout << '\n';
}

export template<typename... Ts>
struct log_deduction_trace
{
	log_deduction_trace(const std::string& msg, Ts&&... ts, const SL& loc = SL::current())
	{
		log(loc, msg, LogLevel::trace, ts...);
	}
};


export template<typename... Ts>
log_deduction_trace(const std::string& msg, Ts&&... ts) -> log_deduction_trace<Ts...>;

