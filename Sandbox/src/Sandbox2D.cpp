
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
}

void Sandbox2D::OnDetach()
{
	ES::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(ES::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	fps = 1.0f / ts;

	m_CameraController.OnUpdate(ts);

	ES::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ES::RenderCommand::Clear();
	ES::Renderer2D::BeginScene(m_CameraController.GetCamera());
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	ES::Renderer2D::DrawQaud({ 0.0f,0.0f }, { 1.0f,1.0f }, { 0.8f,0.6f,0.1f,1.0f });
	
	ES::Renderer2D::EndScene();
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
