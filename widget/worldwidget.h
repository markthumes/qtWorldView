#ifndef __H_WORLD_H__
#define __H_WORLD_H__

#if defined(__gl_h_) || defined(__GL_H__) || defined(_GL_H) || defined(__X_GL_H)
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include <QWidget>
#include <QColor>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QOpenGLWidget>

class QDESIGNER_WIDGET_EXPORT WorldWidget : public QOpenGLWidget {

    Q_OBJECT

	Q_PROPERTY(QColor background READ background WRITE setBackground )

public:
    WorldWidget(QWidget *parent = 0);
	void paintGL();
	void initializeGL();
	void resizeGL(int w, int h);

	QColor background() const{ return m_background; }
	void setBackground( QColor c ){
		m_background = c;
		glClearColor( c.redF(), c.greenF(), c.blueF(), c.alphaF() );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

signals:

protected:
	QColor m_background;
	
	int m_width;
	int m_height;
};

#endif
