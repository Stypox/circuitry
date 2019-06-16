#ifndef _CIRCUITRY_REND_RECTANGLESRENDER_HPP_
#define _CIRCUITRY_REND_RECTANGLESRENDER_HPP_

#include <stypox/stock_container.hpp>
#include <stypox/gl/shader.hpp>
#include <stypox/gl/texture.hpp>
#include <memory>
#include <glm/mat4x4.hpp>

#include "Rectangle.hpp"

namespace rend {

class RectangleRender {
	friend class Rectangle;
	static stypox::StockContainer<RectangleData> rectangles;

	static std::unique_ptr<stypox::gl::Shader> shader;
	static std::unique_ptr<stypox::gl::Texture2D> texture;

	static GLuint vao, verticesVbo, verticesEbo, dataVbo;

public:
	static void init();
	static void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
};

} // namespace rend

#endif // _CIRCUITRY_REND_RECTANGLESRENDER_HPP_