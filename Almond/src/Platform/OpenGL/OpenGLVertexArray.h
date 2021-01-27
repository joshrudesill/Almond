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

		virtual void addVertexBuffer(const Ref<VertexBuffer>& buffer) override;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& buffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const { return m_VertexBuffers; };
		virtual const Ref<IndexBuffer>& getIndexBuffers() const { return m_IndexBuffers; };

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffers;
		uint32_t m_RendererID;
	};

}