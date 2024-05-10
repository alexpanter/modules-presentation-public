

// disable_lib.cpp
export module disable_lib;
import <iostream>;

#if defined(DLIB_DISABLE_LOG)
constexpr bool bDoStuff = false;
#else
constexpr bool bDoStuff = true;
#endif

export void do_stuff()
{
	if constexpr (bDoStuff)
	{
		std::cout << "stuff" << std::endl;
	}
}
