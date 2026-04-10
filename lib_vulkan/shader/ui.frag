#version 460

layout(location = 0) in vec4 iColor;
layout(location = 1) in vec2 iUV;
layout(location = 2) in float iIsButton;

layout(location = 0) out vec4 fragColor;

void main()
{
	if (iIsButton == 1.0)
	{
		float dist = length(iUV);
		if (dist > 1.0)
			discard;

		float thickness = 0.1;
		float crossSize = 0.5;

		float d1 = abs(iUV.x - iUV.y) / sqrt(2.0);
		float d2 = abs(iUV.x + iUV.y) / sqrt(2.0);

		bool onCross = (d1 < thickness || d2 < thickness)
					&& length(iUV) < crossSize;

		if (onCross)
			fragColor = vec4(1.0, 1.0, 1.0, 1.0);
		else
			fragColor = iColor;
		return;
	}

	fragColor = iColor;
}
