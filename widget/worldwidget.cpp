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
	const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
	projection.setToIdentity();
	projection.perspective(fov, aspect, zNear, zFar);
}
void WorldWidget::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	texture->bind();
	QMatrix4x4 matrix;
	matrix.translate(0.0, 0.0, -5.0);
	matrix.rotate(rotation);
	m_shader.setUniformValue("mvp_matrix", projection * matrix);
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
