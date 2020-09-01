#include "espch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>
namespace ES
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ES::ShaderDataType::Float:  return GL_FLOAT;
        case ES::ShaderDataType::Float2: return GL_FLOAT;
        case ES::ShaderDataType::Float3: return GL_FLOAT;
        case ES::ShaderDataType::Float4: return GL_FLOAT;
        case ES::ShaderDataType::Mat3:	 return GL_FLOAT;
        case ES::ShaderDataType::Mat4:	 return GL_FLOAT;
        case ES::ShaderDataType::Int:	 return GL_INT;
        case ES::ShaderDataType::Int2:	 return GL_INT;
        case ES::ShaderDataType::Int3:	 return GL_INT;
        case ES::ShaderDataType::Int4:	 return GL_INT;
        case ES::ShaderDataType::Bool:	 return GL_BOOL;
        }
        ES_CORE_ASSERT(false, "Unkown ShaderDataType!");
        return 0;
    }
    OpenGLVertexArray::OpenGLVertexArray()
    {
        ES_PROFILE_FUNCTION();
        glCreateVertexArrays(1, &m_RendererID);

    }
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        ES_PROFILE_FUNCTION();
        glDeleteVertexArrays(1, &m_RendererID);
    }
    void OpenGLVertexArray::Bind() const
    {
        ES_PROFILE_FUNCTION();
        glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::Unbind() const
    {
        ES_PROFILE_FUNCTION();
        glBindVertexArray(0);
    }
    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        ES_PROFILE_FUNCTION();
        ES_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();
        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), 
                element.Normalized ? GL_TRUE : GL_FALSE, 
                layout.GetStride(), 
                (const void*)element.Offset);
            index++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }
    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        ES_PROFILE_FUNCTION();
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}
