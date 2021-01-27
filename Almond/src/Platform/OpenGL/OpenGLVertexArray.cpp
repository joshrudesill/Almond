#include "hzpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Almond {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Almond::ShaderDataType::Float:		return GL_FLOAT;
		case Almond::ShaderDataType::Float2:	return GL_FLOAT;
		case Almond::ShaderDataType::Float3:	return GL_FLOAT;
		case Almond::ShaderDataType::Float4:	return GL_FLOAT;
		case Almond::ShaderDataType::Mat3:		return GL_FLOAT;
		case Almond::ShaderDataType::Mat4:		return GL_FLOAT;
		case Almond::ShaderDataType::Int:		return GL_INT;
		case Almond::ShaderDataType::Int2:		return GL_INT;
		case Almond::ShaderDataType::Int3:		return GL_INT;
		case Almond::ShaderDataType::Int4:		return GL_INT;
		case Almond::ShaderDataType::Bool:		return GL_BOOL;
		}
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& buffer)
	{
		AL_CORE_ASSERT(buffer->getLayout().getElements().size(), "Vertex buffer has no elements");
		glBindVertexArray(m_RendererID);
		buffer->bind();

		
		uint32_t index = 0;
		const auto& layout = buffer->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.getElementCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, buffer->getLayout().getStride(), (const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& buffer)
	{
		glBindVertexArray(m_RendererID);
		buffer->bind();

		m_IndexBuffers = buffer;
	}

}