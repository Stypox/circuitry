#include "debug.hpp"

#include <iostream>

namespace util {

void debug(Gravity gravity, const std::string& source, const std::string& message) {
	static std::string lastSource, lastMessage;
	if (source == lastSource && message == lastMessage)
		return;
	lastSource = source;
	lastMessage = message;
	
	if (gravity >= /*Arguments::verbosity*/Gravity::info) {
		switch (gravity) {
			case Gravity::info:
				std::clog << "[" << source << "] info: " << message << "\n";
				break;
			case Gravity::warning:
				std::clog << "[" << source << "] warning: " << message << "\n";
				break;
			case Gravity::error:
				std::cerr << "[" << source << "] ERROR: " << message << "\n";
				break;
			case Gravity::critical:
				std::cerr << "[" << source << "] CRITICAL: " << message << "\n";
				break;
		}
	}
}

} // namespace util