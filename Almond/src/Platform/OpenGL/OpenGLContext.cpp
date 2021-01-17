#include "hzpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace Almond {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		AL_CORE_ASSERT(windowHandle, "Handle is null.");
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); 
		AL_CORE_ASSERT(status, "Failed to initialize Glad.");

		AL_CORE_TRACE("***OpenGL Info***");
		AL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		AL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		AL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}