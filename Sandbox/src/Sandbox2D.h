#pragma once
#include "Engine.h"
class Sandbox2D : public ES::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(ES::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ES::Event& e) override;
	bool MouseMoved(ES::Event& e);
private:
	ES::OrthographicCameraController m_CameraController;

	ES::Ref<ES::VertexArray> m_SquareVA;
	ES::Ref<ES::Shader> m_Shader;
	ES::Ref<ES::Texture2D> m_Woody;
	float fps;
	ES::SystemInformation m_SystemInfo;
	glm::vec4 m_SquareColor = { 0.1f, 0.3f, 0.9f,1.0f };
	
	
};