#ifndef __OGL_SHADER_H__
#define __OGL_SHADER_H__

#include <GL/glew.h>
#include <GL/gl.h>
#include <file.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = NULL);
	void use();
	void setBool(const char* name, bool value);
	void setInt(const char* name, int value);
	void setFloat(const char* name, float value);
	void setVec3(const char* name, const glm::vec3 value);
	void setMat4(const char* name, glm::mat4 ref);
	~Shader();
	unsigned int getID();
	void setID(unsigned int id);
private:
	unsigned int m_id;
	char* m_vShaderCode;
	char* m_fShaderCode;
	char* m_gShaderCode;
};

#endif
