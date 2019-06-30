#include "util/debug.hpp"
#include "rend/RectanglesRender.hpp"
#include "app/Application.hpp"

int main(int argc, char const* argv[]) {
	try {
		app::Application::run();
	} catch (const std::exception& e) {
		util::debug(util::Gravity::critical, "main", e.what());
	}
}