#ifndef __H_WORLD_H__
#define __H_WORLD_H__

#include "sphere.h"
#include "camera.h"
#include "light.h"

#include <QtUiPlugin/QDesignerExportWidget>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QWidget>
#include <QColor>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>

class QDESIGNER_WIDGET_EXPORT WorldWidget : public QOpenGLWidget, QOpenGLFunctions {

	Q_OBJECT
	Q_PROPERTY(QColor background READ background WRITE setBackground )

public:
	WorldWidget(QWidget *parent = 0);

	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void timerEvent(QTimerEvent *e) override;
	void wheelEvent(QWheelEvent *event) override;

	void resizeGL(int w, int h) override;
	void initializeGL() override;
	void paintGL() override;

	void initShaders();
	void initTextures();

	QColor background() const{ return m_background; }
	void setBackground( QColor c ){
		m_background = c;
		glClearColor( c.redF(), c.greenF(), c.blueF(), c.alphaF() );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}


signals:

protected:
	QColor m_background;

	QBasicTimer m_timer;
	QOpenGLShaderProgram m_shader[2];
	Sphere *sphere = nullptr;
	Sphere *light = nullptr;
	
	QOpenGLTexture *texture = nullptr;

	QMatrix4x4 projMat;

	QVector2D mousePressPosition;
	QVector3D rotationAxis;
	qreal angularSpeed = 0;
	QQuaternion rotation;

	int m_width;
	int m_height;

	float alpha;

	Camera camera;

	QVector<DirLight>   dLights;
	QVector<PointLight> pLights;
};

#endif
