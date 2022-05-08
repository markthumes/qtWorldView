#include "light.h"

PointLight::PointLight(
		QVector3D _position,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular,
		float _constant, float _linear, float _quadratic
		):Light(){
	position  = _position;
	ambient   = _ambient;
	diffuse   = _diffuse;
	specular  = _specular;
	constant  = _constant;
	linear    = _linear;
	quadratic = _quadratic;
	type = Point;
	name = "pointLight";
}
void PointLight::setProperties(QOpenGLShaderProgram *s){
	char temp[100];
	sprintf(temp,"pointLight[%d].enable",index);
	s->setUniformValue( temp, m_enabled );
	sprintf(temp,"pointLight[%d].position",index);
	s->setUniformValue( temp, position );
	sprintf(temp,"pointLight[%d].ambient",index);
	s->setUniformValue( temp, ambient );
	sprintf(temp,"pointLight[%d].diffuse",index);
	s->setUniformValue( temp, diffuse );
	sprintf(temp,"pointLight[%d].specular",index);
	s->setUniformValue( temp, specular );
	sprintf(temp,"pointLight[%d].constant",index);
	s->setUniformValue( temp, constant );
	sprintf(temp,"pointLight[%d].linear",index);
	s->setUniformValue( temp, linear );
	sprintf(temp,"pointLight[%d].quadratic",index);
	s->setUniformValue( temp, quadratic );
}
SpotLight::SpotLight(
		QVector3D _position, QVector3D _direction,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular,
		float _constant, float _linear, float _quadratic,
		float _cutOff, float _outerCutOff
		):Light(){
	position    = _position;
	direction   = _direction;
	ambient     = _ambient;
	diffuse     = _diffuse;
	specular    = _specular;
	constant    = _constant;
	linear      = _linear;
	quadratic   = _quadratic;
	cutOff      = _cutOff;
	outerCutOff = _outerCutOff;
	type = Spot;
	name = "spotLight";
}
void SpotLight::setProperties(QOpenGLShaderProgram *s){
	char temp[100];
	sprintf(temp,"spotLight[%d].enable",index);
	s->setUniformValue( temp, m_enabled );
	sprintf(temp,"spotLight[%d].direction",index);
	s->setUniformValue( temp, direction );
	sprintf(temp,"spotLight[%d].position",index);
	s->setUniformValue( temp, position );
	sprintf(temp,"spotLight[%d].ambient",index);
	s->setUniformValue( temp, ambient );
	sprintf(temp,"spotLight[%d].diffuse",index);
	s->setUniformValue( temp, diffuse );
	sprintf(temp,"spotLight[%d].specular",index);
	s->setUniformValue( temp, specular );
	sprintf(temp,"spotLight[%d].constant",index);
	s->setUniformValue( temp, constant );
	sprintf(temp,"spotLight[%d].linear",index);
	s->setUniformValue( temp, linear );
	sprintf(temp,"spotLight[%d].quadratic",index);
	s->setUniformValue( temp, quadratic );
	sprintf(temp,"spotLight[%d].cutOff",index);
	s->setUniformValue( temp, cutOff );
	sprintf(temp,"spotLight[%d].outerCutOff",index);
	s->setUniformValue( temp, outerCutOff );
}
DirLight::DirLight(
		QVector3D _direction,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular
		):Light(){
	direction   = _direction;
	ambient     = _ambient;
	diffuse     = _diffuse;
	specular    = _specular;
	type = Dir;
	name = "dirLight";
}
void DirLight::setProperties(QOpenGLShaderProgram *s){
	char temp[100];
	sprintf(temp,"dirLight[%d].enable",index);
	fprintf(stdout, "%s:%s\n", temp, m_enabled ? "True" : "False");
	s->setUniformValue( temp, m_enabled );
	sprintf(temp,"dirLight[%d].direction",index);
	s->setUniformValue( temp, direction );
	sprintf(temp,"dirLight[%d].ambient",index);
	s->setUniformValue( temp, ambient );
	sprintf(temp,"dirLight[%d].diffuse",index);
	s->setUniformValue( temp, diffuse );
	sprintf(temp,"dirLight[%d].specular",index);
	s->setUniformValue( temp, specular );
}

