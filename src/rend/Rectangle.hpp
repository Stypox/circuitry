#ifndef _CIRCUITRY_REND_RECTANGLE_HPP_
#define _CIRCUITRY_REND_RECTANGLE_HPP_

#include <stypox/stock_container.hpp>
#include <glad/glad.h>

namespace rend {

struct RectangleData {
	GLfloat x, y, w, h,
		textureOffset, textureWidth;
};

struct Rectangle {
	stypox::StockContainer<RectangleData>::handler m_renderData;

	Rectangle(const RectangleData& rectangleData);
};

} // namespace rend

#endif // _CIRCUITRY_REND_RECTANGLE_HPP_