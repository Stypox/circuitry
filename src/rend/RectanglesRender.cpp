#include "RectanglesRender.hpp"

#include "Renderer.hpp"
#include "util/debug.hpp"

using namespace stypox::gl;

namespace rend {

stypox::StockContainer<RectangleData> RectangleRender::m_rectangles{};
std::unique_ptr<stypox::gl::Shader> RectangleRender::m_shader = nullptr;
std::unique_ptr<stypox::gl::Texture2D> RectangleRender::m_texture = nullptr;
GLuint RectangleRender::m_vao{}, RectangleRender::m_verticesVbo{}, RectangleRender::m_verticesEbo{}, RectangleRender::m_dataVbo{};

void RectangleRender::init() {
	m_shader.reset(new Shader{"./src/rend/shader/rectangles.vert", "./src/rend/shader/rectangles.frag"});
	m_texture.reset(new Texture2D{Renderer::rectanglesTexturePos, "rectangles.png", GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST});


	if (m_shader->errors())
		util::debug(util::Gravity::error, "Rectangles", m_shader->debugInfo("rend::Rectangles::m_shader"));
	else
		util::debug(util::Gravity::info, "Rectangles", m_shader->debugInfo("rend::Rectangles::m_shader"));
	if (m_texture->fileOk())
		util::debug(util::Gravity::info, "Rectangles", m_texture->debugInfo("rend::Rectangles::m_texture"));
	else
		util::debug(util::Gravity::error, "Rectangles", m_texture->debugInfo("rend::Rectangles::m_texture"));


	constexpr std::array<GLfloat, 16> vertices {
		-1.0f, +1.0f, +0.0f, +0.0f, // Top-left
		+1.0f, +1.0f, +1.0f, +0.0f, // Top-right
		+1.0f, -1.0f, +1.0f, +1.0f, // Bottom-right
		-1.0f, -1.0f, +0.0f, +1.0f, // Bottom-left
	};
	constexpr std::array<GLuint, 6> indices {
		0, 1, 2,
		2, 3, 0,
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_verticesVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_verticesVbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_verticesEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_verticesEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_dataVbo);

	GLint positionLoc = m_shader->getAttribLocation("position");
	GLint texturePositionLoc = m_shader->getAttribLocation("texturePosition");
	GLint offsetLoc = m_shader->getAttribLocation("offset");
	GLint sizeLoc = m_shader->getAttribLocation("size");
	GLint textureOffsetLoc = m_shader->getAttribLocation("textureOffset");
	GLint textureWidthLoc = m_shader->getAttribLocation("textureWidth");

	constexpr size_t vertexStride = 4 * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, m_verticesVbo);

	glEnableVertexAttribArray(positionLoc);
	glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, vertexStride, (void*)0);
	glVertexAttribDivisor(positionLoc, 0);
	glEnableVertexAttribArray(texturePositionLoc);
	glVertexAttribPointer(texturePositionLoc, 2, GL_FLOAT, GL_FALSE, vertexStride, (void*)(2 * sizeof(GLfloat)));
	glVertexAttribDivisor(texturePositionLoc, 0);

	constexpr size_t dataStride = sizeof(RectangleData);
	glBindBuffer(GL_ARRAY_BUFFER, m_dataVbo);

	glEnableVertexAttribArray(offsetLoc);
	glVertexAttribPointer(offsetLoc, 2, GL_FLOAT, GL_FALSE, dataStride, (void*)0);
	glVertexAttribDivisor(offsetLoc, 1);
	glEnableVertexAttribArray(sizeLoc);
	glVertexAttribPointer(sizeLoc, 2, GL_FLOAT, GL_FALSE, dataStride, (void*)(2 * sizeof(GLfloat)));
	glVertexAttribDivisor(sizeLoc, 1);
	glEnableVertexAttribArray(textureOffsetLoc);
	glVertexAttribPointer(textureOffsetLoc, 1, GL_FLOAT, GL_FALSE, dataStride, (void*)(4 * sizeof(GLfloat)));
	glVertexAttribDivisor(textureOffsetLoc, 1);
	glEnableVertexAttribArray(textureWidthLoc);
	glVertexAttribPointer(textureWidthLoc, 1, GL_FLOAT, GL_FALSE, dataStride, (void*)(5 * sizeof(GLfloat)));
	glVertexAttribDivisor(textureWidthLoc, 1);

	m_shader->bind();
	m_shader->uniform("rectanglesTexture", Renderer::rectanglesTexturePos);
}

void RectangleRender::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
	glBindBuffer(GL_ARRAY_BUFFER, m_dataVbo);
	glBufferData(GL_ARRAY_BUFFER, m_rectangles.size()*sizeof(RectangleData), m_rectangles.data(), GL_STREAM_DRAW);

	glBindVertexArray(m_vao);
	m_shader->bind();
	m_shader->uniform("projection", projectionMatrix);
	m_shader->uniform("view", viewMatrix);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_rectangles.size());
}

} // namespace rend