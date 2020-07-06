#pragma once

#include "espch.h"

#include "Engine/Core.h"
#include "Engine/Events/Event.h"
//abstract window class
namespace Engine
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		//default parameters
		WindowProps(const std::string& title = "ES Engine",
					unsigned int width = 1920,
					unsigned int height = 1080)
			: Title(title), Width(width), Height(height)
		{}

	};

	//Interface for a desktop system based window

	class ES_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;//for dealing with events

		virtual ~Window(){}
		
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVsync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};
}