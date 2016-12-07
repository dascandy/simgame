#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <glm/glm.hpp>
#include <map>

class ShaderProgram
{
public:
    ShaderProgram(const std::string &filename, const char *vss, const char *fss, const char **invarsX);
    ~ShaderProgram();
    void Set(const char *name, const glm::mat4 &mat);
    void Set(const char *name, const glm::vec2 &vec);
    void SetActive();
    void Set(const char *name, int value);
    void Set(const char *name, unsigned int value);
    void Set(const char *name, float value);
    void Set(const char *name, const glm::vec3 &value);
private:
    std::string filename;
    int getUniformLocation(const char *name);
    int vs, fs;
    int prog;
    std::map<std::string, int> uniforms;
};

#endif

