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
	shader.reset(new Shader{"./src/rend/shader/rectangles.vert", "./src/rend/shader/rectangles.vert"});
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
	glGenBuffers(1, &verticesVbo);
	glGenBuffers(1, &verticesEbo);
	glGenBuffers(1, &dataVbo);

	glBindVertexArray(vao);	

	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verticesEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);


	constexpr size_t strideVertices = 4 * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
	GLint positionIndex = shader->getAttribLocation("position");
	glEnableVertexAttribArray(positionIndex);
	glVertexAttribPointer(positionIndex, 2, GL_FLOAT, GL_FALSE, strideVertices, (void*)0);
	glVertexAttribDivisor(positionIndex, 0);
	GLint texturePositionIndex = shader->getAttribLocation("texturePosition");
	glEnableVertexAttribArray(texturePositionIndex);
	glVertexAttribPointer(texturePositionIndex, 2, GL_FLOAT, GL_FALSE, strideVertices, (void*)2);
	glVertexAttribDivisor(texturePositionIndex, 0);

	constexpr size_t strideData = sizeof(RectangleData);
	glBindBuffer(GL_ARRAY_BUFFER, dataVbo);
	GLint offsetIndex = shader->getAttribLocation("offset");
	glEnableVertexAttribArray(offsetIndex);
	glVertexAttribPointer(offsetIndex, 2, GL_FLOAT, GL_FALSE, strideData, (void*)0);
	glVertexAttribDivisor(offsetIndex, 0);
	GLint sizeIndex = shader->getAttribLocation("size");
	glEnableVertexAttribArray(sizeIndex);
	glVertexAttribPointer(sizeIndex, 2, GL_FLOAT, GL_FALSE, strideData, (void*)2);
	glVertexAttribDivisor(sizeIndex, 0);
	GLint textureOffsetIndex = shader->getAttribLocation("textureOffset");
	glEnableVertexAttribArray(textureOffsetIndex);
	glVertexAttribPointer(textureOffsetIndex, 1, GL_FLOAT, GL_FALSE, strideData, (void*)4);
	glVertexAttribDivisor(textureOffsetIndex, 0);
	GLint textureWidthIndex = shader->getAttribLocation("textureWidth");
	glEnableVertexAttribArray(textureWidthIndex);
	glVertexAttribPointer(textureWidthIndex, 1, GL_FLOAT, GL_FALSE, strideData, (void*)5);
	glVertexAttribDivisor(textureWidthIndex, 0);
}

} // namespace rend