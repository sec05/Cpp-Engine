#include "espch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "ES/ImGui/ImGuiLayer.h"
namespace ES
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
#ifdef ES_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		ES_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Engine requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
