#include <camera.h>

Camera::Camera( QVector3D pos, QVector3D up, float yaw, float pitch  ){
	m_front = QVector3D(0.0, 0.0, -1.0);
	m_movementSpeed = SPEED;
	m_mouseSens = SENS;
	m_zoom = ZOOM;

	m_position = pos;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors();
}


QMatrix4x4 Camera::getViewMat(){
	QMatrix4x4 ret;
	ret.lookAt(m_position, m_position + m_front, m_up);
	return ret;
}
QMatrix4x4 Camera::getViewMat(QVector3D center){
	QMatrix4x4 ret;
	ret.QMatrix4x4::lookAt(m_position, center, m_up);
	return ret;
}

void Camera::processKeyboard(Camera_Movement direction, float dt){
	float vel = m_movementSpeed * dt;
	switch(direction){
		case FORWARD : m_position += m_front * vel; break;
		case BACKWARD: m_position -= m_front * vel; break;
		case LEFT    : m_position -= m_right * vel; break;
		case RIGHT   : m_position += m_right * vel; break;
	}
}
//cpit = constrain pitch
void Camera::processMouse( float xoffset, float yoffset, bool cpit){
	xoffset *= m_mouseSens;
	yoffset *= m_mouseSens;
	m_yaw   += xoffset;
	m_pitch += yoffset;
	if( cpit){
		if(m_pitch > 89.0f) m_pitch = 89.0f;
		if(m_pitch <-89.0f) m_pitch =-89.0f;
	}
	updateCameraVectors();
}
void Camera::processScroll( float yoffset ){
	m_zoom -= (float)yoffset;
	if( m_zoom <  1.0 ) m_zoom =  1.0;
	if( m_zoom > 45.0 ) m_zoom = 45.0;
}

QVector3D& Camera::position(){
	return m_position;
}

void Camera::updateCameraVectors(){
	QVector3D front;
	front.setX(cos( glm::radians(m_yaw)) * cos( glm::radians(m_pitch) ));
	front.setY(sin( glm::radians(m_pitch) ));
	front.setZ(sin( glm::radians(m_yaw)) * cos( glm::radians(m_pitch) ));
	m_front = front.normalized();
	m_right = QVector3D::crossProduct(m_front, m_worldUp).normalized();
	m_up    = QVector3D::crossProduct(m_right, m_front).normalized();
}
