#include "pch.h"

#include "Application.h"
#include "Platform/WindowManager.h"

Application::Application(const std::string& appName) {
	_window = std::make_unique<window::GLWindow>();
	_window->init(1920, 1080, appName);
}

void Application::run() {
	while (_window->isRunning()) { _window->render(); }
}

/*// Resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Application::Application(const std::string& name) {
	Application::Init();
}

bool Application::Init()
{
	if (!glfwInit()) { std::cerr << "Failed to initialize GLFW" << std::endl; return false; }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);

	window = glfwCreateWindow(1920, 1080, "Simulator V0.1", nullptr, nullptr);	// Create window (windowed mode) and its OpenGL context
	if (!window) { std::cerr << "Failed to create GLFW window" << std::endl; return false; }

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cerr << "Failed to initialize GLAD" << std::endl; return false; }

	glEnable(GL_DEPTH_TEST);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();

	windowManager.SetupWindow(window);
	gui = std::make_unique<GUIManager>(&windowManager);
	simulation = std::make_unique<SimulationManager>();

	gui->InitResources();
	simulation->Init();

	return true;
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		//glViewport(0, 0, display_w, display_h);
		
		float ctrlPanelWidth = 400.0f;
		float debugHeight = 300.0f;
		float paddingY = 10.0f;

		// --- Renders simulation first ---
		// Top-right simulation panel
		float simWidth = display_w - ctrlPanelWidth;
		float simHeight = display_h - debugHeight;
		float simX = ctrlPanelWidth;                  // start after control panel
		float simY = display_h - simHeight;           // top-left corner in OpenGL is bottom-left, so shift down

		glViewport(static_cast<int>(simX),
			static_cast<int>(simY),
			static_cast<int>(simWidth),
			static_cast<int>(simHeight));

		glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		simulation->Render(1920, 1080);

		//gui->BeginFrame();
		//gui->DrawPanel();
		//gui->EndFrame();

		glfwSwapBuffers(window);	// Swap front and back buffers
	}
}

void Application::Shutdown() {
	ResourceManager::CleanUp();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(0);
}*/