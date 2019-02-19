#pragma once

#include <string>
#include <map>
#include "Shader.h"
#include "Texture.h"

class ResourceLoader
{
public:
	~ResourceLoader();

	static void loadShader(const char* name, Shader& shader);
	static Shader getShader(const char* name);

	static void loadTexture(const char* name, const char* path);
	static Texture getTexture(const char* name);

	static std::map<std::string, Texture> textures;
	static std::map<std::string, Shader> shaders;

	static void clearResources();
	static inline ResourceLoader& getInstance() { return *instance; }
private:
	ResourceLoader();
	static Shader loadShaderFromFile(const char *file);
	static Texture loadTextureFromFile(const char *file);
	static ResourceLoader *instance;
};

