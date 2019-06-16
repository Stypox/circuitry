#include "Arguments.hpp"

using namespace util;

namespace app {

	Gravity Arguments::verbosity = Gravity::info;
	uint16_t Arguments::width = 480;
	uint16_t Arguments::height = 480;

	std::filesystem::path Arguments::rectanglesVertexShader = "src/rend/shader/rectangles.vert",
		Arguments::rectanglesFragmentShader = "src/rend/shader/rectangles.frag",
		Arguments::textureFolder = "res/";

} // namespace app