#ifndef __light_h__
#define __light_h__

#include <QVector3D>
#include <QOpenGLShaderProgram>


class Light{
public:
	Light(){
		m_enabled = true;
	}
	enum Type{
		Point, Spot, Dir
	};
	QVector3D position;
	QVector3D direction;
	QVector3D ambient;
	QVector3D diffuse;
	QVector3D specular;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	const char* name;
	Type type;
	int index;
	void enable( QOpenGLShaderProgram *s, bool state=true ){ 
		m_enabled = state; 
		char uniform[100];
		sprintf(uniform, "%s[%d].enable", name, index);
		fprintf(stdout, "%s:%s\n", uniform, state ? "True" : "False");
		s->bind();
		s->setUniformValue(uniform, state);
	}
	void disable(QOpenGLShaderProgram *s, bool state=false){ enable(s,state); }
	bool isDisabled(){ return !m_enabled; }
	bool isEnabled(){  return  m_enabled; }
	virtual void setProperties( __attribute__((unused))QOpenGLShaderProgram *s){
		fprintf(stdout, "OVERRIDE!\n");
	}
/*
	virtual void setProperties(QOpenGLShaderProgram *s,int i);
*/
protected:
	bool m_enabled;
};

class PointLight : public Light{
public:
	PointLight(
		QVector3D _position,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular,
		float _constant, float _linear, float _quadratic
		);
	void setProperties(QOpenGLShaderProgram *s) override;
};

class SpotLight : public Light{
public:
	SpotLight(
		QVector3D _position, QVector3D _direction,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular,
		float _constant, float _linear, float _quadratic,
		float _cutOff, float outerCutOff
		);
	void setProperties(QOpenGLShaderProgram *s) override;
};

class DirLight : public Light{
public:
	DirLight(
		QVector3D _direction,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular
		);
	void setProperties(QOpenGLShaderProgram *s) override;
};

#endif
