export module stringlib;

import <string_view>;

export
{
	std::string_view GetWelcome()
	{
		return "Welcome!";
	}

	std::string_view GetGoodbye()
	{
		return "Goodbye!";
	}
}
