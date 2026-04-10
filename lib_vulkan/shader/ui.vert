#version 460

layout(push_constant) uniform uPushConstantVert {
	vec4	color;
	float	height;
	float	ratio;
	bool	isButton;
} pc;

const float	margin = 0.2;
float		btnHeight = pc.height * (1.0 - margin);
float		btnWidth = btnHeight / pc.ratio;

vec2	btnCorners[6] = vec2[](
	vec2(0.0,		0.0),
	vec2(0.0,		pc.height),
	vec2(btnWidth,	0.0),
	vec2(0.0,		pc.height),
	vec2(btnWidth,	0.0),
	vec2(btnWidth,	pc.height)
);

vec2	pos[6] = vec2[](
	vec2(0.0, 0.0),
	vec2(0.0, pc.height),
	vec2(2.0, 0.0),
	vec2(0.0, pc.height),
	vec2(2.0, 0.0),
	vec2(2.0, pc.height)
);

layout(location = 0) out vec4 oColor;
layout(location = 1) out vec2 oUV;
layout(location = 2) out float oIsButton;

void main()
{
	float	x;
	float	y;

	if (pc.isButton)
	{
		x = 1.0 - btnWidth - (btnWidth * margin / 2.0) + btnCorners[gl_VertexIndex].x;
		y = -1.0 + (pc.height * margin / 2.0) + btnCorners[gl_VertexIndex].y;

		oIsButton = 1.0;
		oUV = vec2(
			btnCorners[gl_VertexIndex].x / btnWidth * 2.0 - 1.0,
			btnCorners[gl_VertexIndex].y / btnHeight * 2.0 - 1.0
		);
	}
	else
	{
		x = -1.0 + pos[gl_VertexIndex].x;
		y = -1.0 + pos[gl_VertexIndex].y;

		oIsButton = 0.0;
		oUV = vec2( 0.0, 0.0 );
	}

	oColor = pc.color;

	gl_Position = vec4(x, y, 0.0, 1.0);
}
