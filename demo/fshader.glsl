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
	
	bool enable;
};
struct PointLight{
        vec3 position;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;

        float constant;
        float linear;
        float quadratic;
	bool enable;
};
struct SpotLight{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
	bool enable;
};

bool colorMode;

uniform int        dirLightCount;
uniform int        pointLightCount;
uniform int        spotLightCount;
uniform DirLight   dirLight[MAX_LIGHTS];
uniform PointLight pointLight[MAX_LIGHTS];
uniform SpotLight  spotLight[MAX_LIGHTS];

uniform vec3 viewPos;

vec3 calcDLight(DirLight   light, vec3 normal, vec3 viewDir );
vec3 calcPLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 calcSLight(SpotLight  light, vec3 normal, vec3 viewDir, vec3 fragPos);

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
	for( int i = 0; i < pointLightCount; i++ )
		if( pointLight[i].enable ){
                	result += calcPLight(pointLight[i],norm,viewDir,v_fragPos);
		}
	for( int i = 0; i < dirLightCount; i++ ){
		if( dirLight[i].enable ){
			result += calcDLight(dirLight[i],norm,viewDir);
		}
	}
	for( int i = 0; i < spotLightCount; i++ ){
		if( spotLight[i].enable ){
			result += calcSLight(spotLight[i],norm,viewDir,v_fragPos);
		}
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
        ambient      = light.ambient;
        diffuse      = light.diffuse * diff;
        specular     = light.specular * spec;

        ambient  *= attenuation;
        diffuse  *= attenuation;
	specular *= attenuation;
        return (ambient + diffuse + specular);
}
vec3 calcSLight(SpotLight  light, vec3 normal, vec3 viewDir, vec3 fragPos){
	vec3 lightDir     = normalize(light.position - fragPos);
	float diff        = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir   = reflect(-lightDir, normal);
	float spec        = pow(max(dot(viewDir, reflectDir), 0.0), 
			material.shininess);
	float distance    = length(light.position - fragPos);
	float attenuation =1.0 / (light.constant + light.linear * distance +
			light.quadratic * (distance * distance));    
	float theta       = dot(lightDir, normalize(-light.direction)); 
	float epsilon     = light.cutOff - light.outerCutOff;
	float intensity   = clamp((theta - light.outerCutOff) / epsilon, 
			0.0, 1.0);
	vec3 ambient      = light.ambient;
	vec3 diffuse      = light.diffuse * diff;
	vec3 specular     = light.specular * spec;

	ambient  *= attenuation * intensity;
	diffuse  *= attenuation * intensity;
	specular *= attenuation * intensity;
	return (ambient + diffuse + specular);
}
