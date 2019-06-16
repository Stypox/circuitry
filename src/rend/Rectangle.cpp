#include "Rectangle.hpp"
#include "RectanglesRender.hpp"

namespace rend {

Rectangle::Rectangle(const RectangleData& rectangleData) :
	m_renderData{RectangleRender::m_rectangles.push(rectangleData)} {}

} // namespace rend