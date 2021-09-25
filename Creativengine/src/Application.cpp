//#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logger/LoggerMacros.h"

namespace Creativengine {

	__declspec(dllexport) int Run(void)
	{
		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
			LOGGER_CRITICALERROR("Error initializing GLFW!");

		//if (glewInit() != GLEW_OK)
			//LOGGER_CRITICALERROR("Error initializing GLEW!");

		LOGGER_WARNING("Creativengine loaded successfully!");

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(1080, 600, "Creativengine", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f( 0.0f,  0.5f);
			glVertex2f( 0.5f, -0.5f);
			glEnd();

			glClearColor(0.0f, 0.3f, 0.4f, 1.0f);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();

			glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {

				glViewport(0, 0, width, height);

			});
		}

		glfwTerminate();
		return 0;
	}

}