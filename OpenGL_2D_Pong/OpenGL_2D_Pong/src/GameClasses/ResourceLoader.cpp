#include "ResourceLoader.h"

ResourceLoader*  ResourceLoader::instance = nullptr;
std::map<std::string, Texture> ResourceLoader::textures;
std::map<std::string, Shader>  ResourceLoader::shaders;

ResourceLoader::ResourceLoader()
{
	instance = this;
}

ResourceLoader::~ResourceLoader()
{
}

void ResourceLoader::loadShader(const char* name, Shader& shader)
{
	shaders.insert(std::make_pair(name, shader));
}

void ResourceLoader::loadTexture(const char* name, const char* path)
{
	Texture texture = loadTextureFromFile(path);
	textures.insert(std::make_pair(name, texture));
}

Shader ResourceLoader::getShader(const char* name)
{
	return shaders[name];
}

Texture ResourceLoader::getTexture(const char* name)
{
	return textures[name];
}

void ResourceLoader::clearResources()
{
	for (auto iter : shaders)
	{
		glDeleteProgram(iter.second.ID);
	}
	for (auto iter : textures)
	{
		unsigned int id = iter.second.getID();
		glDeleteTextures(1,&id);
	}
}

Shader ResourceLoader::loadShaderFromFile(const char* file)
{
	Shader shader(file);
	return shader;
}

Texture ResourceLoader::loadTextureFromFile(const char *file)
{
	// Create Texture object
	Texture texture(file);
	return texture;
}
