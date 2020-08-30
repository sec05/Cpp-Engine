
#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true, true)
{

}
void Sandbox2D::OnAttach()
{
	m_Woody = ES::Texture2D::Create("assets/textures/woody.png");
}

void Sandbox2D::OnDetach()
{
	ES::Renderer2D::Shutdown();
}
float alpha = 1.0f;
void Sandbox2D::OnUpdate(ES::Timestep ts)
{

	ES_TRACE("{0}", alpha);
	m_CameraController.OnUpdate(ts);
	fps = 1.0f / ts;

	m_CameraController.OnUpdate(ts);

	ES::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	ES::RenderCommand::Clear();
	ES::Renderer2D::BeginScene(m_CameraController.GetCamera());
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	ES::Renderer2D::DrawQaud({ -1.0f,0.0f }, { 1.5f,0.8f }, { 0.2f,0.0f,0.9f,1.0f });
	ES::Renderer2D::DrawQaud({ 1.0f,0.0f }, { 2.0f,1.0f }, { 0.8f,0.6f,0.1f,1.0f });
	
	ES::Renderer2D::DrawQaud({ 0.0f,0.0f,-0.1f }, { 3.0f,3.0f }, m_Woody,0.0f, {1.0f,1.0f,1.0f,alpha});
	ES::Renderer2D::DrawTriangle({ 0.0f,0.0f,0.1f }, { 1.5f,2.0f}, { 0.2,0.8f,0.9f,1.0f });
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

}

void Sandbox2D::OnEvent(ES::Event& e)
{
	m_CameraController.OnEvent(e);
	ES::EventDispatcher dispatcher(e);
	//dispatcher.Dispatch<ES::MouseMovedEvent>(ES_BIND_EVENT_FN(Sandbox2D::MouseMoved));
}
bool Sandbox2D::MouseMoved(ES::Event& e)
{
	ES::MouseMovedEvent mm = (ES::MouseMovedEvent&)e;
	ES_TRACE("Mouse Moved Event: {0},{1}", mm.GetX(), mm.GetY());
	return false;
}
