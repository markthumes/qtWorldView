#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

attribute vec4 a_position;
attribute vec3 a_normal;
attribute vec3 a_color;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;
varying vec3 v_color;
varying vec3 v_fragPos;
varying vec3 v_normal;

mat4 transpose(mat4 m){
	return mat4(
		vec4(m[0].x,m[1].x,m[2].x,m[3].x),
		vec4(m[0].y,m[1].y,m[2].y,m[3].y),
		vec4(m[0].z,m[1].z,m[2].z,m[3].z),
		vec4(m[0].w,m[1].w,m[2].w,m[3].w)
	);
}

mat3 toMat3(mat4 m){
	return mat3(
		vec3(m[0].x,m[1].x,m[2].x),
		vec3(m[0].y,m[1].y,m[2].y),
		vec3(m[0].z,m[1].z,m[2].z) 
	);
}

void main(){
	gl_Position = projection * view * model * a_position;
	v_texcoord = a_texcoord;
	v_color    = a_color;
	v_normal   = toMat3(transpose((model))) * a_normal;
	v_fragPos  = vec3( model * a_position );
}
