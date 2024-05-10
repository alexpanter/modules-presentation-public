module;

#include <utility>

export module mathlib;

export import :arithmetics;
//import <utility>;

export
{
	template<class... Ts>
	int sum_wrapper(const Ts&&... ts)
	{
		return sum(std::forward<const Ts>(ts)...);
	}
}
