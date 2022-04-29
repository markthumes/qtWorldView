#include "mesh.h"

Mesh::Mesh():indexBuf(QOpenGLBuffer::IndexBuffer){
	initializeOpenGLFunctions();
	arrayBuf.create();
	indexBuf.create();
	m_wireFrame = false;
}

Mesh::~Mesh(){
	arrayBuf.destroy();
	indexBuf.destroy();
}

void Mesh::init(){
	arrayBuf.bind();
	arrayBuf.allocate(&vertices[0],vertices.size() * sizeof(Vertex));
	indexBuf.bind();
	indexBuf.allocate(&indices[0], indices.size()  * sizeof(GLushort));
}

void Mesh::draw(QOpenGLShaderProgram *program)
{
	arrayBuf.bind();
	indexBuf.bind();

	int ofst = 0;
	int loc  = 0;

	len = program->attributeLocation("a_position");
	program->enableAttributeArray(loc);
	program->setAttributeBuffer(loc, GL_FLOAT, ofst, 3, sizeof(Vertex));

	ofst += sizeof(QVector3D);
	loc = program->attributeLocation("a_normal");
	program->enableAttributeArray(loc);
	program->setAttributeBuffer(loc, GL_FLOAT, ofst, 3, sizeof(Vertex));

	ofst += sizeof(QVector3D);
	loc = program->attributeLocation("a_texcoord");
	program->enableAttributeArray(loc);
	program->setAttributeBuffer(loc, GL_FLOAT, ofst, 2, sizeof(Vertex));

	ofst += sizeof(QVector2D);
	loc = program->attributeLocation("a_color");
	program->enableAttributeArray(loc);
	program->setAttributeBuffer(loc, GL_FLOAT, ofst, 3, sizeof(Vertex));

	glPolygonMode( GL_FRONT_AND_BACK, m_wireFrame ? GL_LINE : GL_FILL );
	glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,0);
}
