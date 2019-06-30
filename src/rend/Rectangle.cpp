#include "Rectangle.hpp"
#include "RectanglesRender.hpp"

namespace rend {

Rectangle::Rectangle(const RectangleData& rectangleData) :
	renderData{RectangleRender::m_rectangles.push(rectangleData)} {}

} // namespace rend