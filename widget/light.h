#ifndef __light_h__
#define __light_h__

#include <QVector3D>
#include <QOpenGLShaderProgram>


class Light{
public:
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
};

class PointLight : public Light{
public:
	PointLight(
		QVector3D _position,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular,
		float _constant, float _linear, float _quadratic
		);
//	PointLight( const PointLight &oldLight);
	const char* name = "pointlight";
	void setProperties(QOpenGLShaderProgram *s, int i);
};

class SpotLight : public Light{
public:
	SpotLight(
		QVector3D _position, QVector3D _direction,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular,
		float _constant, float _linear, float _quadratic,
		float _cutOff, float outerCutOff
		);
	SpotLight( const SpotLight &oldLight);
	const char* name = "spotlight";
	void setProperties(QOpenGLShaderProgram *s, int i);
};

class DirLight : public Light{
public:
	DirLight(
		QVector3D _direction,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular
		);
//	DirLight( const DirLight &oldLight);
	const char* name = "dirlight";
	void setProperties(QOpenGLShaderProgram *s, int i);
};

#endif
