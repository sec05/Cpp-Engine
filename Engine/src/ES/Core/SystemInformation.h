#pragma once
#include <gl\GL.h>

namespace ES
{
	class SystemInformation
	{
	public:
		inline auto GetVendor() const { return glGetString(GL_VENDOR); }
		inline auto GetRenderer() const { return glGetString(GL_RENDERER); }
		inline auto GetVersion() const { return glGetString(GL_VERSION); }
	};
}