#ifndef _CIRCUITRY_APP_APPLICATION_HPP_
#define _CIRCUITRY_APP_APPLICATION_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace app {

class Application {
	static GLFWwindow* window;

	static void init();
	static void loop();
public:
	static int run();
};

} // namespace app

#endif // _CIRCUITRY_APP_APPLICATION_HPP_