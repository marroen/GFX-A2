#include <metal_stdlib>
using namespace metal;

struct VertexOut {
    float4 position [[position]];
    float4 color;
};

fragment float4 fragment_main(VertexOut in [[stage_in]]) : color {
    return in.color;
}
