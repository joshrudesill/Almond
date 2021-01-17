#pragma once
#include "Almond/Renderer/VertexArray.h"

namespace Almond {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return m_VertexBuffers; };
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffers() const { return m_IndexBuffers; };

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffers;
		uint32_t m_RendererID;
	};

}