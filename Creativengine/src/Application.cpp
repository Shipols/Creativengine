#include "Logger/LoggerFunctions.h"

#include "LibraryIncludes.h"

#include "Imgui/docking/imgui.h"
#include "Imgui/docking/imgui_impl_glfw.h"
#include "Imgui/docking/imgui_impl_opengl3.h"

#include "ImGui/ImGuiDockspace.h"
#include "ImGui/ImGuiWindows.h"
#include "ImGui/ImGuiStyle.h"

#include "OpenGL/Renderer.h"

#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

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
			PrintError("Failed to compile shader!");
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLCall(unsigned int program = glCreateProgram());
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		return program;
	}

	__declspec(dllexport) int Run()
	{
		
		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit()) {
			PrintCriticalError("Error initializing GLFW!");
		
		}
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(1080, 600, "Creativengine", NULL, NULL);
		
		glfwMakeContextCurrent(window);
		
		if (glewInit() != GLEW_OK) {
			PrintCriticalError("Error initializing GLEW!");

		}
		else {
			PrintWarning("Creativengine loaded successfully!");
		}
		
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

		IndexBuffer ib(indices, 6);

		ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
		unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
		GLCall(glUseProgram(shader));

		const char* openGLversion = "OpenGL Version: 4.1 (Compatibility Profile) Mesa 20.2.0-devel (git-bced9b46e7)";

		PrintInfo(openGLversion);

		GLCall(int location = glGetUniformLocation(shader, "u_Color"));

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
		ImGui::StyleColorsDark();
		
		SetImGuiStyle();

		ImVec4 skyColor = ImVec4(0.0f, 0.2f, 0.4f, 1.0f);
		
		#pragma region ImGui Windows

		PropertiesWindow propertiesWindow;
		ObjectsWindow objectsWindow;
		WorldSettingsWindow worldSettingsWindow(skyColor);
		AssetViewerWindow assetViewerWindow;

		#pragma endregion
		
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			GLCall(glUseProgram(shader));
			
			GLCall(glUniform4f(location, 1.0f, 1.0f, 0.5f, 1.0f));

			GLCall(glBindVertexArray(vao));
			ib.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			//GLCall(glClearColor(skyColor.x, skyColor.y, skyColor.z, skyColor.w));

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ShowImGuiDockSpace(window);

			#pragma region ImGui Windows Rendering

			objectsWindow.Render();
			propertiesWindow.Render();
			worldSettingsWindow.Render();
			assetViewerWindow.Render();

			#pragma endregion

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));

			/* Poll for and process events */
			GLCall(glfwPollEvents());

			glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {

				glViewport(0, 0, width, height);

			});
		}

		glDeleteProgram(shader);

		glfwTerminate();
		return 0;
	}


}