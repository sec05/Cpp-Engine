
#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ES/Platform/OpenGL/OpenGLShader.h"
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}
void Sandbox2D::OnAttach()
{
	m_SquareVA = ES::VertexArray::Create();

	float SQvertices[5 * 4] = {//screen right now is -1 to 1 because there is no projection matrix
		-0.5f, -0.5f, 0.0f,	//bottom left of square is 0,0 top right is 1,1 for tex coords
		 0.5f, -0.5f, 0.0f, 
		 0.5f,  0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f, 

	};
	ES::Ref<ES::VertexBuffer> SquareVB;
	SquareVB.reset(ES::VertexBuffer::Create(SQvertices, sizeof(SQvertices)));
	SquareVB->SetLayout({
		{ES::ShaderDataType::Float3, "a_Position"},
		
		});
	m_SquareVA->AddVertexBuffer(SquareVB);
	uint32_t squareIndicies[6] = { 0,1,2,2,3,0 };//draws 2 triangles so 0,1,2 then 2,3,0 for the different points
	ES::Ref<ES::IndexBuffer> SquareIB;
	SquareIB.reset(ES::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(SquareIB);


	m_Shader = ES::Shader::Create("assets/shaders/FlatColorShader.glsl");


	

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(ES::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	fps = 1.0f / ts;

	m_CameraController.OnUpdate(ts);

	ES::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ES::RenderCommand::Clear();
	ES::Renderer::BeginScene(m_CameraController.GetCamera());
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<ES::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<ES::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);

	ES::Renderer::Submit(m_Shader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

	
	ES::Renderer::EndScene();
;
}

void Sandbox2D::OnImGuiRender() 
{
	ImGui::Begin("System Information");
	ImGui::Text("FPS: %f", floor(fps));
	ImGui::Text("Vendor: %s", m_SystemInfo.GetVendor());
	ImGui::Text("Renderer: %s", m_SystemInfo.GetRenderer());
	ImGui::Text("Version: %s", m_SystemInfo.GetVersion());
	ImGui::End();

	ImGui::Begin("Flat Color Shader");
	ImGui::ColorPicker4("Flat Color Shader Picker", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(ES::Event& e)
{
	m_CameraController.OnEvent(e);
}
