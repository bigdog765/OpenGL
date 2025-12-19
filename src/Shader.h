#pragma once

#include <string>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

// Shader creation
ShaderProgramSource ParseShader(const std::string& filePath);
unsigned int CompileShader(unsigned int type, const std::string& source);
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

// Uniform helpers
void setBoolShader(unsigned int shaderId, const std::string& name, bool value);
void setIntShader(unsigned int shaderId, const std::string& name, int value);
void setFloatShader(unsigned int shaderId, const std::string& name, float value);

