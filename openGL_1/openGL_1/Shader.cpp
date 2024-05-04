#include "Shader.h"

Shader::Shader(const char* vertex_path, const char* fragment_path)
{

    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_source_file;
    std::ifstream fragment_source_file;

    vertex_source_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_source_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {

        vertex_source_file.open(vertex_path);
        fragment_source_file.open(fragment_path);
        std::stringstream vertex_shader_stream, fragment_shader_stream;

        vertex_shader_stream << vertex_source_file.rdbuf();
        fragment_shader_stream << fragment_source_file.rdbuf();

        vertex_source_file.close();
        fragment_source_file.close();

        vertex_code = vertex_shader_stream.str();
        fragment_code = fragment_shader_stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertex_code.c_str();
    const char* fShaderCode = fragment_code.c_str();

    uint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}