#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;

in vec2 TexCoord;
 
//////////////////////////////////////

uniform vec3 viewPos; 

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 lookAt;
uniform float spotCutoff;
uniform float ambientIntensity;

uniform sampler2D texture1;
//////////////////////////////////////

void main(){

	//Color del fragmento
	FragColor = texture(texture1, TexCoord);
	FragColor.a = 1.0;

    	//Ambiente
  	float ambientI = ambientIntensity;
    	vec3 ambient = ambientI * ambientColor;
  	
    	vec3 ld = normalize(vec3(lookAt - lightPos));
    	vec3 fd = normalize(vec3((FragPos - lightPos)));

   	if (acos(dot(fd,ld)) < radians(spotCutoff)){

    		//Difusa
		float diffuseStrength = 1.0;
    		vec3 norm = normalize(Normal);
    		vec3 lightDir = normalize(lightPos - FragPos);
    		float diff = max(dot(norm, lightDir), 0.0);
    		vec3 diffuse = diffuseStrength * diff * lightColor;
		

    		//Especular
    		float specularStrength = 1.0;
    		vec3 viewDir = normalize(viewPos - FragPos);
    		vec3 reflectDir = reflect(-lightDir, norm);
    		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    		vec3 specular = specularStrength * spec * lightColor;

            	//Union
    		vec3 result = (ambient + diffuse + specular);
		FragColor = vec4(result, 1.0) * FragColor;

	 }else{

		FragColor = vec4(ambient, 1.0) * FragColor;
	}

} 
