#ifndef _CIRCUTRY_REND_RENDERER_HPP_
#define _CIRCUTRY_REND_RENDERER_HPP_

#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace rend {

class Renderer {
	static glm::mat4 m_projectionMatrix, m_viewMatrix;
	static GLfloat m_zoom;

public:
	static constexpr GLint rectanglesTexturePos = 0;

	static void updateScreenSize(int width, int height);
	static void moveCameraTo(float x, float y);
	static void setZoom(float zoom);
	static void scaleZoomBy(float scale);
	
	static void init();
	static void draw();
};

} // namespace rend

#endif // _CIRCUTRY_REND_RENDERER_HPP_