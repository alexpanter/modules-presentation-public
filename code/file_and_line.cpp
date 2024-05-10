export module fileandline;

import <iostream>;
import <source_location>;
import <string>;


export
{
	void log(
		std::string message,
		const std::source_location& location = std::source_location::current())
	{
		std::cout << "log: \"" << message << "\", info:"
		          << location.file_name() << ':' << location.line() << ':'
		          << location.function_name() << std::endl;
	}
}
