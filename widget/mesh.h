#ifndef __MESH_H__
#define __MESH_H__

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>

typedef struct{
	QVector3D position;
	QVector3D normal;
	QVector2D texCoord;
	QVector3D color;
}Vertex;

class Mesh : protected QOpenGLFunctions
{
public:
	Mesh();
	Mesh( const Mesh& m );
	virtual ~Mesh();

	void generate();

	void draw(QOpenGLShaderProgram *program);
	void init();

	void setWireFrame(bool state = true ){m_wireFrame = state;}
	bool isWireFrame(){ return m_wireFrame; }

protected:
	QVector<Vertex> vertices;
	QVector<GLushort> indices;

private:
	bool m_wireFrame;
	void initCubeGeometry();

	QOpenGLBuffer arrayBuf;
	QOpenGLBuffer indexBuf;
};

#endif // __MESH_H__
