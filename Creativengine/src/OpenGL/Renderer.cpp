#include "Renderer.h"

#include "Logger/LoggerFunctions.h"

namespace Creativengine {

	void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall()
	{
		while (GLenum error = glGetError())
		{
			//const char* formattedError = "[OpenGL Error]" + error;

			PrintCriticalError("An OpenGL error occurred!");

			return false;
		}
		return true;
	}

}