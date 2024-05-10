export module color_utils;

export import <cstdint>; // TODO: Also export it later!
import <iostream>;

export struct FColor { float r; float g; float b; };
export struct UColor { uint8_t r; uint8_t g; uint8_t b; };

export std::ostream& operator<<(std::ostream& os, const FColor& fc);
export std::ostream& operator<<(std::ostream& os, const UColor& uc);

export
{
	/**
	 * @brief Convert a UColor to an FColor by scaling to normalized range.
	 */
	FColor ConvertColor(const UColor& uc);
}
