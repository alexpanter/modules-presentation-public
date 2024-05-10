import mathlib;
import <iostream>;

int main()
{
	std::cout << (sum(1,2,3)) << '\n'; // <-- ERROR: Will not compile!
	std::cout << (sum_wrapper(1,2,3,-5)) << '\n';
	return 0;
}
