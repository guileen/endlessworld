#version 330 core
struct Material {
    vec3 ambient;
    // vec3 diffuse;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float emissionStrength;
    float shininess;
};

struct Light {
    // 点光源
    vec3 position;
    // 平行光
    // vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float c1;
    float c2;
    float c3;
};

out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

uniform Light light;
uniform Material material;

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords))
     + vec3(texture(material.emission, TexCoords)) * material.emissionStrength;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    // vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
            
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.c1 + light.c2 * distance + light.c3 * distance * distance);

    vec3 result = (ambient + diffuse + specular) * attenuation;
    FragColor = vec4(result, 1.0);

} 