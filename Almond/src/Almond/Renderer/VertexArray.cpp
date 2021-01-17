#include "hzpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Almond {

	VertexArray* VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::None:		AL_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}
		AL_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}