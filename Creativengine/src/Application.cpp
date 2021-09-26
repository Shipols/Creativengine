#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logger/LoggerMacros.h"

namespace Creativengine {

	static unsigned int CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			LOGGER_CRITICALERROR("Failed to compile shader!");
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		return program;
	}

	__declspec(dllexport) int Run(void)
	{
		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit()) {
			LOGGER_CRITICALERROR("Error initializing GLFW!");
		
		}
		
		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(1080, 600, "Creativengine", NULL, NULL);
		
		glfwMakeContextCurrent(window);
		
		if (glewInit() != GLEW_OK) {
			LOGGER_CRITICALERROR("Error initializing GLEW!");

		}
		else {
			LOGGER_INFO("Creativengine loaded successfully!");
		}
		
		
		
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		float positions[6] = {
			-0.5f, -0.5f,
			 0.0f,  0.5f,
			 0.5f, -0.5f
		};

		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		std::string vertexShader =
			"#version 330 core\n"
			"\n"
			"layout(location = 0) in vec4 position;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = position;\n"
			"}\n";

		std::string fragmentShader =
			"#version 330 core\n"
			"\n"
			"layout(location = 0) out vec4 color;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	color = vec4(0.8, 0.9, 0.4, 1.0);\n"
			"}\n";

		unsigned int shader = CreateShader(vertexShader, fragmentShader);
		glUseProgram(shader);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glClearColor(0.0f, 0.3f, 0.4f, 1.0f);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();

			glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {

				glViewport(0, 0, width, height);

			});
		}

		glDeleteProgram(shader);

		glfwTerminate();
		return 0;
	}

}