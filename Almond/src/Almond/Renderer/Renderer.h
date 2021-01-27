#pragma once
#include "RenderCommand.h"
#include "Almond/Renderer/OrthographicCamera.h"
#include "Shader.h"

namespace Almond {


	class Renderer
	{
	public:
		static void beginScene(OrthographicCamera& camera);
		static void endScene();
		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 viewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
	
}


