#include "ComponentBase.hpp"

namespace game::comp {

void ComponentBase::updateOutputWires() {
	std::vector<bool> inputValues(m_inputWires.size());
	for(int i = 0; i != m_inputWires.size(); ++i) {
		inputValues[i] = m_inputWires[i]->value();
	}

	std::vector<bool> outputValues = getOutputValues(inputValues);
	for(int i = 0; i != m_outputWires.size(); ++i) {
		m_outputWires[i]->setValue(outputValues[i]);
	}
}

} // namespace game::comp