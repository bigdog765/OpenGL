#include "Shader.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

ShaderProgramSource ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length);
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader!\n"
                  << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int CreateShader(const std::string& vertexShader,
                          const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

// ---------------- Uniform helpers ----------------

void setBoolShader(unsigned int shaderId, const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
}

void setIntShader(unsigned int shaderId, const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}

void setFloatShader(unsigned int shaderId, const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
}
