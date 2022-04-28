#ifndef __texture_h__
#define __texture_h__

#include <GL/glew.h> //must be before gl.h
#include <GL/gl.h>

typedef struct t_tex{
	unsigned int id;
	const char* type;
	const char* path;
	t_tex( ){
	}
	t_tex( unsigned int _id, const char* _type ){
		id = _id;
		type = _type;
	}
}Texture;

unsigned int loadTexture( const char* path );

#endif
