#include "ShaderProgram.h"
#include <GLAD/glad.h>

static inline void compileShader(const std::string &filename, int prog, int &shader, const char **source, int type)
{
    shader = glCreateShader(type);
    glAttachShader(prog, shader);

    glShaderSource(shader, 1, (const char **)source, NULL);
    glCompileShader(shader);
    int ok = true;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        int length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char buffer[1024];
        glGetShaderInfoLog(shader, length, NULL, buffer);
        buffer[length] = 0;
        fprintf(stderr, "ERROR:\n%s\n", buffer);
        throw 42;
    }
}

ShaderProgram::ShaderProgram(const std::string &filename, const char *vss, const char *fss, const char **invarsX)
: filename(filename)
, vs(0)
, fs(0)
, prog(glCreateProgram())
{
    compileShader(filename, prog, vs, &vss, GL_VERTEX_SHADER);
    compileShader(filename, prog, fs, &fss, GL_FRAGMENT_SHADER);

    int invarcount = 0;
    while (invarsX[invarcount]) invarcount++;
    for (int i = 0; i < invarcount; i++)
    {
        glBindAttribLocation(prog, i, invarsX[i]);
    }

    int ok = false;
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        int length = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &length);
        std::string errors;
        errors.reserve(length);
        glGetProgramInfoLog(prog, length, NULL, &errors[0]);
        fprintf(stderr, "ERROR:\n%s\n", errors.c_str());
        throw 42;
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteShader(this->vs);
    glDeleteShader(this->fs);
    glDeleteProgram(this->prog);
}

static int usedProg = 0;

void ShaderProgram::Set(const char *name, const glm::mat4 &mat)
{
    int uniform = getUniformLocation(name);
    if (uniform == -1) return;

    glUniformMatrix4fv(uniform, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::Set(const char *name, const glm::vec2 &vec)
{
    int uniform = getUniformLocation(name);
    if (uniform == -1) return;

    glUniform2f(uniform, vec.x, vec.y);
}

void ShaderProgram::Set(const char *name, int value)
{
    int uniform = getUniformLocation(name);
    if (uniform == -1) return;

    glUniform1i(uniform, value);
}

void ShaderProgram::Set(const char *name, unsigned int value)
{
    int uniform = getUniformLocation(name);
    if (uniform == -1) return;

    glUniform1ui(uniform, value);
}

void ShaderProgram::Set(const char *name, float value)
{
    int uniform = getUniformLocation(name);
    if (uniform == -1) return;

    glUniform1f(uniform, value);
}

void ShaderProgram::Set(const char *name, const glm::vec3 &value)
{
    int uniform = getUniformLocation(name);
    if (uniform == -1) return;

    glUniform3f(uniform, value.x, value.y, value.z);
}

void ShaderProgram::SetActive() 
{
    usedProg = prog;
    glUseProgram(prog); 
}

int ShaderProgram::getUniformLocation(const char *name) {
    std::map<std::string, int>::iterator it = uniforms.find(name);
    if (it != uniforms.end()) return it->second;
    int value = uniforms[name] = glGetUniformLocation(prog, name);
    return value;
}


