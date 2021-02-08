#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;  
in vec3 FragPos;  

uniform sampler2D texture_diffuse1;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float emissionStrength;
    float shininess;
};

// 光照逻辑
uniform vec3 viewPos;

// 平行光
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, Material material, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面反射光
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
}

// 点光源
struct PointLight {
    vec3 position;
    float c1;
    float c2;
    float c3;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcPointLight(PointLight light, vec3 normal, Material material, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色. dot 计算cos* 强度， max把负值最多降到0，表示全黑。
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面反射光, reflect计算反射角度
    vec3 reflectDir = reflect(-lightDir, normal);
    // dot 计算反射光在视角上的cos分量，至少为0。使用pow，模拟镜面光焦点分布集中度，shininess越高要求反射分量越接近于1
    // 反射分量==1 表示必须视角恰巧与反射角完全一致才能看到反射光，也就是绝对镜面。
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减。 length 计算光源到片段的距离。
    float distance = length(light.position - fragPos);
    // 常量衰减，一次衰减表示光线均匀衰减，二次衰减表示光线高速衰减至某一距离几乎不可见，按能量的耗散还应有三次衰减。
    float attenuation = 1.0 / (light.c1 + light.c2 * distance + light.c3 * distance * distance);
    // 合并
    // 环境光 * 材质漫反射表面
    vec3 ambient = light.ambient * material.diffuse;
    // 漫反射 = 散射光 * 漫反射分量 * 漫反射材质
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    // 镜面 = 直射光 * 镜面反射分量 * 镜面材质
    vec3 specular = light.specular * spec * material.specular;
    // 返回 总计*衰减
    return (ambient + diffuse + specular) * attenuation;
}

// 聚光
struct SpotLight {
    // 点光源
    PointLight point;
    vec3 direction;
    // 聚光角
    float cutOff;
    // 虚化角
    float outerCutOff;
};
uniform SpotLight spotLight;

// 计算聚焦光
vec3 CalcSpotLight(SpotLight light, vec3 normal, Material material, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.point.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    // clamp 约束范围，此处可以代替if-else, 负值变成了0.
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // 将点光源约束在一定范围内
    return CalcPointLight(light.point, normal, material, fragPos, viewDir) * intensity;
}

void main()
{    
    // 素材颜色
    Material material;
    material.diffuse = vec3(texture(texture_diffuse1, TexCoords));

    // 法向量归一化, 归一使其长度为1.
    vec3 norm = normalize(Normal);
    // A->B的方向 = B-A
    vec3 viewDir = normalize(viewPos - FragPos);
    // 计算平行光照
    vec3 result  = CalcDirLight(dirLight, norm, material, viewDir);
    for(int i = 0; i<NR_POINT_LIGHTS; i++) {
        // 计算点光源光照
        result += CalcPointLight(pointLights[i], norm, material, FragPos, viewDir);
    }
    // 计算聚焦光
    result +=  CalcSpotLight(spotLight, norm, material, FragPos, viewDir);
    FragColor = vec4(result, 1.0);
}