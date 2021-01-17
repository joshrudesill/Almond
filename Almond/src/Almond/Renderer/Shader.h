#pragma once
#include <string>

namespace Almond {
	class Shader 
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragementSrc);
		~Shader();

		void bind() const;
		void unbind() const;

	private:
		uint32_t m_RendererID;
	};
}
