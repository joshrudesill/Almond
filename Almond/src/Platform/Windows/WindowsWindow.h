#pragma once
#include "Almond/Window.h"
#include <GLFW/glfw3.h>


namespace Almond {
	
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;
		inline unsigned int getWidth() const override { return m_Data.Width; }
		inline unsigned int getHeight() const override { return m_Data.Height; }

		inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;

		};
		WindowData m_Data;
	};
}