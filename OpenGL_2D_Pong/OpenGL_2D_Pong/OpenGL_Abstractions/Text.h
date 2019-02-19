#pragma once

#include <glm/vec3.hpp>
#include "Shader.h"
#include <string>
#include <map>



struct glyphData
{
	unsigned int textureID;  // ID handle of the glyph texture
	glm::ivec2	 size;       // Size of glyph
	glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
	unsigned int advance;    // Offset to advance to next glyph
};

class Text
{
public:
	Text(const std::string &fontPath, int fontSize);
	~Text();

	void bind();
	void unbind();

	void renderText(Shader &shader, std::string text, glm::vec2 screenPos, float scale, glm::vec3 color);
private:
	unsigned int vao;
	unsigned int vbo;
	std::map<char, glyphData> characters;
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
};
