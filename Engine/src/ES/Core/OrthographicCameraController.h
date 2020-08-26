#pragma once
#include "ES/Renderer/OrthographicCamera.h"
#include "ES/Core/Timestep.h"
#include "ES/Events/ApplicationEvent.h"
#include "ES/Events/MouseEvent.h"
namespace ES {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);


		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private: 
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e); 

	private:
		bool m_Rotation;
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		float m_CameraRotation = 0.0f;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraTransalationSpeed = 1.0f;
		float m_CameraRotationSpeed = 1.0f;
		OrthographicCamera m_Camera;
	};
}
