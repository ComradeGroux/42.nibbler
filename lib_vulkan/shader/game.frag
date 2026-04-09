#version 460

layout(push_constant) uniform uPushConstantFrag {
	layout(offset = 32) vec4	color;
} pc;

layout(location = 0) out vec4 fragColor;

void main()
{
	fragColor = pc.color;
}
