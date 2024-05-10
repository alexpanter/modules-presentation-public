module color_utils;

std::ostream& operator<<(std::ostream& os, const FColor& fc)
{
	return os << '{' << fc.r << ',' << fc.g << ',' << fc.b << '}';
}

std::ostream& operator<<(std::ostream& os, const UColor& uc)
{
	return os << '{' << (int)uc.r << ',' << (int)uc.g << ',' << (int)uc.b << '}';
}

FColor ConvertColor(const UColor& uc)
{
	constexpr float scale = 1.0f / 255.0f;

	return {
		static_cast<float>(uc.r) * scale,
		static_cast<float>(uc.g) * scale,
		static_cast<float>(uc.b) * scale
	};
}
