#pragma once
#include "Almond/Renderer/Buffer.h"
#include <memory>

namespace Almond {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer( const Ref<VertexBuffer>& buffer) = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffers() const = 0;
		static VertexArray* create();
	};

}