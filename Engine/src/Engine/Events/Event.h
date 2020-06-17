#pragma once

#include "Engine/Core.h"
#include "espch.h"


namespace Engine {
	//currently events block meaning it must immediately dealt with 
	//should get it to be buffered
	enum class EventType//event types
	{
		None =0,
		WindowClose,WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCategory//categories for the types
	{
		None = 0,
		EventCategoryApplication = BIT(0),//defined in core
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};
	//need the static function to get the initial event type, need the virtual function to get the specific type
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
			virtual EventType GetEventType() const override{return GetStaticType();}\
			virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	class ES_API Event //base event class
	{
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;
	};
	
	
	
	class EventDispatcher//deals with gotten event
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)//receives event as a reference 
			: m_Event(event)
		{

		}
		template<typename T>
		bool Dispatch(EventFn<T> func)//takes event and then a function 
		{
			if (m_Event.GetEventType() == T::GetStaticType()) {//checks if event matches the type and the dispatches it to the correct class
				m_Event.m_handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
		
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)//exists for logging library to log events.
	{
		return os << e.ToString();
	}
}