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
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBufferLayout.h"
#include "OpenGL/Shader.h"

namespace Creativengine {

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

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		const char* openGLversion = "OpenGL Version: 4.1 (Compatibility Profile) Mesa 20.2.0-devel (git-bced9b46e7)";
		PrintInfo(openGLversion);

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

		glViewport(120, 200, 1080 - 200, 600 - 200);
		
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Bind();

			shader.SetUniform4f("u_Color", 1.0f, 1.0f, 0.5f, 1.0f);

			GLCall(glBindVertexArray(vao));
			ib.Bind();
			va.Bind();

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

				glViewport(120, 200, width - 200, height - 200);

			});
		}

		glfwTerminate();
		return 0;
	}


}