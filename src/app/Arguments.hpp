#ifndef _CIRCUITRY_APP_ARGUMENTS_HPP_
#define _CIRCUITRY_APP_ARGUMENTS_HPP_

#include <filesystem>
#include "util/debug.hpp"

namespace app {

struct Arguments {
	static util::Gravity verbosity;
	static uint16_t width, height;

	static std::filesystem::path rectanglesVertexShader,
		rectanglesFragmentShader,
		textureFolder;
};

} // namespace app

#endif // _CIRCUITRY_APP_ARGUMENTS_HPP_