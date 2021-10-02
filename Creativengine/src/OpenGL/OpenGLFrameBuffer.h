#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLFrameBuffer
{
public:
	
	OpenGLFrameBuffer(uint32_t width, uint32_t height);
	~OpenGLFrameBuffer();

	inline uint32_t GetFbo() const { return m_Fbo; }
	inline uint32_t GetTextureId() const { return m_TextureId; }
	inline uint32_t GetRenderbufferId() const { return m_RenderbufferId; }
	inline void GetSize(uint32_t& w, uint32_t& h) { w = m_Width; h = m_Height; }
	inline void SetClearColor(float r, float g, float b, float a) { m_CCR = r; m_CCG = g; m_CCB = b; m_CCA = a; }
	inline void SetClearColor(float& r, float& g, float& b, float& a) { m_CCR = r; m_CCG = g; m_CCB = b; m_CCA = a; }

private:

	uint32_t m_Fbo;
	uint32_t m_TextureId;
	uint32_t m_RenderbufferId;

	uint32_t m_Width, m_Height;
	float m_CCR, m_CCG, m_CCB, m_CCA;
};

