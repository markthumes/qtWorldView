#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

#define MAX_LIGHTS 100

struct Material{
        float shininess;
};

struct DirLight{
        vec3 direction;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
};
struct PointLight{
        vec3 position;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        float constant;
        float linear;
        float quadratic;
};

bool colorMode;

uniform int        dirLightCount;
uniform int        pointLightCount;
uniform DirLight   dirlight[MAX_LIGHTS];
uniform PointLight pointlight[MAX_LIGHTS];

uniform vec3 viewPos;

vec3 calcDLight(DirLight   light, vec3 normal, vec3 viewDir );
vec3 calcPLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

uniform sampler2D texture;
uniform Material material;

varying vec2 v_texcoord;
varying vec3 v_color;
varying vec3 v_fragPos;
varying vec3 v_normal;

void main(){
	vec3 norm    = normalize( v_normal );
	vec3 viewDir = normalize( viewPos - v_fragPos);
	vec3 result  = vec3(0.0);
	for( int i = 0; i < pointLightCount; i++ ){
                result += calcPLight(pointlight[i],norm,viewDir,v_fragPos);
        }
	for( int i = 0; i < dirLightCount; i++ ){
		result += calcDLight( dirlight[i], norm, viewDir);
	}
	//gl_FragColor = vec4(result + v_color, 1.0);
	gl_FragColor = vec4(result, 1.0) * texture2D(texture, v_texcoord);
}

vec3 calcDLight(DirLight   light, vec3 normal, vec3 viewDir ){
        vec3 lightDir   = normalize(-light.direction);
        float diff      = max(dot(normal, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec      = pow(max(dot(viewDir, reflectDir), 0.0),
                        material.shininess);

        vec3 ambient, diffuse, specular;
        ambient    = light.ambient;
        diffuse    = light.diffuse * diff;
        specular   = light.specular * spec;
        return (ambient + diffuse + specular);
}

vec3 calcPLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos){
        vec3 lightDir     = normalize(light.position - fragPos);
        float diff        = max(dot(normal, lightDir), 0.0);
        vec3 reflectDir   = reflect(-lightDir, normal);
        float spec        = pow(max(dot(viewDir, reflectDir), 0.0),
                                material.shininess);

        float distance    = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance
                        + light.quadratic * (distance * distance));

        vec3 ambient, diffuse, specular;
        ambient      = light.ambient * v_color;
        diffuse      = light.diffuse * diff * v_color;
        specular     = light.specular * spec * v_color;

        ambient  *= attenuation;
        diffuse  *= attenuation;
	specular *= attenuation;
        return (ambient + diffuse + specular);
}
