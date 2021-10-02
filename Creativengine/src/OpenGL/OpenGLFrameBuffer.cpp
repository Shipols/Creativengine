#include "OpenGLFrameBuffer.h"

#include "Logger/LoggerMacros.h"

OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height)
	: m_Fbo(0)
	, m_TextureId(0)
	, m_RenderbufferId(0)
	, m_Width(width)
	, m_Height(height)
	, m_CCR(1)
	, m_CCG(1)
	, m_CCB(1)
	, m_CCA(1)
{
	glGenFramebuffers(1, &m_Fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);

	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureId, 0);
	
	glGenRenderbuffers(1, &m_RenderbufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferId);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	glDeleteFramebuffers(1, &m_Fbo);
	m_Fbo = 0;
	m_TextureId = 0;
}
