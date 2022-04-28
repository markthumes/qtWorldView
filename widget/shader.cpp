#include <shader.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath){

	/* Read Data */
	File vfile(vertexPath);
	File ffile(fragmentPath);
	if( geometryPath != NULL ){
		File gfile(geometryPath);
		gfile.read();
		m_gShaderCode = new char[gfile.size() + 1];
		m_gShaderCode[gfile.size()] = 0;
		memcpy(m_gShaderCode, &gfile, gfile.size());
		gfile.close();
	}
	vfile.read();
	ffile.read();
	m_vShaderCode = new char[vfile.size() + 1];
	m_fShaderCode = new char[ffile.size() + 1];
	m_vShaderCode[vfile.size()] = 0;
	m_fShaderCode[ffile.size()] = 0;
	memcpy(m_vShaderCode, &vfile, vfile.size());
	memcpy(m_fShaderCode, &ffile, ffile.size());
	vfile.close();
	ffile.close();

	/* Compile Shader */
	// 2. compile shaders
	unsigned int vertex, fragment, geometry;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &m_vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		fprintf(stderr, "Error::Shader::Vertex::\
				Compilation Failed: %s\n",
				infoLog);
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &m_fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		fprintf(stderr, "Error::Shader::Fragment::\
				Compilation Failed: %s\n",
				infoLog);
	}

	if( geometryPath != NULL ){
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &m_gShaderCode, 
				NULL);
		glCompileShader(geometry);
		glGetShaderiv(geometry, GL_COMPILE_STATUS, 
				&success);
	}
	if( geometryPath != NULL && !success)
	{
		glGetShaderInfoLog(geometry, 512, NULL, 
				infoLog);
		fprintf(stderr, "Error::Shader::Geometry::\
				Compilation Failed: %s\n",
				infoLog);
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vertex);
	if( geometryPath != NULL )
		glAttachShader(m_id, geometry);
	glAttachShader(m_id, fragment);
	glLinkProgram(m_id);
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(m_id, 512, NULL, infoLog);
		fprintf(stderr,"Error::Shader::Linking Failed%s\n",
				infoLog);
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if( geometryPath != NULL ) glDeleteShader(geometry);
}
void Shader::use(){
	glUseProgram(m_id);
}
void Shader::setBool(const char* name, bool value)
{
	glUniform1i(
			glGetUniformLocation(
				m_id, 
				name
				), 
			(int)value);
}
void Shader::setInt(const char* name, int value)
{
	glUniform1i(
			glGetUniformLocation(
				m_id, 
				name
				), 
			value);
}
void Shader::setFloat(const char* name, float value)
{
	glUniform1f(
			glGetUniformLocation(
				m_id, 
				name
				), 
			value);
}
void Shader::setVec3(const char* name, const glm::vec3 value){
	glUniform3fv(
			glGetUniformLocation(
				m_id,
				name
				),
			1,
			&value[0]
		    );
}
void Shader::setMat4(const char* name, glm::mat4 ref){
	glUniformMatrix4fv(
			glGetUniformLocation(
				m_id,
				name
				),
			1,
			GL_FALSE,
			&ref[0][0]
			//glm::value_ptr(ref)
			);
}
Shader::~Shader(){
	delete [] m_vShaderCode;
	delete [] m_fShaderCode;
	delete [] m_gShaderCode;
}
unsigned int Shader::getID(){
	return m_id;
}
void Shader::setID(unsigned int id){
	m_id = id;
}
