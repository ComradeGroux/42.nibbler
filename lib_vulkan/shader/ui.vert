#version 460

layout(push_constant) uniform uPushConstantVert {
	vec4	color;
	float	height;
	float	closeButtonWidth;
	bool	isButton;
} pc;

vec2 pos[6] = vec2[](
	vec2(0.0, 0.0),
	vec2(0.0, pc.height),
	vec2(2.0, 0.0),
	vec2(0.0, pc.height),
	vec2(2.0, 0.0),
	vec2(2.0, pc.height)
);

layout(location = 0) out vec4 oColor;

void main()
{
	float	x;
	float	y = -1.0 + pos[gl_VertexIndex].y;

	if (!pc.isButton)
		x = -1.0 + pos[gl_VertexIndex].x;
	else
		x = 1.0 - pc.closeButtonWidth + pos[gl_VertexIndex].x;

	oColor = pc.color;

	gl_Position = vec4(x, y, 0.0, 1.0);
}
