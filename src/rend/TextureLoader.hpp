#ifndef _CIRCUITRY_REND_TEXTURELOADER_HPP_
#define _CIRCUITRY_REND_TEXTURELOADER_HPP_

#include <glad/glad.h>
#include <filesystem>

namespace rend {

class TextureLoader {
	GLuint getTextureId(const std::filesystem::path& image);
};

} // namespace rend

#endif // _CIRCUITRY_REND_TEXTURELOADER_HPP_