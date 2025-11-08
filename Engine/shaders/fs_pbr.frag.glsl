#version 410 core

out vec4 FragColour;
in vec3 WorldPos;
in vec3 Normal;

// material parameters
uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

// CheckerBoard Plane parameters
uniform float checkSize;
uniform vec3 colour1;
uniform vec3 colour2;
uniform bool isFloor; // true for the checker floor, false for objects

// lights
uniform vec3 lightPosition;
uniform vec3 lightColour;
uniform float lightSize;
uniform vec3 lightDirection;

uniform sampler2D shadowMap;
uniform mat4 lightSpaceMatrix;

uniform vec3 camPos;

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
  float a = roughness * roughness;
  float a2 = a * a;
  float NdotH = max(dot(N, H), 0.0);
  float NdotH2 = NdotH * NdotH;

  float nom = a2;
  float denom = (NdotH2 * (a2 - 1.0) + 1.0);
  denom = PI * denom * denom;

  return nom / max(denom, 0.0000001); // prevent divide by zero for roughness=0.0 and NdotH=1.0
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
  float r = (roughness + 1.0);
  float k = (r * r) / 8.0;

  float nom = NdotV;
  float denom = NdotV * (1.0 - k) + k;

  return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
  float NdotV = max(dot(N, V), 0.0);
  float NdotL = max(dot(N, L), 0.0);
  float ggx2 = GeometrySchlickGGX(NdotV, roughness);
  float ggx1 = GeometrySchlickGGX(NdotL, roughness);

  return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
  return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

float computeShadowPCF(vec3 N, vec3 L, vec4 lightSpacePos)
{
    vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;

    if (projCoords.z > 1.0) return 0.0;
    if (projCoords.x < 0.0 || projCoords.x > 1.0 ||
        projCoords.y < 0.0 || projCoords.y > 1.0) return 0.0;

    float bias = max(0.002 * (1.0 - dot(N, L)), 0.0007);

    vec2 texel = 1.0 / vec2(textureSize(shadowMap, 0));
    float shadow = 0.0;

    for (int x = -1; x <= 1; ++x)
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texel).r;
            shadow += (projCoords.z - bias > pcfDepth) ? 1.0 : 0.0;
        }
    return shadow / 9.0;
}

void main()
{
    vec3 N = normalize(Normal);
    vec3 V = normalize(camPos - WorldPos);

    vec3 finalAlbedo = albedo;
    if (isFloor)
    {
        float pattern = mod(floor(WorldPos.x * checkSize) + floor(WorldPos.z * checkSize), 2.0);
        finalAlbedo = mix(colour1, colour2, pattern);
    }

    // Cook-Torrance PBR
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, finalAlbedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);

    // calculate per-light radiance
    vec3 L = normalize(-lightDirection);
    vec3 H = normalize(V + L);

    vec3 radiance = lightColour;

    // lightSpaceMatrix
    vec4 lightSpacePos = lightSpaceMatrix * vec4(WorldPos, 1.0);
    float shadow = computeShadowPCF(N, L, lightSpacePos);

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness * lightSize);
    float G = GeometrySmith(N, V, L, roughness);
    vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

    vec3 nominator = NDF * G * F;
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
    vec3 specular = nominator / max(denominator, 0.001); // prevent divide by zero for NdotV=0.0 or NdotL=0.0

    // kS is equal to Fresnel
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;
     
    // scale light by NdotL
    float NdotL = max(dot(N, L), 0.0);

    Lo += (kD * finalAlbedo / PI + specular) * radiance * NdotL;

    vec3 ambient = vec3(0.03) * finalAlbedo * ao;

    vec3 colour = ambient + (1.0 - shadow) * Lo;

    // HDR tonemapping
    colour = colour / (colour + vec3(1.0));

    // gamma correct
    colour = pow(colour, vec3(1.0 / 2.2));

    FragColour = vec4(colour, 1.0);
}
