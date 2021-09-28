#include "Logger/LoggerMacros.h"

#include "LibraryIncludes.h"

namespace Creativengine {

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	static ShaderProgramSource ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

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

		ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
		unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
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