#ifndef _CIRCUITRY_REND_RECTANGLESRENDER_HPP_
#define _CIRCUITRY_REND_RECTANGLESRENDER_HPP_

#include <stypox/stock_container.hpp>
#include <glm/mat4x4.hpp>

#include "Rectangle.hpp"

namespace rend {

class RectangleRender {
	friend class rend::Rectangle;
	static stypox::StockContainer<RectangleData> rectangles;

public:
	static void init();
	static void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
};

} // namespace rend

#endif // _CIRCUITRY_REND_RECTANGLESRENDER_HPP_