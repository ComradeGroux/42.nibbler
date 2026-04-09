#version 460

layout(push_constant) uniform uPushConstantFrag {
	layout(offset = 16) vec4	barColor;
	vec4						closeButtonColor;
} pc;

layout(location = 0) out vec4 fragColor;

void main()
{
	fragColor = pc.barColor;
}
