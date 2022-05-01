#include <QMouseEvent>
#include <QPainter>

#include "worldwidget.h"

WorldWidget::WorldWidget(QWidget *parent){
	setParent(parent);
	setWindowTitle(tr("World Widget"));
}

void WorldWidget::mousePressEvent(QMouseEvent *e){
	mousePressPosition = QVector2D(e->position());
}

void WorldWidget::wheelEvent(QWheelEvent *e){
//	if( !isActive() ) ignore();
//	else camera.m_zoom -= e.pixelDelta().y();
	camera.m_zoom -= e->pixelDelta().y() / 100.0f;
	update();
/*
	QMatrix4x4 modelMat;;
	modelMat.translate(0.0, 0.0, -5.0);
	modelMat.rotate(rotation);
	qreal aspect = qreal(m_width) / qreal(m_height ? m_height : 1);
	const qreal zNear = 3.0, zFar = 7.0;
	projMat.setToIdentity();
	projMat.perspective(camera.m_zoom, aspect, zNear, zFar);
	m_shader.setUniformValue("mvp_matrix", projMat * modelMat);
*/
}

void WorldWidget::mouseReleaseEvent(QMouseEvent *e){
	QVector2D diff = QVector2D(e->position()) - mousePressPosition;
	QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
	qreal acc = diff.length() / 100.0;
	rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
	angularSpeed += acc;
}
void WorldWidget::timerEvent(QTimerEvent *)
{
	angularSpeed *= 0.99;
	if (angularSpeed < 0.01) {
		angularSpeed = 0.0;
	} else {
		rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
		update();
	}
}

void WorldWidget::initShaders(){
	if (!m_shader.addShaderFromSourceFile(QOpenGLShader::Vertex, "/home/humes/src/qtWorldView/demo/vshader.glsl")) close();
	if (!m_shader.addShaderFromSourceFile(QOpenGLShader::Fragment, "/home/humes/src/qtWorldView/demo/fshader.glsl")) close();
	if (!m_shader.link()) close();
	if (!m_shader.bind()) close();
}
void WorldWidget::initializeGL(){
	initializeOpenGLFunctions();
	glClearColor( 	m_background.redF(),
			m_background.greenF(),
			m_background.blueF(),
			m_background.alphaF()
	);


	initShaders();
	initTextures();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	sphere = new Sphere(20,20,1);
	//sphere->setWireFrame();

	m_timer.start(12, this);
}
void WorldWidget::resizeGL(int w, int h){
	qreal aspect = qreal(w) / qreal(h ? h : 1);
	const qreal zNear = 3.0, zFar = 7.0;
	projMat.setToIdentity();
	projMat.perspective(camera.m_zoom, aspect, zNear, zFar);
	m_width = w;
	m_height = h;
}
void WorldWidget::paintGL(){
	fprintf(stdout, "painting\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	texture->bind();

	QMatrix4x4 modelMat;
	modelMat.translate(0.0, 0.0, -5.0);
	modelMat.rotate(rotation);

	qreal aspect = qreal(m_width) / qreal(m_height ? m_height : 1);
	const qreal zNear = 3.0, zFar = 7.0;
	projMat.setToIdentity();
	projMat.perspective(camera.m_zoom, aspect, zNear, zFar);

	for( int i = 0; i < 4; i++ ){
		for( int j = 0; j < 4; j++ ){
			fprintf(stdout, "[%10.5f]", projMat.column(i)[j]);
		}
		fprintf(stdout, "\n");
	}

	m_shader.setUniformValue("model", modelMat);
	m_shader.setUniformValue("view", camera.getViewMat());
	m_shader.setUniformValue("projection", projMat);

	m_shader.setUniformValue("texture", 0);
	sphere->draw(&m_shader);
}

void WorldWidget::initTextures()
{
	texture = new QOpenGLTexture(QImage("/home/humes/src/qtWorldView/demo/earth.jpg"));
	texture->setMinificationFilter(QOpenGLTexture::Nearest);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture->setWrapMode(QOpenGLTexture::Repeat);
}
