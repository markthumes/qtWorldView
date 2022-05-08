#include <QMouseEvent>
#include <QPainter>

#include "worldwidget.h"

WorldWidget::WorldWidget(QWidget *parent){
	setParent(parent);
	setFocusPolicy(Qt::StrongFocus);
	setWindowTitle(tr("World Widget"));
	m_drag = false;
        m_firstMouse = false;
	rotateMode = false;
	m_spaceLock = false;
}

WorldWidget::~WorldWidget(){
	delete sphere;
	delete texture;
}

void WorldWidget::keyPressEvent( QKeyEvent *event ){
	QKeyEvent *e = event;
	e->accept();
	     if(e->key()==Qt::Key_W    )camera.processKeyboard(FORWARD, dt);
	else if(e->key()==Qt::Key_Up   )camera.processKeyboard(FORWARD, dt);
	else if(e->key()==Qt::Key_A    )camera.processKeyboard(LEFT,    dt);
	else if(e->key()==Qt::Key_Left )camera.processKeyboard(LEFT,    dt);
	else if(e->key()==Qt::Key_D    )camera.processKeyboard(RIGHT,   dt);
	else if(e->key()==Qt::Key_Right)camera.processKeyboard(RIGHT,   dt);
	else if(e->key()==Qt::Key_S    )camera.processKeyboard(BACKWARD,dt);
	else if(e->key()==Qt::Key_Down )camera.processKeyboard(BACKWARD,dt);
	else if(e->key()==Qt::Key_Z){
		if( sphere->isWireFrame() ) sphere->setWireFrame(false);
		else sphere->setWireFrame(true);
	}
	else if(e->key()==Qt::Key_Space){
		if( !m_spaceLock ){
			m_spaceLock = true;
			rotateMode = !rotateMode;
		}
	}
	else if(e->key()==Qt::Key_T){
		for( int j = 0; j < shaders.size(); j++ ){
			for( int i = 0; i < lights.size(); i++ ){
				if(lights[i]->type==Light::Dir){
					lights[i]->enable(shaders[j], !lights[i]->isEnabled());
				}
			}
		}
		sphere->draw(shaders[0]);
		update();
	}
	else if(e->key()==Qt::Key_Y){
		for( int j = 0; j < shaders.size(); j++ ){
			for( int i = 0; i < lights.size(); i++ ){
				if(lights[i]->type==Light::Point){
					lights[i]->enable(shaders[j], !lights[i]->isEnabled());
				}
			}
		}
		sphere->draw(shaders[0]);
		update();
	}
	else if(e->key()==Qt::Key_U){
		for( int j = 0; j < shaders.size(); j++ ){
			for( int i = 0; i < lights.size(); i++ ){
				if(lights[i]->type==Light::Spot){
					lights[i]->enable(shaders[j], !lights[i]->isEnabled());
				}
			}
		}
		sphere->draw(shaders[0]);
		update();
	}
}

void WorldWidget::keyReleaseEvent( QKeyEvent *event ){
	if(event->key()==Qt::Key_Space)
		if( m_spaceLock ) m_spaceLock = false;
}
void WorldWidget::mousePressEvent(QMouseEvent *e){
	mousePressPosition = QVector2D(e->position());
	if( e->button() == Qt::LeftButton ){
                m_drag = true;
        }
}

void WorldWidget::wheelEvent(QWheelEvent *e){
	camera.m_zoom -= e->pixelDelta().y() / 100.0f;
	update();
}

void WorldWidget::mouseReleaseEvent(QMouseEvent *e){
	if( e->button() == Qt::LeftButton ){
                m_drag = false;
                m_firstMouse = true;
        }
}
void WorldWidget::mouseMoveEvent(QMouseEvent *event){
	if( m_drag ){
		int xpos = event->pos().x();
		int ypos = event->pos().y();
		m_drag = true; 
		if( m_firstMouse ){
			lastX = xpos;
			lastY = ypos;
			m_firstMouse = false;
		}
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;
		camera.processMouse(
			xoffset, 
			yoffset);
	}
}

void WorldWidget::timerEvent(QTimerEvent *){
	if( rotateMode ) alpha += 1.0;
	update();
}

void WorldWidget::initShaders(){
	shaders.push_back( new QOpenGLShaderProgram );
	if (!shaders.last()->addShaderFromSourceFile(QOpenGLShader::Vertex, "/home/humes/src/qtWorldView/demo/vshader.glsl")) close();
	if (!shaders.last()->addShaderFromSourceFile(QOpenGLShader::Fragment, "/home/humes/src/qtWorldView/demo/fshader.glsl")) close();
	if (!shaders.last()->link()) close();
	if (!shaders.last()->bind()) close();

}
void WorldWidget::initializeGL(){
	lastX = m_width / 2.0f;
	lastY = m_height / 2.0f;
	m_firstMouse = true;

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
//	sphere->setWireFrame();

	addLight(
		new DirLight(
			QVector3D( 10.0, 0.0, 0.0 ),
			QVector3D(  0.2, 0.2, 0.2 ),
			QVector3D(  0.9, 0.9, 0.9 ),
			QVector3D(  1.0, 1.0, 1.0 )
		)
	);

#if 1
	addLight(
		new PointLight(
			QVector3D(  2.0, 0.0,-2.0 ),
			QVector3D(  0.2, 0.2, 0.2 ),
			QVector3D(  0.9, 0.9, 0.9 ),
			QVector3D(  1.0, 1.0, 1.0 ),
			1.0, 0.0014, 0.000007
		)
	);

	addLight(
		new SpotLight(
			QVector3D( 0.0, 3.0, 0.0 ),
			QVector3D( 0.0, 1.0, 0.0 ),
			QVector3D( 0.2, 0.2, 0.2 ),
			QVector3D( 0.9, 0.9, 0.9 ),
			QVector3D( 1.0, 1.0, 1.0 ),
			1.0, 0.0014, 0.000007,
			0.82, 35.0
			
		)
	);
#endif
	
	shaders[0]->setUniformValue("material.shininess", 32.0f);

	m_timer.start(12, this);
	m_elapsed.start();
}
void WorldWidget::resizeGL(int w, int h){
	qreal aspect = qreal(w) / qreal(h ? h : 1);
	const qreal zNear = 0.1, zFar = 7.0;
	projMat.setToIdentity();
	projMat.perspective(camera.m_zoom, aspect, zNear, zFar);
	m_width = w;
	m_height = h;
}
void WorldWidget::paintGL(){

	dt = m_elapsed.elapsed() / 1000.0;
	//fprintf(stdout, "Elapsed: %f\n", dt);
	m_elapsed.start();
	
	//fprintf(stdout, "painting\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	texture->bind();

	QMatrix4x4 modelMat;
	modelMat.translate(0.0, 0.0, -5.0);
	modelMat.rotate(alpha / 2.0, QVector3D( 0.0, 1.0, 0.0) );
	

	qreal aspect = qreal(m_width) / qreal(m_height ? m_height : 1);
	const qreal zNear = 1.0, zFar = 100.0;
	projMat.setToIdentity();
	projMat.perspective(camera.m_zoom, aspect, zNear, zFar);

/*
	QMatrix4x4 rot;
	pLights[0].position = QVector3D(0.0, 0.0, -5.0);
	rot.rotate(alpha/10.0, QVector3D(0.0, 1.0, 0.0) );
	rot.translate(QVector3D(2.0, 0.0, 0.0));
	pLights[0].position = rot * pLights[0].position;
	for( unsigned int i = 0; i < pLights.size(); i++ ){
                pLights[i].setProperties(&m_shader[0],i);
	}
*/

	if (!shaders[0]->bind()) close();
	shaders[0]->setUniformValue("viewPos", camera.position());
	shaders[0]->setUniformValue("model", modelMat);
	shaders[0]->setUniformValue("view", camera.getViewMat());
	shaders[0]->setUniformValue("projection", projMat);
	shaders[0]->setUniformValue("texture", 0);
	sphere->draw(shaders[0]);

	//QMatrix4x4 lightMat;
	//if (!shaders[1].bind()) close();
	//lightMat.translate(pLights[0].position);
	//lightMat.rotate(alpha, QVector3D(0.0, 1.0, 0.0));
	//lightMat.translate(2.0, 0.0, 0.0);
	//m_shader[1].setUniformValue("model", lightMat);
	//m_shader[1].setUniformValue("view", camera.getViewMat());
	//m_shader[1].setUniformValue("projection", projMat);
	//light->draw(&m_shader[1]);
}

void WorldWidget::initTextures()
{
	texture = new QOpenGLTexture(QImage("/home/humes/src/qtWorldView/demo/earth.jpg"));
	texture->setMinificationFilter(QOpenGLTexture::Nearest);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
	texture->setWrapMode(QOpenGLTexture::Repeat);
}

int WorldWidget::addLight(Light *light){
	lights.push_back(light);
	int index = lights.size() - 1;
	int dc = 0, pc = 0, sc = 0;

	/* Move this to shader code with a boolean flag */
	for( int i = 0; i < lights.size(); i++ ){
		if( lights[i]->type == Light::Point ){
			lights[i]->index = pc++;
		}
		if( lights[i]->type == Light::Dir   ){
			lights[i]->index = dc++;
		}
		if( lights[i]->type == Light::Spot  ){
			lights[i]->index = sc++;
		}
	}
	for( int i = 0; i < shaders.size(); i++ ){
                light->setProperties(shaders[i]);
		if (!shaders[i]->bind()) close();
		shaders[i]->setUniformValue("pointLightCount",pc);
		shaders[i]->setUniformValue("dirLightCount",  dc);
		shaders[i]->setUniformValue("spotLightCount", sc);
	}
	return index;
}
