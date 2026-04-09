#version 460

layout(push_constant) uniform uPushConstant {
	vec2	gridPos;
	vec2	gridSize;
	vec4	color;
	float	ratio;
} pc;

layout(location = 0) out vec4 color;

vec2 pos[6] = vec2[](
	vec2(0.0, 0.0),
	vec2(0.0, 1.0),
	vec2(1.0, 0.0),
	vec2(0.0, 1.0),
	vec2(1.0, 0.0),
	vec2(1.0, 1.0)
);

void main()
{
	float	cellWidth  = 2.0 / pc.gridSize.x;
	float	cellHeight = 2.0 / pc.gridSize.y;
	float	gridRatio = pc.gridSize.x / pc.gridSize.y;

	if (gridRatio <= pc.ratio)
		cellWidth = cellHeight / pc.ratio;
	else
		cellHeight = cellWidth / pc.ratio;

	float	x = -1.0 + (pc.gridPos.x + pos[gl_VertexIndex].x) * cellWidth;
	float	y = -1.0 + (pc.gridPos.y + pos[gl_VertexIndex].y) * cellHeight;

	gl_Position = vec4(x, y, 0.0, 1.0);
	color = pc.color;
}
