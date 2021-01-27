#pragma once

namespace Almond {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			:m_Time(time)
		{
		}
		operator float() const { return m_Time; }
		float getSeconds() const { return m_Time; }
		float getMilliseconds() const { return m_Time * 1000.0f; }
		float getFrameRate() const {
			return 1.0f / m_Time;
		}

		
	private:
		float m_Time;
		
	};

}