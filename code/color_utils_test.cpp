import color_utils;
import <iostream>;

int main()
{
	UColor red {255, 0, 0};
	FColor redf = ConvertColor(red);
	uint8_t red_r = red.r; // <-- ERROR: cstdint not "export-imported"!
	std::cout << red << " => " << redf << std::endl;

	red = {128, 127, 64};
	redf = ConvertColor(red);
	std::cout << red << " => " << redf << std::endl;

	return 0;
}
