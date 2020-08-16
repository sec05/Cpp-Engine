#pragma once
#include <glm/glm.hpp>
namespace ES
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		
		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }//rotation along the z axis
		
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		
	private:
		void RecalculateViewMatrix();//also coul;d do on update with the event system to respond to mouse movement

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;//matrix of where he camera is 
		glm::mat4 m_ViewProjectionMatrix;//view matrix * projection matrix 
		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };//cordinates of the camera
		float m_Rotation = 0.0f;
	};
}


