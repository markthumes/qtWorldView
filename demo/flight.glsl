#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

varying vec2 v_texcoord;
varying vec3 v_color;
varying vec3 v_fragPos;
varying vec3 v_normal;

void main(){
	gl_FragColor = vec4(1.0);
}

