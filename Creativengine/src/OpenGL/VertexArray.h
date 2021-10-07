#pragma once

#include "VertexBuffer.h"

namespace Creativengine {

	class VertexBufferLayout;

	class VertexArray
	{
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
	};

}