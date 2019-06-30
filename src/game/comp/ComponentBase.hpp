#ifndef _CIRCUITRY_GAME_COMP_COMPONENTBASE_HPP_
#define _CIRCUITRY_GAME_COMP_COMPONENTBASE_HPP_

#include <memory>
#include "rend/Rectangle.hpp"
#include "Wire.hpp"

namespace game::comp {

class ComponentBase {
	rend::Rectangle m_rectangle;

	// the vectors will be the same throughout the whole life of ComponentBase
	std::vector<std::shared_ptr<Wire>> m_inputWires;
	std::vector<std::shared_ptr<Wire>> m_outputWires;

public:
	ComponentBase(float x, float y);
	virtual ~ComponentBase();

	void updateOutputWires();
	virtual std::vector<bool> getOutputValues(const std::vector<bool>& inputs) = 0;
};

} // namespace game::comp

#endif // _CIRCUITRY_GAME_COMP_COMPONENTBASE_HPP_