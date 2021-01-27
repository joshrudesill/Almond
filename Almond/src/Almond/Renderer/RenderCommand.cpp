#include "hzpch.h"
#include "RenderCommand.h"

#include "hzpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"



namespace Almond {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}