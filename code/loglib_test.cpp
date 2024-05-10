import loglib;

#ifdef DISABLE_LOGGING
#error Disable logging macro is exposed!
#endif

struct Spaceship
{
	int missileDamage {0};
	bool hasGravDrive {false};
	double thrusterBoost {0.0};
	std::string name {};
};

std::ostream& operator<<(std::ostream& s, const Spaceship& ship)
{
	return s << "{dam=" << ship.missileDamage
	         << ", gravDrive=" << std::boolalpha << ship.hasGravDrive
	         << ", boost=" << ship.thrusterBoost
	         << ", name=\"" << ship.name
	         << "\"}";
}

int main()
{
	log_trace("Tracing message");
	log_info("Info message");
	log_debug("Debug message");
	log_warn("Warning message");
	log_error("Error message");
	log_fatal("Fatal message");

	log_trace("Tracing message: {}", 5);
	log_trace("Tracing {} messages!", 5);
	log_trace("Tracing message {} {} {}", 5, 5, "hello");

	log_trace("Tracing message {}", 1);
	log_info("Info message {}", 42);
	log_debug("Debug message {}", -5.3);
	log_warn("Warning message {}", "modules are cool");
	log_error("Error message {}", "programming is fun!");
	log_fatal("Fatal message {}", 'G');

	log_trace("Tracing message {} {} {} {}", 5, 5, "hello", 7.4);
	log_info("Info message {} {} {} {}", 5, 5, "hello", 7.4);
	log_debug("Debug message {} {} {} {}", 5, 5, "hello", 7.4);
	log_warn("Warning message {} {} {} {}", 5, 5, "hello", 7.4);
	log_error("Error message {} {} {} {}", 5, 5, "hello", 7.4);
	log_fatal("Fatal message {} {} {} {}", 5, 5, "hello", 7.4);

	log_trace("Trace with two parameters: {}x{}", 1080, 720);

	// NOTE: Without concept, 429 lines of template error in terminal
	Spaceship s{};
	s.missileDamage = 25;
	s.hasGravDrive = true;
	s.thrusterBoost = 579126.0f;
	s.name = "Starfield could have been better!";
	log_warn("Warning: Spaceship preparing for landing: {}", s);

	log_deduction_trace("hello, {}", "world!");
}
