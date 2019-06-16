#include "Application.hpp"

#include <stdexcept>
#include <stypox/gl/texture.hpp>
#include "rend/Renderer.hpp"
#include "util/debug.hpp"
#include "rend/Rectangle.hpp"

namespace app {

GLFWwindow* Application::m_window = nullptr;

void Application::init() {
	// GLFW initialization
	if (int errorCode = glfwInit(); !errorCode)
		throw std::runtime_error{"Unable to initialize glfw, error " + std::to_string(errorCode)};
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// window creation with GLFW
	m_window = glfwCreateWindow(500, 500, "windowTitle", nullptr, nullptr);
	if (m_window == nullptr) {
		glfwTerminate();
		throw std::runtime_error{"Unable to create glfw window."};
	}

	// context settings
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

	// GLAD initialization
	if (int errorCode = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); !errorCode) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
		throw std::runtime_error{"Unable to initialize glad, error " + std::to_string(errorCode)};
	}

	// render engine initialization
	stypox::gl::Texture2D::setDirectory("./res");
	rend::Renderer::init();
}
void Application::loop() {
	glClearColor(0.0625, 0.0625, 0.0625, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	rend::Rectangle rect1{rend::RectangleData{0,0,0.9,0.7,1.0,0.5}};
	rend::Rectangle rect2{rend::RectangleData{0,0.1,0.2,0.2,0.5,0.5}};

	while (!glfwWindowShouldClose(m_window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		if (GLenum e = glGetError(); e) {
			util::debug(util::Gravity::error, "MainLoop", "OpenGL " + std::to_string(e));
		}

		glfwPollEvents();
		rend::Renderer::draw();
		glfwSwapBuffers(m_window);
	}
}

int Application::run() {
	init();
	loop();
	return 0;
}

} // namespace app