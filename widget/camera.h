#ifndef __OGL_CAMERA_H__
#define __OGL_CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <QMatrix4x4>
#include <vector>

enum Camera_Movement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW	  = -90.0;
const float PITCH =   0.0;
const float SPEED =   5.0;
const float SENS  =   0.1;
const float ZOOM  =  45.0;

class Camera{
public:
	QVector3D m_position;
	QVector3D m_front;
	QVector3D m_up;
	QVector3D m_right;
	QVector3D m_worldUp;

	float m_yaw;
	float m_pitch;

	float m_movementSpeed;
	float m_mouseSens;
	float m_zoom;

	Camera( 	QVector3D pos =QVector3D(0.0,0.0,0.0), 
			QVector3D up = QVector3D(0.0,1.0,0.0),
			float yaw = YAW,
			float pitch = PITCH);
	QMatrix4x4 getViewMat();
	QMatrix4x4 getViewMat(QVector3D center);
	void processKeyboard(Camera_Movement direction, float dt);
	//cpit = constrain pitch
	void processMouse( float xoffset, float yoffset, bool cpit = true);
	void processScroll( float yoffset );
	QVector3D& position();
protected:
	void updateCameraVectors();
};

#endif
