#pragma once
#include "Almond/Renderer/Buffer.h"

namespace Almond {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		virtual ~OpenGLVertexBuffer();
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void setLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& getLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		virtual ~OpenGLIndexBuffer();
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual void bind() const;
		virtual void unbind() const;
		virtual uint32_t getCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}