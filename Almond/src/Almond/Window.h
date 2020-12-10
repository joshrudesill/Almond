#pragma once
#include "hzpch.h"
#include "Almond/Core.h"
#include "Almond/Events/Event.h"

namespace Almond {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Almond Engine",
					unsigned int width = 1280,
					unsigned int height = 720) 
			: Title(title), Width(width), Height(height) {}
	};

	class ALMOND_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window(){}
		virtual void onUpdate() = 0;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;
		static Window* create(const WindowProps& props = WindowProps());
	};
}