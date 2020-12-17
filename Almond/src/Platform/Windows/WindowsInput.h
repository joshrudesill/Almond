#pragma once

#include "Almond/Input.h"


namespace Almond {

	class WindowsInput : public Input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> getMousePositionImpl() override;
	};

}