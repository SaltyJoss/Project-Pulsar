#version 410 core

in vec3 WorldPos;

layout(location = 0) out vec4 FragColour;

uniform float gGridMinPixelsBetweenCells = 2.0;
uniform float gGridCellSize = 0.25;
uniform float gGridSize = 1000.0;

uniform vec3 gCameraWorldPos;
uniform vec4 gGridColourThin = vec4(0.5, 0.5, 0.5, 1.0);
uniform vec4 gGridColourThick = vec4(0.0, 0.0, 0.0, 1.0);


void main() {
    vec2 dvx = vec2(dFdx(WorldPos.x), dFdy(WorldPos.x));
    vec2 dvy = vec2(dFdx(WorldPos.z), dFdy(WorldPos.z));

    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx, ly);
    dudv = max(dudv, vec2(1e-6));

    float l = length(dudv);
    float LOD = max(0.0, (log(l * gGridMinPixelsBetweenCells / gGridCellSize) / log(10.0)) + 1.0);

    float GridCellSizeLOD0 = gGridCellSize * pow(10.0, floor(LOD));
    float GridCellSizeLOD1 = GridCellSizeLOD0 * 10.0;
    float GridCellSizeLOD2 = GridCellSizeLOD1 * 10.0;

    dudv *= 4.0;

    vec2 cell = vec2(1.0) - abs(clamp(mod(WorldPos.xz, GridCellSizeLOD0) / dudv, 0.0, 1.0) * 2.0 - vec2(1.0));
    float LOD_0a = max(cell.x, cell.y);

    cell = vec2(1.0) - abs(clamp(mod(WorldPos.xz, GridCellSizeLOD1) / dudv, 0.0, 1.0) * 2.0 - vec2(1.0));
    float LOD_1a = max(cell.x, cell.y);

    cell = vec2(1.0) - abs(clamp(mod(WorldPos.xz, GridCellSizeLOD2) / dudv, 0.0, 1.0) * 2.0 - vec2(1.0));
    float LOD_2a = max(cell.x, cell.y);

    float LOD_fade = fract(LOD);

    vec4 Colour;

    if (LOD_2a > 0.0){
        Colour = gGridColourThick;
        Colour.a *= LOD_2a;
    }
    else {
        if (LOD_1a > 0.0) {
            Colour = mix(gGridColourThick, gGridColourThin, LOD_fade);
            Colour.a *= LOD_1a;
        }
        else {
            Colour = gGridColourThin;
            Colour.a *= (LOD_0a * (1.0 - smoothstep(0.0, 1.0, LOD_fade)));
        }
    }

    float OpacityFalloff = 1.0 - clamp((length(WorldPos.xz - gCameraWorldPos.xz) / gGridSize), 0.0, 1.0);
    Colour.a *= OpacityFalloff;

    FragColour = Colour;
}