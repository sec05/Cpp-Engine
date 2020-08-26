#include "espch.h"
#include "OrthographicCameraController.h"
#include "ES/Core/Input.h"
#include "ES/Core/KeyCodes.h"
namespace ES
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio),m_Rotation(rotation), m_Camera(-m_AspectRatio* m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) //aspectratio*zoom gives you x values and zoom is the y value
    {

    }
    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
		if (Input::IsKeyPressed(ES_KEY_W))
		{
			m_CameraPosition.y += m_CameraTransalationSpeed * ts;
		}
		if (Input::IsKeyPressed(ES_KEY_A))
		{
			m_CameraPosition.x -= m_CameraTransalationSpeed * ts;
		}
		if (Input::IsKeyPressed(ES_KEY_S))
		{
			m_CameraPosition.y -= m_CameraTransalationSpeed * ts;
		}
		if (Input::IsKeyPressed(ES_KEY_D))
		{
			m_CameraPosition.x += m_CameraTransalationSpeed * ts;
		}
		if (Input::IsKeyPressed(ES_KEY_R))
		{
			m_CameraPosition.x = 0.0f;
			m_CameraPosition.y = 0.0f;
			m_CameraPosition.z = 0.0f;
			m_CameraRotation = 0.0f;
		}
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(ES_KEY_Q))
			{
				m_CameraRotation += 20.0f * ts;
			}
			if (Input::IsKeyPressed(ES_KEY_E))
			{
				m_CameraRotation -= 20.0f * ts;
			}
		}
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation( m_CameraRotation);
		m_CameraTransalationSpeed = m_ZoomLevel;
    }
    void OrthographicCameraController::OnEvent(Event& e)
    {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ES_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ES_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }
    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.15f, 5.0f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
		m_AspectRatio -= (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}