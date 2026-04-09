#version 460

layout(push_constant) uniform uPushConstantVert {
	float	height;
	float	closeButtonWidth;
	float	_pad[2];
} pc;

vec2 pos[6] = vec2[](
	vec2(0.0, 0.0),
	vec2(0.0, pc.height),
	vec2(2.0, 0.0),
	vec2(0.0, pc.height),
	vec2(2.0, 0.0),
	vec2(2.0, pc.height)
);

void main()
{
	float	x = -1.0 + pos[gl_VertexIndex].x;
	float	y = -1.0 + pos[gl_VertexIndex].y;

	gl_Position = vec4(x, y, 0.0, 1.0);
}
