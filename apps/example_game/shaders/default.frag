#version 330 core
struct Lighting {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
    Lighting lighting;
};

struct Material {
    sampler2D diffuseTexture0;
    sampler2D specularTexture0;
    float specularExponent;
};

out vec4 fragColor;

in VS_OUT {
    vec3 fragPosition;
    vec3 fragNormal;
    vec2 fragTextureCoordinates;
} fs_in;

uniform vec3 viewPosition;
uniform Material material;

uniform DirectionalLight directionalLight;

Lighting calculateBaseLight(vec3 lightDirection, Lighting lighting);
vec3 calculateDirectionalLight();

void main(void) {
    vec3 color = calculateDirectionalLight();

    fragColor = vec4(color, 1.0);
}

Lighting calculateBaseLight(vec3 lightDirection, Lighting lighting) {
    // Calculates Blinn-Phong lighting
    Lighting result;

    // Sets ambient color the same as the diffuse color
    vec3 materialDiffuse = texture2D(material.diffuseTexture0, fs_in.fragTextureCoordinates).rgb;
    result.ambient = lighting.ambient * materialDiffuse;

    // Fragment is brighter the closer it is aligned to the light ray direction
    float lightAngle = max(dot(fs_in.fragNormal, -lightDirection),
                           0.0);
    result.diffuse = lighting.diffuse * lightAngle * materialDiffuse;

    // Specular light is brighter the closer the angle btwn the reflected
    // light ray and the viewing vector.
    vec3 viewDirection = normalize(viewPosition - fs_in.fragPosition);
    vec3 halfwayDirection = normalize(-lightDirection + viewDirection);
    float specularAngle = dot(halfwayDirection, fs_in.fragNormal);

    result.specular = lighting.specular *
            pow(max(specularAngle, 0.0), material.specularExponent) *
            texture2D(material.specularTexture0, fs_in.fragTextureCoordinates).rgb;

    return result;
}

vec3 calculateDirectionalLight() {
    vec3 lightDirection = normalize(directionalLight.direction);
    Lighting result = calculateBaseLight(lightDirection,
                                         directionalLight.lighting);
    return result.ambient + result.diffuse + result.specular;
}
