#include "hzpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Almond {

	Shader* Shader::create(const std::string& vertexSrc, const std::string& fragementSrc)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::API::None:		AL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragementSrc);
		}
		AL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}