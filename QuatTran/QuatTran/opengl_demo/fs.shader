#version 460
//in vec4 fragment_color;

out vec4 out_Color;
uniform vec3 objectColor;
void main(void)
{
	out_Color = vec4 (objectColor, 1.0f);
}
