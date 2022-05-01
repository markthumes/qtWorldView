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

void main(){
    gl_Position = projection * view * model * a_position;
    v_texcoord = a_texcoord;
    v_color = a_color;
}
