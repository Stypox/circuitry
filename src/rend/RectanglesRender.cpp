#include "RectanglesRender.hpp"

#include "Renderer.hpp"
#include "util/debug.hpp"

using namespace stypox::gl;

namespace rend {

stypox::StockContainer<RectangleData> RectangleRender::rectangles{};
std::unique_ptr<stypox::gl::Shader> RectangleRender::shader = nullptr;
std::unique_ptr<stypox::gl::Texture2D> RectangleRender::texture = nullptr;
GLuint RectangleRender::vao{}, RectangleRender::verticesVbo{}, RectangleRender::verticesEbo{}, RectangleRender::dataVbo{};

void RectangleRender::init() {
	shader.reset(new Shader{"./src/rend/shader/rectangles.vert", "./src/rend/shader/rectangles.frag"});
	texture.reset(new Texture2D{Renderer::rectanglesTexturePos, "rectangles.png", GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST});


	if (shader->errors())
		util::debug(util::Gravity::error, "Rectangles", shader->debugInfo("rend::Rectangles::m_shader"));
	else
		util::debug(util::Gravity::info, "Rectangles", shader->debugInfo("rend::Rectangles::m_shader"));
	if (texture->fileOk())
		util::debug(util::Gravity::info, "Rectangles", texture->debugInfo("rend::Rectangles::m_texture"));
	else
		util::debug(util::Gravity::error, "Rectangles", texture->debugInfo("rend::Rectangles::m_texture"));


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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &verticesVbo);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &verticesEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verticesEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &dataVbo);

	GLint positionLoc = shader->getAttribLocation("position");
	GLint texturePositionLoc = shader->getAttribLocation("texturePosition");
	GLint offsetLoc = shader->getAttribLocation("offset");
	GLint sizeLoc = shader->getAttribLocation("size");
	GLint textureOffsetLoc = shader->getAttribLocation("textureOffset");
	GLint textureWidthLoc = shader->getAttribLocation("textureWidth");

	constexpr size_t vertexStride = 4 * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);

	glEnableVertexAttribArray(positionLoc);
	glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, vertexStride, (void*)0);
	glVertexAttribDivisor(positionLoc, 0);
	glEnableVertexAttribArray(texturePositionLoc);
	glVertexAttribPointer(texturePositionLoc, 2, GL_FLOAT, GL_FALSE, vertexStride, (void*)(2 * sizeof(GLfloat)));
	glVertexAttribDivisor(texturePositionLoc, 0);

	constexpr size_t dataStride = sizeof(RectangleData);
	glBindBuffer(GL_ARRAY_BUFFER, dataVbo);

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

	shader->bind();
	shader->uniform("rectanglesTexture", Renderer::rectanglesTexturePos);
}

void RectangleRender::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
	glBindBuffer(GL_ARRAY_BUFFER, dataVbo);
	glBufferData(GL_ARRAY_BUFFER, rectangles.size()*sizeof(RectangleData), rectangles.data(), GL_STREAM_DRAW);

	glBindVertexArray(vao);
	shader->bind();
	shader->uniform("projection", projectionMatrix);
	shader->uniform("view", viewMatrix);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, rectangles.size());
}

} // namespace rend