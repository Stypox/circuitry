#ifndef _CIRCUTRY_REND_RENDERER_HPP_
#define _CIRCUTRY_REND_RENDERER_HPP_

#include <glad/glad.h>

namespace rend {

class Renderer {
public:
	static constexpr GLint rectanglesTexturePos = 0;
	
	static void init();
	static void draw();
};

} // namespace rend

#endif // _CIRCUTRY_REND_RENDERER_HPP_