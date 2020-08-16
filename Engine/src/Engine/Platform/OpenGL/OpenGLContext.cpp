#include "espch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Engine/ImGui/ImGuiLayer.h"
namespace Engine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ES_CORE_ASSERT(windowHandle, "Window handle is null");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		
		ES_CORE_ASSERT(status, "Failed to initialize Glad!");
		ES_CORE_INFO("---------- OpenGL Info ----------");
		ES_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		ES_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		ES_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
		ES_CORE_INFO("---------------------------------");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
