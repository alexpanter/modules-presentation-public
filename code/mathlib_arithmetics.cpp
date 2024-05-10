export module mathlib :arithmetics;

template<class... Ts>
int sum(const Ts&&... ts)
{
	return (ts + ...); // C++17 fold expression
}
