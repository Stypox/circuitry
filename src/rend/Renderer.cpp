#include "Renderer.hpp"

#include "RectanglesRender.hpp"

namespace rend {

void Renderer::init() {
	RectangleRender::init();
}
void Renderer::draw() {
	RectangleRender::draw(glm::mat4{1.0f}, glm::mat4{1.0f});
}

} // namespace rend