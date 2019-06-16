#include "Renderer.hpp"

#include "RectanglesRender.hpp"
#include "util/resources.hpp"

namespace rend {

glm::mat4 Renderer::m_projectionMatrix{1.0f}, 
	Renderer::m_viewMatrix{1.0f};
GLfloat Renderer::m_zoom{1.0f};

void Renderer::updateScreenSize(int width, int height) {
	GLfloat ratio = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
	GLfloat zoom = m_zoom * util::baseScreenZoom / static_cast<GLfloat>(width);

	m_projectionMatrix[0][0] = zoom;
	m_projectionMatrix[1][1] = ratio * zoom;
}
void Renderer::moveCameraTo(float x, float y) {
	m_viewMatrix[3][0] = -x;
	m_viewMatrix[3][1] = -y;
}
void Renderer::setZoom(float zoom) {
	m_zoom = zoom;
}
void Renderer::scaleZoomBy(float scale) {
	m_zoom *= scale;
}

void Renderer::init() {
	RectangleRender::init();
}
void Renderer::draw() {
	RectangleRender::draw(m_projectionMatrix, m_viewMatrix);
}

} // namespace rend