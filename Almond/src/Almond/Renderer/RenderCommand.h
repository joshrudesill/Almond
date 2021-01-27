#pragma once
#include "RendererAPI.h"


namespace Almond {

	class RenderCommand
	{
	public:
		inline static void drawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->drawIndexed(vertexArray);
		}
		inline static void clear()
		{
			s_RendererAPI->clear();
		}
		inline static void setClearColor(const glm::vec4& color)
		{
			s_RendererAPI->setClearColor(color);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}