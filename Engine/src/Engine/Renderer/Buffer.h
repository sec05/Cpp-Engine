#pragma once
namespace Engine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer(){}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* verticies, uint32_t size);//equivelant of a constructor

	};
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static IndexBuffer* Create(uint32_t* indicies, uint32_t count);
		virtual uint32_t GetCount() const = 0;
	};
}