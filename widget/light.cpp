#include "light.h"

PointLight::PointLight(
		QVector3D _position,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular,
		float _constant, float _linear, float _quadratic
		){
	position  = _position;
	ambient   = _ambient;
	diffuse   = _diffuse;
	specular  = _specular;
	constant  = _constant;
	linear    = _linear;
	quadratic = _quadratic;
}
/*
PointLight::PointLight( const PointLight &oldLight){
	position  = oldLight.position;
	ambient   = oldLight.ambient;
	diffuse   = oldLight.diffuse;
	specular  = oldLight.specular;
	constant  = oldLight.constant;
	linear    = oldLight.linear;
	quadratic = oldLight.quadratic;
}
*/
void PointLight::setProperties(QOpenGLShaderProgram *s, int i){
	char temp[100];
	sprintf(temp,"%s[%d].position",name,i);
	s->setUniformValue( temp, position );
	sprintf(temp,"%s[%d].ambient",name,i);
	s->setUniformValue( temp, ambient );
	sprintf(temp,"%s[%d].diffuse",name,i);
	s->setUniformValue( temp, diffuse );
	sprintf(temp,"%s[%d].specular",name,i);
	s->setUniformValue( temp, specular );
	sprintf(temp,"%s[%d].constant",name,i);
	s->setUniformValue( temp, constant );
	sprintf(temp,"%s[%d].linear",name,i);
	s->setUniformValue( temp, linear );
	sprintf(temp,"%s[%d].quadratic",name,i);
	s->setUniformValue( temp, quadratic );
}
SpotLight::SpotLight(
		QVector3D _position, QVector3D _direction,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular,
		float _constant, float _linear, float _quadratic,
		float _cutOff, float _outerCutOff
		){
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
}
SpotLight::SpotLight( const SpotLight &oldLight){
	position    = oldLight.position;
	direction   = oldLight.direction;
	ambient     = oldLight.ambient;
	diffuse     = oldLight.diffuse;
	specular    = oldLight.specular;
	constant    = oldLight.constant;
	linear      = oldLight.linear;
	quadratic   = oldLight.quadratic;
	cutOff      = oldLight.cutOff;
	outerCutOff = oldLight.outerCutOff;
}
void SpotLight::setProperties(QOpenGLShaderProgram *s, int i){
	char temp[100];
	sprintf(temp,"%s[%d].direction",name,i);
	s->setUniformValue( temp, direction );
	sprintf(temp,"%s[%d].position",name,i);
	s->setUniformValue( temp, position );
	sprintf(temp,"%s[%d].ambient",name,i);
	s->setUniformValue( temp, ambient );
	sprintf(temp,"%s[%d].diffuse",name,i);
	s->setUniformValue( temp, diffuse );
	sprintf(temp,"%s[%d].specular",name,i);
	s->setUniformValue( temp, specular );
	sprintf(temp,"%s[%d].constant",name,i);
	s->setUniformValue( temp, constant );
	sprintf(temp,"%s[%d].linear",name,i);
	s->setUniformValue( temp, linear );
	sprintf(temp,"%s[%d].quadratic",name,i);
	s->setUniformValue( temp, quadratic );
	sprintf(temp,"%s[%d].cutOff",name,i);
	s->setUniformValue( temp, cutOff );
	sprintf(temp,"%s[%d].outerCutOff",name,i);
	s->setUniformValue( temp, outerCutOff );
}
DirLight::DirLight(
		QVector3D _direction,
		QVector3D _ambient, QVector3D _diffuse, QVector3D _specular
		){
	direction   = _direction;
	ambient     = _ambient;
	diffuse     = _diffuse;
	specular    = _specular;
}
/*
DirLight::DirLight( const DirLight &oldLight){
	direction   = oldLight.direction;
	ambient     = oldLight.ambient;
	diffuse     = oldLight.diffuse;
	specular    = oldLight.specular;
}
*/
void DirLight::setProperties(QOpenGLShaderProgram *s, int i){
	char temp[100];
	sprintf(temp,"%s[%d].direction",name,i);
	s->setUniformValue( temp, direction );
	sprintf(temp,"%s[%d].ambient",name,i);
	s->setUniformValue( temp, ambient );
	sprintf(temp,"%s[%d].diffuse",name,i);
	s->setUniformValue( temp, diffuse );
	sprintf(temp,"%s[%d].specular",name,i);
	s->setUniformValue( temp, specular );
}

