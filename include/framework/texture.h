#pragma once
#include <string>
#include <glad/glad.h>

class Texture
{
public:
    Texture(const std::string& path, bool flipVertically = true);
    ~Texture();

    void Bind(GLuint unit = 0) const;
    void Unbind() const;

    GLuint GetID() const { return ID; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    GLuint ID;
    int m_width, m_height, m_channels;
};
