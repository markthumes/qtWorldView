#include <QMouseEvent>
#include <QPainter>

#include "worldwidget.h"

WorldWidget::WorldWidget(QWidget *parent){
	setParent(parent);
    setWindowTitle(tr("World Widget"));
    resize(200, 200);
}

void WorldWidget::initializeGL(){
	/* MUST BE FIRST */
	glewInit();
	/* MUST BE FIRST */
	glClearColor( 	m_background.redF(),
			m_background.greenF(),
			m_background.blueF(),
			m_background.alphaF()
	);

}
void WorldWidget::resizeGL(int w, int h){
	m_width = w;
	m_height = h;
	glViewport(0,0,w,h);
}
void WorldWidget::paintGL(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
