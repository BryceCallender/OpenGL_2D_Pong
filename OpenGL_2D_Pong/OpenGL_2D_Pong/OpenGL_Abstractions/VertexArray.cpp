#include "VertexArray.h"

//Attrib pointer needs index of the attribute, number of things to describe the attribute, type of thing and then if we need to normalize, size in BYTES of stride, offset as a void pointer 

VertexArray::VertexArray() : numAttributes(0)
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

VertexArray::VertexArray(std::vector<VertexArrayAttribute> data) : ID(0)
{
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
	attributes = data;

	for (unsigned int i = 0; i < data.size(); i++)
	{
		glVertexAttribPointer(i, data[i].count, data[i].type, data[i].normalized, data[i].stride * getTypeSize(data[i].type), (void*)(data[i].offset * getTypeSize(data[i].type)));
		glEnableVertexAttribArray(i);
	}
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::bind()
{
	glBindVertexArray(ID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::pushAttribute(VertexArrayAttribute& data)
{
	glVertexAttribPointer(numAttributes, data.count, data.type, data.normalized, data.stride * getTypeSize(data.type), (void*)(data.offset * getTypeSize(data.type)));
	glEnableVertexAttribArray(numAttributes);

	attributes.push_back(data);

	numAttributes++;
}

unsigned int VertexArray::getTypeSize(unsigned int type)
{
	switch (type)
	{
		case GL_FLOAT: return sizeof(GL_FLOAT);
		case GL_UNSIGNED_INT: return sizeof(GL_UNSIGNED_INT);
		case GL_UNSIGNED_BYTE: return sizeof(GL_UNSIGNED_BYTE);
		default: return -1;
	}
}


